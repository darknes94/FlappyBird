#include "EstadoMenu.hpp"
#include "EstadoJuego.hpp"

namespace Flappy
{
    EstadoMenu::EstadoMenu()
    {
        _juego = Juego::Instance();
    }
    
    EstadoMenu* EstadoMenu::_pinstance=0;
    
    EstadoMenu* EstadoMenu::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoMenu();
        }
        return _pinstance;
    }
    
    void EstadoMenu::Vaciar()
    {
        _pinstance=0;
    }
    
    EstadoMenu::~EstadoMenu()
    {
        delete suelo;
        suelo = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoMenu::Init()
    {
        // Imagen de fondo y titulo
        fondo.setTexture(_juego->assets.GetTextura("Fondo Menu"));
        titulo.setTexture(_juego->assets.GetTextura("Titulo juego"));
        
        // Texto
        _juego->assets.CargarFuente("Fuente", FUENTE);
        fuente.setFont(_juego->assets.GetFuente("Fuente"));
        fuente.setString(EMPEZAR);
        fuente.setCharacterSize(50);
        
        titulo.setPosition((ANCHO / 2) - (titulo.getGlobalBounds().width / 2), titulo.getGlobalBounds().height / 2);
        fuente.setPosition((ANCHO / 2)- 150, titulo.getPosition().y+250);
        
        // Suelo
        suelo = new Suelo();
        personaje = new Personaje();
        
        yIni = titulo.getPosition().y;
        yQuieto = VELO_ANIM_TIT;
    }
    
    void EstadoMenu::ManejarEventos()
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (_juego->window.pollEvent(event))
        {
            switch(event.type)
            {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    _juego->window.close();
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla
                    switch(event.key.code)
                    {
                        //Mapeo del cursor
                        case sf::Keyboard::Space:
                            _juego->maquina.Anyadir(EstadoJuego::Instance());
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
    
    void EstadoMenu::Actualizar(float tiempoActual)
    {
        MoverTitulo();
        personaje->AnimQuieto();
        suelo->MoverSuelo(tiempoActual);
    }
    
    void EstadoMenu::Dibujar(float tiempoActual)
    {
        _juego->window.clear();
        
        _juego->window.draw(fondo);
        _juego->window.draw(titulo);
        _juego->window.draw(fuente);
        personaje->Dibujar();
        suelo->Dibujar();
        
        _juego->window.display();
    }
    
    void EstadoMenu::MoverTitulo()
    {
        if (titulo.getPosition().y <= yIni-MARGEN_MOV)
        {
            yQuieto = VELO_ANIM_TIT;
        }
        else if (titulo.getPosition().y >= yIni+MARGEN_MOV)
        {
            yQuieto = -VELO_ANIM_TIT;
        }
        titulo.move(0, yQuieto);
        //_fuente.move(0, yQuieto);
    }
}