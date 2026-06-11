# Laboratorio #4 Sistemas operativos

## Integrantes 

> Kelly Julieth Arango Henao
> kjulieth.arango@udea.edu.co
> 1036657098


> Brayan Stiven Jaraba Alvarez
> b.jaraba@udea.edu.co
> 1032178608
>
> **Enlace Notebook: https://colab.research.google.com/drive/153-MZ6iJ31cUpQqQoDdPHE0qF6HuF6n-?usp=sharing#scrollTo=CA8neu8OX88z**
---
## Integración numérica $\pi$
En esta parte del laboratorio se implementó un programa para calcular una aproximación del número π utilizando integración numérica. El método empleado se basa en la siguiente integral:

$$
pi = \int_{0}^{1} \frac{4}{1+x^2}dx
$$

La idea consiste en dividir el intervalo ([0,1]) en una gran cantidad de subintervalos y aproximar el área bajo la curva mediante la regla del punto medio. A medida que aumenta el número de divisiones, la aproximación obtenida se acerca cada vez más al valor real de π.

Para el desarrollo de la práctica se implementaron dos versiones del programa:

Versión serial (pi.c): realiza todos los cálculos utilizando un único hilo de ejecución.

Versión paralela (pi_p.c): distribuye el trabajo entre varios hilos.




## Implementación y documentación de funciones

## Versión serial (pi.c)

- **Función GetTime()**

Esta función obtiene el tiempo actual del sistema utilizando la estructura timeval y la llamada al sistema gettimeofday(). Su propósito es medir el tiempo de ejecución del algoritmo y evaluar el rendimiento de la aplicación.

- **Función f(double x)**

Implementa la función matemática utilizada para calcular la integral:

$$
f(x)=\frac{4}{1+x^2}
$$

Recibe como parámetro el valor de x y retorna el resultado de la evaluación de la función.

- **Función CalcPi(long long n)**

Es la función encargada de realizar el cálculo de π mediante integración numérica. Calcula el tamaño de cada subintervalo y recorre las n particiones del intervalo. Para cada iteración determina el punto medio:

$$
x=h(i+0.5)
$$

evalúa la función en dicho punto y acumula el resultado en una suma total. Finalmente multiplica la suma acumulada por el tamaño del subintervalo para obtener la aproximación de π.

- **Función main()**

Controla la ejecución general del programa. Recibe el número de iteraciones desde la línea de comandos, inicia la medición del tiempo, invoca la función CalcPi(), muestra el valor calculado de π y reporta el tiempo total de ejecución.

## Versión paralela (pi_p.c)

- **Estructura ThreadData**

Se utiliza para transferir información entre el hilo principal y los hilos trabajadores. Contiene:

start: inicio del rango de iteraciones.
end: fin del rango de iteraciones.
partial_sum: suma parcial calculada por el hilo.
h: tamaño del subintervalo.
Función CalcPartialPi(void *arg)

Es la función ejecutada por cada hilo. Recibe una estructura ThreadData con el rango de iteraciones asignado y calcula una suma parcial de la integral únicamente para ese segmento. El resultado es almacenado en el campo partial_sum de la estructura correspondiente.

- **Función main()**

La función principal recibe el número total de iteraciones y la cantidad de hilos a utilizar. Posteriormente divide el trabajo entre los hilos disponibles, crea los hilos mediante pthread_create(), espera su finalización con pthread_join() y suma todos los resultados parciales obtenidos. Finalmente calcula el valor aproximado de π y muestra el tiempo de ejecución.


## Estrategia de paralelización

La versión paralela implementa una estrategia de paralelismo de datos. El conjunto total de iteraciones se divide en bloques de tamaño similar y cada hilo procesa un bloque de manera independiente.

Cada hilo calcula una suma parcial local, evitando el acceso concurrente a variables compartidas durante el cálculo. Una vez finalizada la ejecución de todos los hilos, el hilo principal recopila los resultados mediante pthread_join() y realiza la suma final.

Esta estrategia elimina la necesidad de utilizar mutex o mecanismos adicionales de sincronización durante la fase de cálculo, reduciendo la contención entre hilos y simplificando la implementación.

## Medición del rendimiento

Para comparar el desempeño de ambas versiones se incorporó instrumentación utilizando la función GetTime(), basada en gettimeofday().

Las pruebas se realizaron utilizando:

n = 2000000000

Posteriormente se ejecutó la versión paralela con diferentes cantidades de hilos (1, 2, 4, 8 y 16) para analizar el impacto del paralelismo sobre el tiempo de ejecución.

A partir de los resultados obtenidos se calcularon las métricas de:

Speedup (Ts/Tp), que indica cuántas veces la versión paralela es más rápida que la serial.

Eficiencia (Speedup/N), que mide el aprovechamiento de los hilos utilizados.

## Problemas encontrados y soluciones implementadas

- El primero consistió en definir una estrategia adecuada para distribuir las iteraciones entre los diferentes hilos. Para solucionarlo se calculó un tamaño de bloque para cada hilo utilizando la división del número total de iteraciones entre la cantidad de hilos. Las iteraciones restantes fueron asignadas al último hilo para garantizar que todo el trabajo fuera procesado.

- Otro aspecto importante fue evitar condiciones de carrera al acumular los resultados parciales. Inicialmente se consideró utilizar una variable compartida para almacenar la suma total; sin embargo, esto habría requerido mecanismos adicionales de sincronización. La solución adoptada consistió en que cada hilo almacenara su resultado en una variable propia (partial_sum) y que la suma final fuera realizada exclusivamente por el hilo principal.

- Durante las pruebas también se observó que la versión paralela no siempre obtuvo mejores tiempos que la versión serial. Este comportamiento puede explicarse por el overhead asociado a la creación, planificación y sincronización de los hilos, además de las características particulares del entorno de ejecución utilizado para las pruebas.

## Pruebas realizadas

- Para verificar la funcionalidad de la implementación se realizaron diversas pruebas.

- Inicialmente se comprobó que tanto la versión serial como la versión paralela produjeran valores de π prácticamente idénticos, validando la correcta división del trabajo entre los hilos.

- Posteriormente se ejecutó la versión serial para obtener el tiempo de referencia (Ts). Después se realizaron múltiples ejecuciones de la versión paralela utilizando diferentes cantidades de hilos para obtener los tiempos paralelos (Tp).

- Con los resultados obtenidos se construyó una tabla comparativa y una gráfica de Speedup, las cuales permitieron analizar el comportamiento del algoritmo frente al incremento del paralelismo y evaluar el impacto de la utilización de múltiples hilos sobre el rendimiento general de la aplicación.

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


## Conclusiones

- La integración numérica mediante la regla del punto medio permitió obtener una aproximación precisa del número π, evidenciando que el error disminuye a medida que aumenta el número de subdivisiones utilizadas en el cálculo.
  
- La implementación paralela utilizando Pthreads permitió aplicar los conceptos de creación, ejecución y sincronización de hilos, demostrando cómo un problema computacional puede dividirse en tareas independientes para ser procesadas concurrentemente.

-El uso de sumas parciales por hilo evitó condiciones de carrera y eliminó la necesidad de emplear mecanismos adicionales de sincronización durante el cálculo, simplificando la solución y mejorando su escalabilidad.

-Los resultados experimentales mostraron que el aumento del número de hilos no garantiza necesariamente una reducción proporcional del tiempo de ejecución, debido al overhead asociado a la creación, administración y sincronización de los hilos.

-El análisis de las métricas de Speedup y Eficiencia permitió evaluar el comportamiento de la versión paralela y comprender las limitaciones prácticas del paralelismo, especialmente cuando el número de hilos supera la capacidad real de procesamiento del sistema.

-La práctica permitió reforzar conceptos fundamentales de programación concurrente, como la distribución de carga, el modelo de memoria compartida y la sincronización mediante pthread_join(), proporcionando experiencia práctica en el desarrollo de aplicaciones multihilo.
