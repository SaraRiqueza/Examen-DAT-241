/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import multiprocessing

def calcular_pi_segmento(inicio, paso):
    suma_local = 0.0
    for n in range(inicio, 1000000, paso):  # Límite a 1 millón
        signo = 1 if n % 2 == 0 else -1
        denominador = 2 * n + 1
        suma_local += signo * 1.0 / denominador
    return suma_local

if __name__ == "__main__":
    num_procesadores = max(3, multiprocessing.cpu_count())  # Usar al menos 3 procesos
    with multiprocessing.Pool(processes=num_procesadores) as pool:

        # Asignar segmentos a los procesos
        segmentos = [(i, num_procesadores) for i in range(num_procesadores)]
        resultados_parciales = pool.starmap(calcular_pi_segmento, segmentos)

    # Calcular la suma total de las partes
    pi_aproximado = sum(resultados_parciales) * 4  # Multiplicamos por 4 para obtener π

    print("Valor estimado de π:", pi_aproximado)