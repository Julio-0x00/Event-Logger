# File System Monitor en C

Este proyecto es un programa en C que monitoriza en tiempo real los cambios en un directorio usando `inotify` (Linux).

Detecta eventos como:

- Creación de archivos y directorios  
- Eliminación  
- Modificación de archivos  

Todos los eventos se registran en un archivo de log con timestamp.

---

## Características

- Monitorización en tiempo real  
- Registro de eventos con fecha y hora  
- Diferenciación entre archivos y directorios  
- Uso de colores en consola y logs  
- Manejo de señal CTRL+C para cerrar correctamente  

---

## Tecnologías usadas

- Lenguaje: C  
- API del sistema: `inotify` (Linux)  
- Librerías estándar:
  - stdio.h  
  - unistd.h  
  - time.h  
  - signal.h  

---

## Compilación

```bash
gcc event-logger.c -o event-logger.c
```

---

## Uso

```bash
./event-logger
```

El programa te pedirá:

- Directorio a monitorizar  
- Directorio donde guardar el log  

Ejemplo:

```bash
Introduce el directorio que quieras controlar: /home/user/test
Introduce el directorio donde van a ir los logs: /home/user/logs
```

---

## Ejemplo de log

```
[2026-04-14 20:04:47] El programa se ha iniciado
[2026-04-14 20:04:52] Se ha creado un directorio: test
[2026-04-14 20:04:58] Se ha creado un archivo: test.txt
[2026-04-14 20:05:07] Se ha eliminado el directorio: test
[2026-04-14 20:05:18] Se ha modificado el archivo: test.txt
[2026-04-14 20:05:18] Se ha modificado el archivo: test.txt
[2026-04-14 20:05:25] Se ha eliminado el archivo: test.txt
```

---

## ⚠️ Requisitos

- Sistema operativo Linux (necesario para `inotify`)  
- Permisos de lectura sobre el directorio monitorizado  
