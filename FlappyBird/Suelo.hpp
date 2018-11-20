#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Juego.hpp"
#include "Declaraciones.hpp"    // Para la VELOCIDAD

namespace Flappy
{
    class Suelo
    {
        public:
            Suelo();

            void MoverSuelo(float tiempoActual);
            void Dibujar();
            sf::Sprite &GetSprite(int pos);

	private:
            Juego* _juego;
            vector<sf::Sprite> SpritesSuelo;
            int y;
            int ancho;
    };
}