#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Task {

    private:
        string name;
        int priority; // 1-10
        bool completed;

    public:
        Task(string n, int p) : name (n), priority(p), completed(false) {}
        void markCompleted() {
            completed = true;
        }
        bool isCompleted() const {
            return completed;
        }
        string getName() const {
            return name;
        }
        int getPriority() const {
            return priority
        }
};

class Scheduler {
    private:
        vector<Task> tasks; // holds all tasks for easy iteration and removal
    
    public:
        //Clear memory to avoid leaks
        ~Scheduler() {
            for (auto t : tasks) {
                delete t; 
            }
        }

        void addTask(string name, int priority) {
            if (priority < 1 || priority > 10) {
                throw invalid_argument("Priority must be between 1 and 10.");
            }            
            Task* t = new Task(name, priority);
            tasks.push_back(t);
        }

        void removeTask(string name) {
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if ((*it ) -> getName() == name && !(*it) -> isCompleted()) {
                    delete *it;
                    tasks.erase(it);
                    cout << "Removed: " << name << endl;
                    return;
                }
            }
            cout << "Task not found or already completed." << endl;
        }

        void executeNext() {
            if (tasks.empty()) {
                return;
            }

            //Find the unfinished task of highest priority (lowest p value)
            Task* nextTask = nullptr;
            int minPriority = INT_MAX;
            for (auto t : tasks) {
                if (!t -> isCompleted() && t -> getPriority() < minPriority) {
                    minPriority = t -> getPriority();
                    nextTask = t;
                }
            }

            if (nextTask) {
                nextTask -> markCompleted();
                cout << "Executing: " << nextTask -> getName() << endl;
            }
            else {
                cout << "No tasks to execute." << endl;
            }
        }

        void listTasks() {
            vector<Task*> unfinished;
            for (auto t : tasks) {
                if (!t -> isCompleted()) {
                    unfinished.push_back(t);
                }
            }

            // Sort the unfinished tasks by priority
            sort(unfinished.begin(), unfinished.end(), [](Task* a, Task* b) {
                return a -> getPriority() < b -> getPriority();
            });

            for (auto t : unfinished) {
                cout << t -> getName() << " (Priority: " << t -> getPriority() << ")" << endl;
            }
        }

        int getTaskCount() const {
            int count = 0;
            for (auto t : tasks) {
                if(!t -> isCompleted()) {
                    count ++;
                }
            }
            return count;
        }
};

int main() {
    Scheduler scheduler;
    string command;

    cout << "Task Scheduler Commands: add <name> <priority>, execute, list, remove <name>, quit" << endl;
    
    // test samples
    try {
        scheduler.addTask("Task1", 3);
        scheduler.addTask("Task2", 1);
        scheduler.addTask("Task3", 5);
        Scheduler.addTask("Invalid", 11); // Should throw an error
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
        cout << "Initial list:" << endl;

        scheduler.listTasks();
        scheduler.executeNext();
        scheduler.executeNext();
        scheduler.removeTask("Task2");

        cout << "After execution:" << endl;
        scheduler.listTasks(); // Should be empty
        cout << "Remaining tasks: " << scheduler.getTaskCount() << endl // 0
    
    while (true) {
        cout << "> ";
        cin >> command;

        if (command == "add") {
            string name;
            int priority;
            cin >> name >> priority;
            try {
                scheduler.addTask(name, priority);
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (command == "execute") {
            scheduler.executeNext();
        }
        else if (command == "list") {
            scheduler.listTasks();
        }
        else if (command == "remove") {
            string name;
            cin >> name;
            scheduler.removeTask(name);
        }
        else if (command == "count") {
            scheduler.getTaskCount();
        }
        else if (command == "quit") {
            break;
        }
        else {
            cout << "Invalid command." << endl;
        }

    }

    return 0;
}