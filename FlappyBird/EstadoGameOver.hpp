#pragma once

#include <SFML/Graphics.hpp>
#include "Declaraciones.hpp"
#include "State.hpp"
#include "Juego.hpp"
#include "Suelo.hpp"
#include "EstadoJuego.hpp"
#include "Moneda.hpp"

namespace Flappy
{
    class EstadoGameOver : public State
    {
    public:
        EstadoGameOver(int sc, int monedas);
        static EstadoGameOver* Instance(int sc, int monedas);
        void Vaciar();
        
        void Init();
        void ManejarEventos();
        void Actualizar(float tiempoActual);
        void Dibujar(float tiempoActual);
        
        ~EstadoGameOver();
    private:
        static EstadoGameOver* _pinstance;
        
        Juego* _juego;
        sf::Sprite fondo;
        Suelo* suelo;
        
        sf::Sprite titulo;
        sf::Sprite panel;
        sf::Sprite medalla;
        
        sf::Text scoreText;
        sf::Text maxScoreText;
        sf::Text reintentar1;
        sf::Text reintentar;
        
        int scoreMonedas;
        int score;
        int auxScore;
        int maxScore;
        int totalMonedas;
        
        int yIniTit;
        bool activarControl;
        sf::Clock relojAnim;
        
        Moneda* monedero;
        bool activarLluvia;
        
        void ObtenerMedallaTitulo();
        void AnimarScore();
        void LluviaDeMonedas();
    };
}