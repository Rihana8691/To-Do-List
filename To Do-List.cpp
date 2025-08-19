#include <iostream>
#include <stack>
#include <string>
#include <set>         // For duplicate checking (to maintain uniqueness)
#include <stdexcept>   // For exception handling
#include <limits>      // For input clearing
using namespace std;

class ToDoList {
private:
    stack<string> tasks;               // Stack for task storage
    set<string> taskSet;               // Set for duplicate checking (faster search)

    string toLower(const string& s) const {
        string result;
        for (char c : s) result += tolower(c);
        return result;
    }

public:
    ToDoList() {
        cout << "ToDo List Initialized." << endl;
    }

    void addTask(const string& task) {
        // Time complexity: O(1) for insert into stack, O(1) for set check.
        string newTaskLower = toLower(task);
        
        // Check if the task already exists in the set (for duplicates)
        if (taskSet.find(newTaskLower) != taskSet.end()) {
            cout << "Error: Task already exists." << endl;
            return;
        }
        
        // Add task to stack and set
        tasks.push(task);
        taskSet.insert(newTaskLower);
        cout << "Task added: " << task << endl;
    }

    void completeTask() {
        // Time complexity: O(1) for pop operation.
        if (tasks.empty()) {
            cout << "No tasks to complete." << endl;
        } else {
            string completedTask = tasks.top();
            tasks.pop();
            taskSet.erase(toLower(completedTask));  // Remove from set
            cout << "Task completed: " << completedTask << endl;
        }
    }

    void viewTasks() const {
        // Time complexity: O(n) for traversing the stack.
        if (tasks.empty()) {
            cout << "No tasks." << endl;
        } else {
            cout << "Tasks (Top to Bottom):" << endl;
            stack<string> temp = tasks;
            while (!temp.empty()) {
                cout << "- " << temp.top() << endl;
                temp.pop();
            }
        }
    }

    void clearTasks() {
        // Time complexity: O(n) for popping all tasks.
        while (!tasks.empty()) {
            taskSet.erase(toLower(tasks.top()));  // Remove from set
            tasks.pop();
        }
        cout << "All tasks cleared." << endl;
    }

    void searchTask(const string& keyword) const {
        // Time complexity: O(n) for searching through stack.
        string key = toLower(keyword);
        bool found = false;
        stack<string> temp = tasks;
        
        while (!temp.empty()) {
            if (toLower(temp.top()).find(key) != string::npos) {
                cout << "Found: " << temp.top() << endl;
                found = true;
            }
            temp.pop();
        }
        
        if (!found) cout << "No task found with keyword." << endl;
    }

    void deleteSpecificTask(const string& taskToDelete) {
        // Time complexity: O(n) for searching and deleting task.
        string target = toLower(taskToDelete);
        stack<string> temp;
        bool deleted = false;
        
        // Remove task from stack and set
        while (!tasks.empty()) {
            if (!deleted && toLower(tasks.top()) == target) {
                tasks.pop();
                taskSet.erase(target);  // Remove from set
                deleted = true;
            } else {
                temp.push(tasks.top());
                tasks.pop();
            }
        }
        
        // Restore remaining tasks back to the stack
        while (!temp.empty()) {
            tasks.push(temp.top());
            temp.pop();
        }

        if (deleted) {
            cout << "Task deleted: " << taskToDelete << endl;
        } else {
            cout << "Task not found: " << taskToDelete << endl;
        }
    }

    int taskCount() const {
        // Time complexity: O(1), directly returns the stack size.
        return tasks.size();
    }
};

// Function to display a fancy menu
void printFancyMenu() {
    cout << "\033[1;32m====================================\033[0m\n";
    cout << "\033[1;33m           TO-DO LIST MENU          \033[0m\n";
    cout << "\033[1;32m====================================\033[0m\n";

    cout << "\n\033[1;34m👉\033[0m \033[1;36m1. Add Task\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m2. Complete Task\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m3. View Tasks\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m4. Clear All Tasks\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m5. Search Task\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m6. Delete Task\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m7. Total Tasks\033[0m\n";
    cout << "\033[1;34m👉\033[0m \033[1;36m8. Exit\033[0m\n";

    cout << "\n\033[1;32m====================================\033[0m\n";
}

int main() {
    ToDoList myList;
    int option;
    string input;

    do {
        printFancyMenu();

        // User input prompt with highlighted choices
        cout << "\033[1;35mPlease enter your choice (1-8): \033[0m";
        cin >> option;
        cin.ignore();

        // Handle invalid input for menu choice
        if (cin.fail() || option < 1 || option > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31mError: Invalid input! Please enter a number between 1 and 8.\033[0m\n";
            continue;
        }

        cout << "\033[1;37m------------------------------------\033[0m\n";

        switch (option) {
            case 1:
                cout << "\033[1;32mEnter the task to add: \033[0m";
                getline(cin, input);
                myList.addTask(input);
                break;

            case 2:
                myList.completeTask();
                break;

            case 3:
                myList.viewTasks();
                break;

            case 4:
                myList.clearTasks();
                break;

            case 5:
                cout << "\033[1;32mEnter the search keyword: \033[0m";
                getline(cin, input);
                myList.searchTask(input);
                break;

            case 6:
                cout << "\033[1;32mEnter the task to delete: \033[0m";
                getline(cin, input);
                myList.deleteSpecificTask(input);
                break;

            case 7:
                cout << "\033[1;32mTotal number of tasks: \033[0m" << myList.taskCount() << endl;
                break;

            case 8:
                cout << "\033[1;31mExiting... Thank you for using the To-Do List! \033[0m\n";
                break;

            default:
                cout << "\033[1;31mInvalid choice, please try again.\033[0m\n";
                break;
        }
    } while (option != 8);

    return 0;
}
