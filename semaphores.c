/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define  CHILD		0       /* Return value of child proc from fork call */

int main()
{
    sem_t * EM; /* my semaphores */
    sem_t * MP;
    sem_t * DC;
    sem_t * CP;          /* my semaphores */
    
    int pid;		/* Process id after fork call */
    int i;		/* Loop index. */
    int N;		/* Number of requests to process */
    int status;  	/* Exit status of child process. */
    int type;           /* Type of animal */


    /*   Initialization of the semaphores   */
     
     
    printf("How many requests to be processed: \n");
    scanf("%d",&N);
      /* create, initialize semaphore */
    if ((EM = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("semaphore initilization");
      exit(1);
  }
  else if ((MP = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("semaphore initilization");
      exit(1);
  }
  else if ((DC = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("semaphore initilization");
      exit(1);
  }
  else if ((CP = sem_open("examplesemaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("semaphore initilization");
      exit(1);
  }
 

    for (i=1; i<=N; i++) {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) {
   	        /* Fork failed! */
	        perror("fork");
	        exit(1);
        }
        
     
        if (pid == CHILD) {
	        pid = getpid();
            switch (type) {

		    case 1: /* Elephant code*/
                    printf("     Elephant process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(EM);
                    printf("     Elephant process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Elephant process with pid %d is out.\n",pid);
                    fflush(stdout); 
                    sem_post(EM);
                    exit(0);
                    break;

		    case 2:  /*Dog code*/
                    printf("     Dog process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(DC);
                    printf("     Dog process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Dog process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(DC);
                    exit(0);
		            break;

		    case 3: /*Cat Code*/
                    printf("     Cat process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(CP);
                    sem_wait(DC);
                    printf("     Cat process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Cat process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(CP);
                    sem_post(DC);
                    exit(0);
		            break;

		    case 4: /*Mouse code*/
                    printf("     Mouse process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(EM);
                    sem_wait(MP);
                    printf("     Mouse process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Mouse process with pid %d is out.\n",pid);
                    fflush(stdout); 
                    sem_post(EM);
                    sem_post(MP);
                    exit(0);
		            break;
		
		    case 5: /*Parrot  Code*/
                    printf("     Parrot process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(CP);
                    sem_wait(MP);
                    printf("     Parrot process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Parrot process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_wait(CP);
                    sem_wait(MP);
                    exit(0);
		            break;
            }
            exit(0);
        }
    }
    
    /* Now wait for the child processes to finish */
    for (i=1; i<=N; i++) {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}
