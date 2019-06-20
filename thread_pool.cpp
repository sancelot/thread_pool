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
    // burning cycles
    for (int n=0;n < 10000;n++)
    {
    alpha += 0.00000001;
    if (alpha > 1.)
       alpha = 0.;
    float x = cos(alpha);
    }
    //printf("job is running\n");
    }
}

ThreadPool::ThreadPool(int num_threads)
{
int ret;

ret = sem_init(&jobs, 0, 0);

for (int n=0;n < num_threads;n++)
{
    pthread_attr_t tattr;

    pthread_t *t = new pthread_t;

    
	/* Initilisation des attribut du thread */
    ret = pthread_attr_init (&tattr); // Attribut par defaut
    ret = pthread_create(t,&tattr,&job,NULL);
	struct sched_param param;


	ret = pthread_attr_getschedparam (&tattr, &param); // On recupere les attribut par defaut
	/* Modification attribut apres la creation de la tache */
	param.sched_priority = 99; // modification de la priorite
	ret = pthread_setschedparam(* t,SCHED_FIFO, &param); // On applique les different parametre
    if (ret == -1)
        perror("pthread_setschedparam failed\n");

    // each allocated thread is linked to a core.
    cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(1 << n,&cpuset);
    ret = pthread_setaffinity_np(*t,sizeof(cpu_set_t), &cpuset);

    threads.push_back(t);
}
// testing purpose infinite job loop
    while (1==1)
    {
    PushJob();  
    }
}

// push a job in the job queue
void ThreadPool::PushJob()
{
    sem_post(&jobs);
}

ino_t getNbCores()
{
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#else
    return (int) sysconf(_SC_NPROCESSORS_ONLN);
#endif
}
int main()
{
printf("core availables : %d\n",getNbCores());
mlockall(MCL_CURRENT|MCL_FUTURE);
ThreadPool *pool = new ThreadPool(getNbCores());
pause();
}
