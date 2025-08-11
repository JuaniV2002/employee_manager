# Employee Manager (English UI)

This C program manages a list of employee surnames. The codebase and all prompts are in English. It uses a simple CSV format and auto-loads data from `employee.csv`.

## Features

- Add employee
- Remove employee (with confirmation)
- Modify employee surname (with validation)
- List surnames (with indexes)
- Search a surname (shows position)
- Save to file
- Auto-load on startup from CSV
 
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

Storage format:
- CSV file: `employee.csv` with a header line `surname` and one surname per row.

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

Sample data:
- `employee.csv` is included with 10 sample surnames so you can test immediately.

Menu options:
1. Add employee
2. Remove employee
3. Modify employee surname
4. List employees
5. Search surname (exact)
6. Find by substring
7. Sort surnames (A-Z)
8. Save to CSV
9. Save to CSV as...
10. Exit
```