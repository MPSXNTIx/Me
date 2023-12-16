// Manuel Ponce Santibañez 21.727.343-9 S1
#include <stdio.h>

void ingresarNotas(char nombre[]) {
    FILE *archivo;
    float nota, suma = 0;
    int cantidadNotas, i;

    printf("Ingrese la cantidad de notas: ");
    scanf("%d", &cantidadNotas);

    if (cantidadNotas <= 0) {
        printf("Cantidad de notas no válida. Volviendo al menú principal.\n");
        return;
    }

    archivo = fopen(nombre, "w");

    if (archivo == NULL) {
        printf("Error al abrir el archivo. Volviendo al menú principal.\n");
        return;
    }

    for (i = 0; i < cantidadNotas; i++) {
        do {
            printf("Ingrese la nota %d (entre 1.0 y 7.0): ", i + 1);
            scanf("%f", &nota);

            if (nota < 1.0 || nota > 7.0) {
                printf("Nota no válida. Debe estar entre 1.0 y 7.0. Inténtelo nuevamente.\n");
            }
        } while (nota < 1.0 || nota > 7.0);

        fprintf(archivo, "%.2f\n", nota);
        suma += nota;
    }

    fclose(archivo);
    printf("Notas ingresadas correctamente. Volviendo al menú principal.\n");
}

void calcularPromedio(char nombre[]) {
    FILE *archivo;
    float nota, suma = 0, promedio;
    int contador = 0;

    archivo = fopen(nombre, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo. Volviendo al menú principal.\n");
        return;
    }

    while (fscanf(archivo, "%f", &nota) == 1) {
        suma += nota;
        contador++;
    }

    fclose(archivo);

    if (contador == 0) {
        printf("No hay notas almacenadas para el estudiante. Volviendo al menú principal.\n");
        return;
    }

    promedio = suma / contador;

    printf("El promedio de %s es: %.2f\n", nombre, promedio);
}

int main() {
    char nombre[50];
    int opcion;

    do {
        printf("1. Ingresar notas\n");
        printf("2. Calcular promedio\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del estudiante: ");
                scanf("%s", nombre);
                ingresarNotas(nombre);
                break;

            case 2:
                printf("Ingrese el nombre del estudiante: ");
                scanf("%s", nombre);
                calcularPromedio(nombre);
                break;

            case 3:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;

            default:
                printf("Opción no válida. Inténtelo nuevamente.\n");
        }

    } while (opcion != 3);

    return 0;
}
