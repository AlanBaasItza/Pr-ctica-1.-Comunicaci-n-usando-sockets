#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PUERTO 6000
#define BUFFER 1024

int main() {
    WSADATA wsa;
    SOCKET cliente;
    struct sockaddr_in servidor;
    char buffer[BUFFER];

    WSAStartup(MAKEWORD(2,2), &wsa);

    cliente = socket(AF_INET, SOCK_DGRAM, 0);

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PUERTO);
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");

    FILE *archivo = fopen("imagen.jpg", "rb");

    int bytes;
    while ((bytes = fread(buffer, 1, BUFFER, archivo)) > 0) {
        sendto(
            cliente,
            buffer,
            bytes,
            0,
            (struct sockaddr*)&servidor,
            sizeof(servidor)
        );
    }

    sendto(cliente, "FIN", 3, 0,
           (struct sockaddr*)&servidor,
           sizeof(servidor));

    printf("Archivo enviado correctamente por UDP.\n");
    printf("Presiona ENTER para salir...\n");
    getchar();

    fclose(archivo);
    closesocket(cliente);
    WSACleanup();
    return 0;
}
