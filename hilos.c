#include <pthread.h>
#include <stdio.h>

#define NUM_VECES 10000
#define forn(i,j) for(int i = 0; i<j; i++)

// HOW TO COMPILE:
// gcc hilos.c -o hilos 
// Ley de Amdhal: Revisar


int D; int T; //...

int a = 0;
pthread_t hilos[2];
pthread_mutex_t sem;

void * sumar(void * param){
    forn(i,NUM_VECES)
        forn(j,NUM_VECES){
            pthread_mutex_lock(&sem);
            a++;
            pthread_mutex_unlock(&sem);
            }
}

void * restar(void * param){
    forn(i,NUM_VECES)
        forn(j,NUM_VECES){
            pthread_mutex_lock(&sem);
            a--;
            pthread_mutex_unlock(&sem);
            }
}

int main(){
    
    pthread_mutex_init(&sem, 0);
       

    pthread_create(hilos, NULL, sumar, NULL);
    pthread_create(hilos+1, NULL, restar, NULL);
    
    forn(i,2)
        pthread_join(hilos[i],NULL);
        
    printf("%d\n", a);
    return 0;
}
