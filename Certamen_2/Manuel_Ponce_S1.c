// Manuel Ponce Santibañez 21.727.343-9 S.2
#include <stdio.h>
#include <string.h>

struct Pookimon {
    char name[16];
    char pooki_type[9];
    int hp;
};

struct Jugador {
    char nombre[21];
    int edad;
    struct Pookimon bolsa[3];
    int num_pookimones;
};

void agregar_pookimon(struct Jugador *jugador, char nombre[], char tipo[], int hp) {
    if (jugador->num_pookimones < 3) {
        struct Pookimon nuevo_pookimon;
        strncpy(nuevo_pookimon.name, nombre, 15);
        nuevo_pookimon.name[15] = '\0';
        strncpy(nuevo_pookimon.pooki_type, tipo, 8);
        nuevo_pookimon.pooki_type[8] = '\0';
        nuevo_pookimon.hp = (hp < 10) ? 10 : (hp > 30) ? 30 : hp;
        jugador->bolsa[jugador->num_pookimones] = nuevo_pookimon;
        jugador->num_pookimones++;
    } else {
        printf("La bolsa ya tiene 3 pookimones, no se puede agregar más.\n");
    }
}

int main() {
    struct Jugador jugador;
    jugador.num_pookimones = 0;

    printf("Ingresa el nombre del jugador: ");
    scanf("%s", jugador.nombre);
    printf("Ingresa la edad del jugador: ");
    scanf("%d", &jugador.edad);

    for (int i = 0; i < 3; i++) {
        char nombre_pookimon[16];
        char tipo_pookimon[9];
        int hp_pookimon;

        printf("Ingrese el nombre del pookimon %d: ", i + 1);
        scanf("%s", nombre_pookimon);
        printf("Ingrese el tipo del pookimon %d (agua, fuego, tierra, planta): ", i + 1);
        scanf("%s", tipo_pookimon);
        printf("Ingrese los HP del pookimon %d: ", i + 1);
        scanf("%d", &hp_pookimon);

        agregar_pookimon(&jugador, nombre_pookimon, tipo_pookimon, hp_pookimon);
    }

    printf("Nombre del jugador: %s\n", jugador.nombre);
    printf("Edad: %d\n", jugador.edad);
    printf("Pookimones en la bolsa:\n");
    for (int i = 0; i < jugador.num_pookimones; i++) {
        printf("Nombre: %s, Tipo: %s, HP: %d\n", jugador.bolsa[i].name, jugador.bolsa[i].pooki_type, jugador.bolsa[i].hp);
    }

    return 0;
}
