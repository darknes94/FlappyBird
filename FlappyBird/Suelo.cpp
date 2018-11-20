#include "Suelo.hpp"

namespace Flappy
{
    Suelo::Suelo()
    {
        _juego = Juego::Instance();
        
        sf::Sprite sprite(_juego->assets.GetTextura("Suelo"));
           
        y = _juego->window.getSize().y - sprite.getLocalBounds().height+150;
        ancho = sprite.getLocalBounds().width;
        
        sprite.setPosition(0, y);
        SpritesSuelo.push_back(sprite);
        
        sprite.setPosition(ancho, y);
        SpritesSuelo.push_back(sprite);
    }

    void Suelo::MoverSuelo(float tiempoActual)
    {
        float movimiento = VELOCIDAD * tiempoActual;
        int auxAncho = 0 - ancho;

        if (SpritesSuelo.at(0).getPosition().x < auxAncho)
        {
            SpritesSuelo.at(0).setPosition(SpritesSuelo.at(1).getPosition().x+ancho, y);
        }

        if (SpritesSuelo.at(1).getPosition().x < auxAncho)
        {
            SpritesSuelo.at(1).setPosition(SpritesSuelo.at(0).getPosition().x+ancho, y);
        }

        SpritesSuelo.at(0).move(-movimiento, 0.0f);
        SpritesSuelo.at(1).move(-movimiento, 0.0f);
    }

    void Suelo::Dibujar()
    {
        for (unsigned short int i = 0; i < SpritesSuelo.size(); i++)
        {
            _juego->window.draw(SpritesSuelo.at(i));
        }
    }
    
    sf::Sprite &Suelo::GetSprite(int pos)
    {
        return SpritesSuelo.at(pos);
    }
}