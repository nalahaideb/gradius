//Mothership.h
#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H
#include "Alien.h"

class Mothership: public Alien
{
public:
    inline Mothership(int FLEETX, int FLEETY)
        :Alien(new Image("images/galaxian/metroid.gif"),
               FLEETX, FLEETY), f_X(FLEETX), f_Y(FLEETY)
    {
        attackTimer.setInterval(1000);
        speed = 2;
        points = 100;
    }               
    inline void run()
    {
        if (attackTimer.canDo()) {shoot(alienLaserID);}
        if (STATE == IN_FLEET)
        {
            rect.x = f_X + fleetPosX, rect.y = f_Y + fleetPosY;
            if (rand() % 2000 == 0)
            {STATE = DIVE;}
        }
        else if (STATE == DIVE)
        {
            sineWave();
            if (rect.x + rect.w <= 0) 
            {
                rect.x = W + 50, rect.y = rand() % H;
                STATE = REJOIN;
            }
        }
        else if (STATE == REJOIN)
        {
            homing();
            if (STATE == REJOIN && rect.x == fleetPosX + f_X && rect.y == fleetPosY + f_Y)
            {
                STATE = IN_FLEET;
            }
        }
        else
        {
            mLt();
        }
    }       
    inline void homing()
    {
        if (f_Y + fleetPosY > rect.y)
        {mDn();}
        if (f_Y + fleetPosY < rect.y)
        {mUp();}
        if (f_X + fleetPosX > rect.x)
        {mRt();}
        if (f_X + fleetPosX < rect.x)
        {mLt();}   
    }
    static int squadOffset;
    int f_X, f_Y;
    int fleetPosX, fleetPosY;
    
    inline int givePoints() const
    {return points;}
    //to hell with privacy, brave new world 
private:
};
#endif


