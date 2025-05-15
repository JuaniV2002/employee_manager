# Employee Manager

This **C** program allows you to manage a list of **employee surnames**. It's ideal for small HR systems, academic exercises, or any situation where surname tracking is required.

## Features

- **_Alta de empleado_ (Register employee):** Adds a new surname to the list.
- **_Baja de empleado_ (Delete employee):** Removes a surname from the list, with confirmation.
- **_Modificar empleado_ (Modify employee):** Modifies a surname, with input validation.
- **_Listar_ (List surnames):** Displays all current surnames with index numbers.
- **_Buscar empleado_ (Search):** Finds the position of a given surname.
- **_Guardar en archivo_ (Save to file):** Saves all surnames to a plain text file.
- **_Carga automática_ (Auto-load):** Automatically loads existing surnames at program startup from file.

## Improvements

- ✅ Input validation: only allows surnames with letters and spaces, up to 30 characters.
- ✅ Cleans newline and carriage return characters (compatible with macOS/Linux terminals).
- ✅ Index shown on listing for easy reference.
- ✅ Prevents duplicate entries (`eliminarRepetidos`).
- ✅ Safe input handling (`fgets` + length validation).
- ✅ Handles unexpected EOF or invalid input (e.g. `Ctrl+D`) gracefully.

## Getting Started

To give this program a try on **Linux**:

```bash
sudo apt update
sudo apt install build-essential
```
or if you are on mac using homebrew:
  
```bash
brew update
brew install gcc
```
Verify the compiler is available:
  
```bash
gcc --version
```

## Compile the program:
  
```bash
gcc -o employee employee.c
```

## Run the program:
  
```bash
./employee
```