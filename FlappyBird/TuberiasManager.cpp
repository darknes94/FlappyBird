#include "TuberiasManager.hpp"

namespace Flappy {

    TuberiasManager::TuberiasManager() {
        _juego = Juego::Instance();
        spawnY = 0;

        textura = _juego->assets.GetTextura("Tuberia");
        sprite.setTexture(textura);
        ancho = sprite.getLocalBounds().width;
        puntoMedio = ancho / 2;
        sprite.setOrigin(puntoMedio, 0);

        margen = _juego->window.getSize().x;
        alturaArriba = 0 - sprite.getGlobalBounds().height / 2;
        alturaAbajo = _juego->window.getSize().y + 100;
        
        maxTub = 3;
        for (unsigned short int i = 0; i < maxTub; i++) {

            RandomY();
            
            sprite.setPosition(margen + (DIST_TUB * (i + 1)), alturaArriba + spawnY);
            tubArriba[i] = sprite;
            
            sprite.rotate(180);
            sprite.setPosition(margen + (DIST_TUB * (i + 1)), alturaAbajo + spawnY);
            tubAbajo[i] = sprite;
            
            sprite.rotate(-180);
            sumaScore[i] = true;
        }
    }

    void TuberiasManager::Mover(float tiempoActual) {
        float moviemiento = 0.0f;
        unsigned short int _siguiente = -1;
        
        for (unsigned short int i = 0; i < maxTub; i++)
        {
            if (tubArriba[i].getPosition().x <
                0 - ancho)
            {
                switch(i)
                {
                    case 0:
                        _siguiente = 2;
                        break;
                    case 1:
                        _siguiente = 0;
                        break;
                    case 2:
                        _siguiente = 1;
                        break;
                }
                
                RandomY();
                        
                tubArriba[i].setPosition(tubArriba[_siguiente].getPosition().x
                    +DIST_TUB, alturaArriba + spawnY);
                tubAbajo[i].setPosition(tubAbajo[_siguiente].getPosition().x
                    +DIST_TUB, alturaAbajo + spawnY);
                
                sumaScore[i] = true;
            }
            
            moviemiento = VELOCIDAD * tiempoActual;
            tubArriba[i].move(-moviemiento, 0);
            tubAbajo[i].move(-moviemiento, 0);
        }
    }

    void TuberiasManager::Dibujar() {
        for (unsigned short int i = 0; i < maxTub; i++) {
            _juego->window.draw(tubArriba[i]);
            _juego->window.draw(tubAbajo[i]);
        }
    }

    void TuberiasManager::RandomY() {
        int negativo = spawnY = rand() % (0 - 2);
        spawnY = rand() % (200 - 1);
        
        if (negativo == 1) {
            spawnY = spawnY * (-1);
        }
    }

    float TuberiasManager::GetPuntoMedio() {
        return puntoMedio;
    }

    sf::Sprite &TuberiasManager::GetTubA(int pos)
    {
        return tubArriba[pos];
    }
    
    sf::Sprite &TuberiasManager::GetTubB(int pos)
    {
        return tubAbajo[pos];
    }
        
    bool &TuberiasManager::GetSumaScore(int pos)
    {
        return sumaScore[pos];
    }
    
    int TuberiasManager::Tamanyo()
    {
        return maxTub;
    }
}