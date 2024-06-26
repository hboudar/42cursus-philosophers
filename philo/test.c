#include <stdio.h>
#include <pthread.h>

// Each thread will count TIMES_TO_COUNT times
#define TIMES_TO_COUNT 21000


typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

void	*thread_routine(void *data)
{

	t_counter	*counter;
	unsigned int	i;

	counter = (t_counter *)data;

	pthread_mutex_lock(&counter->count_mutex);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0;
		pthread_mutex_lock(&counter->count_mutex);
	while (i < TIMES_TO_COUNT)
	{
		counter->count++;
		i++;
	}
		pthread_mutex_unlock(&counter->count_mutex);
	pthread_mutex_lock(&counter->count_mutex);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL); // Thread termine ici.
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_counter	counter;


	counter.count = 0;
	pthread_mutex_init(&counter.count_mutex, NULL); // mutex initialization dynamicly
	pthread_create(&tid1, NULL, thread_routine, &counter);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", (long)tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", (long)tid2);

	pthread_mutex_destroy(&counter.count_mutex);
	printf("Counter value: %u\n", counter.count);
	return (0);
}