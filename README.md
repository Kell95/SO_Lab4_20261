# Laboratorio #4 Sistemas operativos 

## Integrantes 

> Kelly Julieth Arango Henao
> kjulieth.arangoh@udea.edu.co
> 1036657098


> Brayan Stiven Jaraba Alvarez
> b.jaraba@udea.edu.co
> 1032178608
---
## Integracion numerica $\pi$

---

## Sucecion de fibonacci
Para este laboratorio se implemento una version de la sucecion de fibonacci utilizando hilos. Esta implementacion tiene una ligera diferencia con la mas comun. En esta version de la sucesion de fibonacci, se tomaron los siguentes casos bases

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

### Explicacion de la implementacion del codigo

- **Funcion que ejecuta el hilo hijo**. Esta funcion recibira como parametro una estructura que contendra el valor `n` pasado por consola por el usuario mas un array de tamaño n en donde si iran almacenando las sumas de la sucesión. Luego se definiran los casos bases, es decir para cuando `n = 0` y `n = 1`, el para los cuales los valores son 1 y 2 respectivamente. y por ultimo, se iterara a traves del array para donde el valor del indice `i` del array sera la suma del anterior y el segundo anterior. Como se ve en el siguiente fragmento de codigo 

```{c}
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

- **Funcion `main`, hilo padre**. En esta parte del codigo recibimos los argumentos pasados por consola (el valor de `n`), se comprueba que sean correctos, se crea el espacio de memoria para el array de tamaño `n` y se crea una instancia de la estructura usando n y el puntero del array. Luego se crea la rama usando `pthread_create`, luego esperamos que el hilo termine usando la funcion `pthread_join` se calcula el tiempo gastado, en caso de que el `n` se menor o igual a 100 imprimimos cuada uno de los elementos del array, y finalmente liberamos el puntero al array. Como se puede ver en el siguiente fragmento de codigo.

```{c}

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