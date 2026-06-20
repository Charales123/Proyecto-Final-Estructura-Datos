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
    nodo *cola;     //ultimo nodo
    int total;  //total de reactivos
    listaDoble(): cabeza(nullptr), cola(nullptr), total(0){}    //crea una listaDoble limpia
};

/* ------------ Prototipos ------------ */
void insertarLista(listaDoble &, pregunta);
void eliminarNodo(listaDoble &, nodo *);
void liberarLista(listaDoble &);
void cargarArch(listaDoble &, string &);
void guardarArch(listaDoble &, string &);

/* ------------ Funciones de la ListaDoble ------------ */
void insertarLista(listaDoble &lista, pregunta p){
    nodo *nuevo= new nodo(p);       
    if(lista.cabeza == nullptr){
        lista.cabeza = nuevo;
        lista.cola = nuevo;
    }else{
        nuevo->anterior = lista.cola;
        lista.cola->siguiente = nuevo;
        lista.cola = nuevo;
    }
    lista.total++;
}

void eliminarNodo(listaDoble &lista, nodo *nodo){
    if(nodo==nullptr) return;

    if(nodo->anterior) nodo->anterior->siguiente = nodo->siguiente;
    else lista.cabeza = nodo->siguiente;

    if(nodo->siguiente) nodo->siguiente->anterior = nodo->anterior;
    else lista.cola = nodo->anterior;

    delate nodo;
    lista.total--;
}

void liberarLista(listaDoble &lista){
    nodo *actual= lista.cabeza;
    while(actual!=nullptr){
        nodo *siguiente = actual->siguiente;
        delate actual;
        actual = siguiente;
    }
    lista.cabeza=nullptr;
    lista.cola=nullptr;
    lista.total=0;
}

/* ------------ Manejo de Archivos ------------ */
void cargarArch(listaDoble &lista, string nomArch){
    ifstream archivo(nomArch.c_str());
    if(!archivo.is_open()){
        cout<<"Error,no se pudo abrir:"<<nomArch<<endl;
        return;
    }
    string linea;
    pregunta p;
    bool leyendo=false;
}

void guardarArch(listaDoble &lista, string nomArch){

}