#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Juego.hpp"
#include "Suelo.hpp"
#include "Marcador.hpp"
#include "Personaje.hpp"
#include "TuberiasManager.hpp"
#include "Moneda.hpp"

namespace Flappy
{
    class EstadoJuego : public State
    {
    public:
        EstadoJuego();
        static EstadoJuego* Instance();
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoJuego();
    private:
        static EstadoJuego* _pinstance;
        
        Juego* _juego;
        sf::Sprite fondo;
        Suelo* suelo;
        Marcador* marcador;
        Personaje* personaje;
        TuberiasManager* tuberias;
        
        bool ColisionSuelo();
        bool ColisionTuberias();
        void ColisionTuberiasScore();
        void ColisionMoneda();
        
        bool gameOver;
        bool sonar;
        
        sf::RectangleShape fondoFlash;
        bool flashOn;
        sf::Sprite preparadoText;
        
        void MonedaEnPantalla(float tiempoActual);
        Moneda* moneda;
        unsigned short int numTub;
    };
}