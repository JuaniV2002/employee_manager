// Enhanced Employee Manager with EOF Handling and Robust Validation
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NMAX 1001
#define LMAX 31
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

typedef struct data {
    char arreglo[NMAX][LMAX];
    int cant;
} TData;

// Funciones básicas
bool vacia(TData *data);
bool llena(TData *data);
void insertar(TData *data, char apellido[LMAX]);
void suprimir(TData *data, char apellido[LMAX]);
void modificar(TData *data, char apellido[LMAX]);
void mostrar(TData *data);
int encontrar(TData *data, char apellido[LMAX]);
bool repetidos(char apellido1[LMAX], char apellido2[LMAX]);
void eliminarRepetidos(TData *data);
void guardarEmpleadosEnArchivo(TData *data, const char *filename);
void cargarEmpleadosDesdeArchivo(TData *data, const char *filename);
bool apellidoValido(const char apellido[]);
void limpiarEntrada(char *input);

// Acciones
void opcion1(TData *data);
void opcion2(TData *data);
void opcion3(TData *data);
void opcion4(TData *data);
void opcion5(TData *data);
void opcion6(TData *data);
void opcion7(TData *data);

int main() {
    int opcion;
    TData data;
    data.cant = 0;

    cargarEmpleadosDesdeArchivo(&data, "empleados.txt");

    do {
        printf("\n-----------------------------------\n");
        printf("Alta de empleado (1)\n");
        printf("Baja de empleado (2)\n");
        printf("Modificar datos de empleado (3)\n");
        printf("Listar (4)\n");
        printf("Buscar un empleado (5)\n");
        printf("Guardar en archivo (6)\n");
        printf("Salir (7)\n");
        printf("-----------------------------------\n");
        printf("Ingrese una opci\u00f3n: ");
        scanf("%d", &opcion);
        getchar(); // limpia salto de línea

        switch (opcion) {
            case 1: opcion1(&data); break;
            case 2: opcion2(&data); break;
            case 3: opcion3(&data); break;
            case 4: opcion4(&data); break;
            case 5: opcion5(&data); break;
            case 6: opcion6(&data); break;
            case 7: return 0;
            default:
                printf("\nOpci\u00f3n inv\u00e1lida.\n");
        }
    } while (1);
}

bool vacia(TData *data) {
    return data->cant == 0;
}

bool llena(TData *data) {
    return data->cant == NMAX;
}

void limpiarEntrada(char *input) {
    input[strcspn(input, "\n\r")] = 0;
}

bool apellidoValido(const char apellido[]) {
    if (strlen(apellido) == 0) return false;
    for (int i = 0; apellido[i] != '\0'; i++) {
        if (!isalpha(apellido[i]) && apellido[i] != ' ') {
            return false;
        }
    }
    return true;
}

void insertar(TData *data, char apellido[LMAX]) {
    if (llena(data)) {
        printf("Error: No hay espacio para m\u00e1s apellidos.\n");
        return;
    }
    strncpy(data->arreglo[data->cant], apellido, LMAX - 1);
    data->arreglo[data->cant][LMAX - 1] = '\0';
    printf("\n%sEl apellido '%s' fue registrado exitosamente.%s\n", GREEN, apellido, RESET);
    data->cant++;
}

void suprimir(TData *data, char apellido[LMAX]) {
    int index = encontrar(data, apellido);
    if (index == -1) {
        printf("Error: El apellido '%s' no se encontr\u00f3.\n", apellido);
        return;
    }
    printf("\n\u00bfEst\u00e1s seguro que quer\u00e9s eliminar '%s'? (s/n): ", apellido);
    char confirm;
    scanf(" %c", &confirm);
    getchar();
    if (confirm != 's' && confirm != 'S') {
        printf("Eliminaci\u00f3n cancelada.\n");
        return;
    }
    for (int j = index; j < data->cant - 1; j++) {
        strcpy(data->arreglo[j], data->arreglo[j + 1]);
    }
    data->cant--;
    printf("\n%sEl apellido '%s' fue dado de baja exitosamente.%s\n", RED, apellido, RESET);
}

void modificar(TData *data, char apellido[LMAX]) {
    int index = encontrar(data, apellido);
    if (index == -1) {
        printf("Error: El apellido '%s' no se encontr\u00f3.\n", apellido);
        return;
    }
    char nuevoApellido[LMAX];
    do {
        printf("\nIngrese apellido modificado: ");
        if (fgets(nuevoApellido, LMAX, stdin) == NULL) {
            printf("Error de entrada.\n");
            return;
        }
        limpiarEntrada(nuevoApellido);
        if (!apellidoValido(nuevoApellido)) {
            printf("\nEl apellido debe tener solo letras y como m\u00e1ximo 30 caracteres.\n");
        }
    } while (!apellidoValido(nuevoApellido));
    strncpy(data->arreglo[index], nuevoApellido, LMAX - 1);
    data->arreglo[index][LMAX - 1] = '\0';
    printf("\nSe ha modificado '%s' por '%s' exitosamente.\n", apellido, nuevoApellido);
}

void mostrar(TData *data) {
    if (vacia(data)) {
        printf("No hay apellidos para mostrar.\n");
        return;
    }
    printf("\nApellidos:\n");
    for (int i = 0; i < data->cant; i++) {
        printf("[%d] %s\n", i + 1, data->arreglo[i]);
    }
}

int encontrar(TData *data, char apellido[LMAX]) {
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
                printf("\n%sEl apellido '%s' ya existe, se eliminar\u00e1 la primera ocurrencia.%s\n", RED, data->arreglo[i], RESET);
                suprimir(data, data->arreglo[i]);
                j--;
            }
        }
    }
}

void guardarEmpleadosEnArchivo(TData *data, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error al abrir el archivo para escribir.\n");
        return;
    }
    for (int i = 0; i < data->cant; i++) {
        fprintf(file, "%s\n", data->arreglo[i]);
    }
    fclose(file);
    printf("\n\u00a1Datos guardados en el archivo %s con \u00e9xito!\n", filename);
}

void cargarEmpleadosDesdeArchivo(TData *data, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;
    data->cant = 0;
    while (fgets(data->arreglo[data->cant], LMAX, file) && data->cant < NMAX) {
        limpiarEntrada(data->arreglo[data->cant]);
        data->cant++;
    }
    fclose(file);
}

// Acciones switch
void opcion1(TData *data) {
    char apellido[LMAX];
    if (llena(data)) {
        printf("\nNo se pueden a\u00f1adir m\u00e1s empleados.\n");
        return;
    }
    do {
        printf("\nIngrese el apellido (solo letras, m\u00e1ximo 30 caracteres): ");
        if (fgets(apellido, LMAX, stdin) == NULL) return;
        limpiarEntrada(apellido);
        if (!apellidoValido(apellido)) {
            printf("\nEl apellido es inv\u00e1lido.\n");
        }
    } while (!apellidoValido(apellido));
    insertar(data, apellido);
    eliminarRepetidos(data);
}

void opcion2(TData *data) {
    char apellido[LMAX];
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
        return;
    }
    printf("\nIngrese el apellido a dar de baja: ");
    if (fgets(apellido, LMAX, stdin) == NULL) return;
    limpiarEntrada(apellido);
    suprimir(data, apellido);
}

void opcion3(TData *data) {
    char apellido[LMAX];
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
        return;
    }
    printf("\nIngrese el apellido a modificar: ");
    if (fgets(apellido, LMAX, stdin) == NULL) return;
    limpiarEntrada(apellido);
    if (encontrar(data, apellido) != -1) {
        modificar(data, apellido);
        eliminarRepetidos(data);
    } else {
        printf("\nEl apellido '%s' no existe en la lista.\n", apellido);
    }
}

void opcion4(TData *data) {
    mostrar(data);
}

void opcion5(TData *data) {
    char apellido[LMAX];
    if (vacia(data)) {
        printf("\nNo hay apellidos en la lista.\n");
        return;
    }
    printf("\nIngrese el apellido a buscar: ");
    if (fgets(apellido, LMAX, stdin) == NULL) return;
    limpiarEntrada(apellido);
    int pos = encontrar(data, apellido);
    if (pos != -1) {
        printf("\nEl apellido '%s' se encuentra en la posici\u00f3n %d.\n", apellido, pos + 1);
    } else {
        printf("\nEl apellido '%s' no est\u00e1 en la lista.\n", apellido);
    }
}

void opcion6(TData *data) {
    guardarEmpleadosEnArchivo(data, "empleados.txt");
}