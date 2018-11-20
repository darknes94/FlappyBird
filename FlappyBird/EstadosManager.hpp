#pragma once

#include <stack>  // Para la pila de estados
#include "State.hpp"
using namespace std;

namespace Flappy
{
    class EstadosManager
    {
    public:
        EstadosManager() { }
        ~EstadosManager() {
            while (estados.size() > 0) {
                estado = estados.top();
                delete estado;
                estado = 0;
                estados.pop();
            }
        }
        
        void Anyadir(State* nuevoEstado, bool reemplazar = true);
        void Eliminar();
        
        void ProcesarPilaEstados();
        
        State* &GetEstadoActivo();
        
    private:
        stack<State*> estados;
        
        State* estado;
        
        bool reemplazando;
        bool anyadiendo;
        bool eliminando;
    };
}