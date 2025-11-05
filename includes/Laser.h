//Laser.h
#ifndef LASER_H
#define LASER_H
class Laser
{
    /*
▒██░░░░▒▄█▀▄░▒▄█▀▀█▒▐█▀▀▒▐█▀▀▄▒█▒█▒█ 
▒██░░░▒▐█▄▄▐█▒▀▀█▄▄▒▐█▀▀▒▐█▒▐█░▀░▀░▀ 
▒██▄▄█▒▐█░▒▐█▒█▄▄█▀▒▐█▄▄▒▐█▀▄▄▒▄▒▄▒▄   
*/

public:
    //change to accomodate other laser colors
    inline Laser(const int & x, const int & y, lsrID laserType)//, const int & r, const int & g, const int & b)
        :psurface(&surface), rect(x, y, 15, 3), laserType(laserType), color(laserType == playerLaserID ? GREEN : RED),
         isAlive(true), speed(laserType == alienLaserID ? -7 : 7)
    {}
    //draws the initial laser
    inline void drawLaser()
    { 
        psurface->put_rect(rect, color);
    }
    inline void killMe()
    {
        isAlive = false;
    }
    //rect.x += positive direction for player, negative direction for enemies
    inline void moveLaser()
    {
        rect.x += speed;
    }
    lsrID laserType;
    bool isAlive;
    Color color;
    Surface * psurface;
    Rect rect;
    int speed;
private:
};
static std::vector < Laser > laserray;

#endif


