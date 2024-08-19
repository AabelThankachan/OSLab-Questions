#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
};

// Function to sort processes by arrival time
void sortByArrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                // Swap processes[j] and processes[j + 1]
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, int wt[], int tat[]) {
    int current_time = 0;
    int completed = 0;
    bool process_selected[n];
    int remaining_time[n];
    
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        process_selected[i] = false; // Track if the process has been selected
    }

    while (completed < n) {
        int min_burst_index = -1;
        int min_burst_time = 1e9;

        // Find the process with the minimum burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !process_selected[i] && remaining_time[i] < min_burst_time) {
                min_burst_time = remaining_time[i];
                min_burst_index = i;
            }
        }

        if (min_burst_index != -1) {
            // Process the selected process
            current_time += processes[min_burst_index].burst_time;
            wt[min_burst_index] = current_time - processes[min_burst_index].arrival_time - processes[min_burst_index].burst_time;
            tat[min_burst_index] = current_time - processes[min_burst_index].arrival_time;

            // Mark the process as completed
            process_selected[min_burst_index] = true;
            completed++;
        } else {
            // No process is currently available, move time forward
            current_time++;
        }
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAvgTimes(struct Process processes[], int n) {
    int wt[n], tat[n];
    calculateTimes(processes, n, wt, tat);

    float avg_wt = 0, avg_tat = 0;
    printf("PID \tArrival Time\tBurst Time\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", avg_wt / n);
    printf("Average turnaround time = %.2f\n", avg_tat / n);
}

int main() {
    int n;

    // Ask user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Get process details from the user
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        processes[i].pid = i + 1; // Assigning Process IDs as 1, 2, 3, ...
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
    }

    // Sort processes by arrival time
    sortByArrival(processes, n);

    // Calculate average waiting time and turnaround time
    calculateAvgTimes(processes, n);

    return 0;
}
