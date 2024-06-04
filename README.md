# Employee management program
This **C** program will help you to manage your **employees** at your company and save their data in a file.  

It has 6 main commands:
- *Alta de empleado* (add an employee): will add a new employee to the list.
- *Baja de empleado* (delete an employee): this command will delete the employee from the list.
- *Modificar datos de empleado* (modify employee data): it will allow you to modify the name of the employee on the list (it has to exist first).
- *Listar* (show employees): will show all the employees which are on the list.
- *Encontrar empleado* (find an employee): this function will come in handy if you want to search an employee in the list.
- *Guardar en archivo* (save in file): it will save the employees in a file.

To give this program a try on Linux:
- Install gcc with this command:
  ```
  sudo apt update
  sudo apt install build-essential
  ```
  or if you are on mac using Homebrew:
  ```
  brew update
  brew install gcc
  ```
- Check C compiler version to verify a successful installation:
  ```
  gcc --version
  ```
- Compile the program:
  ```
  gcc -o employee employee.c
  ```
- Run the program:
  ```
  ./employee
  ```
