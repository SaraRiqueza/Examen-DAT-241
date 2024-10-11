#include <stdio.h>
#include <mpi.h>

#define M 3 // Número de filas de A
#define N 4 // Número de columnas de A (y filas de B)
#define P 2 // Número de columnas de B

int main(int argc, char **argv) {
    int rank, size;
    int A[M][N], B[N][P], C[M][P]; // Matrices A, B y resultado C
    int filaA[N], resultadoFila[P];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Inicializar matriz A
        printf("Matriz A (%d x %d):\n", M, N);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j; // Ejemplo de inicialización
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }

        // Inicializar matriz B
        printf("Matriz B (%d x %d):\n", N, P);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                B[i][j] = i + j; // Ejemplo de inicialización
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }