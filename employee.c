#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 1001
#define LMAX 31

typedef struct data {
    char arreglo[NMAX][LMAX];
    int cant;
} TData;

// Perfil de las funciones y acciones
bool vacia(TData *data);  // Devuelve true si la lista de apellidos está vacía.
bool llena(TData *data);  // Devuelve true si la lista de apellidos está llena. 
void insertar(TData *data, char apellido[LMAX]);  // Inserta un nuevo apellido a la lista.
void suprimir(TData *data, char apellido[LMAX]);  // Elimina un apellido de la lista.
void modificar(TData *data, char apellido[LMAX]);  // Modifica el antiguo apellido por el nuevo apellido.
void mostrar(TData *data);  // Muestra todos los apellidos guardados en la lista.
int encontrar(TData *data, char apellido[LMAX]);  // Devuelve la ubicación de un apellido en la lista.
bool repetidos(char apellido1[LMAX], char apellido2[LMAX]);  // Devuelve verdadero si dos apellidos están repetidos en la lista.
void eliminarRepetidos(TData *data);  // Elimina apellidos repetidos.

// Perfil de las acciones ejecutadas en cada caso del switch.
void opcion1(TData *data);
void opcion2(TData *data);
void opcion3(TData *data);
void opcion4(TData *data);
void opcion5(TData *data);

int main() {
    int opcion;
    TData data;
    data.cant = 0;

    do {
        printf("\n-----------------------------------\n");
        printf("Alta de empleado (1)\n");
        printf("Baja de empleado (2)\n");
        printf("Modificar datos de empleado (3)\n");
        printf("Listar (4)\n");
        printf("Buscar un empleado (5)\n");
        printf("Salir (6)\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opción: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &opcion);
        fflush(stdin);

        // Sentencia switch que interpretará la opción elegida por el usuario.
        switch (opcion) {
            case 1:
                opcion1(&data);    
                break;
            case 2:
                opcion2(&data);
                break;
            case 3:
                opcion3(&data);
                break;
            case 4: 
                opcion4(&data);
                break;
            case 5:
                opcion5(&data);
                break;
            case 6:
                return 0;
            default:  // 'opcion' no está entre 1 y 6.
                printf("\nOpción inválida.\n");
                break;
        }
    } while (1); 
}

// Cuerpo de las funciones y acciones.
bool vacia(TData *data) {
    return data->cant == 0;
}

bool llena(TData *data) {
    return data->cant == NMAX;
}

void insertar(TData *data, char apellido[LMAX]) {
    if (llena(data)) {
        printf("Error: No hay espacio para más apellidos.\n");
        return;
    }
    strncpy(data->arreglo[data->cant], apellido, LMAX - 1);
    data->arreglo[data->cant][LMAX - 1] = '\0';
    printf("\nEl apellido '%s' fue registrado exitosamente.\n", apellido);
    data->cant++; 
}

void suprimir(TData *data, char apellido[LMAX]) {
    int index = encontrar(data, apellido);
    if (index == -1) {
        printf("Error: El apellido '%s' no se encontró.\n", apellido);
        return;
    }
    for (int j = index; j < data->cant - 1; j++) {
        strcpy(data->arreglo[j], data->arreglo[j + 1]);
    }
    printf("\nEl apellido '%s' fue dado de baja exitosamente.\n", apellido); 
    data->cant--;
}

void modificar(TData *data, char apellido[LMAX]) {
    int index = encontrar(data, apellido);
    if (index == -1) {
        printf("Error: El apellido '%s' no se encontró.\n", apellido);
        return;
    }
    char apellidoM[LMAX];
    printf("\nIngrese apellido modificado: ");
    scanf(" %[^\n]s", apellidoM);
    strncpy(data->arreglo[index], apellidoM, LMAX - 1);
    data->arreglo[index][LMAX - 1] = '\0';
    printf("\nSe ha modificado '%s' por '%s' exitosamente.\n", apellido, apellidoM);
}

void mostrar(TData *data) {
    if (vacia(data)) {
        printf("No hay apellidos para mostrar.\n");
        return;
    }
    printf("\nApellidos:\n"); 
    for (int i = 0; i < data->cant; i++) {
        printf("- %s\n", data->arreglo[i]);
    }
}

int encontrar(TData *data, char apellido[LMAX]) {
    if (vacia(data)) {
        printf("No hay apellidos para buscar.\n");
        return -1;
    }
    for (int i = 0; i < data->cant; i++) {
        if (strcmp(data->arreglo[i], apellido) == 0) {
            return i;
        }
    }
    return -1;
}

bool repetidos(char apellido1[LMAX], char apellido2[LMAX]) {
    return strcmp(apellido1, apellido2) == 0;
}

void eliminarRepetidos(TData *data) {
    for (int i = 0; i < data->cant; i++) { 
        for (int j = i + 1; j < data->cant; j++) {
            if (repetidos(data->arreglo[i], data->arreglo[j])) {
                printf("\nEl apellido '%s' ya existe, se eliminará la primera ocurrencia del mismo.\n", data->arreglo[i]);
                suprimir(data, data->arreglo[i]);
                j--;  // Decrementar j para compensar el elemento eliminado
            }
        }
    }
}

// Acciones ejecutadas en cada caso del switch.
void opcion1(TData *data) {
    char apellido[LMAX];
    if (llena(data)) {
        printf("\nNo se pueden añadir más empleados.\n");
    } else {
        do {
            printf("\nIngrese el apellido (máximo: 30 caracteres) del nuevo empleado (no pueden haber dos apellidos iguales): ");
            fflush(stdin);
            scanf(" %[^\n]%*c", apellido);
            if (strlen(apellido) >= LMAX) {
                printf("\nEl apellido debe tener como máximo 30 caracteres.\n");
            }
        } while (strlen(apellido) >= LMAX);
        insertar(data, apellido);
        eliminarRepetidos(data);
    }
}

void opcion2(TData *data) {
    char apellido[LMAX];
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
    } else {
        do {
            printf("\nIngrese el apellido (máximo: 30 caracteres) del empleado a dar de baja: ");
            scanf(" %[^\n]s", apellido);
            if (strlen(apellido) >= LMAX) {
                printf("\nEl apellido debe tener como máximo 30 caracteres.\n");
            }
        } while (strlen(apellido) >= LMAX);
        if (encontrar(data, apellido) != -1) {
            suprimir(data, apellido); 
        } else {
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        }
    }
}

void opcion3(TData *data) {
    char apellido[LMAX];
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
    } else {
        do {
            printf("\nIngrese el apellido (máximo: 30 caracteres) del empleado a modificar: ");
            scanf(" %[^\n]s", apellido);
            if (strlen(apellido) >= LMAX) {
                printf("\nEl apellido debe tener como máximo 30 caracteres.\n");
            }
        } while (strlen(apellido) >= LMAX);
        if (encontrar(data, apellido) != -1) {
            modificar(data, apellido);
        } else {
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        }
        eliminarRepetidos(data);   
    }
}

void opcion4(TData *data) {
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
    } else {
        mostrar(data);
    }
}

void opcion5(TData *data) {
    char apellido[LMAX];
    int pos;
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
    } else {
        do {
            printf("\nIngrese el apellido (máximo: 30 caracteres) del empleado a buscar: ");
            scanf(" %[^\n]s", apellido);
            if (strlen(apellido) >= LMAX) {
                printf("\nEl apellido debe tener como máximo 30 caracteres.\n");
            }
        } while (strlen(apellido) >= LMAX);
        pos = encontrar(data, apellido);
        if (pos != -1) {
            printf("\nEl apellido '%s' se encuentra en la posición %d.\n", apellido, pos);
        } else {
            printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
        } 
    }
}
