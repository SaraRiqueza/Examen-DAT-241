#include <stdio.h>

// Cálculo de π utilizando una aproximación iterativa
void calcular_pi_iterativo(int n, float *resultado) {
    float pi = 0.0;
    for (int i = 0; i < n; i++) {
        pi += (float)(4 * ((i % 2 == 0) ? 1 : -1)) / (2 * i + 1);
    }
    *resultado = pi; // Almacena el resultado en la dirección apuntada por resultado
}

// Cálculo de π utilizando una aproximación recursiva
float calcular_pi_recursivo(int n, int i) {
    if (i >= n) {
        return 0; // Condición de salida
    }
    float term = (float)(4 * ((i % 2 == 0) ? 1 : -1)) / (2 * i + 1);
    return term + calcular_pi_recursivo(n, i + 1); // Llama recursivamente
}

// Función principal
int main() {
    int n; // Número de términos a calcular
    float pi_iterativo, pi_recursivo;

    // Solicitar al usuario el número de términos
    printf("Introduzca el número de términos para calcular π: ");
    scanf("%d", &n);

    // Calcular π de forma iterativa
    calcular_pi_iterativo(n, &pi_iterativo);
    printf("Valor de π (iterativo) con %d términos: %.6f\n", n, pi_iterativo);

    // Calcular π de forma recursiva
    pi_recursivo = calcular_pi_recursivo(n, 0);
    printf("Valor de π (recursivo) con %d términos: %.6f\n", n, pi_recursivo);

    return 0; // Finaliza el programa
}
