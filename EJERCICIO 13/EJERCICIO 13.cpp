#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define TAM 5       // Tamaño del vector de cadenas
#define MAX_STR 100 // Longitud máxima de las cadenas

int main(int argc, char **argv) {
    int rank, num_procesos;
    char palabras[TAM][MAX_STR] = {"Martes", "Sabado", "Azul", "Nieve", "Raton"}; // Vector de cadenas
    char cadenas_pares[(TAM + 1) / 2][MAX_STR], cadenas_impares[TAM / 2][MAX_STR]; // Arrays para pares e impares

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);        // Rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos); // Número de procesos

    if (rank == 0) {
        // El procesador 0 distribuye las cadenas
        for (int i = 0; i < TAM; i += 2) {
            MPI_Send(palabras[i], MAX_STR, MPI_CHAR, 1, 0, MPI_COMM_WORLD);  // Enviar cadenas en posiciones pares al procesador 1
        }
        for (int i = 1; i < TAM; i += 2) {
            MPI_Send(palabras[i], MAX_STR, MPI_CHAR, 2, 0, MPI_COMM_WORLD);  // Enviar cadenas en posiciones impares al procesador 2
        }
    } else if (rank == 1) {
        // El procesador 1 recibe y muestra las cadenas en posiciones pares
        printf("Procesador 1 (cadenas pares): [");
        for (int i = 0; i < (TAM + 1) / 2; i++) {
            MPI_Recv(cadenas_pares[i], MAX_STR, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", cadenas_pares[i]);
            if (i < (TAM + 1) / 2 - 1) {
                printf(", "); // Separador entre palabras
            }
        }
        printf("]\n"); // Cerrar el formato
    } else if (rank == 2) {
        // El procesador 2 recibe y muestra las cadenas en posiciones impares
        printf("Procesador 2 (cadenas impares): [");
        for (int i = 0; i < TAM / 2; i++) {
            MPI_Recv(cadenas_impares[i], MAX_STR, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", cadenas_impares[i]);
            if (i < TAM / 2 - 1) {
                printf(", "); // Separador entre palabras
            }
        }
        printf("]\n"); // Cerrar el formato
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
