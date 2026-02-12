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

    printf("Servidor UDP esperando archivos...\n");

    FILE *archivo = NULL;
    char nombreArchivo[100];

    while (1) {

        int bytes = recvfrom(
            servidor,
            buffer,
            BUFFER,
            0,
            (struct sockaddr*)&cliente,
            &tam
        );

        if (bytes <= 0) continue;

        if (strncmp(buffer, "FIN", 3) == 0) {
            printf("Archivo recibido de %s:%d\n",
                   inet_ntoa(cliente.sin_addr),
                   ntohs(cliente.sin_port));

            if (archivo != NULL) {
                fclose(archivo);
                archivo = NULL;
            }

            continue;
        }

        // Si es primer bloque, crear archivo nuevo
        if (archivo == NULL) {
            sprintf(nombreArchivo, "imagen_%s_%d.jpg",
                    inet_ntoa(cliente.sin_addr),
                    ntohs(cliente.sin_port));

            archivo = fopen(nombreArchivo, "wb");

            if (!archivo) {
                printf("Error al crear archivo\n");
                continue;
            }
        }

        fwrite(buffer, 1, bytes, archivo);
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}
