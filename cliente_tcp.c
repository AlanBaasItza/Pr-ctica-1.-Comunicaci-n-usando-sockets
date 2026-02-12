#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PUERTO 5000
#define BUFFER 1024

int main() {
    WSADATA wsa;
    SOCKET cliente;
    struct sockaddr_in servidor;
    char buffer[BUFFER];
    int bytes;

    WSAStartup(MAKEWORD(2,2), &wsa);

    cliente = socket(AF_INET, SOCK_STREAM, 0);

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PUERTO);
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(cliente, (struct sockaddr*)&servidor, sizeof(servidor));

    FILE *archivo = fopen("archivo.txt", "rb");
    if (!archivo) {
        printf("No se encontró archivo\n");
        return 1;
    }

    while ((bytes = fread(buffer, 1, BUFFER, archivo)) > 0) {
        send(cliente, buffer, bytes, 0);
    }

    printf("Archivo enviado correctamente\n");

    fclose(archivo);
    closesocket(cliente);
    WSACleanup();
    return 0;
}