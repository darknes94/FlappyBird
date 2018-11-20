#pragma once
#include <SFML/Graphics.hpp>
#include "EstadosManager.hpp"
#include "AssetManager.hpp"
using namespace std;

// Medidas ventana
#define ANCHO 768
#define ALTO 1024
#define TITULO_WINDOW "Flappy Bird by Marines"

namespace Flappy
{
    class Juego {
    public:
        static Juego* Instance();
        
        EstadosManager maquina;
        sf::RenderWindow window;
        AssetManager assets;
        void Iniciar();
        
        ~Juego();
    private:
        Juego() { };
        Juego(const Juego &);
        Juego &operator=(const Juego &);
        
        static Juego* _pinstance;
        sf::Clock reloj;
    };
}