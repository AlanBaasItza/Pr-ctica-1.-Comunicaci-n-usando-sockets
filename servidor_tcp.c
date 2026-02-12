#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PUERTO 5000
#define BUFFER 1024

DWORD WINAPI manejarCliente(LPVOID socket_cliente) {
    SOCKET cliente = (SOCKET)socket_cliente;
    char buffer[BUFFER];
    int bytes;

    FILE *archivo = fopen("archivo_recibido.txt", "ab");
    if (!archivo) {
        printf("Error al crear archivo\n");
        closesocket(cliente);
        return 1;
    }

    while ((bytes = recv(cliente, buffer, BUFFER, 0)) > 0) {
        fwrite(buffer, 1, bytes, archivo);
    }

    printf("Archivo recibido correctamente.\n");

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
        cliente = accept(servidor, (struct sockaddr*)&dirCliente, &tam);
        CreateThread(NULL, 0, manejarCliente, (LPVOID)cliente, 0, NULL);
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}