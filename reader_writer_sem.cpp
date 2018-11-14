#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex, writeblock;
int data = 0, rcount = 0;

void *reader(void *arg) {
  while(1)
  {
	  int f;
	  f = *((int *)arg);
	  sem_wait(&mutex);
	  rcount = rcount + 1;
	  if (rcount == 1)
		sem_wait(&writeblock);
	  sem_post(&mutex);
	  printf("Data read by the reader%d is %d\n", f, data);
	  sleep(1);
	  sem_wait(&mutex);
	  rcount = rcount - 1;
	  if (rcount == 0)
		sem_post(&writeblock);
	  sem_post(&mutex);
  }
  return (void *)nullptr;
}

void *writer(void *arg) {
  while(1)
  {
	  int f;
	  f = *((int *)arg);
	  sem_wait(&writeblock);
	  data++;
	  printf("Data writen by the writer%d is %d\n", f, data);
	  //sleep(1);
	  sem_post(&writeblock);
  } 
  return (void *)nullptr;
}

int main() {
  int i, b;
  pthread_t rtid[5], wtid[5];
  sem_init(&mutex, 0, 1);  // int sem_init(sem_t *sem, int pshared, unsigned int value)  pshared:0 => semaphore is shared among threads of a process
  sem_init(&writeblock, 0, 1);
  int arr[3];
  for (i = 0; i <= 2; i++) {
    arr[i] = i;
    pthread_create(&wtid[i], NULL, writer, (void *)&arr[i]);
    pthread_create(&rtid[i], NULL, reader, (void *)&arr[i]);
  }
  for (i = 0; i <= 2; i++) {
    pthread_join(wtid[i], NULL);
    pthread_join(rtid[i], NULL);
  }
  return 0;
}
