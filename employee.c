// Enhanced Employee Manager (English) with EOF Handling and Robust Validation
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

typedef struct {
    char surnames[NMAX][LMAX];
    int count;
    bool dirty; // track unsaved changes
} EmployeeData;

// Basic operations
bool isEmpty(EmployeeData *data);
bool isFull(EmployeeData *data);
void addEmployee(EmployeeData *data, char surname[LMAX]);
void deleteEmployee(EmployeeData *data, char surname[LMAX]);
void updateEmployeeSurname(EmployeeData *data, char surname[LMAX]);
void listEmployees(EmployeeData *data);
int findSurname(EmployeeData *data, char surname[LMAX]);
bool isDuplicate(char surname1[LMAX], char surname2[LMAX]);
void removeDuplicates(EmployeeData *data);
void saveEmployeesToFile(EmployeeData *data, const char *filename);
void loadEmployeesFromFile(EmployeeData *data, const char *preferredFilename, const char *fallbackFilename);
bool isValidSurname(const char surname[]);
void trimNewline(char *input);
void normalizeSurname(char *surname);
void sortSurnames(EmployeeData *data);
void saveEmployeesToFileAs(EmployeeData *data);
void searchBySubstring(EmployeeData *data);
int promptSaveIfDirty(EmployeeData *data);

// Actions
void actionAddEmployee(EmployeeData *data);
void actionDeleteEmployee(EmployeeData *data);
void actionModifyEmployee(EmployeeData *data);
void actionListEmployees(EmployeeData *data);
void actionSearchEmployee(EmployeeData *data);
void actionSaveToFile(EmployeeData *data);

int main() {
    int option;
    EmployeeData data;
    data.count = 0;
    data.dirty = false;

    // Load from English filename; if not found, attempt Spanish legacy filename
    loadEmployeesFromFile(&data, "employees.txt", "empleados.txt");

    do {
        printf("\n-----------------------------------\n");
        printf("Add employee (1)\n");
        printf("Remove employee (2)\n");
        printf("Modify employee surname (3)\n");
    printf("List employees (4)\n");
    printf("Search surname (exact) (5)\n");
    printf("Find by substring (6)\n");
    printf("Sort surnames (A-Z) (7)\n");
    printf("Save to file (8)\n");
    printf("Save to file as... (9)\n");
    printf("Exit (10)\n");
        printf("-----------------------------------\n");
        printf("Enter an option: ");
        if (scanf("%d", &option) != 1) {
            printf("\nInvalid input. Exiting.\n");
            return 0;
        }
        getchar(); // consume newline

        switch (option) {
            case 1: actionAddEmployee(&data); break;
            case 2: actionDeleteEmployee(&data); break;
            case 3: actionModifyEmployee(&data); break;
            case 4: actionListEmployees(&data); break;
            case 5: actionSearchEmployee(&data); break;
            case 6: searchBySubstring(&data); break;
            case 7: sortSurnames(&data); break;
            case 8: actionSaveToFile(&data); break;
            case 9: saveEmployeesToFileAs(&data); break;
            case 10:
                if (promptSaveIfDirty(&data)) {
                    return 0;
                }
                break;
            default:
                printf("\nInvalid option.\n");
        }
    } while (1);
}

bool isEmpty(EmployeeData *data) {
    return data->count == 0;
}

bool isFull(EmployeeData *data) {
    return data->count == NMAX;
}

void trimNewline(char *input) {
    input[strcspn(input, "\n\r")] = 0;
}

bool isValidSurname(const char surname[]) {
    if (strlen(surname) == 0) return false;
    for (int i = 0; surname[i] != '\0'; i++) {
        if (!isalpha((unsigned char)surname[i]) && surname[i] != ' ') {
            return false;
        }
    }
    return true;
}

void addEmployee(EmployeeData *data, char surname[LMAX]) {
    if (isFull(data)) {
        printf("Error: No more space for additional surnames.\n");
        return;
    }
    normalizeSurname(surname);
    strncpy(data->surnames[data->count], surname, LMAX - 1);
    data->surnames[data->count][LMAX - 1] = '\0';
    printf("\n%sThe surname '%s' was registered successfully.%s\n", GREEN, surname, RESET);
    data->count++;
    data->dirty = true;
}

void deleteEmployee(EmployeeData *data, char surname[LMAX]) {
    int index = findSurname(data, surname);
    if (index == -1) {
        printf("Error: The surname '%s' was not found.\n", surname);
        return;
    }
    printf("\nAre you sure you want to delete '%s'? (y/n): ", surname);
    char confirm;
    if (scanf(" %c", &confirm) != 1) {
        printf("Input error.\n");
        return;
    }
    getchar();
    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion canceled.\n");
        return;
    }
    for (int j = index; j < data->count - 1; j++) {
        strcpy(data->surnames[j], data->surnames[j + 1]);
    }
    data->count--;
    printf("\n%sThe surname '%s' was removed successfully.%s\n", RED, surname, RESET);
    data->dirty = true;
}

void updateEmployeeSurname(EmployeeData *data, char surname[LMAX]) {
    int index = findSurname(data, surname);
    if (index == -1) {
        printf("Error: The surname '%s' was not found.\n", surname);
        return;
    }
    char newSurname[LMAX];
    do {
        printf("\nEnter the new surname: ");
        if (fgets(newSurname, LMAX, stdin) == NULL) {
            printf("Input error.\n");
            return;
        }
        trimNewline(newSurname);
        if (!isValidSurname(newSurname)) {
            printf("\nThe surname must contain only letters and spaces, up to 30 characters.\n");
        }
    } while (!isValidSurname(newSurname));
    normalizeSurname(newSurname);
    strncpy(data->surnames[index], newSurname, LMAX - 1);
    data->surnames[index][LMAX - 1] = '\0';
    printf("\nSuccessfully changed '%s' to '%s'.\n", surname, newSurname);
    data->dirty = true;
}

void listEmployees(EmployeeData *data) {
    if (isEmpty(data)) {
        printf("There are no surnames to display.\n");
        return;
    }
    printf("\nSurnames (total: %d):\n", data->count);
    for (int i = 0; i < data->count; i++) {
        printf("[%d] %s\n", i + 1, data->surnames[i]);
    }
}

int findSurname(EmployeeData *data, char surname[LMAX]) {
    char normalized[LMAX];
    strncpy(normalized, surname, LMAX - 1);
    normalized[LMAX - 1] = '\0';
    normalizeSurname(normalized);
    for (int i = 0; i < data->count; i++) {
        if (strcmp(data->surnames[i], normalized) == 0) {
            return i;
        }
    }
    return -1;
}

bool isDuplicate(char surname1[LMAX], char surname2[LMAX]) {
    return strcmp(surname1, surname2) == 0;
}

void removeDuplicates(EmployeeData *data) {
    for (int i = 0; i < data->count; i++) {
        for (int j = i + 1; j < data->count; j++) {
            if (isDuplicate(data->surnames[i], data->surnames[j])) {
                printf("\n%sThe surname '%s' already exists, the first occurrence will be removed.%s\n", RED, data->surnames[i], RESET);
                deleteEmployee(data, data->surnames[i]);
                j--;
            }
        }
    }
}

void saveEmployeesToFile(EmployeeData *data, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < data->count; i++) {
        fprintf(file, "%s\n", data->surnames[i]);
    }
    fclose(file);
    printf("\nData saved to %s successfully.\n", filename);
    data->dirty = false;
}

void loadEmployeesFromFile(EmployeeData *data, const char *preferredFilename, const char *fallbackFilename) {
    FILE *file = fopen(preferredFilename, "r");
    if (!file && fallbackFilename) {
        file = fopen(fallbackFilename, "r");
    }
    if (!file) return;
    data->count = 0;
    while (data->count < NMAX && fgets(data->surnames[data->count], LMAX, file)) {
        trimNewline(data->surnames[data->count]);
        normalizeSurname(data->surnames[data->count]);
        data->count++;
    }
    fclose(file);
    removeDuplicates(data);
    data->dirty = false;
}

// Actions switch
void actionAddEmployee(EmployeeData *data) {
    char surname[LMAX];
    if (isFull(data)) {
        printf("\nYou can't add more employees.\n");
        return;
    }
    do {
        printf("\nEnter the surname (letters and spaces only, max 30 chars): ");
        if (fgets(surname, LMAX, stdin) == NULL) return;
        trimNewline(surname);
        if (!isValidSurname(surname)) {
            printf("\nInvalid surname.\n");
        }
    } while (!isValidSurname(surname));
    addEmployee(data, surname);
    removeDuplicates(data);
}

void actionDeleteEmployee(EmployeeData *data) {
    char surname[LMAX];
    if (isEmpty(data)) {
        printf("\nThere are no surnames in the list.\n");
        return;
    }
    printf("\nEnter the surname to remove: ");
    if (fgets(surname, LMAX, stdin) == NULL) return;
    trimNewline(surname);
    deleteEmployee(data, surname);
}

void actionModifyEmployee(EmployeeData *data) {
    char surname[LMAX];
    if (isEmpty(data)) {
        printf("\nThere are no surnames in the list.\n");
        return;
    }
    printf("\nEnter the surname to modify: ");
    if (fgets(surname, LMAX, stdin) == NULL) return;
    trimNewline(surname);
    if (findSurname(data, surname) != -1) {
        updateEmployeeSurname(data, surname);
        removeDuplicates(data);
    } else {
        printf("\nThe surname '%s' does not exist in the list.\n", surname);
    }
}

void actionListEmployees(EmployeeData *data) {
    listEmployees(data);
}

void actionSearchEmployee(EmployeeData *data) {
    char surname[LMAX];
    if (isEmpty(data)) {
        printf("\nThere are no surnames in the list.\n");
        return;
    }
    printf("\nEnter the surname to search (exact): ");
    if (fgets(surname, LMAX, stdin) == NULL) return;
    trimNewline(surname);
    int pos = findSurname(data, surname);
    if (pos != -1) {
        char normalized[LMAX];
        strncpy(normalized, surname, LMAX - 1);
        normalized[LMAX - 1] = '\0';
        normalizeSurname(normalized);
        printf("\nThe surname '%s' is at position %d.\n", normalized, pos + 1);
    } else {
        printf("\nThe surname '%s' is not in the list.\n", surname);
    }
}

void actionSaveToFile(EmployeeData *data) {
    saveEmployeesToFile(data, "employees.txt");
}

// ===== Additional enhancements implementation =====

static void ltrim(char *s) {
    size_t i = 0;
    while (s[i] == ' ') i++;
    if (i > 0) memmove(s, s + i, strlen(s + i) + 1);
}

static void rtrim(char *s) {
    size_t len = strlen(s);
    while (len > 0 && s[len - 1] == ' ') {
        s[--len] = '\0';
    }
}

static void collapseSpaces(char *s) {
    char *dst = s;
    bool inSpace = false;
    for (char *src = s; *src; ++src) {
        if (*src == ' ') {
            if (!inSpace) {
                *dst++ = ' ';
                inSpace = true;
            }
        } else {
            *dst++ = *src;
            inSpace = false;
        }
    }
    *dst = '\0';
}

void normalizeSurname(char *surname) {
    // Trim and collapse spaces
    ltrim(surname);
    rtrim(surname);
    collapseSpaces(surname);
    // Lowercase all, then title-case each word
    for (int i = 0; surname[i] != '\0'; ++i) {
        surname[i] = (char)tolower((unsigned char)surname[i]);
    }
    bool newWord = true;
    for (int i = 0; surname[i] != '\0'; ++i) {
        if (surname[i] == ' ') {
            newWord = true;
        } else if (newWord) {
            surname[i] = (char)toupper((unsigned char)surname[i]);
            newWord = false;
        }
    }
}

static void toLowerCopy(char *dst, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n - 1 && src[i] != '\0'; ++i) {
        dst[i] = (char)tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

static bool containsSubstringCI(const char *haystack, const char *needle) {
    if (!*needle) return true;
    char h[LMAX];
    char n[LMAX];
    toLowerCopy(h, haystack, LMAX);
    toLowerCopy(n, needle, LMAX);
    // simple substring search
    size_t hl = strlen(h), nl = strlen(n);
    if (nl > hl) return false;
    for (size_t i = 0; i + nl <= hl; ++i) {
        if (strncmp(&h[i], n, nl) == 0) return true;
    }
    return false;
}

void searchBySubstring(EmployeeData *data) {
    if (isEmpty(data)) {
        printf("\nThere are no surnames in the list.\n");
        return;
    }
    char term[LMAX];
    printf("\nEnter a substring to search: ");
    if (fgets(term, LMAX, stdin) == NULL) return;
    trimNewline(term);
    if (strlen(term) == 0) {
        printf("Empty search term.\n");
        return;
    }
    int found = 0;
    printf("\nMatches:\n");
    for (int i = 0; i < data->count; ++i) {
        if (containsSubstringCI(data->surnames[i], term)) {
            printf("[%d] %s\n", i + 1, data->surnames[i]);
            found++;
        }
    }
    if (!found) {
        printf("No matches found for '%s'.\n", term);
    }
}

static int cmpSurnamesAsc(const void *a, const void *b) {
    const char (*sa)[LMAX] = (const char (*)[LMAX])a;
    const char (*sb)[LMAX] = (const char (*)[LMAX])b;
    return strcmp(*sa, *sb);
}

void sortSurnames(EmployeeData *data) {
    if (data->count <= 1) {
        printf("\nNothing to sort.\n");
        return;
    }
    // qsort over fixed-size string array
    qsort(data->surnames, data->count, sizeof(data->surnames[0]), cmpSurnamesAsc);
    printf("\nSurnames sorted A-Z.\n");
    data->dirty = true;
}

void saveEmployeesToFileAs(EmployeeData *data) {
    char filename[128];
    printf("\nEnter filename to save as: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) return;
    trimNewline(filename);
    if (strlen(filename) == 0) {
        printf("Invalid filename.\n");
        return;
    }
    saveEmployeesToFile(data, filename);
}

int promptSaveIfDirty(EmployeeData *data) {
    if (!data->dirty) return 1; // safe to exit
    printf("\nYou have unsaved changes. Save before exit? (y/n/c): ");
    char c;
    if (scanf(" %c", &c) != 1) return 0;
    getchar();
    if (c == 'y' || c == 'Y') {
        saveEmployeesToFile(data, "employees.txt");
        return 1;
    } else if (c == 'n' || c == 'N') {
        return 1;
    } else {
        printf("Exit canceled.\n");
        return 0;
    }
}