//SquadMember.h
#ifndef SQUADMEMBER_H
#define SQUADMEMBER_H

class SquadMember: public Grunt
{
    
// ▒▄█▀▀█▒█▀▐█▒█▒█░▒▄█▀▄░▒▐█▀█▄▒▐█▀▀▄▒▐█▀▀█▌▒██▄░▒█▌▒█▒█▒█ 
// ▒▀▀█▄▄▒█▒▐█▒█▒█▒▐█▄▄▐█▒▐█▌▐█▒▐█▒▐█▒▐█▄▒█▌▒▐█▒█▒█░░▀░▀░▀ 
// ▒█▄▄█▀▒▀▀█▄▒▀▄▀▒▐█░▒▐█▒▐█▄█▀▒▐█▀▄▄▒▐██▄█▌▒██░▒██▌▒▄▒▄▒▄ 

public:
    inline SquadMember(Mothership * mother, int offX, int offY)
        :Grunt(new Image("images/galaxian/clam.gif"), offX, offY),
         mother(mother), mshipOffsetY(mother->squadOffset)
    {
        speed = mother->speed;
        mother->squadOffset += 32;
        points = 50;
    }
    
    inline void run()
    {
        if (attackTimer.canDo()) {shoot(alienLaserID);}
        if (mother->isAlive)
        {
            STATE = mother->STATE;
            rect.y = mshipOffsetY + mother->rect.y,
                rect.x =  mother->rect.x - rect.w;
        }
        else
        {
            if (STATE == IN_FLEET)
            {
                if (rand() % 10000 == 0)
                {STATE = DIVE;}
            }
            else if (STATE == DIVE)
            {
                sineWave();
                //dive();            
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
        }
    }
    inline int givePoints() const
    {return points;}
private:
    Mothership * mother;
    int mshipOffsetY;
};
#endif

