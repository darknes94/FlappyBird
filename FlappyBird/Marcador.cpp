#include "Marcador.hpp"

namespace Flappy
{
    Marcador::Marcador()
    {
        _juego = Juego::Instance();
        
        score = 0;
        totalMonedas = 0;
        
        scoreText.setFont(_juego->assets.GetFuente("Fuente"));
        scoreText.setString(to_string(score));
        scoreText.setCharacterSize(75);
        scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().width / 2,
            scoreText.getGlobalBounds().height / 2));
        scoreText.setPosition(sf::Vector2f(_juego->window.getSize().x / 2, 50));
        
        moneda = new Moneda(50, 50);
        monedaText.setFont(_juego->assets.GetFuente("Fuente"));
        monedaText.setString("x "+to_string(totalMonedas));
        monedaText.setCharacterSize(40);
        monedaText.setOrigin(sf::Vector2f(monedaText.getGlobalBounds().width / 2,
            monedaText.getGlobalBounds().height / 2));
        monedaText.setPosition(sf::Vector2f(90, 20));
    }
    
    void Marcador::ActualizarMarcador()
    {
        score++;
        scoreText.setString(to_string(score));
    }
    
    void Marcador::RotarMoneda()
    {
        moneda->Animar();
    }
    
    void Marcador::ActualizarMonedas()
    {
        totalMonedas++;
        monedaText.setString("x "+to_string(totalMonedas));
    }
    
    void Marcador::DibujarMarcador()
    {
        _juego->window.draw(scoreText);
        _juego->window.draw(monedaText);
        moneda->Dibujar();
    }
    
    int Marcador::GetScore()
    {
        return score;
    }
    
    int Marcador::GetTotalMonedas()
    {
        return totalMonedas;
    }
}