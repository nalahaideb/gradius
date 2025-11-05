//Grunt.h
#ifndef GRUNT_H
#define GRUNT_H
//this class should basically comprise the entirety of the fleet
class Grunt: public Alien
{ 
public:
    Grunt(Image * image, int offX, int offY)
        :Alien(image, offX, offY)
    {
        speed = 1;
        points = 20;
    }
    inline void run()
    {
        if (attackTimer.canDo()) {shoot(alienLaserID);}
        if (STATE == IN_FLEET)
        {
            if (rand() % 10000 == 0)
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
        }
        else
        {
            dive();
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
    inline void dive()
    {
        mLt();
    }
        //change all the others after fixing it in Entity
    inline int givePoints() const
    {return points;}

    //offset
    //private:
    int f_X, f_Y;
    //current fleet coords
    int fleetPosX, fleetPosY;
    
    // Fleet * homeFleet;
};
#endif

