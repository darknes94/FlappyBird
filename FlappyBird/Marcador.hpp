#pragma once

#include <SFML/Graphics.hpp>
#include "Juego.hpp"
#include "Moneda.hpp"
using namespace std;

namespace Flappy
{
    class Marcador
    {
        public:
            Marcador();

            void ActualizarMarcador();
            void ActualizarMonedas();
            void RotarMoneda();
            void DibujarMarcador();
            int GetScore();
            int GetTotalMonedas();
            
	private:
            Juego* _juego;
            sf::Text scoreText;
            sf::Text monedaText;
            Moneda* moneda;
            
            int score;
            int totalMonedas;
    };
}