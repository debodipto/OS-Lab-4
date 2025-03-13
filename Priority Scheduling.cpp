
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;

    Process(int id, int at, int bt, int pr)
        : pid(id), arrival_time(at), burst_time(bt), remaining_time(bt),
          priority(pr), completion_time(0), waiting_time(0), turnaround_time(0) {}
};

bool compare(Process* a, Process* b) {
    if (a->priority == b->priority) {
        return a->arrival_time < b->arrival_time;
    }
    return a->priority > b->priority;
}

vector<Process*> priority_scheduling_preemptive_time_quantum(vector<Process*>& processes, int time_quantum = 2) {
    int time = 0, completed = 0, n = processes.size();
    vector<Process*> queue;
    vector<pair<int, int>> sequence;

    while (completed < n) {
        for (auto& p : processes) {
            if (p->arrival_time == time && p->remaining_time > 0 && find(queue.begin(), queue.end(), p) == queue.end()) {
                queue.push_back(p);
                sort(queue.begin(), queue.end(), compare);
            }
        }

        if (!queue.empty()) {
            Process* current_process = queue.front();
            queue.erase(queue.begin());
            sequence.push_back({time, current_process->pid});

            int execution_time = min(time_quantum, current_process->remaining_time);
            current_process->remaining_time -= execution_time;
            time += execution_time;

            for (auto& p : processes) {
                if (time_quantum > 1 && p->arrival_time >= time - execution_time + 1 && p->arrival_time <= time &&
                    p->remaining_time > 0 && find(queue.begin(), queue.end(), p) == queue.end()) {
                    queue.push_back(p);
                    sort(queue.begin(), queue.end(), compare);
                }
            }

            if (current_process->remaining_time > 0) {
                queue.push_back(current_process);
                sort(queue.begin(), queue.end(), compare);
            } else {
                current_process->completion_time = time;
                completed++;
            }
        } else {
            time++;
        }
    }

    for (auto& p : processes) {
        p->turnaround_time = p->completion_time - p->arrival_time;
        p->waiting_time = p->turnaround_time - p->burst_time;
    }

    return processes;
}

int main() {
    vector<Process*> processes = {
        new Process(1, 0, 5, 10),
        new Process(2, 1, 4, 20),
        new Process(3, 3, 2, 30),
        new Process(4, 4, 1, 40)
    };

    auto scheduled_processes = priority_scheduling_preemptive_time_quantum(processes, 2);

    cout << "\nPID | AT | BT | Priority | CT  | TAT | WT\n";
    for (auto& p : scheduled_processes) {
        cout << p->pid << "   | " << p->arrival_time << "  | " << p->burst_time << "  | " << p->priority << "        | "
             << p->completion_time << "  | " << p->turnaround_time << "   | " << p->waiting_time << endl;
    }

    return 0;
}
