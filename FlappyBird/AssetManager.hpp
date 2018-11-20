#pragma once

using namespace std;            // Para los string
#include <iostream>             // Para la salida por consola de los errores
#include <map>                  // Para la clave-valor de las texturas y fuentes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Declaraciones.hpp"

namespace Flappy
{
    class AssetManager
    {
    public:
        AssetManager() {}
        ~AssetManager();
        
        void CargarTextura(string nombre, string fichero);
        sf::Texture &GetTextura(string nombre);
        
        void CargarFuente(string nombre, string fichero);
        sf::Font &GetFuente(string nombre);
        
        void CargarAudios();
        sf::Sound &GetGolpe();
        sf::Sound &GetVuelo();
        sf::Sound &GetPunto();
        
    private:
        map<string, sf::Texture> texturas;
        map<string, sf::Font> fuentes;
        
        sf::SoundBuffer golpeSoundBuffer;
        sf::SoundBuffer vueloSoundBuffer;
        sf::SoundBuffer puntoSoundBuffer;
        
        sf::Sound golpeSound;
        sf::Sound vueloSound;
        sf::Sound puntoSound;
    };
}