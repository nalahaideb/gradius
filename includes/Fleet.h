//Fleet.h
#ifndef FLEET_H
#define FLEET_H
//#include "Grunt.h"
//fix the mothership PLEASE THANKS
class Fleet: public Entity
{
// ▒▐█▀▀▒██░░░▒▐█▀▀▒▐█▀▀▒█▀█▀█▒█▒█▒█ 
// ▒▐█▀▀▒██░░░▒▐█▀▀▒▐█▀▀░░▒█░░░▀░▀░▀ 
// ▒▐█░░▒██▄▄█▒▐█▄▄▒▐█▄▄░▒▄█▄░▒▄▒▄▒▄ 
public:
    inline Fleet(Image *, int, int); 
    //run
    inline void run()
    {
        //std::cout << "remaining aliens " << alierray.size() << '\n';
        isAlive = (alierray.size() == 0? true : false);
        if (alierray.size() == 0)
        {
            Mothership::squadOffset = -64;
            return;
        }
        if (rect.x - rect.w <= W / 2)
        {
            for (unsigned int i = 0; i < alierray.size(); ++i)
            {
                if (!alierray[i]->isAlive) {alierray.erase(alierray.begin() + i);}
                else
                {
                    if (alierray[i]->STATE != IN_FLEET)
                    {
                        alierray[i]->run();
                        alierray[i]->fleetPosX = rect.x, alierray[i]->fleetPosY = rect.y;
                    }
                    else if (alierray[i]->STATE == REJOIN &&
                             alierray[i]->rect.x == alierray[i]->fleetPosX &&
                             alierray[i]->rect.y == alierray[i]->fleetPosY)   
                    {
                        maintainFleetPosition(i);
                        if (alierray[i]->canAttack()) {alierray[i]->shoot(alienLaserID);}
                    }
                    else
                    {
                        maintainFleetPosition(i);
                        if (alierray[i]->canAttack()) {alierray[i]->shoot(alienLaserID);}
                    }
                }   
            }
            //mothership is a high maintenance woman
            if (mothership.isAlive)
            {
                if (mothership.STATE != IN_FLEET)
                {
                    mothership.run();
                    mothership.fleetPosX = rect.x, mothership.fleetPosY = rect.y;
                }
                else if (mothership.STATE == REJOIN &&
                         mothership.rect.x == mothership.fleetPosX &&
                         mothership.rect.y == mothership.fleetPosY)       
                {
                    mothership.rect.x = rect.x + fleetW;
                    mothership.rect.y = rect.y + 64;
                    if (mothership.canAttack()) {mothership.shoot(alienLaserID);}
                }
                else
                {
                    mothership.rect.x = rect.x + fleetW;
                    mothership.rect.y = rect.y + 64;
                    if (mothership.canAttack()) {mothership.shoot(alienLaserID);}
                }
            }            
            fleetBounce();
            changeBounds();
        }
        else
        {
            moveAsOne();
            mothership.rect.x = rect.x + fleetW;
            mothership.rect.y = rect.y + 64;    
        }
    }
    //fleet arrangement
    inline void fleetBounce();    
    inline void changeBounds()
    {
        if (alierray.size() % 5 != 0) {return;}
        //put my swag hat on backwards
        //this might mess up a lot of other stuff, maybe retool
        for (int i = 0; i < numWide; ++i)
        {
            // if (
                
            //     )
            // {rect.h -= 32;}
            
        }
    }
    inline int getFleetH() const
    {return fleetH;}
    inline int getFleetW() const
    {return fleetW;}
private:
    inline void moveAsOne()
    {
        mLt();
        for (unsigned int i = 0; i < alierray.size(); ++i)
        {
            maintainFleetPosition(i);
        }
    }
    inline void maintainFleetPosition(int i)
    {
        alierray[i]->rect.x = alierray[i]->f_X + rect.x,
            alierray[i]->rect.y = alierray[i]->f_Y + rect.y;
    }
    std::vector < Grunt * > alierray;
    Grunt ** fleetBounds;
    bool switchDir;
    int fleetW;
    int fleetH;
    //probs dont need these
    static int fleetX;
    static int fleetY;
    int numHigh;
    int numWide;
    int offset;
    Mothership mothership;
private:
};

Fleet::Fleet(Image * image = NULL, int numHigh = 2, int numWide = 2)
    :numHigh(numHigh), numWide(numWide), switchDir(true),
     fleetBounds(new Grunt*[numWide * numHigh]), mothership(numWide * 32, 64)
{
    mothership.entGen();
    mothership.STATE = IN_FLEET;
    entityID = FLEET;
    rect.x = W + 100, rect.y = 100;
    fleetX = rect.x, fleetY = rect.y, speed = 2;
    isAlive = false;
    for (int i = 0, j = 0; i < numHigh * numWide; ++i, ++j)
    {
        if (j % 4 == 0 && j != 0)
        {
            j = -1;
            alierray.push_back(new SquadMember(&mothership, 0, 0));    
        }
        else
        {
            alierray.push_back(new Grunt(image, 0, 0));
        }
        alierray[i]->entGen();
        alierray[i]->STATE = IN_FLEET;
        fleetBounds[i] = alierray[i];
    }
    offset = alierray[0]->rect.w;
    fleetW = numWide * offset, fleetH = numHigh * offset;
    for (unsigned int i = 0,  j = 0; i < numHigh; ++i)
    {
        for (unsigned int k = 0; k < numWide; ++k, ++j)
        {
            alierray[j]->f_X = offset * k, alierray[j]->f_Y = offset * i;
            alierray[j]->rect.x = offset * k + rect.x, alierray[j]->rect.y = rect.y + offset * i;
        }
    }
    rect.w = numWide * offset, rect.h = numHigh * offset;
}

//fleet subclass methods
void Fleet::fleetBounce()
{
    rect.y += (switchDir ? speed : -speed);
    switchDir = (rect.y <= 0 || rect.y + fleetH >= H ? !switchDir : switchDir);
}
#endif

