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
gcc monitor.c -o monitor
```

---

## Uso

```bash
./monitor
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
[2026-04-14 12:00:00] El programa se ha iniciado
[2026-04-14 12:01:10] Se ha creado un archivo: ejemplo.txt
[2026-04-14 12:02:05] Se ha modificado el archivo: ejemplo.txt
[2026-04-14 12:03:00] Se ha eliminado el archivo: ejemplo.txt
```

---

## ⚠️ Requisitos

- Sistema operativo Linux (necesario para `inotify`)  
- Permisos de lectura sobre el directorio monitorizado  
