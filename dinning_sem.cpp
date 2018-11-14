#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> //for sleep
/* To avoid deadlock an odd philosopher picks up first her
left chopstick and then her right chopstick, whereas an even philosopher
picks up her right chopstick and then her left chopstick
*/

#define N 5 /* Number of times each philosopher tries to eat */
#define P 5 /* Number of philosophers */

sem_t Room;
sem_t Fork[P];

void *tphilosopher(void *ptr) {
    int i, k = *((int *) ptr);
    for(i = 1; i <= N; i++) {
        printf("%*cThink %d %d\n", 10, ' ', k, i);
        sleep(1);
        if( k%2 == 0 ) {
          // even philosopher picks up her right chopstick and then her left chopstick
          sem_wait(&Fork[k]) ;
          sem_wait(&Fork[(k+1) % P]) ;
        } else {
          // odd philosopher picks up her left chopstick and then her right chopstick
          sem_wait(&Fork[(k+1) % P]) ;
          sem_wait(&Fork[k]) ;  
        }
        printf("%*cEat %d %d\n", 1, ' ', k, i);
        sleep(2);
        if( k%2 == 0 ) {
        sem_post(&Fork[k]) ;
        sem_post(&Fork[(k+1) % P]) ;
       } else {
           sem_post(&Fork[(k+1) % P]) ;
           sem_post(&Fork[k]) ;
      }
    }
    pthread_exit(0);
}

int main(int argc, char * argv[]) {
    int i, targ[P];
    pthread_t thread[P];
    sem_init(&Room, 0, P-1);    
    for(i=0;i<P;i++) {
        sem_init(&Fork[i], 0, 1);    
    }
    for(i=0;i<P;i++) {
        targ[i] = i;
        pthread_create(&thread[i], NULL, &tphilosopher,(void *) &targ[i]);
    }
    for(i=0;i<P;i++) {
        pthread_join(thread[i], NULL);
    }
    for(i=0;i<P;i++) {
        sem_destroy(&Fork[i]);
    }
    sem_destroy(&Room);
    return 0;
}

