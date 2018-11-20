#include <fstream>              // Para leer y escribir un fichero
#include "EstadoGameOver.hpp"
using namespace std;

namespace Flappy
{
    EstadoGameOver::EstadoGameOver(int sc, int monedas)
    {
        _juego = Juego::Instance();
        score = sc;
        totalMonedas = monedas;
        scoreMonedas = score+totalMonedas;
    }
    
    EstadoGameOver* EstadoGameOver::_pinstance=0;
    
    EstadoGameOver* EstadoGameOver::Instance(int sc, int monedas)
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoGameOver(sc, monedas);
        }
        return _pinstance;
    }
    
    void EstadoGameOver::Vaciar()
    {
        _pinstance=0;
    }
    
    EstadoGameOver::~EstadoGameOver()
    {
        delete suelo;
        suelo = NULL;
        
        if (totalMonedas > 0) {
            delete[] monedero;
        }
        
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoGameOver::Init()
    {
        ifstream readFile;
        readFile.open(ARCH_MAXSCORE);
        
        if (readFile.is_open())
        {
            while (!readFile.eof())
            {
                readFile >> maxScore;
            }
        }
        readFile.close();
        
        ofstream writeFile(ARCH_MAXSCORE);
        if (writeFile.is_open())
        {
            if ((scoreMonedas) > maxScore)
            {
                maxScore = (scoreMonedas);
            }
            
            writeFile << maxScore;
        }
        writeFile.close();
        
        //Cargar suelo
        suelo = new Suelo();
        
        // Imagen de fondo
        fondo.setTexture(_juego->assets.GetTextura("Fondo Menu"));
        panel.setTexture(_juego->assets.GetTextura("Panel"));
        
        ObtenerMedallaTitulo();
        auxScore = 0;
        
        yIniTit = titulo.getGlobalBounds().height / 2;
        
        titulo.setPosition((ANCHO / 2) - (titulo.getGlobalBounds().width / 2), -600);
        
        panel.setPosition((ANCHO / 2) - (panel.getGlobalBounds().width / 2), 
            titulo.getPosition().y + titulo.getGlobalBounds().height+50);
        
        medalla.setPosition(175, panel.getPosition().y+100);
        
        
        // Puntos
        scoreText.setFont(_juego->assets.GetFuente("Fuente"));
        scoreText.setString(to_string(auxScore));
        scoreText.setCharacterSize(56);
        scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().width / 2, 
            scoreText.getGlobalBounds().height / 2));
        scoreText.setPosition(sf::Vector2f(_juego->window.getSize().x / 10 * 7.25,
            panel.getPosition().y+105));
        
        maxScoreText.setFont(_juego->assets.GetFuente("Fuente"));
        maxScoreText.setString(to_string(maxScore));
        maxScoreText.setCharacterSize(56);
        maxScoreText.setOrigin(sf::Vector2f(maxScoreText.getGlobalBounds().width / 2,
            maxScoreText.getGlobalBounds().height / 2));
        maxScoreText.setPosition(sf::Vector2f(_juego->window.getSize().x / 10 * 7.25,
            panel.getPosition().y+210));
        
        
        // Texto reiniciar
        reintentar1.setFont(_juego->assets.GetFuente("Fuente"));
        reintentar1.setString(EMPEZAR);
        reintentar1.setCharacterSize(50);
        reintentar1.setPosition((ANCHO / 2) - reintentar1.getGlobalBounds().width/2, panel.getPosition().y+310);
        
        reintentar.setFont(_juego->assets.GetFuente("Fuente"));
        reintentar.setString(REINTENTAR);
        reintentar.setCharacterSize(50);
        reintentar.setPosition((ANCHO / 2) - reintentar.getGlobalBounds().width/2, reintentar1.getPosition().y+50);
        
        // Desactivar controles
        activarControl = false;
        
        if (totalMonedas > 0) {
            monedero = new Moneda[totalMonedas];
        }
        activarLluvia = false;
    }
    
    void EstadoGameOver::ManejarEventos()
    {
        if (activarControl) {
            //Bucle de obtención de eventos
            sf::Event event;
            while (_juego->window.pollEvent(event)) {
                
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
                                _juego->maquina.Eliminar();
                                _juego->maquina.Anyadir(EstadoJuego::Instance(), true);
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
    }
    
    void EstadoGameOver::Actualizar(float tiempoActual)
    {
        // Animacion del titulo y el cartel
        float velocidad = VELO_ANIM_TIT*tiempoActual;
        float y = titulo.getPosition().y;
        if (y <= yIniTit)
        {
            titulo.setPosition(titulo.getPosition().x, y+velocidad);
            panel.setPosition(panel.getPosition().x, panel.getPosition().y+velocidad);
            
            scoreText.setPosition(scoreText.getPosition().x, scoreText.getPosition().y+velocidad);
            maxScoreText.setPosition(maxScoreText.getPosition().x, maxScoreText.getPosition().y+velocidad);
            medalla.setPosition(medalla.getPosition().x, medalla.getPosition().y+velocidad);
            
            reintentar1.setPosition(reintentar1.getPosition().x, reintentar1.getPosition().y+velocidad);
            reintentar.setPosition(reintentar.getPosition().x, reintentar.getPosition().y+velocidad);
            
        } else {
            activarControl = true;
            
            // Animacion del Score
            AnimarScore();
            
            // Desactivar la lluvia de monedas
            if (totalMonedas > 0) {
                if (!monedero[totalMonedas-1].Llover()) {
                    activarLluvia = false;
                }
            }
        }
    }
    
    void EstadoGameOver::Dibujar(float tiempoActual)
    {
        _juego->window.clear();
        
        _juego->window.draw(fondo);
        suelo->Dibujar();
        _juego->window.draw(titulo);
        _juego->window.draw(panel);
        
        
        if ((totalMonedas > 0) && (activarLluvia)) {
            LluviaDeMonedas();
        }
        
        _juego->window.draw(scoreText);
        _juego->window.draw(maxScoreText);
        _juego->window.draw(medalla);
        _juego->window.draw(reintentar1);
        _juego->window.draw(reintentar);
        
        _juego->window.display();
    }
    
    void EstadoGameOver::ObtenerMedallaTitulo()
    {
        if (scoreMonedas >= PLATINO_SCORE)
        {
            titulo.setTexture(_juego->assets.GetTextura("Ganar"));
            medalla.setTexture(_juego->assets.GetTextura("Platino"));
        }
        else if (scoreMonedas >= ORO_SCORE)
        {
            titulo.setTexture(_juego->assets.GetTextura("Game over"));
            medalla.setTexture(_juego->assets.GetTextura("Oro"));
        }
        else if (scoreMonedas >= PLATA_SCORE)
        {
            titulo.setTexture(_juego->assets.GetTextura("Game over"));
            medalla.setTexture(_juego->assets.GetTextura("Plata"));
        }
        else
        {
            titulo.setTexture(_juego->assets.GetTextura("Game over"));
            medalla.setTexture(_juego->assets.GetTextura("Bronce"));
        }
    }
    
    void EstadoGameOver::AnimarScore()
    {
        if ((auxScore < score) && 
            (relojAnim.getElapsedTime().asSeconds() > 0.1f)) {
            
                auxScore++;
                scoreText.setString(to_string(auxScore));
                relojAnim.restart();
                
        } else if ((totalMonedas > 0) && (auxScore == score)) {
            activarLluvia = true;
        }
    }
    
    void EstadoGameOver::LluviaDeMonedas()
    {
        for (unsigned short int i=0; i<totalMonedas; i++) {
                
            if ((relojAnim.getElapsedTime().asSeconds() > 0.01f)
                && (monedero[i].Llover()))
            {
                monedero[i].Lluvia();
                monedero[i].Animar();
                monedero[i].Dibujar();

                if (monedero[i].GetCogerMoneda()) {
                    _juego->assets.GetPunto().play();
                    auxScore++;
                    scoreText.setString(to_string(auxScore));
                    monedero[i].SetCogerMoneda();
                }
                relojAnim.restart();
            }
        }
    }
}