//SKELETRON.h
#ifndef SKELETRON_H
#define SKELETRON_H
class SKELETRON: public Entity
{
public:
    SKELETRON(Image * image = new Image("images/galaxian/skeletron.gif"))
        :Entity(image, SKELETRONID, 950, 200),
         hurtImage(new Image("images/galaxian/skeletronmouthopen.gif")), skeleImage(image),
         orbsTimer(getTicks(), 1000), animationTimer(getTicks(), 100),
         swap(false)
    {
        entGen();
        rect = image->getRect();
        rect.x = 950, rect.y = 0 + rect.h / 2;
        speed = 1;
        health = 50;
        skeletronRoar.on();
        skeletronRoar.play();
        points = 9001;
    }
    inline void run()
    {
        //std::cout << "skeletron xy " << rect.x << ' ' << rect.y << '\n';
        if (health == 0)
        {
            //play animation
            killMe();
        }
        if (rect.x >= 600)
        {
            mLt();
        }
        else if (animationTimer.canDo())
        {
            swapImage(skeleImage, hurtImage);
        }
        else
        {
            if (orbsTimer.canDo())
            {
                spawnOrbs();
            }
        }
        swapImage(skeleImage, hurtImage);
    }
    inline void swapImage(Image * from, Image * to)
    {
        std::cout << " swapped " << from << ' ' << to << '\n';
        Image ** t = &from;
        from = to, to = *t;
    }
    //just for my special boy skeletron :)
    inline void spawnOrbs()
    {
        for (unsigned int i = 0; i < rand() % 6; ++i)
        {
            miniVector.push_back(new Alien(this));
        }
    }
    static void hurt()
    {
        --health;
        //sound
    }
    static int health;
private:
    bool swap;
    std::vector < Alien * > miniVector;
    Timer animationTimer;
    Timer orbsTimer;
    Image * skeleImage;
    Image * hurtImage;
};

#endif

