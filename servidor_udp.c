#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PUERTO 6000
#define BUFFER 1024

int main() {
    WSADATA wsa;
    SOCKET servidor;
    struct sockaddr_in dirServidor, cliente;
    int tam = sizeof(cliente);
    char buffer[BUFFER];

    WSAStartup(MAKEWORD(2,2), &wsa);

    servidor = socket(AF_INET, SOCK_DGRAM, 0);

    dirServidor.sin_family = AF_INET;
    dirServidor.sin_addr.s_addr = INADDR_ANY;
    dirServidor.sin_port = htons(PUERTO);

    bind(servidor, (struct sockaddr*)&dirServidor, sizeof(dirServidor));

    FILE *archivo = fopen("imagen_recibida.jpg", "wb");

    printf("Servidor UDP esperando archivo...\n");

    while (1) {
        int bytes = recvfrom(servidor, buffer, BUFFER, 0,
                            (struct sockaddr*)&cliente, &tam);

        if (strncmp(buffer, "FIN", 3) == 0)
            break;

        fwrite(buffer, 1, bytes, archivo);
    }

    printf("Archivo multimedia recibido.\n");

    fclose(archivo);
    closesocket(servidor);
    WSACleanup();
    return 0;
}