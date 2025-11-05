//Alien.h
#ifndef ALIEN_H
#define ALIEN_H
class Alien: public Entity
{
/*
░▒▄█▀▄░▒██░░░▒▐██▒▐█▀▀▒██▄░▒█▌▒█▒█▒█ 
▒▐█▄▄▐█▒██░░░░▒█▌▒▐█▀▀▒▐█▒█▒█░░▀░▀░▀ 
▒▐█░▒▐█▒██▄▄█▒▐██▒▐█▄▄▒██░▒██▌▒▄▒▄▒▄ 
*/
public:
    inline Alien(Image *, int, int);
    inline Alien(Entity *);
//state updaters
    virtual inline void run()
    {   
        if (!isAlive) {return;}
        else
        {
            if (canAttack())
            {
                //they were playing this so much it was lagging my game please understand
                // shoot(alienLaserID);
                // enemyLaser.play();
            }
            if (STATE == HOMING)
            {
                homing();
            } 
            else if (STATE == DIVE)
            {
                sineWave();
            }
        }
    }    
    //mans chill as hell gawtdayum
    inline void drift();
    inline void sineWave()
    {
        //many thanks to cole and ryan
        mLt();     
        rect.y += 2 * cos(rect.x * 3.14159 / 50);
    }
    //friggin pissed off!!!!!
    virtual inline void homing();
    virtual inline void getCoords(int, int);
    inline bool canAttack()
    {
        return attackTimer.canDo();
    }
    //CALCULATE MOVEMENT
    stateID STATE;
    Timer movementTimer;
    Timer attackTimer;
    //¯\_(ツ)_/¯
    int homingX, homingY;
    Timer moveTimer;
    Entity * player;
private:
};

Alien::Alien(Image * image = NULL, int x = W + 100, int y = rand() % H)
    :Entity(image, ALIEN, x, y), player(PLAYA),
     movementTimer(getTicks(), 10), attackTimer(getTicks(), rand() % 4000 + 2000)    
{
    speed = 3;
    STATE = AGGRO;
    rect.x =  W + 100;
    rect.y = rand() % H;
    points = 10;
    entGen();
}

//just for homing aliens
Alien::Alien(Entity * entity)
    :Entity(new Image("images/galaxian/minitron.gif"), ALIEN, entity->rect.x, entity->rect.y), player(PLAYA),
     movementTimer(getTicks(), 10), attackTimer(getTicks(), rand() % 4000 + 2000)
{
    speed = rand() % 6;
    STATE = HOMING;
    rect.x =  entity->rect.x - rand() % 30;
    rect.y = rand() % int(entity->rect.y) + entity->rect.h / 2;
    points = 10;
    entGen();
}
//alien methods

void Alien::drift()
{
    mLt();   
}
void Alien::getCoords(int x = 0, int y = 0)
{
    homingX = player->rect.x;
    homingY = player->rect.y;
}
void Alien::homing()
{
    //delay acquisition of target, dont stop moving towards last coordinates
    //make a separate homing (virtual) for other aliens
    if (moveTimer.canDo()) {getCoords();}
    if (homingY > rect.y)
    {mDn();}
    if (homingY < rect.y)
    {mUp();}
    if (homingX> rect.x)
    {mRt();}
    if (homingX < rect.x)
    {mLt();}   
}

#endif


