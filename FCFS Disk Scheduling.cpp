#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int fcfs_disk_scheduling(vector<int> requests, int head) {
    int total_seek_time = 0;
    vector<int> sequence;
    sequence.push_back(head);

    for (int request : requests) {
        int seek_distance = abs(request - head);
        total_seek_time += seek_distance;
        head = request;
        sequence.push_back(head);
    }

    cout << "Total Seek Time: " << total_seek_time << endl;
    cout << "Head Movement Sequence: ";
    for (size_t i = 0; i < sequence.size(); ++i) {
        cout << sequence[i];
        if (i != sequence.size() - 1) cout << " -> ";
    }
    cout << endl;

    return total_seek_time;
}

int main() {
    vector<int> requests = {60, 100, 30, 150, 20};
    int initial_head = 50;

    fcfs_disk_scheduling(requests, initial_head);

    return 0;
}
