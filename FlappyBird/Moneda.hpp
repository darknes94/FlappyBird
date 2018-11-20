#pragma once

#include <SFML/Graphics.hpp>
#include "Declaraciones.hpp"    // Para la velocidad
#include "Juego.hpp"

namespace Flappy
{
    class Moneda {
    public:
        Moneda(float x, float y);
        Moneda(float x);
        Moneda();
        void Instanciar();
        void Dibujar();
        void Animar();
        void Mover(float x, float y);
        float GetX();
        float GetY();
        void SetX(float x);
        void SetY();
        sf::CircleShape &GetCirculo();
        bool GetCogerMoneda();
        void SetCogerMoneda();
        bool Colocada();
        bool Llover();
        void Lluvia();
        //void Parabola();
        
    private:
        Juego* _juego;
        sf::Clock relojAnim;
        sf::CircleShape moneda;
        sf::IntRect frames[6];
        unsigned short int nFrame;
        unsigned short int maxFrames;
        
        int RandomY();
        bool sumar;
        bool colocada;
        
        float xFin;
        float yFin;
        
        float Vox;
        float Voy;
        bool llover;
    };
}