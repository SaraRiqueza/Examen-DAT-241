#include <stdio.h>
#include <mpi.h>

#define N 6 // Tamaño del vector

int main(int argc, char **argv) {
    int procesador, cantidad;
    int n1, n2;
    int vector1[N], vector2[N], resultado[N], resultado1[N], resultado2[N];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    if (procesador == 0) {
        // Inicializa los vectores en el procesador 0
        n1 = 6;
        for (int i = 0; i < N; i++) {
            vector1[i] = i + 1;          // Ejemplo: [1, 2, 3, 4, 5, 6]
            vector2[i] = (i + 1) * 2;    // Ejemplo: [2, 4, 6, 8, 10, 12]
        }

        // Enviar posiciones impares a procesador 1
        MPI_Send(vector1, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector2, N, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Enviar posiciones pares a procesador 2
        MPI_Send(vector1, N, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vector2, N, MPI_INT, 2, 0, MPI_COMM_WORLD);

        // Recibir resultado de posiciones impares desde procesador 1
        MPI_Recv(resultado1, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Recibir resultado de posiciones pares desde procesador 2
        MPI_Recv(resultado2, N, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Combinar resultados
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) {
                resultado[i] = resultado2[i]; // Posiciones pares
            } else {
                resultado[i] = resultado1[i]; // Posiciones impares
            }
        }

        // Imprimir el vector resultado
        printf("Vector resultado de la suma: [");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado[i]);
        }
        printf("]\n");
    }

    if (procesador == 1) {
        // Recibir los vectores desde el procesador 0
        MPI_Recv(vector1, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector2, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Sumar posiciones impares
        for (int i = 1; i < N; i += 2) {
            resultado[i] = vector1[i] + vector2[i];
        }

        // Enviar resultado de posiciones impares al procesador 0
        MPI_Send(resultado, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (procesador == 2) {
        // Recibir los vectores desde el procesador 0
        MPI_Recv(vector1, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector2, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Sumar posiciones pares
        for (int i = 0; i < N; i += 2) {
            resultado[i] = vector1[i] + vector2[i];
        }

        // Enviar resultado de posiciones pares al procesador 0
        MPI_Send(resultado, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;