#include "Moneda.hpp"
using namespace std;
#include "iostream"

namespace Flappy
{
    Moneda::Moneda()
    {
        Instanciar();
        moneda.setPosition(50.0f,50.0f);
        
        xFin = 650.0f;
        yFin = 277.5f;
         
        Vox = 19.5f;
        Voy = -1.0f;
    }
    
    Moneda::Moneda(float x, float y)
    {
        Instanciar();
        moneda.setPosition(x,y);
    }
    
    Moneda::Moneda(float x)
    {
        Instanciar();
        moneda.setPosition(x,RandomY());
    }
    
    void Moneda::Instanciar() {
        _juego = Juego::Instance();
        
        nFrame = 0;
        maxFrames = 6;
        
        moneda.setTexture(&_juego->assets.GetTextura("Moneda"));
        
        frames[0] = sf::IntRect(0, 0, 96, 96);
        frames[1] = sf::IntRect(96, 0, 96, 96);
        frames[2] = sf::IntRect(192, 0, 96, 96);
        frames[3] = sf::IntRect(288, 0, 96, 96);
        frames[4] = sf::IntRect(384, 0, 96, 96);
        frames[5] = sf::IntRect(480, 0, 96, 96);
        
        moneda.setRadius(25);
        moneda.setOrigin(96/2,96/2);
        moneda.setTextureRect(frames[0]);
        
        sumar = true;
        colocada = true;
        llover = true;
        
        xFin = 50.0f;
        yFin = 50.0f;
        
        Vox = -9.0f;
        Voy = -1.0f;
    }
    
    void Moneda::Animar() 
    {
        if (relojAnim.getElapsedTime().asSeconds() > VELO_ANIM_MONEDA / maxFrames)
        {
            if (nFrame < maxFrames-1)
            {
                nFrame++;
            }
            else
            {
                nFrame = 0;
            }

            moneda.setTextureRect(frames[nFrame]);
            relojAnim.restart();
        }
    }
    
    void Moneda::Dibujar()
    {
        _juego->window.draw(moneda);
    }
    
    void Moneda::Mover(float x, float y)
    {
        moneda.move(x, y);
    }
    
    float Moneda::GetX() 
    {
        return moneda.getPosition().x;
    }
    
    float Moneda::GetY() 
    {
        return moneda.getPosition().y;
    }
    
    // Y entre 100 y 850
    int Moneda::RandomY() {
        return 100+rand()%(851-100);
    }
    
    void Moneda::SetY()
    {
        moneda.setPosition(GetX(),RandomY());
    }
    
    void Moneda::SetX(float x)
    {
        moneda.setPosition(x,GetY());
        sumar = true;
        colocada = true;
    }
    
    sf::CircleShape &Moneda::GetCirculo()
    {
        return moneda;
    }
    
    bool Moneda::GetCogerMoneda()
    {
        return sumar;
    }
    
    void Moneda::SetCogerMoneda()
    {
        sumar = false;
        colocada = false;
    }
    
    bool Moneda::Colocada()
    {
        return colocada;
    }
    
    bool Moneda::Llover()
    {
        return llover;
    }
    
    void Moneda::Lluvia(){
        Voy++;
        if ((GetX() < xFin) && (GetY() < yFin)) {
            Mover(Vox,Voy);
        } else {
            llover = false;
        }
    }
    
    /*void Moneda::Parabola(){
        Voy--;
        if ((GetX() > xFin) && (GetY() > yFin)) {
            Mover(Vox,Voy);
        }
    }*/
}


        