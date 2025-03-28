#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>  
#include <unistd.h> 

#define NUM_PHILOSOPHERS 5  

sem_t *forks[NUM_PHILOSOPHERS]; 

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    if (id % 2 == 0) {
        sem_wait(forks[left_fork]);  
        sem_wait(forks[right_fork]); 
    } else {
        sem_wait(forks[right_fork]); 
        sem_wait(forks[left_fork]);  
    }

    printf("Philosopher %d is eating 🍽️\n", id);
    sleep(1);  

    sem_post(forks[left_fork]);
    sem_post(forks[right_fork]);

    printf("Philosopher %d has finished eating 🍴\n", id);

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int id[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        char sem_name[10];
        sprintf(sem_name, "/fork%d", i);
        forks[i] = sem_open(sem_name, O_CREAT, 0644, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_close(forks[i]);
        char sem_name[10];
        sprintf(sem_name, "/fork%d", i);
        sem_unlink(sem_name);
    }

    return 0;
}
