// Funciones para manejo de la lista doblemente enlazada
NodoPregunta* crear_nodo(char *p, char respuestas[4][100], int correcta, int pts) {
    // Se reserva la memoria para el reactivo
    NodoPregunta *nuevo_nodo = (NodoPregunta*) malloc(sizeof(NodoPregunta));
    
    // Copiar los datos de la pregunta
    strcpy(nuevo_nodo->pregunta, p);
    
    // Pasar las 4 opciones al nodo
    for (int i = 0; i < 4; i++) {
        strcpy(nuevo_nodo->opciones[i], respuestas[i]);
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
