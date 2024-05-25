/**
 * @file longest_processing_time_first.cpp
 * @brief A C++ implementation of the LPT(Largest Processing Time) scheduling algorithm for multiple machines
 *        LPT is a scheduling algorithm that schedules tasks based on their processing times
 *        The task with the longest processing time is scheduled first
 *        This implementation uses a priority queue to sort the tasks in descending order of processing times
 *        The tasks are then scheduled to the machine with the least current load.
 *        There is <queue> to implement the priority queue, so we can relatively easily implement the LPT algorithm. >_< 
 */

#include <iostream>
#include <queue>
#include <vector>

// Define the task structure with task ID and processing time
struct Task {
    unsigned int id;
    unsigned int processingTime;

    // Constructor
    Task(unsigned int id, unsigned int processingTime) : id(id), processingTime(processingTime) {}

    // Overload the less than operator for the priority queue
    bool operator<(const Task& other) const {
        return processingTime < other.processingTime;
    }
};

// Define the machine structure with machine ID and current load
struct Machine {
    unsigned int id;
    unsigned int currentLoad;

    // Constructor
    Machine(unsigned int id, unsigned int currentLoad = 0) : id(id), currentLoad(currentLoad) {}

    // Overload the greater than operator for the priority queue (min heap)
    bool operator>(const Machine& other) const {
        return currentLoad > other.currentLoad;
    }
};

// A function performing the LPT scheduling algorithm for multiple machines
std::vector<std::vector<Task>> lptScheduling(std::vector<Task> tasks, unsigned int numMachines) {
    // Create a priority queue to sort the tasks in descending order of processing times
    std::priority_queue<Task> taskQueue;
    for (const Task& task : tasks) {
        taskQueue.push(task);
    }

    // Create a priority queue (min heap) for machines based on their current load
    std::priority_queue<Machine, std::vector<Machine>, std::greater<Machine>> machineQueue;
    for (unsigned int index = 0; index < numMachines; index++) {
        machineQueue.push(Machine(index));
    }

    // Create a vector to store the tasks assigned to each machine
    std::vector<std::vector<Task>> machineTasks(numMachines);

    // Schedule the tasks to machines
    while (!taskQueue.empty()) {
        Task task = taskQueue.top();
        taskQueue.pop();

        // Get the machine with the least current load
        Machine machine = machineQueue.top();
        machineQueue.pop();

        // Assign the task to this machine with the least current load
        machineTasks[machine.id].push_back(task);
        machine.currentLoad += task.processingTime;

        // Push the machine back into the priority queue
        machineQueue.push(machine);
    }

    return machineTasks;
}

int main() {
    // Create a vector of tasks with task ID and processing time
    std::vector<Task> tasks = {
        Task(1, 10),
        Task(2, 5),
        Task(3, 15),
        Task(4, 7),
        Task(5, 3),
        Task(6, 8),
        Task(7, 12),
        Task(8, 6),
        Task(9, 9),
        Task(10, 4),
    };

    // Number of machines
    unsigned int numMachines = 3;

    // Perform the LPT scheduling algorithm
    std::vector<std::vector<Task>> scheduledTasks = lptScheduling(tasks, numMachines);

    // Display the scheduled tasks for each machine
    for (unsigned int index = 0; index < numMachines; index++) {
        std::cout << "Machine " << index + 1 << " scheduled tasks: " << std::endl;
        unsigned int totalTime = 0;
        for (const Task& task : scheduledTasks[index]) {
            totalTime += task.processingTime;
            std::cout << "  Task " << task.id << " (Processing Time: " << task.processingTime << ") ";
            std::cout << "Total Time: " << totalTime << std::endl;
        }
        std::cout << "Machine " << index + 1 << " Total Load: " << totalTime << std::endl;
    }

    return 0;
}

// Machine 1 scheduled tasks: 
//   Task 3 (Processing Time: 15) Total Time: 15
//   Task 4 (Processing Time: 7) Total Time: 22
//   Task 10 (Processing Time: 4) Total Time: 26
// Machine 1 Total Load: 26
// Machine 2 scheduled tasks:
//   Task 7 (Processing Time: 12) Total Time: 12
//   Task 6 (Processing Time: 8) Total Time: 20
//   Task 2 (Processing Time: 5) Total Time: 25
// Machine 2 Total Load: 25
// Machine 3 scheduled tasks:
//   Task 1 (Processing Time: 10) Total Time: 10
//   Task 9 (Processing Time: 9) Total Time: 19
//   Task 8 (Processing Time: 6) Total Time: 25
//   Task 5 (Processing Time: 3) Total Time: 28
// Machine 3 Total Load: 28