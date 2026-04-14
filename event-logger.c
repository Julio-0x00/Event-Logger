#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_WHITE     "\033[37m"
#define COLOR_RESET     "\033[0m"

FILE *log_events;

char* get_timestamp() {

  static char buffer[20];
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", t);
  return buffer;
}

void CTRL_C(int sig) {
  printf("\033[2J\033[H" COLOR_RED "Saliendo..." COLOR_RESET "\n");
  fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_RED "El programa se ha detenido" COLOR_RESET "\n", get_timestamp());
  fflush(log_events);
  fclose(log_events);
  exit(0);
}

int main (void) {

  int file_descriptor, watch_descriptor;
  char buffer[4096];
  char listen_directory[512];
  char log_directory[512];
  char log_events_name[] = "/events.txt";
  char path_file_events[512];

  printf("Introduce el directorio que quieras controlar: ");
  if (fgets(listen_directory, sizeof(listen_directory), stdin) == NULL) {
	printf(COLOR_RED"Violación de segmentación en la variable: " COLOR_RESET COLOR_BLUE "listen_directory" COLOR_RESET "\n");
	return 1;
  }

  printf("Introduce el directorio donde van a ir los logs: ");
  if (fgets(log_directory, sizeof(log_directory), stdin) == NULL) {
	printf(COLOR_RED "Violación de segmentación en la variable: " COLOR_RESET COLOR_BLUE "log_directory" COLOR_RESET "\n");
	return 1;
  }

  listen_directory[strcspn(listen_directory, "\n")] = '\0';
  log_directory[strcspn(log_directory, "\n")] = '\0';

  snprintf(path_file_events, sizeof(path_file_events), "%s%s", log_directory, log_events_name);

  log_events = fopen(path_file_events, "a");

  if (log_events == NULL) {
    perror("Error abriendo el log: ");
    exit(1);
  }

  signal(SIGINT, CTRL_C);

  fseek(log_events, 0, SEEK_END);
  long size = ftell(log_events);

  if (size == 0) {
      fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_BLUE "El programa se ha iniciado" COLOR_RESET "\n", get_timestamp());

  } else {
      fprintf(log_events, "\n" COLOR_GREEN "[%s] " COLOR_RESET COLOR_BLUE "El programa se ha iniciado" COLOR_RESET "\n", get_timestamp());
  }

  if ((file_descriptor = inotify_init()) < 0) {
    perror("inotify_init");
    exit(1);
  }

  watch_descriptor = inotify_add_watch(file_descriptor, listen_directory, IN_CREATE | IN_DELETE | IN_MODIFY);

  if (watch_descriptor < 0) {
    perror("inotify_add_watch");
    exit(1);
  }

  while (1) {

    read(file_descriptor, buffer, 4096);
    struct inotify_event *event = (struct inotify_event*)buffer;

    if (event->mask & IN_CREATE) {
      if (event->mask & IN_ISDIR) {    
        fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_BLUE "Se ha creado un directorio: " COLOR_RESET COLOR_WHITE "%s" COLOR_RESET "\n", get_timestamp(), event->name);

      } else {
        fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_BLUE "Se ha creado un archivo: " COLOR_RESET COLOR_WHITE "%s" COLOR_RESET "\n", get_timestamp(), event->name);
      }

    } else if (event->mask & IN_DELETE) {
        if (event->mask & IN_ISDIR) {
          fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_RED "Se ha eliminado el directorio: "COLOR_RESET COLOR_WHITE "%s" COLOR_RESET "\n", get_timestamp(), event->name);

        } else {
          fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_RED "Se ha eliminado el archivo: " COLOR_RESET COLOR_WHITE "%s" COLOR_RESET "\n", get_timestamp(), event->name);
        }
    } else if (event->mask & IN_MODIFY) {
        fprintf(log_events, COLOR_GREEN "[%s] " COLOR_RESET COLOR_YELLOW "Se ha modificado el archivo: " COLOR_RESET COLOR_WHITE "%s" COLOR_RESET "\n", get_timestamp(), event->name);
    }
  }

  return 0;
}
