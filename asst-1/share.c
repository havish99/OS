# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/mman.h>

int main(){
	const int size = 4096;  // the shared memory size
	const char *name = "OS"; // the name of shared memory object
	int fd,fd1; // shared memory desciptor
	char *ptr,*ptr1; // shared memory pointer
	fd = shm_open(name,O_CREAT | O_RDWR,0666); // creates the shared memory object
	ftruncate(fd,size); // truncate buffer upto given size
	ptr = (char *) mmap(0,size,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // pointint to shared memory 	
	const char *msg = "Hi";
	sprintf(ptr,"%s",msg);
	ptr+=strlen(msg);
	// fd1 = shm_open(name,O_RDONLY,0666);
	ptr = (char *)mmap(0,size,PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
	printf("%s",ptr);
}