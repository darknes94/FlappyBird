#include "Juego.hpp"
#include "EstadoMenu.hpp"

namespace Flappy
{
    Juego* Juego::_pinstance=0;
    
    Juego* Juego::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new Juego();
        }
        return _pinstance;
    }
    
    Juego::~Juego()
    {
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void Juego::Iniciar()
    {
        window.create(sf::VideoMode(ANCHO, ALTO), TITULO_WINDOW);
        
        //Activa la sincronizacion vertical (60 fps)
        window.setVerticalSyncEnabled(true); 
        window.setFramerateLimit(60);
        
        maquina.Anyadir(EstadoMenu::Instance());
        
        float tiempoActual = 0;
        
        //Cargar imagenes
        assets.CargarTextura("Suelo", SUELO);
        assets.CargarTextura("Fondo Menu", FONDO);
        assets.CargarTextura("Titulo juego", TITULO);
        assets.CargarTextura("Tuberia", TUBERIA);
        assets.CargarTextura("Moneda", MONEDA);
        assets.CargarTextura("Ready", READY);
        assets.CargarTextura("Personaje", PAJARO);
        
        assets.CargarTextura("Bronce", BRONCE);
        assets.CargarTextura("Oro", ORO);
        assets.CargarTextura("Plata", PLATA);
        assets.CargarTextura("Platino", PLATINO);
        assets.CargarTextura("Panel", PANEL);
        assets.CargarTextura("Game over", GAME_OVER);
        assets.CargarTextura("Ganar", WIN);
        
        // Audios
        assets.CargarAudios();
        
        while (window.isOpen()) 
        {
            tiempoActual = reloj.restart().asMilliseconds();
            
            maquina.ProcesarPilaEstados();
            maquina.GetEstadoActivo()->ManejarEventos();
            
            // Actualiza 15 veces por segunto
            if (tiempoActual >= (1/15)) {
                maquina.GetEstadoActivo()->Actualizar(tiempoActual);
                tiempoActual = reloj.restart().asMilliseconds();
            }
            
            // Actualiza siempre
            maquina.GetEstadoActivo()->Dibujar(tiempoActual);
        }
    }
}