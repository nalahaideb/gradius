#ifndef GRADIUS_H
#define GRADIUS_H
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Sound.h"
static bool godMode = false;
static bool avoidCopyRight = false;
static bool quitGame = false;    
static Surface surface(W, H);

enum gameState
{
    TITLE, GAMEPLAY, QUITGAME
};  
//ID 
enum lsrID
{
    playerLaserID, alienLaserID
};
enum entID
{
    PLAYER, ALIEN, FLEET, SKELETRONID, ENTITY 
};
enum stateID
{
   AGGRO, IN_FLEET, REJOIN, HOMING, DIVE
};
static gameState GAME_STATE = TITLE;
//static sounds
static Sound explosionSound("sounds/SuperMissileExplosion.wav");
static Sound enemyLaser("sounds/BasicChargedShot.wav");
static Sound skeletronRoar("sounds/TerrariaRoar.wav");
//custom
#include "Timer.h"
#include "Entity.h"
#include "Laser.h"
#include "Player.h"
#include "Star.h"
#include "Explosion.h"
#include "HUD.h"
//now all of gradius knows youre here...
static Entity * PLAYA;
#include "Alien.h"
#include "SKELETRON.h"
#include "Grunt.h"
#include "Mothership.h"
#include "SquadMember.h"
#include "Fleet.h"
#include "GameMaster.h"

// class OrbFlinger: public Alien {};
// class Kamikaze: public Alien {};


// Alien::Alien(Image * image = NULL, int x = W + 100, int y = rand() % H)
// :Entity(image, ALIEN, x, y), player(PLAYA),
//  movementTimer(getTicks(), 10), attackTimer(getTicks(), rand() % 4000 + 2000)
// class Sniper: public Alien
// {
//     //use surface.putline(x0, x1, y0, y1, r, g, b)
//     inline Sniper()
//         :Alien(new Image("images/galaxian/GalaxianFlagship.gif"), W + rand() % 50, rand() % H - 20)    
//     {
//         attackTimer.setInterval(10000);
//     }
//     inline void run()
//     {
        
//     }
    
// };

//﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽
//the testing will be good and the bugs destroyed inshallah
//﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽

//************************************************************************************
//overall state / wellness checks
// inline void gameReset()
// {
    
//     exploVector.clear(), laserray.clear(), livingEntities.clear();
//     Mothership::squadOffset = -64, Player::resetLives();
// }
inline void runAliens();
inline void collisionCheck(std::vector < Entity * > &livingEntities, Player * player);
inline void killCheck(std::vector < Entity * > &livingEntities);
inline void drawEntities(std::vector < Entity * > &livingEntities);
inline void explodingExplosions(std::vector < Explosion * > &e);
//************************************************************************************

//************************************************************************************
//general drawing functions-----------------------------------------------------------
inline void drawAfterMe();
inline void drawBeforeMe();
//************************************************************************************

//************************************************************************************
//laser test functions----------------------------------------------------------------
//this moves the laser if its alive, deletes it if its alive and not below W
inline void laserAliveCheck();
//redraws the lasers
inline void drawLaserray();
//moves lasers. wow
inline void moveLaserray();
//************************************************************************************

//************************************************************************************
//GRAPHIX!!!
//this needs to be fixed, literally everything is in here
void test_image();

static void moveRects(Rect * e, Rect * score)
{
    if (e->x + e->w <= 0) {e->x = rand() % 600 + W, e->y = rand() % H;}
    e->x -= 1;
    score->x = e->x + 8, score->y = e->y + e->h;
}
inline void titleScreen()
{
    Surface * psurface = &surface;
    KeyPressed keypressed;
    Event event;
    //GameMaster gameMaster(1000);
    Font font("fonts/gradius.ttf", 96);
    Image title(font.render("G R A D I U S", GREEN));
    Font nameFont("fonts/gradius.ttf", 48);
    Image myName(nameFont.render("Nasser Alahaideb  COSC245 SPR24", GREEN));
    //lol, like get rekt. get it? lol...
    Rect titleRect = title.getRect();
    Rect nameRect = myName.getRect();
    titleRect.x = W / 2 - titleRect.w /2, titleRect.y = H / 2 - titleRect.h / 2;
    nameRect.x = 0;
    nameRect.y = H - nameRect.h;
    int breakticks = getTicks();
    const int size = 50;
    Star ** starray = new Star*[size];
    generateStarray(starray, size);
    
    Font scoreFont("fonts/FreeSans.ttf", 18);
    Rect enemyRectArr [5]; 
    Image * enemyImgArr [5];
    enemyImgArr[0] = new Image("images/galaxian/clam.gif");
    enemyImgArr[1] = new Image("images/galaxian/turtle.gif");
    enemyImgArr[2] = new Image("images/galaxian/metroid.gif");
    enemyImgArr[3] = new Image("images/galaxian/minitron.gif");
    enemyImgArr[4] = new Image("images/galaxian/skeletron.gif");
    for (int i = 0; i < 5; ++i)
    {
        enemyRectArr[i] = enemyImgArr[i]->getRect();
    }
    Rect scoreRectArr [5]; 
    Image * scoreImgArr [5];
    scoreImgArr[0] = new Image(scoreFont.render("40", WHITE));
    scoreImgArr[1] = new Image(scoreFont.render("100", WHITE));
    scoreImgArr[2] = new Image(scoreFont.render("200", WHITE));
    scoreImgArr[3] = new Image(scoreFont.render("150", WHITE));
    scoreImgArr[4] = new Image(scoreFont.render("9001", WHITE));
    Image * playTextImage(new Image(scoreFont.render("PRESS SPACEBAR TO PLAY", WHITE)));
    
    Rect playText = playTextImage->getRect();
    playText.x = 300, playText.y = 300;
    for (int i = 0; i < 5; ++i)
    {
        scoreRectArr[i] = scoreImgArr[i]->getRect();
    }
    while (true)
    {
        if (event.poll() && event.type() == QUIT) {quitGame = true; break;}                
        keypressed = get_keypressed();
        if (getTicks() >= breakticks + 1000)
        {
            if (keypressed[TAB])
            {
                GAME_STATE = QUITGAME;
                break;
            }
            else if (keypressed[SPACE])
            {
                GAME_STATE = GAMEPLAY;
                break;
            }
            delay(10);
        }
        
        for (int i = 0; i < 5; ++i)
        {
            moveRects(&enemyRectArr[i], &scoreRectArr[i]);
        }
        psurface->lock();
        psurface->fill(BLACK);
        iterateOverStarray(starray, size);
        psurface->put_image(title, titleRect);
        psurface->put_image(myName, nameRect);
        psurface->put_image(*playTextImage, playText);
            
        for (int i = 0; i < 5; ++i)
        {
            psurface->put_image(*(enemyImgArr[i]), enemyRectArr[i]);
            psurface->put_image(*(scoreImgArr[i]), scoreRectArr[i]);
        }
        psurface->unlock();
        psurface->flip();
        delay(10);
    }
    deleteStars(starray, size);
    delete [] starray;
}
inline void gameOver()
{
    //need to reset EVERYTHING
    //KeyPressed keypressed;
    Event event;
    Font font("fonts/FreeSans.ttf", 96);
    Image gameOver(font.render("G A M E  O V E R", RED));
    Surface * psurface = &surface;
    Rect rect = gameOver.getRect();
    rect.x = 0;
    rect.y = H / 2 - rect.h / 2;
    int breakticks = getTicks();
    psurface->fill(BLACK);
    while (true)
    {
        if (event.poll() && event.type() == QUIT) { quitGame = true; break;}                
        std::cout << "in game over screen\n";
        std::cout << "ticks " << getTicks() << '\n';
        if (getTicks() >= breakticks + 5000)
        {
            GAME_STATE = TITLE; 
            return;
        }
        psurface->lock();
        psurface->fill(BLACK);
        psurface->put_image(gameOver, rect);
        psurface->unlock();
        psurface->flip();
        delay(10);
    }
}
void test_star_bgd();

#endif
