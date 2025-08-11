# Employee Manager (English UI)

This C program manages a list of employee surnames. The codebase and all prompts are now in English. It auto-loads data from `employees.txt` (or legacy `empleados.txt`) and lets you add, remove, modify, search, and list surnames.

## Features

- Add employee
- Remove employee (with confirmation)
- Modify employee surname (with validation)
- List surnames (with indexes)
- Search a surname (shows position)
- Save to file
- Auto-load on startup (from file)
 
New user-facing enhancements:
- Case-insensitive exact search with normalized title-casing
- Substring search (case-insensitive)
- Sort surnames A–Z
- Save As… to choose a filename
- Unsaved changes prompt on exit

## Improvements

- Input validation: only letters and spaces, up to 30 characters
- Cleans newline and carriage return characters (macOS/Linux friendly)
- Index shown for easy reference
- Prevents duplicate entries
- Safe input handling (`fgets` + length validation)
- Handles unexpected EOF or invalid input (e.g. `Ctrl+D`) gracefully

Backward compatibility: on startup it tries `employees.txt`, then falls back to `empleados.txt` if present.

## Getting Started

To try this program on macOS or Linux:

```bash
sudo apt update
sudo apt install build-essential
```
On macOS (Homebrew):

```bash
brew update
brew install gcc
gcc --version
```

## Compile the program:
  
```bash
gcc -o employee employee.c
```

## Run the program:
  
```bash
./employee

Menu options:
1. Add employee
2. Remove employee
3. Modify employee surname
4. List employees
5. Search surname (exact)
6. Find by substring
7. Sort surnames (A-Z)
8. Save to file
9. Save to file as...
10. Exit
```