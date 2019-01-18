# include <sys/types.h>
# include <iostream>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <math.h>

using namespace std;

int main(int argc, char *argv[]){
	double t1,t2;
	pid_t pid;
	const int size = 4096;  // the shared memory size
	const char *name = "OS"; // the name of shared memory object
	int fd; // shared memory desciptor
	struct timeval *ptr; // shared memory pointer
	fd = shm_open(name,O_CREAT | O_RDWR,0666); // creates file descriptor
	ftruncate(fd,size); // truncate buffer upto given size
	ptr = (struct timeval *) mmap(0,size,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // pointer to shared memory location
	struct timeval start,finish; // data types denoting the start and end time of execution of command
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if(pid==0){
	gettimeofday(&start,NULL); // function which gives the time stamp before execution(tv_sec is seconds and tv_usec is micro-seconds) 
	*ptr = start; // stores the time stamp before execution of command in shared memory  
	execvp(argv[1],argv+1); // executes given argument
	}
	else if(pid > 0){
	wait(NULL); // waits for completion of child process
	gettimeofday(&finish,NULL); // reads the time stamp after execution of the command
	t1 = ptr->tv_sec + ptr->tv_usec*pow(10,-6); // reads the initial time stamp from shared memory and converts to seconds
	t2 = finish.tv_sec + finish.tv_usec*pow(10,-6); // converts the final time stamp to seconds 
	cout << "time elapsed: " << t2-t1 << endl; // prints the time taken in seconds
	return 0;
	}
}