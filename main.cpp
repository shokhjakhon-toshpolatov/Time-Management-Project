#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <conio.h>
using namespace std;

void mainMenu();

class TaskManagement {
    int taskID = 0;
    string description;
    string deadline;
    int priority = 0;
    fstream file;

public:
        void Tasks();
        //inside Tasks
        void showTasks();
        void searchTask();
        void manageTask();
        //inside manageTask
        void addTask();
        void editTask();
        void deleteTask();

};
TaskManagement tsk;

void Game1();

void Game2();
char getUserChoice();
char getComputerChoice();
void showChoice(char choice);
void chooseWinner(char player, char computer);

void game1Menu();
void Game2Menu();
void GameMenu();

void timer();

void countDown(int hlim, int mlim);

int main(){
    mainMenu();
    return 0;
}

void mainMenu() {
    char choice;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "~  TIME MANAGEMENT SYSTEM  ~\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Tasks\n";
        cout << "2. Take a little break\n";
        cout << "3. Timer\n";
        cout << "0. Save and Exit\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;
            switch (choice) {
                case '1': tsk.Tasks();
                        break;
                case '2': GameMenu();
                        break;
                case '3': timer();
                        break;
                case '0': cout << "Exiting...";
                        break;
                default: cout << "Invalid choice!\n";
            }
    } while (choice != '0');
}

void TaskManagement :: addTask() {

    file.open("tasks.txt", ios::in);
    taskID = 0;
    if (file.is_open() && file.peek() != EOF) {
        string line, idStr;
        while (getline(file, line)) {
            size_t pos = line.find('*');
            if (pos != string::npos) {
                idStr = line.substr(0, pos);
            }
        }
        taskID = stoi(idStr);
    }
    file.close();
    taskID++;

    cin.ignore();
    cout << "Enter task description: ";
    getline(cin, description);
    cout << "Enter deadline: ";
    getline(cin, deadline);
    do {
        cout << "Enter priority [1-5] (1: Low, 5: High):  ";
        cin >> priority;
        if (priority < 1 || priority > 5) {
            cout << "Invalid priority!\n";
        }
    } while (priority < 1 || priority > 5);

    file.open("tasks.txt", ios::app);
    file << taskID << "*"
         << description << "*"
         << deadline << "*"
         << priority << endl;
    file.close();

    cout << "Task added successfully!\n";

}

void TaskManagement::editTask() {
    int editID;
    cout << "Enter task ID to edit: ";
    cin >> editID;

    file.open("tasks.txt", ios::in);
    if (!file.is_open() || file.peek() == EOF) {
        cout << "No tasks available.\n";
        return;
    }

    vector<string> tasks;
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find('*');
        if (pos == string::npos) continue;

        int currentID = stoi(line.substr(0, pos));
        if (currentID == editID) {
            found = true;

            // Split line into fields
            size_t p1 = pos;
            size_t p2 = line.find('*', p1 + 1);
            size_t p3 = line.find('*', p2 + 1);

            string oldDesc = line.substr(p1 + 1, p2 - p1 - 1);
            string oldDeadline = line.substr(p2 + 1, p3 - p2 - 1);
            int oldPriority = stoi(line.substr(p3 + 1));

            bool editing = true;
            while (editing) {
                int choice;
                cout << "\nWhat do you want to edit?\n";
                cout << "1. Description\n2. Deadline\n3. Priority\n0. Done\nChoice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                    case 1:
                        cout << "Old description: " << oldDesc << "\nNew: ";
                        getline(cin, oldDesc);
                        break;
                    case 2:
                        cout << "Old deadline: " << oldDeadline << "\nNew: ";
                        getline(cin, oldDeadline);
                        break;
                    case 3:
                        cout << "Old priority: " << oldPriority << "\nNew [1–5]: ";
                        cin >> oldPriority;
                        while (oldPriority < 1 || oldPriority > 5) {
                            cout << "Invalid! Enter priority [1–5]: ";
                            cin >> oldPriority;
                        }
                        break;
                    case 0:
                        editing = false;
                        break;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                }
            }

            // Rebuild updated line
            line = to_string(editID) + "*" + oldDesc + "*" + oldDeadline + "*" + to_string(oldPriority);
        }
        tasks.push_back(line);
    }

    file.close();

    if (!found) {
        cout << "Task with ID " << editID << " not found.\n";
        return;
    }

    file.open("tasks.txt", ios::out);
    for (auto &t : tasks) file << t << endl;
    file.close();

    cout << "Task updated successfully!\n";
}

void TaskManagement :: deleteTask() {
    int delID;
    cout << "Enter task ID to delete: ";
    cin >> delID;

    fstream file("tasks.txt", ios::in);
    if (!file.is_open() || file.peek() == EOF) {
        cout << "No tasks available.\n";
        return;
    }

    string line;
    vector<string> tasks;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find('*');
        if (pos == string::npos) continue;

        if (stoi(line.substr(0, pos)) == delID) {
            found = true; // skip this task
        } else {
            tasks.push_back(line); // keep other tasks
        }
    }

    file.close();

    if (!found) {
        cout << "Task with ID " << delID << " not found.\n";
        return;
    }

    // rewrite file without deleted task
    file.open("tasks.txt", ios::out);
    for (auto &t : tasks) file << t << endl;
    file.close();

    cout << "Task deleted successfully.\n";
}

void TaskManagement::showTasks() {

    file.open("tasks.txt", ios::in);
    if (!file.is_open() || file.peek() == EOF) {
        cout << "No tasks available.\n";
        file.close();
        return;
    }

    string ID,PR;
    getline(file, ID, '*');
    getline(file, description, '*');
    getline(file, deadline, '*');
    getline(file, PR, '\n');
    while (!file.eof()) {
        cout << "Task ID: " << ID << endl
             << "\t\tPriority: " << PR << endl
             << "\t\tDescription: " << description << endl
             << "\t\tDeadline: " << deadline << endl;

        getline(file, ID, '*');
        getline(file, description, '*');
        getline(file, deadline, '*');
        getline(file, PR, '\n');
    }
    file.close();
}


void TaskManagement::searchTask() {
    string searchID;
    cout << "Enter task ID to search: ";
    cin >> searchID;

    file.open("tasks.txt", ios::in);
    if (!file.is_open() || file.peek() == EOF) {
        cout << "No tasks available.\n";
        return;
    }

    bool found = false;
    string ID, priority;

    while (getline(file, ID, '*') &&
           getline(file, description, '*') &&
           getline(file, deadline, '*') &&
           getline(file, priority))
    {
        if (searchID == ID) {
            cout << "\nTask ID: " << ID << endl
                 << "\t\tPriority: " << priority << endl
                 << "\t\tDescription: " << description << endl
                 << "\t\tDeadline: " << deadline << endl;
            found = true;
            break;
        }
    } file.close();

    if (!found) {
        cout << "Task NOT found!\n";
    }
}

void TaskManagement :: Tasks() {

    int choice;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "~           TASKS          ~\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Show Tasks\n";
        cout << "2. Search Tasks\n";
        cout << "3. Manage Tasks\n";
        cout << "0. Return\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: tsk.showTasks();
                break;
            case 2: tsk.searchTask();
                break;
            case 3: tsk.manageTask();
                break;
            case 0: cout << "\033[1;33mReturning...\033[0m";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void TaskManagement :: manageTask() {

    char choice;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "~        MANAGE TASKS      ~\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Add Task\n";
        cout << "2. Edit Task\n";
        cout << "3. Delete Task\n";
        cout << "0. Return\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': tsk.addTask();
                break;
            case '2': tsk.editTask();
                break;
            case '3': tsk.deleteTask();
                break;
            case '0': cout << "\033[\n1;33mReturning...\033\n[0m";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != '0');
}

void timer() {
    int hlim, mlim;
    char choice;

    do {
        cout << "\n\033[1;36m--- Countdown Timer Menu ---\033[0m\n"
             << "1. 25 minutes (Recommended)\n"
             << "2. Choose your own time\n"
             << "0. Return\n"
             << "Choice [0-2]: ";
        cin >> choice;

        if (choice == '1'){
            hlim = 0;
            mlim = 25;
            countDown(hlim, mlim);
        }else if (choice == '2'){
            cout << "Input hour limit: ";
            cin >> hlim;

            do {
                cout << "Input minute limit: ";
                cin >> mlim;
                if (mlim > 59) {
                    cout << "\033[1;31mInvalid Input!!!\033[0m" << endl;
                }
            }while (mlim > 59);
            countDown(hlim, mlim);

        }else if (choice == '0'){
            cout << "\033[1;33mExiting the Timer...\033[0m" << endl;
            break;
        }else{
            cout <<  "\033[1;31mInvalid Input!!!\033[0m" << endl;
        }
    }while (true);
}

void countDown(int hlim, int mlim) {
    bool paused = false;
    for (int i = hlim; i >= 0; i-- ) {

        for (int j = ( i == hlim ? mlim: 59); j >=0; j--) {

            for (int l = (i == hlim && j == mlim ? 0 : 59); l >= 0; l-- ) {
                cout << "\r" << setfill('0') << setw(2) << i << ":"
                     << setfill('0') << setw(2) << j << ":"
                     << setfill('0') << setw(2) << l
                     << "  [p=pause, q=quit]" << flush;

                if (_kbhit()) {
                    char c = getch();

                    if (c == 'p') paused = true;
                    else if (c == 'r') paused = false;
                    else if (c == 'q') return;
                }

                while (paused) {
                    cout << "\rPaused... Press 'r' to resume or 'q' to quit." << flush;

                    if (_kbhit()) {
                        char c = getch();
                        if (c == 'r') paused = false;
                        if (c == 'q') return;
                    }
                }

                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }
    cout << "\n\033[1;32mDone!!!\033[0m" << '\a' << endl;
}

void Game1 ( ) {
    int num, guess;
    int tries=0;

    srand(time(NULL));
    num=(rand()%100)+1;

    cout<<"**********NUMBER GUESSING GAME**************\n";

    do{
    cout<<"Enter a number between (1-100) ";
    cin>>guess;
    tries++;

        if(guess > num)
            cout<<"Too high\n";
        else if(guess<num)
            cout<<"Too low\n";
        else
            cout<<"CORRECT! # OF TRIES: "<<tries<<"\n";

    }while( guess!=num);
}

void Game2() {
    char player, computer;

    player = getUserChoice();
    std::cout << "You choice: ";
    showChoice(player);

    computer = getComputerChoice();
    std::cout << "Computer's choice: ";
    showChoice(computer);

    chooseWinner(player, computer);
}

char getUserChoice(){

    char player;
    std::cout << "Rock-Paper-Scissors Game!\n";

    do{
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Choose one of the  following:\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "'r' for rock\n";
        cout << "'p' for paper\n";
        cout << "'s' for scissors\n";
        cin >> player;
    }while (player != 'r' && player != 'p' && player != 's');

    return player;
}

char getComputerChoice(){

    srand(time(0));
    int num = rand() % 3 + 1;

    switch(num){
        case 1: return 'r';
        case 2: return 'p';
        case 3: return 's';
        default: cout << "INVALID INPUT!!!\n Try Again!";
    }
    return 0;
}

void showChoice(char choice) {

    switch(choice){
        case 'r': std::cout << "Rock\n";
            break;
        case 'p': std::cout << "Paper\n";
            break;
        case 's': std::cout << "Scissors\n";
            break;
    }

}

void chooseWinner(char player, char computer) {

    switch(player){
        case 'r':   if(computer == 'r'){
                        cout << "It's a tie!\n";
                    }else if(computer == 'p') {
                        cout << "You lose!\n";
                    }else{
                        cout << "You win!\n";
                    }break;

        case 'p':   if(computer == 'r'){
                        cout << "You win!\n";
                    }else if(computer == 'p') {
                        cout << "It's a tie!\n";
                    }else{
                        cout << "You lose!\n";
                    }break;

        case 's':   if(computer == 'r'){
                        cout << "You lose!\n";
                    }else if(computer == 'p') {
                        cout << "You win!\n";
                    }else{
                        cout << "It's a tie!\n";
                    }break;
    }
}

void game1Menu() {
        int choice;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "~      Guess the number    ~\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Start the game 1\n";
        cout << "0. Return\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: Game1();
                break;
            case 0: cout << "\033[\n1;33mReturning...\033\n[0m";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void game2Menu() {
    int choice;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "~    Rock-paper-scissors   ~\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Start the game 1\n";
        cout << "0. Return\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: Game2();
                break;
            case 0: cout << "\033[\n1;33mReturning...\033\n[0m";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void GameMenu() {
    int choice;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "~          Game Menu       ~\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "1. Game 1\n";
        cout << "2. Game 2\n";
        cout << "0. Return\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: game1Menu();
                break;
            case 2: game2Menu();
                break;
            case 0: cout << "\033[1;33mReturning...\033[0m";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}