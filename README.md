# C-ToDo

A simple, reliable, JSON-powered terminal To-Do application written in pure C, using cJSON for serialization and deserialization.

C-ToDo demonstrates working with dynamic memory, file I/O, JSON parsing, structs, signals, and a modular C codebase — making it a great portfolio project that shows comfort with low-level programming.

## 🚀 Features

✔️ **Add new tasks**

Each task contains:
- A unique random ID
- Description
- Priority (1–5)
- Creation timestamp
- Last updated timestamp
- Completion status

✔️ **View tasks**

Prints all tasks in a readable format, including timestamps.

✔️ **JSON persistence**

Tasks are saved to and loaded from `todos.json` using the cJSON library.

✔️ **Mark tasks as complete**

Automatically updates the task's `updated_at` timestamp.

✔️ **Delete completed tasks**

Optionally remove a completed To-Do from the list.

✔️ **Safe exit**

- Exiting through menu → tasks are fully saved
- Exiting via CTRL + C → app warns the user and exits without saving, preventing accidental overwrites

## 🧱 Project Structure

```
/C-ToDo
├── main.c              # Program entry and UI loop
├── todo.h              # Struct definitions and headers
├── todo_json.c         # JSON handling, CRUD operations, memory mgmt
├── cJSON.c / .h        # cJSON library
├── todos.json          # Auto-generated save file
└── README.md
```

## 📦 Requirements

**Build dependencies**
- GCC or Clang
- cJSON (included or linked manually)

**Run**
```
./main
```

## 🔧 Compiling

Example using GCC:

```bash
gcc main.c todo_json.c cJSON.c -o main
```

If your project files differ, adjust accordingly.

## 📁 JSON Structure

A saved `todos.json` file looks like:

```json
[
  {
    "id": 123456,
    "description": "Buy groceries",
    "priority": 3,
    "isComplete": false,
    "created_at": 1730000000,
    "updated_at": 1730000000
  }
]
```

## 🧠 What This Project Demonstrates

This app showcases core C concepts:

- Dynamic arrays using `malloc()` / `realloc()`
- Manual memory management
- Using structs as objects
- Mapping structs to/from JSON
- Modular header + implementation files
- Parsing and printing JSON
- File I/O and persistence
- Handling SIGINT (CTRL+C) safely
- CLI user interface design

## 📄 Planned Improvements (Future Work)

Optional ideas if you want to expand:

- Edit/rename tasks
- Sorting by priority or creation date
- Color-coded terminal output
- More robust ID generation
- Filtering completed vs. active tasks
- Export to human-readable `.txt` format
- Unit tests (e.g., using CMocka)

## 🎉 Author

**Ty Strong**  
A C project built between tickets at work ;D
IT Consultatnt & Software Developer  
IKT Konsulent at Helse Vest IKT
