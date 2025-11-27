# Time Management System (C++)

A **menu-based Time Management System** built in C++ that helps users manage tasks, take breaks with games, and use a timer. The system stores tasks in a text file and provides options to add, edit, delete, and view tasks.

---

## Key Features

- **Task Management**
  - Add, edit, delete, and view tasks.
  - Tasks include a description, deadline, and priority level (1–5).
  - Tasks are stored in `tasks.txt`.

- **Break Games**
  - Includes simple games to help users take a break.

- **Timer**
  - A countdown timer for productivity sessions.

- **User-Friendly Menu**
  - Intuitive menu-based navigation for all features.

---

## Program Workflow

```mermaid
flowchart TD

A[Start Program] --> B[Load Tasks from tasks.txt]
B --> C[Show Main Menu]

C --> D1[1. Manage Tasks]
C --> D2[2. Take a Break]
C --> D3[3. Timer]
C --> D4[0. Save and Exit]

D1 --> E1[Add Task]
D1 --> E2[Edit Task]
D1 --> E3[Delete Task]
D1 --> E4[View Tasks]
E1 --> C
E2 --> C
E3 --> C
E4 --> C

D2 --> F1[Game 1]
D2 --> F2[Game 2]
F1 --> C
F2 --> C

D3 --> G[Start Timer]
G --> C

D4 --> Z[End Program]
```

---

## How to Run

1. **Compile the Code**
   ```bash
   g++ main.cpp -o time_management
   ```

2. **Run the Executable**
   ```bash
   ./time_management
   ```

---

## Example Console Output

```plaintext
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~  TIME MANAGEMENT SYSTEM  ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Tasks
2. Take a little break
3. Timer
0. Save and Exit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Enter your choice: 
```

---

## Data File Structure

### tasks.txt:
```makefile
ID: 1
Description: Complete project report
Deadline: 2025-12-01
Priority: 5
--------------------------------------------------
```

---

## Detailed Features

### Task Management
- **Add Task**: Users can add tasks with a description, deadline, and priority level.
- **Edit Task**: Modify existing tasks by updating their details.
- **Delete Task**: Remove tasks by their unique ID.
- **View Tasks**: Display all tasks in a structured format.

### Break Games
- **Game 1**: A simple game to refresh the mind.
- **Game 2**: Another engaging game for relaxation.

### Timer
- Set a countdown timer for productivity sessions.
- Helps users focus on tasks for a set duration.

---

## Program Logic

### Task Management Logic
```mermaid
flowchart LR
A[Add Task] --> B[Enter Description]
B --> C[Enter Deadline]
C --> D[Enter Priority]
D --> E[Generate Unique Task ID]
E --> F[Save to tasks.txt]
F --> G[Task Added Successfully]
```

### Timer Logic
```mermaid
flowchart LR
A[Start Timer] --> B[Enter Duration]
B --> C[Countdown Begins]
C --> D[Time's Up!]
```

### Break Games Logic
```mermaid
flowchart LR
A[Choose Game] --> B[Game 1]
A --> C[Game 2]
B --> D[Play Game 1]
C --> E[Play Game 2]
D --> F[Return to Main Menu]
E --> F
```

---

## Menu Overview

```plaintext
1. Manage Tasks
2. Take a Break
3. Timer
0. Save and Exit
```

---

## Example Task Addition

```plaintext
Enter task description: Complete project report
Enter deadline: 2025-12-01
Enter priority [1-5]: 5
Task added successfully!
```

---

## Future Improvements

- Add more games for breaks.
- Enhance the task management system with categories and reminders.
- Implement a graphical user interface (GUI).
- Add support for recurring tasks and notifications.
- Integrate with calendar applications for better scheduling.

---

## Quick Info

The <ins>project</ins> is done by ***Shokhjakhon Toshpolatov*** as part of a learning exercise for C++ programming. It demonstrates the use of file handling, classes, and menu-driven programs. The project was completed on **November 27, 2025**.
