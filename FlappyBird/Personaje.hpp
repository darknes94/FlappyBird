#pragma once

#include <SFML/Graphics.hpp>
#include "Declaraciones.hpp"    // Para los ESTADOS
#include "Juego.hpp"

namespace Flappy
{
    class Personaje {
    public:
        Personaje();
        void Animar(float tiempoActual);
        void Actualizar(float tiempoActual);
        void Salto();
        void Dibujar();
        sf::CircleShape &GetCirculo();
        unsigned short int &GetEstado();
        void Caida(float tiempoActual);
        void AnimQuieto();
        
    private:
        Juego* _juego;
        sf::Sprite sprite;
        sf::CircleShape circulo;
        sf::IntRect frames[4];
        
        unsigned short int nFrame;
        unsigned short int maxFrames;
        unsigned short int estado;
        
        sf::Clock relojAnim;
        sf::Clock relojMove;
        
        float xIni;
        float yIni;
        float yQuieto;
        float ySalto;
        float rotacion;
        float alturaMax;
    };
}