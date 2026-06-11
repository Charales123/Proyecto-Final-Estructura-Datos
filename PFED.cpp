/*              Proyecto Final Estructura de Datos
============ Generador de Examenes ============ */
#include <iostream>
#include <fstream>  //manejo de archivos mas facil
 using namespace std;

/* ------------ Estructura principal de una pregunta ------------ */
struct pregunta{
    string texto;   //texto de la pregunta
    string op1;
    string op2;
    string op3;
    string op4;
    string respuesta;   //la respuesta correcta
    int puntos; //puntos del reactivo
};

struct nodo{
    pregunta dato;
    nodo *anterior;     //al nodo anterior
    nodo *siguiente;    //al nodo siguiente
};

struct listaDoble{
    nodo *cabeza;    //primer nodo
    nodo* cola;     //ultimo nodo
    int total;  //total de reactivos
    listaDoble(): cabeza(nullptr), cola(nullptr), total(0){}    //crea una listaDoble limpia
};

/* ------------ Prototipos ------------ */
