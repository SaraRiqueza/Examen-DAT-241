def fibonacci(n):
    # Creamos un vector (lista) para almacenar los términos de Fibonacci
    fib = [0, 1]  # Los dos primeros términos de la serie
    
    # Generamos la serie de Fibonacci hasta el n-ésimo término
    for i in range(2, n):
        siguiente_fib = fib[i - 1] + fib[i - 2]  # Suma de los dos términos anteriores
        fib.append(siguiente_fib)  # Agregamos el nuevo término al vector
    
    return fib  # Retornamos el vector con los términos de Fibonacci

# Ejemplo de uso
n = int(input("Introduzca el número de términos de Fibonacci a calcular: "))
serie_fibonacci = fibonacci(n)

# Imprimir la serie de Fibonacci
print("Serie de Fibonacci hasta el término", n, ":", serie_fibonacci)