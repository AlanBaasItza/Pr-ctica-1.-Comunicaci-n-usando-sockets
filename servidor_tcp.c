#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PUERTO 5000
#define BUFFER 1024

typedef struct {
    SOCKET socket;
    struct sockaddr_in dirCliente;
} ClienteTCP;

DWORD WINAPI manejarCliente(LPVOID param) {

    ClienteTCP *clienteData = (ClienteTCP*)param;
    SOCKET cliente = clienteData->socket;
    struct sockaddr_in dirCliente = clienteData->dirCliente;

    free(clienteData);

    char buffer[BUFFER];
    int bytes;

    char nombreArchivo[150];

    sprintf(nombreArchivo,
            "texto_%s_%d.txt",
            inet_ntoa(dirCliente.sin_addr),
            ntohs(dirCliente.sin_port));

    FILE *archivo = fopen(nombreArchivo, "wb");

    if (!archivo) {
        printf("Error al crear archivo\n");
        closesocket(cliente);
        return 1;
    }

    printf("Recibiendo archivo de %s:%d\n",
           inet_ntoa(dirCliente.sin_addr),
           ntohs(dirCliente.sin_port));

    while ((bytes = recv(cliente, buffer, BUFFER, 0)) > 0) {
        fwrite(buffer, 1, bytes, archivo);
    }

    printf("Archivo recibido correctamente de %s:%d\n",
           inet_ntoa(dirCliente.sin_addr),
           ntohs(dirCliente.sin_port));

    fclose(archivo);
    closesocket(cliente);
    return 0;
}

int main() {

    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in dirServidor, dirCliente;
    int tam = sizeof(dirCliente);

    WSAStartup(MAKEWORD(2,2), &wsa);

    servidor = socket(AF_INET, SOCK_STREAM, 0);

    dirServidor.sin_family = AF_INET;
    dirServidor.sin_addr.s_addr = INADDR_ANY;
    dirServidor.sin_port = htons(PUERTO);

    bind(servidor, (struct sockaddr*)&dirServidor, sizeof(dirServidor));
    listen(servidor, 5);

    printf("Servidor TCP esperando conexiones...\n");

    while (1) {

        cliente = accept(
            servidor,
            (struct sockaddr*)&dirCliente,
            &tam
        );

        printf("Cliente conectado desde %s:%d\n",
               inet_ntoa(dirCliente.sin_addr),
               ntohs(dirCliente.sin_port));

        ClienteTCP *datos = malloc(sizeof(ClienteTCP));
        datos->socket = cliente;
        datos->dirCliente = dirCliente;

        CreateThread(
            NULL,
            0,
            manejarCliente,
            datos,
            0,
            NULL
        );
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}
