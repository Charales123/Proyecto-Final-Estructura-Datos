// Opción 1: Generar un examen y guardarlo en un archivo
void generarExamen() {
    char nombreArchivo[100];
    NodoPregunta* cabeza = NULL;
    NodoPregunta* cola = NULL;
    int continuar = 1;

    printf("\n--- GENERAR EXAMEN ---\n");
    printf("Introduce el nombre del archivo (ej: examen.txt): ");
    scanf("%s", nombreArchivo);
    getchar(); // Limpiar búfer

    while (continuar) {
        char preg[256];
        char ops[4][100];
        int correcta, pts;

        printf("\nIntroduce la pregunta: ");
        fgets(preg, sizeof(preg), stdin);
        preg[strcspn(preg, "\n")] = 0; // Quitar salto de línea

        for (int i = 0; i < 4; i++) {
            printf("Opción %d: ", i + 1);
            fgets(ops[i], sizeof(ops[i]), stdin);
            ops[i][strcspn(ops[i], "\n")] = 0;
        }

        do {
            printf("Opción correcta (1-4): ");
            scanf("%d", &correcta);
        } while (correcta < 1 || correcta > 4);

        printf("Puntos asignados: ");
        scanf("%d", &pts);
        getchar(); // Limpiar búfer

        NodoPregunta* nuevo = crear_nodo(preg, ops, correcta, pts);
        insertarAlFinal(&cabeza, &cola, nuevo);

        printf("\n¿Deseas agregar otra pregunta? (1=Sí, 0=No): ");
        scanf("%d", &continuar);
        getchar();
    }

    // Guardar en archivo con el formato requerido
    FILE* archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("Error al crear el archivo.\n");
        liberarLista(&cabeza, &cola);
        return;
    }

    NodoPregunta* actual = cabeza;
    int indice = 1;
    while (actual != NULL) {
        fprintf(archivo, ":p;%s\n", actual->pregunta);
        for (int i = 0; i < 4; i++) {
            fprintf(archivo, ":op%d;%s\n", i + 1, actual->opciones[i]);
        }
        fprintf(archivo, ":r;op%d\n", actual->opcion_correcta);
        fprintf(archivo, "%d.\n", actual->puntos);
        
        actual = actual->sig;
        indice++;
    }

    fclose(archivo);
    liberarLista(&cabeza, &cola);
    printf("\n¡Examen guardado exitosamente en '%s'!\n", nombreArchivo);
}
