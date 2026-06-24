#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para cada reactivo (Pregunta)
typedef struct NodoPregunta {
    char pregunta[256];
    char opciones[4][100];
    int opcion_correcta;
    int puntos;
    struct NodoPregunta* sig;
    struct NodoPregunta* ant;
} NodoPregunta;

// Funciones para manejo de la lista doblemente enlazada
NodoPregunta* crear_nodo(char *p, char respuestas[4][100], int correcta, int pts) {
    // Se reserva la memoria para el reactivo de forma dinamica
    NodoPregunta *nuevo_nodo = (NodoPregunta*) malloc(sizeof(NodoPregunta));
    if (nuevo_nodo == NULL) {
        printf("Error: No hay memoria suficiente.\n");
        exit(1);
    }

    // Copiar los datos de la pregunta (con limite seguro para evitar overflow)
    strncpy(nuevo_nodo->pregunta, p, sizeof(nuevo_nodo->pregunta) - 1);
    nuevo_nodo->pregunta[sizeof(nuevo_nodo->pregunta) - 1] = '\0';

    // Pasar las 4 opciones al nodo (tambien con limite seguro)
    for (int i = 0; i < 4; i++) {
        strncpy(nuevo_nodo->opciones[i], respuestas[i], sizeof(nuevo_nodo->opciones[i]) - 1);
        nuevo_nodo->opciones[i][sizeof(nuevo_nodo->opciones[i]) - 1] = '\0';
    }

    nuevo_nodo->opcion_correcta = correcta;
    nuevo_nodo->puntos = pts;

    // Al ser un nodo nuevo, sus punteros apuntan a NULL
    nuevo_nodo->sig = NULL;
    nuevo_nodo->ant = NULL;

    return nuevo_nodo;
}

void insertarAlFinal(NodoPregunta** cabeza, NodoPregunta** cola, NodoPregunta* nuevo) {
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        *cola = nuevo;
    } else {
        (*cola)->sig = nuevo;
        nuevo->ant = *cola;
        *cola = nuevo;
    }
}

void liberarLista(NodoPregunta** cabeza, NodoPregunta** cola) {
    NodoPregunta* actual = *cabeza;
    while (actual != NULL) {
        NodoPregunta* siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
    *cola = NULL;
}

// Funcion generica para guardar la lista completa en un archivo de texto
// Se reutiliza en generarExamen y modificarExamen para no repetir el bloque de fprintf
int guardarArch(char* nombreArchivo, NodoPregunta* cabeza) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        return 0; // 0 = no se pudo guardar
    }

    NodoPregunta* actual = cabeza;
    while (actual != NULL) {
        fprintf(archivo, ":p;%s\n", actual->pregunta);
        for (int i = 0; i < 4; i++) {
            fprintf(archivo, ":op%d;%s\n", i + 1, actual->opciones[i]);
        }
        fprintf(archivo, ":r;op%d\n", actual->opcion_correcta);
        fprintf(archivo, "%d.\n", actual->puntos);
        actual = actual->sig;
    }

    fclose(archivo);
    return 1; // 1 = guardado con exito
}

// Funcion auxiliar para cargar un archivo en la lista doble
int cargarExamenALista(char* nombreArchivo, NodoPregunta** cabeza, NodoPregunta** cola) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        return 0;
    }

    char linea[256];
    char preg[256] = "";
    char ops[4][100];
    int correcta = 0, pts = 0;

    // Inicializar la matriz de opciones limpia
    for (int i = 0; i < 4; i++) {
        strcpy(ops[i], "");
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        // Quitar salto de linea '\n' al final de la fila leida
        linea[strcspn(linea, "\n")] = 0;

        if (strncmp(linea, ":p;", 3) == 0) {
            strncpy(preg, linea + 3, sizeof(preg) - 1);
            preg[sizeof(preg) - 1] = '\0';
        } else if (strncmp(linea, ":op1;", 5) == 0) {
            strncpy(ops[0], linea + 5, sizeof(ops[0]) - 1);
        } else if (strncmp(linea, ":op2;", 5) == 0) {
            strncpy(ops[1], linea + 5, sizeof(ops[1]) - 1);
        } else if (strncmp(linea, ":op3;", 5) == 0) {
            strncpy(ops[2], linea + 5, sizeof(ops[2]) - 1);
        } else if (strncmp(linea, ":op4;", 5) == 0) {
            strncpy(ops[3], linea + 5, sizeof(ops[3]) - 1);
        } else if (strncmp(linea, ":r;op", 5) == 0 && strlen(linea) > 5) {
            // Validamos que exista el caracter en linea[5] antes de leerlo
            correcta = linea[5] - '0';
        } else if (strlen(linea) > 0 && linea[strlen(linea) - 1] == '.') {
            // Es la linea del puntaje (ej: "2.")
            pts = atoi(linea);

            // Insertamos el reactivo completo en la lista
            NodoPregunta* nuevo = crear_nodo(preg, ops, correcta, pts);
            insertarAlFinal(cabeza, cola, nuevo);
        }
    }

    fclose(archivo);
    return 1;
}

// Opcion 1: Generar un examen y guardarlo en un archivo
void generarExamen() {
    char nombreArchivo[100];
    NodoPregunta* cabeza = NULL;
    NodoPregunta* cola = NULL;
    int continuar = 1;

    printf("\n--- GENERAR EXAMEN ---\n");
    printf("Introduce el nombre del archivo (ej: examen.txt): ");
    scanf("%99s", nombreArchivo); // limite seguro para evitar overflow
    getchar(); // Limpiar bufer del teclado

    while (continuar) {
        char preg[256];
        char ops[4][100];
        int correcta, pts;

        printf("\nIntroduce la pregunta: ");
        fgets(preg, sizeof(preg), stdin);
        preg[strcspn(preg, "\n")] = 0; // Quitar salto de linea

        for (int i = 0; i < 4; i++) {
            printf("Opcion %d: ", i + 1);
            fgets(ops[i], sizeof(ops[i]), stdin);
            ops[i][strcspn(ops[i], "\n")] = 0;
        }

        do {
            printf("Opcion correcta (1-4): ");
            scanf("%d", &correcta);
        } while (correcta < 1 || correcta > 4);

        printf("Puntos asignados: ");
        scanf("%d", &pts);
        getchar(); // Limpiar bufer

        NodoPregunta* nuevo = crear_nodo(preg, ops, correcta, pts);
        insertarAlFinal(&cabeza, &cola, nuevo);

        printf("\n¿Deseas agregar otra pregunta? (1=Si, 0=No): ");
        scanf("%d", &continuar);
        getchar();
    }

    // Guardar en archivo con el formato requerido, usando la funcion reutilizable
    if (guardarArch(nombreArchivo, cabeza)) {
        printf("\n¡Examen guardado exitosamente en '%s'!\n", nombreArchivo);
    } else {
        printf("Error al crear el archivo.\n");
    }

    liberarLista(&cabeza, &cola);
}

// Opcion 2: Modificar un examen existente
void modificarExamen() {
    char nombreArchivo[100];
    NodoPregunta* cabeza = NULL;
    NodoPregunta* cola = NULL;

    printf("\n--- MODIFICAR EXAMEN ---\n");
    printf("Introduce el nombre del archivo a modificar: ");
    scanf("%99s", nombreArchivo);
    getchar();

    if (!cargarExamenALista(nombreArchivo, &cabeza, &cola)) {
        printf("No se pudo abrir el archivo o esta vacio.\n");
        return;
    }

    NodoPregunta* actual = cabeza;
    char op;

    if (actual == NULL) {
        printf("El examen no contiene preguntas.\n");
        liberarLista(&cabeza, &cola); // por seguridad, aunque deberia estar vacia
        return;
    }

    do {
        printf("\n=========================================\n");
        printf("Pregunta actual: %s\n", actual->pregunta);
        for (int i = 0; i < 4; i++) {
            printf("  %d) %s\n", i + 1, actual->opciones[i]);
        }
        printf("Respuesta correcta: Opcion %d | Puntos: %d\n", actual->opcion_correcta, actual->puntos);
        printf("=========================================\n");
        printf("[N] Siguiente | [P] Anterior | [E] Editar | [S] Guardar y Salir\n");
        printf("Selecciona una opcion: ");
        scanf(" %c", &op);
        getchar();

        if ((op == 'N' || op == 'n') && actual->sig != NULL) {
            actual = actual->sig;
        } else if ((op == 'P' || op == 'p') && actual->ant != NULL) {
            actual = actual->ant;
        } else if (op == 'E' || op == 'e') {
            char bufferTmp[256];

            printf("\nIntroduce la NUEVA pregunta: ");
            fgets(bufferTmp, sizeof(bufferTmp), stdin);
            bufferTmp[strcspn(bufferTmp, "\n")] = 0;
            strncpy(actual->pregunta, bufferTmp, sizeof(actual->pregunta) - 1);
            actual->pregunta[sizeof(actual->pregunta) - 1] = '\0';

            for (int i = 0; i < 4; i++) {
                printf("Nueva Opcion %d: ", i + 1);
                fgets(bufferTmp, sizeof(bufferTmp), stdin);
                bufferTmp[strcspn(bufferTmp, "\n")] = 0;
                strncpy(actual->opciones[i], bufferTmp, sizeof(actual->opciones[i]) - 1);
                actual->opciones[i][sizeof(actual->opciones[i]) - 1] = '\0';
            }

            do {
                printf("Nueva opcion correcta (1-4): ");
                scanf("%d", &actual->opcion_correcta);
            } while (actual->opcion_correcta < 1 || actual->opcion_correcta > 4);

            printf("Nuevos puntos asignados: ");
            scanf("%d", &actual->puntos);
            getchar();
            printf("\n¡Reactivo modificado temporalmente en memoria!\n");
        }
    } while (op != 'S' && op != 's');

    // Sobrescribir el archivo con los cambios, usando la funcion reutilizable
    if (guardarArch(nombreArchivo, cabeza)) {
        printf("\nCambios guardados exitosamente.\n");
    } else {
        printf("Error: No se pudieron guardar los cambios en disco.\n");
    }

    liberarLista(&cabeza, &cola);
}

// Opcion 3: Aplicar un examen (Responder la prueba)
void aplicarExamen() {
    char nombreArchivo[100];
    NodoPregunta* cabeza = NULL;
    NodoPregunta* cola = NULL;

    printf("\n--- APLICAR EXAMEN ---\n");
    printf("Introduce el nombre del examen a responder: ");
    scanf("%99s", nombreArchivo);
    getchar();

    if (!cargarExamenALista(nombreArchivo, &cabeza, &cola)) {
        printf("No se pudo abrir el archivo del examen.\n");
        return;
    }

    if (cabeza == NULL) {
        printf("El examen seleccionado no tiene reactivos.\n");
        return;
    }

    // Primer recorrido para contar cuantas preguntas tiene el examen
    NodoPregunta* auxContar = cabeza;
    int totalPreguntas = 0;
    while (auxContar != NULL) {
        totalPreguntas++;
        auxContar = auxContar->sig;
    }

    // Reservar arreglo dinamico limpio con ceros para las respuestas
    int* respuestasAlumno = (int*)calloc(totalPreguntas, sizeof(int));
    if (respuestasAlumno == NULL) {
        printf("Error: no hay memoria suficiente para iniciar el examen.\n");
        liberarLista(&cabeza, &cola);
        return;
    }

    NodoPregunta* actual = cabeza;
    int indiceActual = 0;
    char navegar;

    do {
        printf("\n-----------------------------------------\n");
        printf("Pregunta %d de %d\n", indiceActual + 1, totalPreguntas);
        printf("%s\n", actual->pregunta);
        for (int i = 0; i < 4; i++) {
            printf("  %d. %s\n", i + 1, actual->opciones[i]);
        }
        printf("-----------------------------------------\n");
        if (respuestasAlumno[indiceActual] != 0) {
            printf("[Tu respuesta seleccionada actual: %d]\n", respuestasAlumno[indiceActual]);
        }

        printf("Selecciona tu respuesta (1-4) o presiona '0' para dejar en blanco: ");
        int resp;
        scanf("%d", &resp);
        if (resp >= 0 && resp <= 4) {
            respuestasAlumno[indiceActual] = resp;
        }
        getchar();

        printf("\n[N] Siguiente pregunta | [P] Anterior pregunta | [F] Finalizar Examen\n");
        printf("Navegacion: ");
        scanf(" %c", &navegar);
        getchar();

        if ((navegar == 'N' || navegar == 'n') && actual->sig != NULL) {
            actual = actual->sig;
            indiceActual++;
        } else if ((navegar == 'P' || navegar == 'p') && actual->ant != NULL) {
            actual = actual->ant;
            indiceActual--;
        }

    } while (navegar != 'F' && navegar != 'f');

    // Calificar el examen comparando el arreglo contra los campos de los nodos
    int puntosObtenidos = 0;
    int puntosTotales = 0;

    actual = cabeza;
    int i = 0;
    while (actual != NULL) {
        puntosTotales += actual->puntos;
        if (respuestasAlumno[i] == actual->opcion_correcta) {
            puntosObtenidos += actual->puntos;
        }
        actual = actual->sig;
        i++;
    }

    printf("\n=========================================\n");
    printf("        EXAMEN FINALIZADO\n");
    printf(" Puntos logrados: %d de un total de %d considerados.\n", puntosObtenidos, puntosTotales);
    printf("=========================================\n");

    free(respuestasAlumno);
    liberarLista(&cabeza, &cola);
}

// Funcion principal: Menu del programa
int main() {
    int opcion = 0;

    while (opcion != 4) {
        printf("\n====================================\n");
        printf("       GENERADOR DE EXAMENES\n");
        printf("====================================\n");
        printf("1. Generar un examen\n");
        printf("2. Modificar un examen\n");
        printf("3. Aplicar un examen\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion (1-4): ");

        if (scanf("%d", &opcion) != 1) {
            printf("Por favor, introduce un numero valido.\n");
            // limpiar el bufer hasta el siguiente salto de linea, no solo un getchar
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        getchar(); // Limpiar el salto de linea sobrante

        switch (opcion) {
            case 1:
                generarExamen();
                break;
            case 2:
                modificarExamen();
                break;
            case 3:
                aplicarExamen();
                break;
            case 4:
                printf("\nSaliendo del programa. ¡Mucho exito en tu entrega!\n");
                break;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }

    return 0;
}