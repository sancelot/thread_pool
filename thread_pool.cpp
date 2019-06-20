#include <vector>
#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/mman.h>
static sem_t   jobs;    /* number of job requested   */

class ThreadPool {
private:
    std::vector <pthread_t *> threads;
public:
    ThreadPool(int num_threads);
    void PushJob();
    static void *job(void *arg);
}; 

void *ThreadPool::job(void *arg)
{
    int ret;
    while (1 == 1)
    {
    ret = sem_wait(&jobs);
    static float alpha = 0.000001;
    alpha += 0.00000001;
    if (alpha > 1.)
       alpha = 0.;
    float x = cos(alpha);
    //printf("job is running\n");
    }
}

ThreadPool::ThreadPool(int num_threads)
{
int ret;

ret = sem_init(&jobs, 0, 0);

for (int n=0;n < num_threads;n++)
{
    pthread_t *t = new pthread_t;
    ret = pthread_create(t,NULL,&job,NULL);
    threads.push_back(t);
}
for (int n=0;n < 100000;n++)
while (1==1)
{
    PushJob();    PushJob();

}
}

// push a job in the job queue
void ThreadPool::PushJob()
{
    sem_post(&jobs);
}


int main()
{
mlockall(MCL_CURRENT|MCL_FUTURE);
ThreadPool *pool = new ThreadPool(4);
pause();
}
