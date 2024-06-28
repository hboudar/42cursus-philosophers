#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//do a program that has two threads and two mutextes
//each thread will lock one mutex and then try to lock the other mutex
//if the mutexes are not locked in the same order, the program will deadlock
//if the mutexes are locked in the same order, the program will not deadlock
//the program will print "deadlock" or "no deadlock" and exit

//do a struct with two mutexes:
typedef struct s_mutexes
{
    pthread_mutex_t m1;
    pthread_mutex_t m2;
} t_mutexes;

void    *thread1_routine(void *mutex)
{
    t_mutexes *mutex1 = (t_mutexes *)mutex;

    pthread_mutex_lock(&mutex1->m1);
    printf("Thread 1 locked mutex 1\n");
    pthread_mutex_unlock(&mutex1->m1);
    pthread_mutex_lock(&mutex1->m2);
    printf("Thread 1 locked mutex 2\n");
    pthread_mutex_unlock(&mutex1->m2);
    printf("No deadlock\n");
    return NULL;
}

void    *thread2_routine(void *mutex)
{
    t_mutexes *mutex2 = (t_mutexes *)mutex;

    pthread_mutex_lock(&mutex2->m2);
    printf("Thread 2 locked mutex 2\n");
    pthread_mutex_unlock(&mutex2->m2);
    pthread_mutex_lock(&mutex2->m1);
    printf("Thread 2 locked mutex 1\n");
    pthread_mutex_unlock(&mutex2->m1);
    printf("No deadlock\n");
    return NULL;
}

int main()
{
    t_mutexes mutexes;
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&mutexes.m1, NULL);
    pthread_mutex_init(&mutexes.m2, NULL);

    pthread_create(&thread1, NULL, &thread1_routine, &mutexes);
    pthread_create(&thread2, NULL, &thread2_routine, &mutexes);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutexes.m1);
    pthread_mutex_destroy(&mutexes.m2);
    return 0;
}
