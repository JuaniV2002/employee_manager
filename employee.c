#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 1001
#define LMAX 31
#define MAX_APELLIDOS 100

typedef struct data{
    char arreglo[NMAX][LMAX];
    int cant;
}TData;

//perfil de las funciones y acciones
bool vacia(TData* data);  // devuelve true si la lista de apellidos esta vacia.
bool llena(TData* data);  // devuelve true si la lista de apellidos esta llena. 
void insertar(TData* data, char apellido[LMAX]);  // inserta un nuevo apellido a la lista.
void suprimir(TData* data, char apellido[LMAX]);  // elimina un apellido de la lista.
void modificar(TData* data, char apellido[LMAX]);  // dado un apellido, modifica el antiguo apellido por el nuevo apellido.
void mostrar(TData* data);  // muestra todos los apellidos guardados en la lista.
int encontrar(TData* data, char apellido[LMAX]);  // dado un apellido, devuelve su ubicacion en la lista.
bool repetidos(char apellido1[LMAX], char apellido2[LMAX]);  // si dos apellidos esta repetidos en la lista, devuelve verdadero.
void eliminarRepetidos();  // accion que se encargara de elminar apellidos repetidos.

// perfil de las acciones que seran ejectudas en cada case del switch.
void opcion1();
void opcion2();
void opcion3();
void opcion4();
void opcion5();

int main() {
    int opcion;

    do{
        // esto se repetira cada vez que el usuario ingrese al programa o que se termine de correr un comando (1-5).
        printf("\n-----------------------------------\n");
        printf("Alta de empleado (1)\n");
        printf("Baja de empleado (2)\n");
        printf("Modificar datos de empleado (3)\n");
        printf("Listar (4)\n");
        printf("Buscar un empleado (5)\n");
        printf("Salir (6)\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opcion: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &opcion);
        fflush(stdin);

        // sentencia switch que interpretara la opcion elegida por el usuario.
        switch (opcion){
            case 1:
                opcion1();    
                break;

            case 2:
                opcion2();
                break;

            case 3:
                opcion3();
                break;

            case 4: 
                opcion4();
                break;

            case 5:
                opcion5();
                break;

            case 6:
                return 0;
                break;

            default: // 'opcion' no esta entre 1 y 6.
                printf("\nOpcion invalida.\n");
                break;
        }
    } while (1); 
}

// cuerpo de las funciones y acciones.
bool vacia(TData* data){
    // si la cantidad de elementos del arreglo es 0, devuelve verdadero.
    if ((*data).cant == 0){
        return true;
    }else{
        return false;
    }
}

bool llena(TData* data){
    // si la cantidad de elementos del arrelgo es igual a NMAX, devuelve verdadero.
    if ((*data).cant == NMAX){
        return true;
    }else{
        return false;
    }
}

void insertar(TData* data, char apellido[LMAX]){
    // Verificar si data es NULL
    if (data == NULL) {
        printf("Error: data es NULL.\n");
        return;
    }

    // Verificar si hay espacio para un nuevo apellido
    if ((*data).cant >= MAX_APELLIDOS) {
        printf("Error: No hay espacio para más apellidos.\n");
        return;
    }

    // Copiar el apellido al arreglo
    strncpy((*data).arreglo[(*data).cant], apellido, LMAX - 1);

    // Asegurarse de que la cadena esté terminada correctamente
    (*data).arreglo[(*data).cant][LMAX - 1] = '\0';

    printf("\nEl apellido '%s' fue registrado exitosamente.\n", apellido);
    (*data).cant++; 
}

void suprimir(TData* data, char apellido[LMAX]){
    // Verificar si data es NULL
    if (data == NULL) {
        printf("Error: data es NULL.\n");
        return;
    }

    // Encontrar el apellido en el arreglo
    int index = encontrar(data, apellido);

    // Verificar si el apellido se encontró
    if (index == -1) {
        printf("Error: El apellido '%s' no se encontró.\n", apellido);
        return;
    }

    // Mover un lugar para atrás todos los apellidos, pisando el apellido que quería borrar
    for (int j = index; j < (*data).cant - 1; j++){
        strcpy((*data).arreglo[j], (*data).arreglo[j + 1]);
    }

    printf("\nEl apellido '%s' fue dado de baja exitosamente.\n", apellido); 
    (*data).cant--;  // Decrementar el campo 'cant' del registro porque eliminé un apellido
}

void modificar(TData* data, char apellido[LMAX]){
    char apellidoM[LMAX];
    
    printf("\nIngrese apellido modificado: ");
    scanf(" %[^\n]s", apellidoM);
    // usando Encontrar(), encuentro el indice en donde se encuentra el apellido a modificar
    strcpy((*data).arreglo[encontrar(data, apellido)], apellidoM);
    printf("\nSe ha modificado '%s' por '%s' exitosamente.\n", apellido, apellidoM);
}

void mostrar(TData* data){
    // recorro el arreglo mostrando cada apellido.
    printf("\nApellidos:\n"); 
    for (int i = 0; i < (*data).cant; i++){
        printf("- %s\n", (*data).arreglo[i]);
    }
}

int encontrar(TData* data, char apellido[LMAX]){

    // recorro el arreglo chequeando si el apellido en el lugar 'i' del arreglo es igual que el que estoy buscando.
    for (int i = 0; i < (*data).cant; i++){
        if(strcmp((*data).arreglo[i], apellido) == 0){
            return i;  //si lo encontre, devuelvo el indice en donde se encuetra dicho apellido.
        }
    }
    // si no lo encontre, devuelvo un codigo de error.
    return -1;
}

bool repetidos(char apellido1[LMAX], char apellido2[LMAX]){
    // si ambos apellidos son iguales, devuelvo verdadero.
    if (strcmp(apellido1, apellido2) == 0){
        return true;
    }else{
        return false;
    }
}

void eliminarRepetidos(){
    TData data;
    char apellido[LMAX];

    for (int i = 0; i < data.cant; i++){ 
        for (int j = 0; j < data.cant; j++){
            if (repetidos(data.arreglo[i],data.arreglo[j]) && (i != j)){
                printf("\nEl apellido '%s' ya existe, se eliminara la primera ocurrencia del mismo.\n", apellido);
                suprimir(&data,data.arreglo[i]);
            }
        }
    }
}

// acciones que son ejecutadas en cada caso del switch.
void opcion1(){
    TData data;
    char apellido[LMAX];

    if (llena(&data) == true){
        printf("\nNo se pueden añadir mas empleados.\n");
    }else{
        // si la lista no esta llena, leo el apellido ingresado.
        do{
            // ciclo que asegura que la entrada del apellido es de menos de 30 caracteres.
            printf("\nIngrese el apellido (maximo: 30 caracteres) del nuevo empleado (no pueden haber dos apellidos iguales): ");
            fflush(stdin);
            scanf(" %[^\n]%*c", apellido);
            if (strlen(apellido) > LMAX){
                printf("\nEl apellido debe tener como maximo 30 caracteres.\n");
            }
        } while (strlen(apellido) > LMAX);
        insertar(&data, apellido);
        eliminarRepetidos();
    }
}

void opcion2(){
    TData data;
    char apellido[LMAX];

    if (vacia(&data) == true){
        printf("\nNo hay apellidos en la lista.\n");
    }else{
        // si la lista no esta vacia, leo el apellido ingresado.
        do{
            // ciclo que asegura que la entrada del apellido es de menos de 30 caracteres.
            printf("\nIngrese el apellido (maximo: 30 caracteres) del empleado a dar de baja: ");
            scanf(" %[^\n]s", apellido);
            if (strlen(apellido) > LMAX){
                printf("\nEl apellido debe tener como maximo 30 caracteres.\n");
            }
        } while (strlen(apellido) > LMAX);
        // verifico que el apellido existe usando la funcion Encontrar().
        if (encontrar(&data, apellido) != -1){
            suprimir(&data, apellido); 
        }else{
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        }
    }
}

void opcion3(){
    TData data;
    char apellido[LMAX];

    if (vacia(&data) == true){
        printf("\nNo hay apellidos en la lista.\n");
    }else{
        // si la lista no esta vacia, leo el apellido a modificar.
        do{
            // ciclo que asegura que la entrada del apellido es de menos de 30 caracteres.
            printf("\nIngrese el apellido (maximo: 30 caracteres) del empleado a modificar: ");
            scanf(" %[^\n]s", apellido);
            if (strlen(apellido) > LMAX){
                printf("\nEl apellido debe tener como maximo 30 caracteres.\n");
            }
        } while (strlen(apellido) > LMAX);
        // verifico que el apellido existe usando la funcion Encontrar().
        if (encontrar(&data, apellido) != -1){
            modificar(&data, apellido);
        }else{
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        }
        eliminarRepetidos();   
    }
}

void opcion4(){
    TData data;

    if (vacia(&data) == true){
        printf("\nNo hay apellidos en la lista.\n");
    }else{
        // muestro los apellidos si la lista tiene al menos un apellido guardado.
        mostrar(&data);
    }
}

void opcion5(){
    TData data;
    char apellido[LMAX];
    

    if (vacia(&data) == true){
        printf("\nNo hay apellidos en la lista.\n");
    }else{
        do{
            // ciclo que asegura que la entrada del apellido es de menos de 30 caracteres.
            printf("\nIngrese el apellido (maximo: 30 caracteres) del empleado a buscar: ");
            scanf(" %[^\n]s", apellido);
            if (strlen(apellido) > LMAX){
                printf("\nEl apellido debe tener como maximo 30 caracteres.\n");
            }
        } while (strlen(apellido) > LMAX);
        // verifico que el apellido existe usando la funcion Encontrar().
        if (encontrar(&data, apellido) != -1){
            printf("\nEl apellido '%s' se encuentra en la posicion %d.\n", apellido, encontrar(&data, apellido));
        }else{
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        } 
    }
}
