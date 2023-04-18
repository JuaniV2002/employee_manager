#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 1001
#define LMAX 31

typedef struct data{
    char arreglo[NMAX][LMAX];
    int cant;
}TData;

TData data;
char apellido[LMAX];

//perfil de las funciones y acciones
bool Vacia(TData* data);  // devuelve true si la lista de apellidos esta vacia.
bool Llena(TData* data);  // devuelve true si la lista de apellidos esta llena. 
void Insertar(TData* data, char apellido[LMAX]);  // inserta un nuevo apellido a la lista.
void Suprimir(TData* data, char apellido[LMAX]);  // elimina un apellido de la lista.
void Modificar(TData* data, char apellido[LMAX]);  // dado un apellido, modifica el antiguo apellido por el nuevo apellido.
void Mostrar(TData* data);  // muestra todos los apellidos guardados en la lista.
int Encontrar(TData* data, char apellido[LMAX]);  // dado un apellido, devuelve su ubicacion en la lista.
bool Repetidos(char apellido1[LMAX], char apellido2[LMAX]);  // si dos apellidos esta repetidos en la lista, devuelve verdadero.
void EliminarRepetidos();  // accion que se encargara de elminar apellidos repetidos.

// perfil de las acciones que seran ejectudas en cada case del switch.
void Opcion1();
void Opcion2();
void Opcion3();
void Opcion4();
void Opcion5();

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
                Opcion1();    
                break;

            case 2:
                Opcion2();
                break;

            case 3:
                Opcion3();
                break;

            case 4: 
                Opcion4();
                break;

            case 5:
                Opcion5();
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
bool Vacia(TData* data){
    // si la cantidad de elementos del arreglo es 0, devuelve verdadero.
    if ((*data).cant == 0){
        return true;
    }else{
        return false;
    }
}

bool Llena(TData* data){
    // si la cantidad de elementos del arrelgo es igual a NMAX, devuelve verdadero.
    if ((*data).cant == NMAX){
        return true;
    }else{
        return false;
    }
}

void Insertar(TData* data, char apellido[LMAX]){
    // inserto el apellido ingresado por el usuario en el lugar correcto.
    strcpy((*data).arreglo[(*data).cant], apellido);
    printf("\nEl apellido '%s' fue registrado exitosamente.\n", apellido);
    (*data).cant++; 
}

void Suprimir(TData* data,char apellido[LMAX]){
    // muevo un lugar para atras todos los apellidos, pisando el apellido que queria borrar.
    for (int j = Encontrar(data,apellido); j < (*data).cant; j++){
        strcpy((*data).arreglo[j], (*data).arreglo[j + 1]);
    }
    printf("\nEl apellido '%s' fue dado de baja exitosamente.\n", apellido); 
    (*data).cant--;  // decremento el campo 'cant' del registro porque elimine un apellido.
}

void Modificar(TData* data, char apellido[LMAX]){
    char apellidoM[LMAX];
    
    printf("\nIngrese apellido modificado: ");
    scanf(" %[^\n]s", apellidoM);
    // usando Encontrar(), encuentro el indice en donde se encuentra el apellido a modificar
    strcpy((*data).arreglo[Encontrar(data, apellido)], apellidoM);
    printf("\nSe ha modificado '%s' por '%s' exitosamente.\n", apellido, apellidoM);
}

void Mostrar(TData* data){
    // recorro el arreglo mostrando cada apellido.
    printf("\nApellidos:\n"); 
    for (int i = 0; i < (*data).cant; i++){
        printf("- %s\n", (*data).arreglo[i]);
    }
}

int Encontrar(TData* data, char apellido[LMAX]){
    // recorro el arreglo chequeando si el apellido en el lugar 'i' del arreglo es igual que el que estoy buscando.
    for (int i = 0; i < (*data).cant; i++){
        if(strcmp((*data).arreglo[i], apellido) == 0){
            return i;  //si lo encontre, devuelvo el indice en donde se encuetra dicho apellido.
        }
    }
    // si no lo encontre, devuelvo un codigo de error.
    return -1;
}

bool Repetidos(char apellido1[LMAX], char apellido2[LMAX]){
    // si ambos apellidos son iguales, devuelvo verdadero.
    if (strcmp(apellido1, apellido2) == 0){
        return true;
    }else{
        return false;
    }
}

void EliminarRepetidos(){
    for (int i = 0; i < data.cant; i++){ 
        for (int j = 0; j < data.cant; j++){
            if (Repetidos(data.arreglo[i],data.arreglo[j]) && (i != j)){
                printf("\nEl apellido '%s' ya existe, se eliminara la primera ocurrencia del mismo.\n", apellido);
                Suprimir(&data,data.arreglo[i]);
            }
        }
    }
}

// acciones que son ejecutadas en cada caso del switch.
void Opcion1(){
    if (Llena(&data) == true){
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
        Insertar(&data, apellido);
        EliminarRepetidos();
    }
}

void Opcion2(){
    if (Vacia(&data) == true){
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
        if (Encontrar(&data, apellido) != -1){
            Suprimir(&data, apellido); 
        }else{
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        }
    }
}

void Opcion3(){
    if (Vacia(&data) == true){
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
        if (Encontrar(&data, apellido) != -1){
            Modificar(&data, apellido);
        }else{
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        }
        EliminarRepetidos();   
    }
}

void Opcion4(){
    if (Vacia(&data) == true){
        printf("\nNo hay apellidos en la lista.\n");
    }else{
        // muestro los apellidos si la lista tiene al menos un apellido guardado.
        Mostrar(&data);
    }
}

void Opcion5(){
    if (Vacia(&data) == true){
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
        if (Encontrar(&data, apellido) != -1){
            printf("\nEl apellido '%s' se encuentra en la posicion %d.\n", apellido, Encontrar(&data, apellido));
        }else{
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        } 
    }
}
