# Generador de Exámenes

Sistema en lenguaje C para crear, modificar y aplicar exámenes de opción múltiple, desarrollado como Proyecto Final de la materia Estructura de Datos.

## Descripción

El programa utiliza una lista doblemente enlazada donde cada nodo representa un reactivo (pregunta) con sus 4 opciones, la respuesta correcta y su puntaje. Los exámenes se almacenan en archivos de texto con un formato propio basado en etiquetas.

## Funcionalidad

1. **Generar examen** — crea un nuevo examen pregunta por pregunta y lo guarda en un archivo de texto.
2. **Modificar examen** — carga un examen existente, permite navegar y editar reactivos, y guarda los cambios.
3. **Aplicar examen** — permite responder un examen, navegar entre preguntas, y al finalizar muestra el puntaje obtenido.

## Estructuras principales

- `NodoPregunta`: estructura con pregunta, 4 opciones, respuesta correcta, puntos y punteros `sig`/`ant`.
- Funciones clave: `crear_nodo`, `insertarAlFinal`, `liberarLista`, `guardarArch`, `cargarExamenALista`.

## Integrantes

- González García Ryan Yahir
- David Muñoz Barrón

## Materia

Estructura de Datos — 2°A — Ingeniería en Sistemas Computacionales
