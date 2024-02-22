/*
  Assignment: Make an MPI task farm. A "task" is a randomly generated integer.
  To "execute" a task, the worker sleeps for the given number of milliseconds.
  The result of a task should be send back from the worker to the master. It
  contains the rank of the worker
*/

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <array>

// To run an MPI program we always need to include the MPI headers
#include <mpi.h>

const int NTASKS=5000;  // number of tasks
const int RANDOM_SEED=1234;

void master (int nworker) {
    std::array<int, NTASKS> task, result;

    // set up a random number generator
    std::random_device rd;
    //std::default_random_engine engine(rd());
    std::default_random_engine engine;
    engine.seed(RANDOM_SEED);
    // make a distribution of random integers in the interval [0:30]
    std::uniform_int_distribution<int> distribution(0, 30);

    for (int& t : task) {
        t = distribution(engine);   // set up some "tasks"
    }

    int finished_tasks;
    int run = 0;
    while (finished_tasks < NTASKS) {
        // Sending
        for (int i = 0; i < nworker; i++) {
            MPI_Send(&task[i+run*nworker], 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
        }
    
        // Receiving
        for (int i = 0; i < nworker; i++) {
            MPI_Request request;
            MPI_Status status;
            MPI_Irecv(&result[i+run*nworker], 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);

            // Testing if we have received a result
            int flag = 0;
            auto start = std::chrono::high_resolution_clock::now();

            while (!flag) {
                // Check if the message has been received
                MPI_Test(&request, &flag, &status);
    
                // Check for timeout (1 second)
                auto now = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start);
                if (duration.count() >= 1) {
                    // Timeout reached, cancel the receive and resend the task
                    MPI_Cancel(&request);
                    MPI_Send(&task[status.MPI_SOURCE+run*nworker-1], 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
    
                    // Reset the flag and start time, and start another non-blocking receive
                    flag = 0;
                    start = std::chrono::high_resolution_clock::now();
                    MPI_Irecv(&result[i+run*nworker], 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);
                    }
                }

            finished_tasks++;
            }

         run++;   
        }

    for (int i = 0; i < nworker; i++) {
        int stop_signal = -1;
        MPI_Send(&stop_signal, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
    }

    // Print out a status on how many tasks were completed by each worker
    for (int worker=1; worker<=nworker; worker++) {
        int tasksdone = 0; int workdone = 0;
        for (int itask=0; itask<NTASKS; itask++)
        if (result[itask]==worker) {
            tasksdone++;
            workdone += task[itask];
        }
        std::cout << "Master: Worker " << worker << " solved " << tasksdone << 
                    " tasks\n";    
    }
}

// call this function to complete the task. It sleeps for task milliseconds
void task_function(int task) {
    std::this_thread::sleep_for(std::chrono::milliseconds(task));
}

void worker (int rank) {

    while (true) {
    int received_task;
    MPI_Recv(&received_task, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (received_task == -1) break;

    task_function(received_task);

    MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
}

int main(int argc, char *argv[]) {
    int nrank, rank;

    MPI_Init(&argc, &argv);                // set up MPI
    MPI_Comm_size(MPI_COMM_WORLD, &nrank); // get the total number of ranks
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // get the rank of this process

    if (rank == 0)       // rank 0 is the master
        master(nrank-1); // there is nrank-1 worker processes
    else                 // ranks in [1:nrank] are workers
        worker(rank);

    MPI_Finalize();      // shutdown MPI
}
