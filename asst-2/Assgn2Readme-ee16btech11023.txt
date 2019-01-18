compile the thread code as: 
g++ Assgn2-ThStat-ee16btech11023.cpp -std=c++11 -pthread -o thread.out

compile the process code as: 
g++ Assgn2-ProcStat-ee16btech11023.cpp -lrt -o process.out

compile the timer code as:
g++ timer.cpp -lrt -o timer.out

run the testing.py code as:
python testing.py to generate the test data(stored into the file custom). Give user input as values below 20(int or fractions), they will be scaled as a multiple of 5e5

run the thread code as
./thread.out < custom

run the process code as
./timer.out ./process.out < custom

run the plot.py code to get the plots