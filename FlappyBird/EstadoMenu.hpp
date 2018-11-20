#pragma once

#include <SFML/Graphics.hpp>
#include "Declaraciones.hpp"
#include "State.hpp"
#include "Juego.hpp"
#include "Suelo.hpp"
#include "Personaje.hpp"
using namespace std;

namespace Flappy
{
    class EstadoMenu : public State
    {
    public:
        EstadoMenu();
        static EstadoMenu* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoMenu();
    private:
        static EstadoMenu* _pinstance;
        
        Juego* _juego;
        sf::Sprite fondo;
        sf::Sprite titulo;
        sf::Text fuente;
        Suelo* suelo;
        Personaje* personaje;
        
        float yIni;
        float yQuieto;
        
        void MoverTitulo();
    };
}