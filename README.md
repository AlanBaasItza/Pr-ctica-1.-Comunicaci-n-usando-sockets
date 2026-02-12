# Guía de Compilación y Uso

## 1. Compilación de los Programas

### 1.1. Abrir la consola
1. Presiona **Win + R**
2. Escribe `cmd` y presiona **Enter**
3. Navega hasta la carpeta donde se encuentran los archivos `.c`  
   **Ejemplo:**
   ```bash
   cd C:\Sockets\Proyecto
   ```

### 1.2. Compilar los programas TCP
Ejecuta los siguientes comandos:
```bash
gcc servidor_tcp.c -o servidor_tcp -lws2_32
gcc cliente_tcp.c -o cliente_tcp -lws2_32
```

Si no aparecen errores, se generarán los archivos:
- `servidor_tcp.exe`
- `cliente_tcp.exe`

### 1.3. Compilar los programas UDP
Ejecuta:
```bash
gcc servidor_udp.c -o servidor_udp -lws2_32
gcc cliente_udp.c -o cliente_udp -lws2_32
```

Archivos generados:
- `servidor_udp.exe`
- `cliente_udp.exe`

---

## 2. Uso de la Aplicación TCP (Archivo de Texto)

### 2.1. Preparar el servidor TCP
Ejecuta el servidor:
```bash
servidor_tcp.exe
```

El servidor mostrará:
```
Servidor TCP esperando conexiones...
```

El servidor queda en espera de uno o más clientes.

### 2.2. Preparar el cliente TCP
1. Coloca el archivo de texto que deseas enviar en la misma carpeta del cliente.  
2. El archivo debe llamarse: `archivo.txt`

Ejecuta el cliente:
```bash
cliente_tcp.exe
```

El cliente enviará el archivo al servidor.

### 2.3. Resultado
El servidor creará el archivo:
- `archivo_recibido.txt`

Si varios clientes se conectan, el servidor los atiende de forma concurrente.

---

## 3. Uso de la Aplicación UDP (Archivo Multimedia)

### 3.1. Preparar el servidor UDP
Ejecuta:
```bash
servidor_udp.exe
```

El servidor mostrará:
```
Servidor UDP esperando archivo...
```

### 3.2. Preparar el cliente UDP
1. Coloca el archivo multimedia en la carpeta del cliente.  
2. El archivo debe llamarse: `imagen.jpg`  
   *(También puede ser un archivo de audio o video)*

Ejecuta el cliente:
```bash
cliente_udp.exe
```

### 3.3. Resultado
El servidor generará el archivo:
- `imagen_recibida.jpg`

La transmisión se realiza mediante datagramas UDP.

---

## 4. Ejecución con Múltiples Clientes

Se pueden ejecutar varios clientes TCP o UDP al mismo tiempo.

Cada cliente puede ejecutarse en:
- La misma máquina
- Máquinas diferentes (cambiando la IP del servidor)

Ejemplo de IP remota en el cliente:
```c
servidor.sin_addr.s_addr = inet_addr("192.168.1.100");
```

---

## 5. Puertos Utilizados

| Protocolo | Puerto |
|----------|--------|
| TCP      | 5000   |
| UDP      | 6000   |
