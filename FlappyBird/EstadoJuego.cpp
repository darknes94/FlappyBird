#include "EstadoJuego.hpp"
#include "EstadoGameOver.hpp"

namespace Flappy
{
    EstadoJuego::EstadoJuego()
    {
        _juego = Juego::Instance();
    }
    
    EstadoJuego* EstadoJuego::_pinstance=0;
    
    EstadoJuego* EstadoJuego::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoJuego();
        }
        return _pinstance;
    }
    
    void EstadoJuego::Vaciar()
    {
        _pinstance=0;
    }
    
    EstadoJuego::~EstadoJuego()
    {
        delete marcador;
        marcador = NULL;
        delete suelo;
        suelo = NULL;
        delete personaje;
        personaje = NULL;
        delete tuberias;
        tuberias = NULL;
        delete moneda;
        moneda = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoJuego::Init()
    {
         marcador = new Marcador();
         suelo = new Suelo();
         personaje = new Personaje();
         tuberias = new TuberiasManager();
         
         numTub=0;
        // Y entre 100 y 850
        moneda = new Moneda(tuberias->GetTubA(numTub).getPosition().x+DIST_TUB/2);

                 
         // Imagen de fondo
         fondo.setTexture(_juego->assets.GetTextura("Fondo Menu"));
         preparadoText.setTexture(_juego->assets.GetTextura("Ready"));
         
         
         // Ready
         preparadoText.setOrigin(sf::Vector2f(preparadoText.getGlobalBounds().width / 2, preparadoText.getGlobalBounds().height / 2));
         preparadoText.setPosition(sf::Vector2f(_juego->window.getSize().x / 2, 300));

         gameOver = false;
         
         //Flash
        fondoFlash = sf::RectangleShape(sf::Vector2f(_juego->window.getSize().x, _juego->window.getSize().y));
        fondoFlash.setFillColor(sf::Color(255, 255, 255, 0));
        flashOn = false;
        sonar = false;
    }
     
    void EstadoJuego::ManejarEventos()
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (_juego->window.pollEvent(event))
        {
            switch(event.type) {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    _juego->window.close();
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla
                    switch(event.key.code) {
                        //Mapeo del cursor
                        case sf::Keyboard::Space:
                            
                            if ((!gameOver)
                                && (personaje->GetEstado() != CHOQUE)
                                && (personaje->GetEstado() != MUERTO))
                            {
                                personaje->Salto();
                            }
                        break;
                        
                        //Tecla M para anyadir monedas
                        case sf::Keyboard::M:
                            marcador->ActualizarMonedas();
                        break;
                        
                        //Tecla N para anyadir score
                        case sf::Keyboard::N:
                            marcador->ActualizarMarcador();
                        break;
                        
                        //Tecla G para ganar
                        case sf::Keyboard::G:
                            do {
                                marcador->ActualizarMarcador();
                            } while(marcador->GetScore() < PLATINO_SCORE);
                        break;
                        
                        //Tecla H para perder
                        case sf::Keyboard::H:
                            gameOver = true;
                        break;
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            _juego->window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            cout << event.key.code << endl;
                        break;
                    }
                break;
            }
        }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        // Degradamos la pantalla blanca para hacer un flash
        if (flashOn)
        {
            int alpha = (int)fondoFlash.getFillColor().a + (FLASH * tiempoActual);

            if (alpha >= 255.0f)
            {
                alpha = 255.0f;
                flashOn = false;
                gameOver = true;
            }
            fondoFlash.setFillColor(sf::Color(255, 255, 255, alpha));
        }
        
        // Fin del juego
        if (marcador->GetScore() >= PLATINO_SCORE)
        {
            flashOn = true;
        }
            
        if (!gameOver)
        {
            if (personaje->GetEstado() == QUIETO)
            {
                personaje->AnimQuieto();
                suelo->MoverSuelo(tiempoActual);
                marcador->RotarMoneda();
            }
            else
            {
                if (ColisionSuelo())
                {
                    personaje->GetEstado() = MUERTO;
                    if (!sonar) {
                        _juego->assets.GetGolpe().play();
                        sonar = true;
                    }
                    flashOn = true;
                }

                if (personaje->GetEstado() == CHOQUE)
                {
                    personaje->Caida(tiempoActual);
                }
                else if (personaje->GetEstado() != MUERTO)
                {
                    personaje->Animar(tiempoActual);
                    personaje->Actualizar(tiempoActual);
                    suelo->MoverSuelo(tiempoActual);
                    marcador->RotarMoneda();
                    tuberias->Mover(tiempoActual);
                    
                    ColisionTuberiasScore();
                    ColisionMoneda();
                    MonedaEnPantalla(tiempoActual);
                    
                    if (ColisionTuberias())
                    {
                        personaje->GetEstado() = CHOQUE;
                        if (!sonar) {
                            _juego->assets.GetGolpe().play();
                            sonar = true;
                        }
                    }
                }
            }
        }
        else
        {
            _juego->maquina.Eliminar();
            _juego->maquina.Anyadir(EstadoGameOver::Instance(marcador->GetScore(),
                marcador->GetTotalMonedas()), true);
        }
    }
    
    void EstadoJuego::Dibujar(float tiempoActual)
    {
        _juego->window.clear();
        
        _juego->window.draw(fondo);
        tuberias->Dibujar();
        personaje->Dibujar();
        suelo->Dibujar();
        marcador->DibujarMarcador();
        moneda->Dibujar();
        
        if (personaje->GetEstado() == QUIETO)
        {
            _juego->window.draw(preparadoText);
        }
        
        if (flashOn)
        {
            _juego->window.draw(fondoFlash);
        }
        
        _juego->window.display();
    }
    
    bool EstadoJuego::ColisionSuelo()
    {
        if ((personaje->GetCirculo().getGlobalBounds().intersects(
            suelo->GetSprite(0).getGlobalBounds()))
            || (personaje->GetCirculo().getGlobalBounds().intersects(
            suelo->GetSprite(1).getGlobalBounds())))
        {
            return true;
        }
        return false;
    }
    
    // Colision con la tuberia para sumar puntos
    void EstadoJuego::ColisionTuberiasScore()
    {
        for (unsigned short int i = 0; i < tuberias->Tamanyo(); i++) {
            
            float pos = tuberias->GetTubA(i).getPosition().x
                - tuberias->GetPuntoMedio();
            
            if (( personaje->GetCirculo().getPosition().x >= pos)
                && (tuberias->GetSumaScore(i)))
            {
                tuberias->GetSumaScore(i) = false;
                _juego->assets.GetPunto().play();
                marcador->ActualizarMarcador();
            }
        }
    }
    
    bool EstadoJuego::ColisionTuberias()
    {
        for (unsigned short int i = 0; i < tuberias->Tamanyo(); i++) {
            
            if ((personaje->GetCirculo().getGlobalBounds().intersects(
                tuberias->GetTubA(i).getGlobalBounds()))
                || (personaje->GetCirculo().getGlobalBounds().intersects(
                tuberias->GetTubB(i).getGlobalBounds())))
            {
                return true;
            }
        }
        return false;
    }
    
    void EstadoJuego::ColisionMoneda()
    {
        if ((personaje->GetCirculo().getGlobalBounds().intersects(
            moneda->GetCirculo().getGlobalBounds()))
            && (moneda->GetCogerMoneda()))
        {
            _juego->assets.GetPunto().play();
            
            moneda->SetCogerMoneda();
            
            marcador->ActualizarMonedas();
        }
    }
    
    void EstadoJuego::MonedaEnPantalla(float tiempoActual)
    {
        if ((!moneda->Colocada()) || (moneda->GetX() <= 0)) {
            
            // Aparece una tuberia si, otra no
            numTub += 2;
            if (numTub >= 4) {
                numTub = 1;
            } else if (numTub >= 3) {
                numTub = 0;
            }
            moneda->SetY();
            moneda->SetX(tuberias->GetTubA(numTub).getPosition().x+DIST_TUB/2);
        }
        
        moneda->Mover(-(VELOCIDAD*tiempoActual), 0);
        moneda->Animar();
    }
}