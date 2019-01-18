# include <iostream>
# include <pthread.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
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
# include <chrono>
# include <algorithm>
using namespace std;

// stores details of thread arguments
struct thread_args{
    int size;
    int *arr;
};

float mean,stddev,median; // global variables

void *Mean(void *param);
void *Stddev(void *param);
void *Median(void *param);

int main(int argc,char *argv[]){
    chrono :: time_point <chrono :: system_clock> start,end;
	thread_args args;
    // starting time for code
    start = chrono::system_clock::now();
    cin >> args.size;
    args.arr = new int[args.size];
    for(int i=0;i<args.size;i++){
        cin >> args.arr[i];
    }
	pthread_t tid1,tid2,tid3; // the 3 threads for mean, stddev and median
    pthread_create(&tid1,NULL,Mean,(void *)(&args)); // mean thread
    pthread_create(&tid3,NULL,Median,(void *)(&args));// median thread
    pthread_join(tid1,NULL);// wait for mean completion
    pthread_create(&tid2,NULL,Stddev,(void *)(&args));// stddev thread
    pthread_join(tid2,NULL); // wait for stddev completion
    pthread_join(tid3,NULL); // wait for median
    end = chrono::system_clock::now(); // ending time for code
    chrono::duration<double>elapsed = end-start; // difference
    
    cout << "Mean: " << mean << endl;
    cout << "Stddev: " << stddev << endl;
    cout << "Median: " << median << endl;
    cout << "Time taken: " << elapsed.count() << endl;
    
}

void *Mean(void *param){
    thread_args *ptr = (thread_args *)param;
    for(int i=0;i<ptr->size;i++){
        mean=mean+ptr->arr[i];
    }
    mean = mean/(ptr->size);
    pthread_exit(NULL);
}

void *Stddev(void *param){
    thread_args *ptr = (thread_args *)param;
    for(int i=0;i<ptr->size;i++){
        stddev = stddev + pow((ptr->arr[i]-mean),2);
    }
    stddev = sqrt(stddev/ptr->size);
    pthread_exit(NULL);
}

void *Median(void *param){
    thread_args *ptr = (thread_args *)param;
    int arr[ptr->size];
    for(int i=0;i<ptr->size;i++){
        arr[i]=ptr->arr[i];
    }
    sort(arr,arr+ptr->size);
    int size = ptr->size;
    if(size%2==0){ // if even sized array
        median = 0.5*(arr[(size/2)-1] + arr[(size/2)]);
    }
    else{// if odd sized array
        median = arr[size/2];
    }
    pthread_exit(NULL);
}

