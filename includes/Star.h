//Star.h
#ifndef STAR_H
#define STAR_H
class Star
{
public:
    Star()
        :psurface(&surface), x(rand() % W), y(rand() % H),
         vx(rand() % 3 + 1), vy(1), r(rand() % 3 + 1),
         R(rand() % 256), G(rand() % 256), B(rand() % 256),
         dimTimer(getTicks(), 2000)
    {}
    inline void run()
    {
        draw();
        fall();
        blink();
    }
    inline void draw()
    {
        psurface->put_circle(x, y, r, R, G, B);
    }
    inline void fall()
    {
        x -= vx;
        if (x + r / 2 < 0)
        {
            r = rand() % 3 + 1;
            x = W + r, y = rand() % H;
        }
    }
    inline void blink()
    {
        if (dimTimer.canDo() && rand() % 5000 == 0)
        {
            --R, --G, --B;
        }
        else
        {
            ++R, ++G, ++B;
        }
    }
private:
    Timer dimTimer;
    Surface * psurface;
    int x, y, vx, vy, r, R, G, B;
};
//************************************************************************************
//star test functions----------------------------------------------------------------
// inline void generateStarray(Star ** & starray, const int & size);
// inline void iterateOverStarray(Star ** & starray, const int & size);
// inline void deleteStars(Star ** & starray, const int & size);
//************************************************************************************

//************************************************************************************
//star test functions----------------------------------------------------------------
inline void generateStarray(Star ** & starray, const int & size)
{
    for (int i = 0; i < size; ++i)
    {
        starray[i] = new Star();
    }    
}
inline void iterateOverStarray(Star ** & starray, const int & size)
{   
    for (int i = 0; i < size; ++i)
    {
        starray[i]->run();
    }
}
inline void deleteStars(Star ** & starray, const int & size)
{
    for (int i = 0; i < size; ++i)
    {
        delete starray[i];
    }
}
//************************************************************************************

#endif
