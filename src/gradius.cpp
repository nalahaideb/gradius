//lol, lmao even
// PIZZA STEVE!!!!!!!!!!!
#include "gradius.h"
//static declarations
int Player::lives = 5;
int Player::score = 0;
int  Fleet::fleetX;
int Fleet::fleetY;
int Mothership::squadOffset = -64;
int SKELETRON::health = 50;
//VECTORS
std::vector < Explosion * > exploVector;

void test_image()
{
    const int size = 100;
    int RATE = 1000 / 60;
    
    //entity tracker
    GameMaster gameMaster;
    Star ** starray = new Star*[size];
    generateStarray(starray, size);
    
    int start, end, dt;
    Event event;
    KeyPressed keypressed;

    Image image("images/galaxian/GalaxianAquaAlien.gif");
    Player player(&image, PLAYER);
    PLAYA = &player;
    HUD gameHUD(&player);
    
    player.entGen();
    while (true)
    {
        keypressed = get_keypressed();
        if (player.getLives() <= 0)
        {
            //std::cout << "EXITING GAMEPLAY LOOP\n";
            //GAME_STATE = GAMEOVER;
            //gameOver();
            //gameReset();
            exploVector.clear(), laserray.clear(), livingEntities.clear();
            Mothership::squadOffset = -64, Player::resetLives(), Player::resetScore();
            break;
        }
        if (event.poll() && event.type() == QUIT) {break;}                
        //debug statements, uncomment at your own peril
        //std::cout << player.score << '\n';
        //dbg();
        //i wanted to use this to kill the game. if this gets uncommented it will be joever, do not touch 
        //if (keypressed[TAB]) {break;}
        start = getTicks();
        gameMaster.gameClock(livingEntities);
        player.playerControl(keypressed);
        collisionCheck(livingEntities, &player);    
        moveLaserray();
        laserAliveCheck();
        runAliens();
        killCheck(livingEntities);
        //===========================================================================        
        drawAfterMe();//draw background first, then other stuff
        iterateOverStarray(starray, size);
        drawEntities(livingEntities);
        drawLaserray();
        gameHUD.run();        
        explodingExplosions(exploVector);
        //===========================================================================
        drawBeforeMe();
        //rate controls
        end = getTicks();
        dt = RATE - end + start;
        if (dt > 0) delay(dt);
    }
    deleteStars(starray, size);
    delete [] starray;
}

//﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽
//the testing will be good and the bugs destroyed inshallah
//﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽﷽
//************************************************************************************
//overall state / wellness checks
//does what it says on the tin
void explodingExplosions(std::vector < Explosion * > &e)
{
    for (unsigned int i = 0; i < e.size(); ++i)
    {
        e[i]->run();
        if (e[i]->timesUp()) {e.erase(e.begin() + i--);}
    }
}
void runAliens()
{
    for (int i = 0; i < livingEntities.size(); ++i)
    {
        livingEntities[i]->run();
    }
}
//maybe not so many bools for every obj
void collisionCheck(std::vector < Entity * > &ent, Player * player)
{
    //this is bad. no bien. beat half to death with the ugly stick and ran over with the cringe car
    //maybe i dont need this many bools after testing the laserray aganist the player, removing a bool actually fixed a lot down there
    for (unsigned int i = 0; i < ent.size(); ++i)
    {
        //if (player->STATE = INVULN) {break;}
        //this only checks for collisions between the player and the vector of entities (aliens)
        if
            (
                ent[i]->rect.x - player->rect.w <= player->rect.x &&
                ent[i]->rect.x + player->rect.w >= player->rect.x &&
                ent[i]->rect.y - player->rect.h <= player->rect.y &&
                ent[i]->rect.y + player->rect.h >= player->rect.y &&
                ent[i] != player && player->isAlive && ent[i]->isAlive
                )
        {
            player->killMe(), ent[i]->killMe();
            exploVector.push_back(new Explosion(player->rect.x, player->rect.y));
            exploVector.push_back(new Explosion(ent[i]->rect.x / 2, ent[i]->rect.y / 2));
        }
    }
    //kills the aliens if they collide with player lasers
    for (unsigned int i = 0; i < ent.size(); ++i)
    {
        for (unsigned int k = 0; k <  laserray.size(); ++k)
        {            
            if (
                laserray[k].laserType == playerLaserID && 
                laserray[k].rect.x + laserray[k].rect.w >= ent[i]->rect.x &&
                laserray[k].rect.x - laserray[k].rect.w <= ent[i]->rect.x &&
                laserray[k].rect.y + laserray[k].rect.h >= ent[i]->rect.y &&
                laserray[k].rect.y + laserray[k].rect.h <= ent[i]->rect.y + ent[i]->rect.h 
                && ent[i] != player && ent[i]->entityID != FLEET
                )
            {
                if (ent[i]->entityID == SKELETRONID && SKELETRON::health > 0)
                {
                    exploVector.push_back(new Explosion(laserray[k].rect.x + laserray[k].rect.w,
                                                        laserray[k].rect.y));
                    laserray[k].killMe();
                    SKELETRON::hurt();
                    return;
                }
                ent[i]->killMe(), laserray[k].killMe(),
                exploVector.push_back(new Explosion(ent[i]->rect.x, ent[i]->rect.y));
                player->incPlayerScore(ent[i]->points);
//ent[i]->killedByLaser = true;
            }   
        }
    }
    //check the enemy laserray if any lasers have hit the player
    for (unsigned int k = 0; k < laserray.size(); ++k)
    {
        //if (player->STATE = INVULN) {break;}
        if (laserray[k].laserType == alienLaserID &&
            laserray[k].rect.x - player->rect.w <= player->rect.x &&
            laserray[k].rect.x + player->rect.w - laserray[k].rect.w >= player->rect.x &&
            laserray[k].rect.y - player->rect.h <= player->rect.y &&
            laserray[k].rect.y + laserray[k].rect.h >= player->rect.y && player->isAlive
            )
        {
            player->killMe(), laserray[k].killMe(), 
                exploVector.push_back(new Explosion(player->rect.x, player->rect.y));
        }   
    }
    if (player->getLives() >= 0 && !player->isAlive)
    {
        player->lostLife();
        player->rect.x = 0, player->rect.y = H / 2;
        player->isAlive = true;
    }
}
//might not need this because of collisionCheck, retool or remove
void killCheck(std::vector < Entity * > &livingEntities)
{
    for (unsigned int i = 0; i < livingEntities.size(); ++i)
    {
        if (livingEntities[i]->isAlive == false &&
            livingEntities[i]->entityID != PLAYER &&
            livingEntities[i]->entityID != FLEET
            )
        {
            //std::cout << "deleted an entity\n";
            livingEntities.erase(livingEntities.begin() + i--);
            //dont ever uncomment this it will segfault, you can probably see why
            // std::cout << "killed entity " << livingEntities[i]->entityID
            //           << '\n' << livingEntities[i] << '\n';
        }
    }
}

void drawEntities(std::vector < Entity * > &livingEntities)
{
    for (unsigned int i = 0; i < livingEntities.size(); ++i)
    {
        //dumb temporary fix, but if it no longer segfaults is it really that dumb?
        //perchance...
        //std::cout << livingEntities.size() << '\n';
        if (livingEntities[i]->isAlive && livingEntities[i]->entityID != FLEET)
        {
            livingEntities[i]->draw();
        }
    }
}
//************************************************************************************

//laser functions

//this moves the laser if its alive, deletes it if its alive and not below W
void laserAliveCheck()
{
    for (unsigned int i = 0; i < laserray.size(); ++i)
    {
        if ((laserray[i].isAlive && laserray[i].rect.x >= W ||
             laserray[i].isAlive && laserray[i].rect.x + laserray[i].rect.w <= 0 )
            || !laserray[i].isAlive)
        {laserray.erase(laserray.begin() + i--);}
    }
}

//redraws the lasers
void drawLaserray()
{
    for (unsigned int i = 0; i < laserray.size(); ++i)
    {
        laserray[i].drawLaser();
    }
}

void moveLaserray()
{
    for (unsigned int i = 0; i < laserray.size(); ++i)
    {
        laserray[i].moveLaser();
    }
}
//************************************************************************************


//************************************************************************************
//general drawing functions-----------------------------------------------------------
inline void drawAfterMe()
{
    surface.fill(BLACK);
    surface.lock();
}
inline void drawBeforeMe()
{
    surface.unlock();
    surface.flip();
}
//************************************************************************************


//************************************************************************************
inline void dbg()
{
    //-----------------------------------------------------------------
    //debug statements

    //std::cout << getTicks() << '\n';
    //std::cout << "num of lasers = " << laserray.size() << '\n';
        
    //std::cout << "Player = "; print(player);
    //std::cout << "Alien = "; print(alien);
    // std::cout << player.rect.x << " | "  << player.rect.y << '\n';
    // std::cout << player.rect.w << " ||| "  << player.rect.h << '\n';
        
    // std::cout << alien.rect.x << " | "  << alien.rect.y << '\n';
    // std::cout << alien.rect.w << " ||| "  << alien.rect.h << '\n';
    //std::cout << &player << '\n' << &alien << '\n';
    //std::cout << livingEntities.size() << '\n';
    //std::cout << "start = " << start << " end = " << end << " dt = " << dt << '\n';
    //-----------------------------------------------------------------
}
//************************************************************************************
