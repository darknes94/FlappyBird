#pragma once

// Textos fijos
#define EMPEZAR "Pulsa espacio"
#define REINTENTAR "para reintentar"

// Fuente
#define FUENTE "resources/font/FlappyFont.ttf"

// Archivo con maxscore
#define ARCH_MAXSCORE "resources/score/maxscore.txt"

// Audio
#define A_GOLPE "resources/audio/golpe.wav"
#define A_VUELO "resources/audio/vuelo.wav"
#define A_PUNTO "resources/audio/punto.wav"

// Imagenes
#define FONDO "resources/fondo.png"
#define SUELO "resources/suelo.png"
#define TITULO "resources/titulo.png"
#define TUBERIA "resources/tuberia.png"
#define READY "resources/get-ready.png"
#define WIN "resources/win.png"

#define PAJARO "resources/bird.png"
#define MONEDA "resources/moneda.png"

#define PANEL "resources/panel.png"
#define GAME_OVER "resources/game-over.png"

#define BRONCE "resources/bronce.png"
#define ORO "resources/oro.png"
#define PLATA "resources/plata.png"
#define PLATINO "resources/platino.png"

// Datos fijos del juego
#define VELOCIDAD 0.3f          // Velocidad del suelo y las tuberias
#define ANIM_PERSONAJE 0.4f     // Animacion mover alas
#define GRAVEDAD 6.75f
#define VELO_ANIM_QUIETO 0.6f   // Velocidad anim. estado QUIETO
#define MARGEN_MOV 6.0f         // Margen movimiento anim. estado QUIETO
#define T_VUELO 0.24f           // T. vuelo del personaje antes de caer
#define ROTACION 0.4f         // Velocidad de rotacion al caer
#define FLASH 2.0f           // Flash que aparece antes del GAME OVER
#define DIST_TUB 500            // Distancia entre tuberias

#define VELO_ANIM_TIT 0.4f   // Velocidad anim. titulo menu
#define VELO_ANIM_MONEDA 0.6f     // Velocidad de animacion moneda

// Estados
#define QUIETO 0
#define VOLANDO 1
#define CAYENDO 2
#define CHOQUE 3
#define MUERTO 4

// Medallas
#define BRONCE_SCORE 0
#define PLATA_SCORE 5
#define ORO_SCORE 15
#define PLATINO_SCORE 25        // Fin del juego