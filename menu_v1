int main() {
    int opcion = 0;

    while (opcion != 4) {
        printf("\n====================================\n");
        printf("       GENERADOR DE EXÁMENES\n");
        printf("====================================\n");
        printf("1. Generar un examen\n");
        printf("2. Modificar un examen\n");
        printf("3. Aplicar un examen\n");
        printf("4. Salir\n");
        printf("Selecciona una opción (1-4): ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Por favor, introduce un número válido.\n");
            getchar(); // Limpiar entrada incorrecta
            continue;
        }
        getchar(); // Limpiar el salto de línea del búfer

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
                printf("\nSaliendo del programa. ¡Mucho éxito en tu entrega!\n");
                break;
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
    }

    return 0;
}
