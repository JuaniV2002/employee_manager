# Employee management program
This **C** program will help you to manage your **employees** at your company. It can be run on the terminal, so everyone should be able to use it.   

It has 5 main commands:
- *Alta de empleado* (add an employee): Will add a new employee to the list.
- *Baja de empleado* (delete an employee): This command will delete the employee from the list.
- *Modificar datos de empleado* (modify employee data): It will allow you to modify the name of the employee on the list (it has to exist first).
- *Listar* (show employees): Will show all the employees which are on the list.
- *Encontrar empleado* (find an employee): This function will come in handy if you want to search an employee in the list.

To give this program a try on Linux:
- Install gcc with this command:
  ```
  sudo apt update
  sudo apt install build-essential
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
---

# Programa de manejo de empleados
Este programa en **C** te ayudara a administrar tus **empleados** de tu compañia. Puede ser ejecutado en la terminal, por lo que todos pueden usarlo.

Tiene 5 comandos principales:
- *Alta de empleado*: Añade un nuevo empleado a la lista.
- *Baja de empleado*: Este comando eliminara el empleado de la lista.
- *Modificar datos de empleado*: Te permitira modificar el nombre del empleado en la lista (antes debe existir en la lista).
- *Listar*: Muestra todos los empleados registrados en la lista.
- *Encontrar empleado*: Esta funcion es util cuando quieras buscar un empleado en la lista.

Para probar este programa en Linux:
- Instalar gcc usando estos comandos:
  ```
  sudo apt update
  sudo apt install build-essential
  ```
- Revisar la version de gcc para verificar su correcta instalacion:
  ```
  gcc --version
  ```
- Compliar el programa:
  ```
  gcc -o employee employee.c
  ```
- Correr el programa:
  ```
  ./employee
  ```
