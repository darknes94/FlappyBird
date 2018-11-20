#pragma once

#include <SFML/Graphics.hpp>
#include "Declaraciones.hpp"    // Para la VELOCIDAD
#include "Juego.hpp"

namespace Flappy
{
    class TuberiasManager
    {
    public:
        TuberiasManager();
        void Spawn();
        void Mover(float tiempoActual);
        void Dibujar();
        float GetPuntoMedio();
        sf::Sprite &GetTubA(int pos);
        sf::Sprite &GetTubB(int pos);
        bool &GetSumaScore(int pos);
        int Tamanyo();
        
    private:
        Juego* _juego;
        sf::Texture textura;
        sf::Sprite sprite;
        sf::Sprite tubArriba[3];
        sf::Sprite tubAbajo[3];
        bool sumaScore[3];
        int maxTub;
        
        int spawnY;
        float puntoMedio;
        float ancho;
        int margen;
        int alturaArriba;
        int alturaAbajo;
        
        void RandomY();
    };
}