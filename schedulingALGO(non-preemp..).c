#include <stdio.h>

typedef struct Process {
    char name[10];
    int memory;
    int burstTime;
} Process;

typedef struct Queue {
    Process* processes[100];
    int front, rear;
} Queue;

void enqueue(Queue* queue, Process* process) {
    if (queue->rear == 99) {
        printf("Queue overflow\n");
        return;
    }

    queue->processes[queue->rear++] = process;
}

Process* dequeue(Queue* queue) {
    if (queue->front == queue->rear) {
        printf("Queue underflow\n");
        return NULL;
    }

    return queue->processes[queue->front++];
}
void scheduleByMemory(Process* processes, int n) {
    Queue readyQueue;
    readyQueue.front = readyQueue.rear = 0;

    // Sort processes based on memory requirement in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].memory > processes[j].memory) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Enqueue all processes into the ready queue
    for (int i = 0; i < n; i++) {
        enqueue(&readyQueue, &processes[i]);
    }

    while (readyQueue.front != readyQueue.rear) {
        Process* process = dequeue(&readyQueue);
        printf("Process %s started execution\n", process->name);

        // Simulate execution by decrementing burst time
        while (process->burstTime > 0) {
            process->burstTime--;
            // Since non-preemptive, execute until burst time reaches zero
        }

        printf("Process %s completed execution\n", process->name);
    }
}


int main() {
    Process processes[] = {
        {"P1", 50, 10},
        {"P2", 10, 15},
        {"P3", 150, 8}
    };

    int n = sizeof(processes) / sizeof(Process);

    scheduleByMemory(processes, n);

    return 0;
}