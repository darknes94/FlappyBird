#include "AssetManager.hpp"

namespace Flappy
{
    AssetManager::~AssetManager()
    {
    }
    
    void AssetManager::CargarTextura(string nombre, string fichero)
    {
        sf::Texture tex;
        if (tex.loadFromFile(fichero))
        {
            texturas[nombre] = tex;
        }
        else
        {
            cerr << "Error cargando la imagen "<< fichero;
            exit(0);
        }
    }
    
    sf::Texture &AssetManager::GetTextura(string nombre)
    {
        return texturas.at(nombre);
    }
        
    void AssetManager::CargarFuente(string nombre, string fichero)
    {
        sf::Font fuente;
        if (fuente.loadFromFile(fichero))
        {
            fuentes[nombre] = fuente;
        }
        else
        {
            cerr << "Error cargando la fuente "<< fichero;
            exit(0);
        }
    }
    
    sf::Font &AssetManager::GetFuente(string nombre)
    {
        return fuentes.at(nombre);
    }
    
    void AssetManager::CargarAudios()
    {
        if (!golpeSoundBuffer.loadFromFile(A_GOLPE))
        {
            cout << "Error cargando -> " << A_GOLPE << endl;
            exit(0);
        }

        if (!vueloSoundBuffer.loadFromFile(A_VUELO))
        {
            cout << "Error cargando -> " << A_VUELO << endl;
            exit(0);
        }

        if (!puntoSoundBuffer.loadFromFile(A_PUNTO))
        {
            cout << "Error cargando -> " << A_PUNTO << endl;
            exit(0);
        }

        golpeSound.setBuffer(golpeSoundBuffer);
        vueloSound.setBuffer(vueloSoundBuffer);
        puntoSound.setBuffer(puntoSoundBuffer);
    }
    
    sf::Sound &AssetManager::GetPunto()
    {
        return puntoSound;
    }
    
    sf::Sound &AssetManager::GetGolpe()
    {
        return golpeSound;
    }
    
    sf::Sound &AssetManager::GetVuelo()
    {
        return vueloSound;
    }
}