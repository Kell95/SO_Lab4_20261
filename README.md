# Laboratorio #4 Sistemas operativos

## Integrantes 

> Kelly Julieth Arango Henao
> kjulieth.arangoh@udea.edu.co
> 1036657098


> Brayan Stiven Jaraba Alvarez
> b.jaraba@udea.edu.co
> 1032178608
---
## Integración numérica $\pi$

---

## Sucesión de Fibonacci
Para este laboratorio se implementó una versión de la sucesión de Fibonacci utilizando hilos. Esta implementación tiene una ligera diferencia con la más común. En esta versión de la sucesión de Fibonacci, se tomaron los siguientes casos base

$$
f(-2) = 0 \text{, y }
f(-1) = 1
$$

Y para el resto de los casos

$$
f(n) = f(n-1) +f(n-2) \text{ para } n \ge 0
$$

Por lo tanto

$$
f(0) = 1 \text{, y } f(1) = 2
$$

### Explicación de la implementación del código

- **Función que ejecuta el hilo hijo**. Esta función recibirá como parámetro una estructura que contendrá el valor `n` pasado por consola por el usuario más un array de tamaño `n` en donde se irán almacenando las sumas de la sucesión. Luego se definirán los casos base, es decir para cuando `n = 0` y `n = 1`, para los cuales los valores son 1 y 2 respectivamente. Y por último, se iterará a través del array donde el valor del índice `i` del array será la suma del anterior y del segundo anterior. Como se ve en el siguiente fragmento de código

```c
typedef struct {
  int n;
  long long  *arr;
} fibonacci_args;

void *calculate_fibonacci(void *args) {
  fibonacci_args *fargs = (fibonacci_args *)args;
  int n = fargs->n;
  long long  *arr = fargs->arr;

  arr[0] = 1;
  arr[1] = 2;

  for (int i = 2; i < n; i ++ ) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  return 0;
}
```

 - **Función `main`, hilo padre**. En esta parte del código recibimos los argumentos pasados por consola (el valor de `n`), se comprueba que sean correctos, se crea el espacio de memoria para el array de tamaño `n` y se crea una instancia de la estructura usando `n` y el puntero del array. Luego se crea la rama usando `pthread_create`, esperamos que el hilo termine usando la función `pthread_join`, se calcula el tiempo gastado; en caso de que `n` sea menor o igual a 100 imprimimos cada uno de los elementos del array, y finalmente liberamos el puntero al array. Como se puede ver en el siguiente fragmento de código.

```c

int main(int argc, char *argv[]) {
  clock_t start = clock();

  assert(argc == 2 && "usage: fibonacci <n>");
  pthread_t tread_id;

  int n = atoi(argv[1]);
  long long  *arr = malloc(sizeof(long long) * n);
  assert(arr != NULL);
  fibonacci_args fargs = {n, arr};

  pthread_create(&tread_id, NULL, calculate_fibonacci, &fargs);
  pthread_join(tread_id, NULL);

  clock_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

  if (n <= 100) {
    for (int i = 0; i < n; i ++ ) {
      printf("%lld ", arr[i]);
    }
    printf("\n");
  }
  printf("time spent: %f seconds\n", time_spent);
  free(arr);
}
```

### Problemas encontrados durante esta implementación

Tipo de dato `int`. Inicialmente en la implementación utilizamos el tipo de dato `int` para separar la memoria para la lista de números de la sucesión de Fibonacci. Pero como la sucesión de Fibonacci crece tan rápido, para números grandes de `n` empezaban a salir números negativos. Investigamos y nos dimos cuenta que se debía al tipo de dato `int`, que es demasiado pequeño para este tipo de algoritmos. Así que la solución fue utilizar el tipo de dato `long long`.

### Pruebas de funcionalidad del programa

La siguiente imagen muestra una prueba del funcionamiento del programa con diferentes entradas.

![demostración de funcionalidad Fibonacci](images/demostracion-fibonacci.png)

> **Nota**: en la imagen se puede visualizar que para la entrada `n = 190` se muestra el tiempo de ejecución del programa pero no el array de números de la sucesión, y esto es intencional; se puso para que fuera más fácil comparar el tiempo de ejecución para entradas grandes y evitar outputs demasiado grandes que dificulten dicha comparación.

## Manifiesto de transparencia

La IA nos fue útil para la implementación y la búsqueda y solución de problemas; los siguientes son los casos en los que fue utilizada.

- Completaciones de código en editores de texto. Los editores de código modernos tienen sugerencias de código en línea generadas por inteligencia artificial, algunas de las cuales fueron sugerencias muy útiles en esta implementación.

- Investigación y solución de problemas. El motor de búsqueda de Google trae una inteligencia artificial integrada, que ayuda a que las búsquedas sean mucho más rápidas, pues recolecta información de diferentes fuentes y genera sugerencias de código. Esta fue utilizada para resolver dudas relacionadas con cómo implementar hilos en C, cómo medir el tiempo de ejecución de un programa en C y otras relacionadas con el laboratorio