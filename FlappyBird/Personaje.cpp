#include "Personaje.hpp"

namespace Flappy
{
    Personaje::Personaje()
    {
        _juego = Juego::Instance();
        
        nFrame = 1;
        rotacion = 0;
        estado = QUIETO;
        sprite.setTexture(_juego->assets.GetTextura("Personaje"));
        
        maxFrames = 4;
        frames[0] = sf::IntRect(0, 0, 77, 54);
        frames[1] = sf::IntRect(77, 0, 77, 54);
        frames[2] = sf::IntRect(154, 0, 77, 54);
        frames[3] = sf::IntRect(77, 0, 77, 54);
        
        xIni = ANCHO/2-sprite.getGlobalBounds().width/2;
        yIni = ALTO/2;
        
        yQuieto = VELO_ANIM_QUIETO;
        ySalto = yIni;
        
        sprite.setTextureRect(frames[nFrame]);
        sprite.setPosition(xIni, yIni);
        
        sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2-5);
        
        // Circulo de colision
        circulo.setRadius(25);
        circulo.setOrigin(sprite.getOrigin());
        circulo.setPosition(sprite.getPosition());
        
        alturaMax = 0-sprite.getGlobalBounds().height;
    }

    void Personaje::Animar(float tiempoActual)
    {
        if ((estado == QUIETO) || (rotacion == 90.0f)) // Frame de quieto y caida
        {
            sprite.setTextureRect(frames[1]);
        }
        else
        {
            if (relojAnim.getElapsedTime().asSeconds() > ANIM_PERSONAJE / maxFrames)
            {
                if (nFrame < maxFrames-1)
                {
                    nFrame++;
                }
                else
                {
                    nFrame = 0;
                }

                sprite.setTextureRect(frames[nFrame]);
                relojAnim.restart();
            }
        }
    }
    
    void Personaje::Actualizar(float tiempoActual)
    {
        if (estado == VOLANDO)                     // Sube
        {
            // No llega a salirse infinitamente de la ventana
            if (sprite.getPosition().y >= alturaMax)
            {
                sprite.move(0, -GRAVEDAD-1);
            }
        }
        else if (estado == CAYENDO)                // Baja
        {
            Caida(tiempoActual);
        }
        
        if ((relojMove.getElapsedTime().asSeconds() > T_VUELO)
            && (estado == VOLANDO))
        {
            relojMove.restart();
            estado = CAYENDO;
        }
        
        circulo.setPosition(sprite.getPosition());
    }
    
    void Personaje::Salto()
    {
        relojMove.restart();
        estado = VOLANDO;
        rotacion = -25.0f;
        sprite.setRotation(rotacion);
        ySalto = sprite.getPosition().y;
        _juego->assets.GetVuelo().play();
    }
    
    void Personaje::Dibujar()
    {
        _juego->window.draw(sprite);
        //_juego->window.draw(_circulo);
    }
    
    sf::CircleShape &Personaje::GetCirculo()
    {
        return circulo;
    }
    
    unsigned short int &Personaje::GetEstado()
    {
        return estado;
    }
    
    void Personaje::Caida(float tiempoActual)
    {
        if (ySalto < sprite.getPosition().y)   // Baja mas deprisa y gira
        {
            rotacion += ROTACION*tiempoActual;
            if (rotacion > 90.0f)
            {
                rotacion = 90.0f;
            }
            sprite.setRotation(rotacion);
            sprite.move(0, GRAVEDAD+6);
        }
        else                                    // Baja mas despacio
        {
            sprite.move(0, GRAVEDAD-0.5);
        }
        
        circulo.setPosition(sprite.getPosition());
    }
    
    // Animacion de cuando esta QUIETO
    void Personaje::AnimQuieto()
    {
        if (sprite.getPosition().y <= yIni-MARGEN_MOV)
        {
            yQuieto = VELO_ANIM_QUIETO;
        }
        else if (sprite.getPosition().y >= yIni+MARGEN_MOV)
        {
            yQuieto = -VELO_ANIM_QUIETO;
        }
        sprite.move(0, yQuieto);
    }
}