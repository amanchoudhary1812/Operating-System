#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>  
#include <unistd.h> 

#define BUFFER_SIZE 5  

int buffer[BUFFER_SIZE];  
int count = 0;  

sem_t *mutex, *empty, *full;  

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {  
        item = i + 1;  

        sem_wait(empty); 
        sem_wait(mutex); 

        buffer[count++] = item;
        printf("🛠 Producer ne item produce kiya: %d\n", item);

        sem_post(mutex);  
        sem_post(full);   

        sleep(1);  
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {  
        sem_wait(full);  
        sem_wait(mutex); 

        item = buffer[--count];
        printf(" Consumer ne item consume kiya: %d\n", item);

        sem_post(mutex); 
        sem_post(empty); 

        sleep(2); 
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    mutex = sem_open("/mutex", O_CREAT, 0644, 1);  
    empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE);  
    full = sem_open("/full", O_CREAT, 0644, 0);  

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_close(mutex);
    sem_unlink("/mutex");

    sem_close(empty);
    sem_unlink("/empty");

    sem_close(full);
    sem_unlink("/full");

    return 0;
}
