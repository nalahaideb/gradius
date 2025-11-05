//Explosion.h
#ifndef EXPLOSION_H
#define EXPLOSION_H


class Explosion
{
public:
    Explosion(const double rectx, const double recty)
        :psurface(&surface), explosionTimer(getTicks(), 300),
         r(3), x(rectx), y(recty)
    {
        explosionSound.on();
        explosionSound.play();
    }
    inline void run()
    {
        //constants are nice. i like constants. constants are my friend.
        psurface->put_circle(x + 16, y + 16, r += 0.5, 255, 0, 0);
        psurface->put_circle(x + 16, y + 16, r - 3 + 0.5, 0, 0, 0);
    }
    inline bool timesUp() 
    {
        return explosionTimer.canDo();
    }
private:
    double x, y, r;
    Timer explosionTimer;
    Image * image;
    Surface * psurface;
};
#endif

