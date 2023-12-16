// Manuel Ponce 21.727.343-9 S1
// Byron Oñate 21.478.226-k S1
// Nicolas Tapia 19.193.536-5 S2

#include <stdio.h>
#include <stdlib.h>

#define MAX_USUARIOS 100
#define MAX_REPORTES 4

struct Usuario {
  int id;
  char nombre[70];
};

struct CitaMedica {
  int dia;
  int bloqueHorario;
  int bloqueAtencion;
  int idUsuario;
};

// Prototipos de funciones
void agregarCita(struct Usuario usuarios[], struct CitaMedica citas[], int *numUsuarios, int *numCitas);
void mostrarCitas(struct CitaMedica citas[], int numCitas);
void mostrarEstadisticas(struct CitaMedica citas[], int numCitas);
void guardarDatos(struct Usuario usuarios[], struct CitaMedica citas[], int numUsuarios, int numCitas);
void leerDatos(struct Usuario usuarios[], struct CitaMedica citas[], int *numUsuarios, int *numCitas);

int main() {
  int opcion;
  struct CitaMedica citas[MAX_USUARIOS];
  struct Usuario usuarios[MAX_USUARIOS];
  int numCitas = 0;
  int numUsuarios = 0;

  // Leer datos desde el archivo al iniciar
  leerDatos(usuarios, citas, &numUsuarios, &numCitas);

  do {
    // Mostrar el menú
    printf("\n--- Menú ---\n");
    printf("1. Agendar cita médica\n");
    printf("2. Mostrar listado de citas\n");
    printf("3. Mostrar estadísticas\n");
    printf("4. Guardar datos y salir\n");
    printf("Ingrese su opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
      case 1:
        agregarCita(usuarios, citas, &numUsuarios, &numCitas);
        break;
      case 2:
        mostrarCitas(citas, numCitas);
        break;
      case 3:
        mostrarEstadisticas(citas, numCitas);
        break;
      case 4:
        guardarDatos(usuarios, citas, numUsuarios, numCitas);
        printf("Guardando datos y saliendo del programa. ¡Hasta luego!\n");
        break;
      default:
        printf("Opción no válida. Intente de nuevo.\n");
        break;
    }
  } while (opcion != 4);

  return 0;
}

// Función para agregar una cita médica
void agregarCita(struct Usuario usuarios[], struct CitaMedica citas[], int *numUsuarios, int *numCitas) {
  if (*numUsuarios < MAX_USUARIOS) {
    struct Usuario nuevoUsuario;
    struct CitaMedica nuevaCita;

    // Ingresar datos del usuario
    printf("Ingrese su rut: ");
    scanf("%d", &nuevoUsuario.id);
    printf("Ingrese el nombre: ");
    scanf("%s", nuevoUsuario.nombre);

    // Mostrar información ingresada
    printf("Bienvenido al sistema, %s\n", nuevoUsuario.nombre);
    printf("Su identificador es %d\n", nuevoUsuario.id);

    // Ingresar detalles de la cita
    printf("Ingrese el dia de la semana donde quiere agendar su hora\n");
    printf("0 lunes, 1 martes, 2 miercoles, 3 jueves, 4 viernes: ");
    scanf("%d", &nuevaCita.dia);
    printf("Ingrese el bloque de horario que lo acomode (0-7): ");
    scanf("%d", &nuevaCita.bloqueHorario);
    printf("Ingrese el bloque de atencion que lo acomode (0-3): ");
    scanf("%d", &nuevaCita.bloqueAtencion);

    // Validar datos ingresados
    if (nuevaCita.dia < 0 || nuevaCita.dia > 4 || nuevaCita.bloqueHorario < 0 || nuevaCita.bloqueHorario > 7 ||
        nuevaCita.bloqueAtencion < 0 || nuevaCita.bloqueAtencion > 3) {
      printf("Datos ingresados fuera de rango. Por favor, inténtelo de nuevo.\n");
      return;
    }

    // Guardar datos en las estructuras
    nuevaCita.idUsuario = nuevoUsuario.id;
    usuarios[*numUsuarios] = nuevoUsuario;
    citas[*numCitas] = nuevaCita;
    (*numUsuarios)++;
    (*numCitas)++;

    printf("\nCita médica agendada con éxito.\n");
  } else {
    printf("El límite de usuarios ha sido alcanzado. No se pueden agregar más citas.\n");
  }
}

// Función para mostrar el listado de citas
void mostrarCitas(struct CitaMedica citas[], int numCitas) {
  int hayCitas = 0;

  printf("\nListado de citas:\n");

  for (int i = 0; i < numCitas; i++) {
    printf("Día %d, Bloque horario %d, Bloque de atención %d, ID Usuario %d\n",
           citas[i].dia, citas[i].bloqueHorario, citas[i].bloqueAtencion, citas[i].idUsuario);
    hayCitas = 1;
  }

  if (!hayCitas) {
    printf("No hay citas agendadas.\n");
  }
}

// Función para mostrar estadísticas de las citas
void mostrarEstadisticas(struct CitaMedica citas[], int numCitas) {
  int totalCitas = 0;
  int citasPorDia[5] = {0};
  int bloqueHorarioMasUsado = 0;
  int bloqueAtencionMasUsado = 0;

  for (int i = 0; i < numCitas; i++) {
    totalCitas++;
    citasPorDia[citas[i].dia]++;
  }

  // Calcular el bloque de horario y bloque de atención más utilizados
  for (int hora = 0; hora < 8; hora++) {
    for (int atencion = 0; atencion < 4; atencion++) {
      int citasEnBloque = 0;
      for (int i = 0; i < numCitas; i++) {
        if (citas[i].bloqueHorario == hora && citas[i].bloqueAtencion == atencion) {
          citasEnBloque++;
        }
      }
      if (citasEnBloque > citasPorDia[bloqueHorarioMasUsado]) {
        bloqueHorarioMasUsado = hora;
        bloqueAtencionMasUsado = atencion;
      }
    }
  }

  printf("\nEstadísticas:\n");
  printf("Total de citas agendadas: %d\n", totalCitas);
  printf("Citas por día:\n");
  for (int dia = 0; dia < 5; dia++) {
    printf("Día %d: %d citas\n", dia, citasPorDia[dia]);
  }
  printf("Bloque de horario más utilizado: %d\n", bloqueHorarioMasUsado);
  printf("Bloque de atención más utilizado: %d\n", bloqueAtencionMasUsado);
}

// Función para guardar datos en un archivo
void guardarDatos(struct Usuario usuarios[], struct CitaMedica citas[], int numUsuarios, int numCitas) {
  FILE *archivo;

  // Guardar usuarios en el archivo
  archivo = fopen("usuarios.txt", "w");
  if (archivo != NULL) {
    for (int i = 0; i < numUsuarios; i++) {
      fprintf(archivo, "%d %s\n", usuarios[i].id, usuarios[i].nombre);
    }
    fclose(archivo);
  } else {
    printf("Error al abrir el archivo para guardar usuarios.\n");
  }

  // Guardar citas en el archivo
  archivo = fopen("citas.txt", "w");
  if (archivo != NULL) {
    for (int i = 0; i < numCitas; i++) {
      fprintf(archivo, "%d %d %d %d\n", citas[i].dia, citas[i].bloqueHorario, citas[i].bloqueAtencion, citas[i].idUsuario);
    }
    fclose(archivo);
  } else {
    printf("Error al abrir el archivo para guardar citas.\n");
  }
}

// Función para leer datos desde un archivo
void leerDatos(struct Usuario usuarios[], struct CitaMedica citas[], int *numUsuarios, int *numCitas) {
  FILE *archivo;

  // Leer usuarios desde el archivo
  archivo = fopen("usuarios.txt", "r");
  if (archivo != NULL) {
    while (fscanf(archivo, "%d %s", &usuarios[*numUsuarios].id, usuarios[*numUsuarios].nombre) == 2) {
      (*numUsuarios)++;
    }
    fclose(archivo);
  } else {
    printf("Archivo de usuarios no encontrado. Se creará uno nuevo.\n");
  }

  // Leer citas desde el archivo
  archivo = fopen("citas.txt", "r");
  if (archivo != NULL) {
    while (fscanf(archivo, "%d %d %d %d", &citas[*numCitas].dia, &citas[*numCitas].bloqueHorario, &citas[*numCitas].bloqueAtencion, &citas[*numCitas].idUsuario) == 4) {
      (*numCitas)++;
    }
    fclose(archivo);
  } else {
    printf("Archivo de citas no encontrado. Se creará uno nuevo.\n");
  }
}
