#include <stdio.h>

#define NUM_ATMS     5
#define NUM_TIPOS    4
#define NUM_EVENTOS  25
#define LIMITE       3

void imprimirTipo(int tipo) {
    switch (tipo) {
        case 0: printf("Acceso correcto");     break;
        case 1: printf("PIN incorrecto");      break;
        case 2: printf("Usuario inexistente"); break;
        case 3: printf("Tarjeta bloqueada");   break;
        default: printf("Desconocido");
    }
}

int esTipoValido(int tipo) {
    if (tipo >= 0 && tipo < NUM_TIPOS) {
        return 1;
    }
    return 0;
}

void actualizarContador(int *contador) {
    *contador = *contador + 1;
}

int main(void) {

    int equipo[NUM_EVENTOS] = {
        0,1,2,3,4,
        0,1,2,3,4,
        0,1,2,3,4,
        0,1,2,3,4,
        0,1,2,3,4
    };

    int tipo[NUM_EVENTOS] = {
        0,1,1,2,0,
        0,1,1,1,0,
        0,2,1,1,3,
        3,1,0,1,0,
        0,2,0,0,0
    };

    int matriz[NUM_ATMS][NUM_TIPOS] = {0};

    printf(" EVENTOS \n");
    int *pEquipo = equipo;
    int *pTipo   = tipo;

    for (int i = 0; i < NUM_EVENTOS; i++) {
        int e = *(pEquipo + i);
        int t = *(pTipo + i);
        
        if (!esTipoValido(t)) {
            printf("Evento %d: tipo invalido, se omite.\n", i + 1);
            continue;
        }

        printf("Evento %2d | ATM-%02d | ", i + 1, e + 1);
        imprimirTipo(t);
        printf("\n");
    }

    for (int i = 0; i < NUM_EVENTOS; i++) {
        int e = *(pEquipo + i);
        int t = *(pTipo + i);

        if (!esTipoValido(t)) {
            continue;
        }

        actualizarContador(&matriz[e][t]);
    }

    printf("\n RESUMEN POR ATM \n");
    printf("%-8s %-18s %-18s %-18s %-18s\n",
           "ATM", "Acceso correcto", "PIN incorrecto",
           "Usuario inexistente", "Tarjeta bloqueada");

    for (int i = 0; i < NUM_ATMS; i++) {
        printf("ATM-%02d   ", i + 1);
        for (int j = 0; j < NUM_TIPOS; j++) {
            int valor = *(*(matriz + i) + j);
            printf("%-18d ", valor);
        }
        printf("\n");
    }

    printf("\n CLASIFICACION \n");
    for (int i = 0; i < NUM_ATMS; i++) {
        int pinMal   = *(*(matriz + i) + 1);
        int noExiste = *(*(matriz + i) + 2);
        int fallidos = pinMal + noExiste;

        if (fallidos > LIMITE) {
            printf("ATM-%02d -> SOSPECHOSO (intentos fallidos: %d)\n",
                   i + 1, fallidos);
        } else {
            printf("ATM-%02d -> Normal     (intentos fallidos: %d)\n",
                   i + 1, fallidos);
        }
    }

    return 0;
}