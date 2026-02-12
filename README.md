# Guía de Compilación y Uso

**Comunicación de Procesos Distribuidos con Sockets (TCP / UDP)**  
**Sistema Operativo:** Windows 10

---

## 1. Compilación de los Programas

### 1.1. Abrir la consola
1. Presiona **Win + R**  
2. Escribe **cmd** y presiona **Enter**  
3. Navega hasta la carpeta donde se encuentran los archivos `.c`

**Ejemplo:**
```
cd C:\Sockets\Proyecto
```

### 1.2. Compilar los programas TCP
Ejecuta los siguientes comandos:

```
gcc servidor_tcp.c -o servidor_tcp -lws2_32
gcc cliente_tcp.c -o cliente_tcp -lws2_32
```

Si no aparecen errores, se generarán:

- `servidor_tcp.exe`
- `cliente_tcp.exe`

### 1.3. Compilar los programas UDP
Ejecuta:

```
gcc servidor_udp.c -o servidor_udp -lws2_32
gcc cliente_udp.c -o cliente_udp -lws2_32
```

Archivos generados:

- `servidor_udp.exe`
- `cliente_udp.exe`

---

## 2. Uso de la Aplicación TCP (Transferencia de Archivo de Texto)

### 2.1. Preparar el servidor TCP
Ejecuta el servidor:

```
servidor_tcp.exe
```

Salida esperada:

```
Servidor TCP esperando conexiones...
```

El servidor:
- Permanece activo  
- Acepta múltiples clientes simultáneamente  
- Atiende cada cliente en un hilo independiente  

### 2.2. Preparar el cliente TCP
Coloca el archivo de texto que deseas enviar en la carpeta del cliente.  
El archivo debe llamarse:

```
archivo.txt
```

Ejecuta el cliente:

```
cliente_tcp.exe
```

El cliente enviará el archivo y mostrará un mensaje de confirmación.  
La ventana esperará que se presione **ENTER** antes de cerrarse.

### 2.3. Resultado en el servidor TCP
Por cada cliente, el servidor:

- Muestra la IP y puerto del cliente  
- Crea un archivo independiente con el formato:

```
texto_<IP>_<PUERTO>.txt
```

**Ejemplo:**

```
texto_127.0.0.1_60142.txt
texto_127.0.0.1_60145.txt
```

Esto evita sobrescritura de datos y permite múltiples clientes concurrentes.

---

## 3. Uso de la Aplicación UDP (Transferencia de Archivo Multimedia)

### 3.1. Preparar el servidor UDP
Ejecuta:

```
servidor_udp.exe
```

Salida esperada:

```
Servidor UDP esperando archivos...
```

El servidor UDP:
- No se cierra después de recibir un archivo  
- Permanece escuchando indefinidamente  
- Identifica a cada cliente por IP y puerto  

### 3.2. Preparar el cliente UDP
Coloca el archivo multimedia en la carpeta del cliente.  
El archivo debe llamarse:

```
imagen.jpg
```

También puede ser audio o video (por ejemplo `.png`, `.mp3`, `.mp4`).

Ejecuta el cliente:

```
cliente_udp.exe
```

El cliente:
- Envía el archivo por bloques  
- Envía un mensaje lógico de fin (**FIN**)  
- Muestra confirmación  
- Espera que se presione **ENTER** antes de cerrarse  

### 3.3. Resultado en el servidor UDP
Por cada cliente, el servidor genera un archivo independiente con el formato:

```
imagen_<IP>_<PUERTO>.jpg
```

**Ejemplo:**

```
imagen_127.0.0.1_60210.jpg
imagen_127.0.0.1_60225.jpg
```

Esto evita mezclar datos binarios y permite múltiples clientes UDP.

---

## 4. Ejecución con Múltiples Clientes

Se pueden ejecutar varios clientes TCP o UDP:

- En la misma máquina  
- En máquinas distintas dentro de la red  

Cada cliente es identificado por:

- **IP + Puerto**

Para cambiar la IP del servidor en el cliente, modificar en el código:

```
servidor.sin_addr.s_addr = inet_addr("192.168.1.100");
```

---

## 5. Puertos Utilizados

| Protocolo | Puerto |
|----------|--------|
| TCP      | 5000   |
| UDP      | 6000   |

---

## 6. Consideraciones Importantes

- TCP es orientado a conexión y garantiza orden y fiabilidad  
- UDP no es orientado a conexión; la aplicación implementa la lógica de control  
- En UDP no se mezclan archivos de distintos clientes  
- El servidor nunca se cierra automáticamente  
- Cada cliente genera un archivo independiente  
- Compatible con Windows 10 y WinSock2  

---

## 7. Conclusión

Este proyecto implementa comunicación de procesos distribuidos usando:

- Modelo cliente/servidor  
- Paso de mensajes mediante sockets  
- TCP para archivos de texto  
- UDP para archivos multimedia  
- Soporte para múltiples productores  
- Identificación explícita de clientes  

Cumple con los conceptos teóricos de **Sistemas Operativos Distribuidos** y con el uso correcto de sockets TCP y UDP en Windows.
