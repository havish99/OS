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
# include <algorithm>

using namespace std;

// struct storing the details of the process arguments
struct proc_args{
    int size;
    int *arr;
    float mean;
    float median;
    float stddev;
};

// function calculating the mean
float Mean(void *param){
    proc_args *ptr = (proc_args *)param;
    float mean  = 0;
    for(int i=0;i<ptr->size;i++){
        mean=mean+ptr->arr[i];
    }
    mean = mean/(ptr->size);
    return mean;
}

// function calculating the standard deviation
float Stddev(void *param){
    float stddev = 0;
    proc_args *ptr = (proc_args *)param;
    for(int i=0;i<ptr->size;i++){
        stddev = stddev + pow((ptr->arr[i]-ptr->mean),2);
    }
    stddev = sqrt(stddev/ptr->size);
    return stddev;
}
//
//
// function calculating the median
float Median(void *param){
    float median=0;
    proc_args *ptr = (proc_args *)param;
    sort(ptr->arr,ptr->arr + ptr->size);
    int size = ptr->size;
    if(size%2==0){// if even sized array
        median = 0.5*(ptr->arr[(size/2)-1] + ptr->arr[(size/2)]);
    }
    else{// if odd sized array
        median = ptr->arr[size/2];
    }
    return median;
}


int main(){
    float stddev,median;
    pid_t pid,pid1;
    const int size = 4096;  // the shared memory size
    const char *name = "OS1"; // the name of shared memory object
    int fd; // shared memory desciptor
    proc_args args;
    cin >> args.size;
    args.arr = new int[args.size];
    for(int i=0;i<args.size;i++){
        cin >> args.arr[i];
    }
    proc_args *ptr; // shared memory pointer
    fd = shm_open(name,O_CREAT | O_RDWR,0666); // creates file descriptor
    ftruncate(fd,size); // truncate buffer upto given size
    ptr = (struct proc_args *) mmap(0,size,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // pointer to shared memory location
    *ptr = args; // storing in the shared memory 
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if(pid==0){ // the child process
    if(fork()==0){ // the child of child process(calculates the mean)
    float mean = Mean(ptr);
    ptr->mean = mean;
    return 0;
    }
    wait(NULL);// waits for mean calculation
    ptr->stddev = Stddev(ptr);
    }
    else if(pid > 0){// the parent process
    ptr->median = Median(ptr); // calculates the median 
    wait(NULL); // waits for the completion of process
    cout << "Mean: " << ptr->mean << endl;
    cout << "Stddev: " << ptr->stddev << endl;
    cout << "Median: " << ptr->median << endl;
  }
}









