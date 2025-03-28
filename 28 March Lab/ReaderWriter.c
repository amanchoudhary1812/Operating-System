#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>  
#include <unistd.h> 

sem_t *mutex, *wrt;  
int readcount = 0;  

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {  
        sem_wait(mutex);  
        readcount++;  
        if (readcount == 1) 
            sem_wait(wrt);  
        sem_post(mutex);  

        printf("Reader %d is reading\n", id);
        sleep(1);  

        sem_wait(mutex); 
        readcount--;
        if (readcount == 0) 
            sem_post(wrt);  
        sem_post(mutex);  

        sleep(2);  
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 2; i++) {  
        sem_wait(wrt);  

        printf("Writer %d is writing\n", id);
        sleep(2); 

        sem_post(wrt);  

        sleep(2);  
    }
    return NULL;
}

int main() {
    pthread_t r[2], w[1];  
    int id[2] = {1, 2};  
    int wid[1] = {1};  

    mutex = sem_open("/mutex", O_CREAT, 0644, 1);  

    for (int i = 0; i < 2; i++)
        pthread_create(&r[i], NULL, reader, &id[i]);

    for (int i = 0; i < 1; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    for (int i = 0; i < 2; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 1; i++)
        pthread_join(w[i], NULL);

    sem_close(wrt);
    sem_unlink("/wrt");

    sem_close(mutex);
    sem_unlink("/mutex");

    return 0;
}
