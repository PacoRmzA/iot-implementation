#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 10000
int saldo; //variable global, la misma para todos los hilos
pthread_mutex_t saldoLock = PTHREAD_MUTEX_INITIALIZER;

void* suma100(void* arg) { //void en este caso simboliza que el apuntador puede ser a cualquier tipo
    //char* c = (char*) arg; para castear el argumento
    int lsaldo; //Líneas 12-14 región crítica, que se deben correr secuencialmente para evitar race conditions
    pthread_mutex_lock(&saldoLock);
    lsaldo = saldo;
    lsaldo += 100;      //porque se consulta y modifica una variable externa
    saldo = lsaldo;
    pthread_mutex_unlock(&saldoLock);
    pthread_exit(NULL); //termina el hilo, la función devuelve al arugmento
}

int main() {
    pthread_t threads[NUM_THREADS]; //guarda IDs de los hilos
    for(int i=0; i<NUM_THREADS; i++) { 
        pthread_create(&threads[i], NULL, suma100, NULL); //hilo a usar, atributos del hilo, función a ejecutar, argumentos de la función
    }
    for(int i=0; i<NUM_THREADS; i++) { 
        pthread_join(threads[i], NULL); //hilo a esperar y apuntador a lo que regresa ese hilo, espera a que el hilo termine
    }
    printf("Saldo final es %d\n",saldo); //nada garantiza que cuando se imprime esto ya acabaron todos los hilos
    pthread_exit(NULL); //espera a los hilos y termina el programa
    return 0;
}