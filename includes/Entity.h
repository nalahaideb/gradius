//Entity.h
#ifndef ENTITY_H
#define ENTITY_H
#include "Laser.h"

class Entity
{
/*
▐█▀▀▒██▄░▒█▌▒█▀█▀█▒▐██▒█▀█▀█▒▀▄░░░░░▄▀▒█▒█▒█ 
▐█▀▀▒▐█▒█▒█░░░▒█░░░▒█▌░░▒█░░░░▒▀▄░▄▀░░░▀░▀░▀ 
▐█▄▄▒██░▒██▌░▒▄█▄░▒▐██░▒▄█▄░░░░░▒█░░░░▒▄▒▄▒▄ 
 */
    
public:
    inline Entity(Image *, entID, int, int);
    inline Entity();
    //===========================================================================
    //implemented
    inline void killMe();
    inline void entGen();
    inline void draw();
    inline void mUp();inline void mDn();inline void mLt();inline void mRt();
    inline void shoot(lsrID laserType);
    //debugging, draws rects under images
    inline void drawMarker();
    inline void drawMarker(int r, int g, int b);
    virtual inline void run() {}
    //===========================================================================

    entID entityID;
    Surface * psurface;
    Rect rect;
    Image * entImage;
    bool isAlive;
    int speed;
    int points;
};

//muy importante
static std::vector < Entity * > livingEntities;

Entity::Entity(Image * image, entID ID = ENTITY, int x = 0, int y = 100)
    :psurface(&surface), entImage(image), isAlive(true), entityID(ID)
{
    rect = image->getRect();
    rect.x = x;
    rect.y = y;
}
Entity::Entity()
    :psurface(&surface)
{}
//ENTITY FUNCTIONS   
void Entity::draw()
{
    //drawMarker();
    psurface->put_image(*entImage, rect);
}
void Entity::mUp()
{rect.y -= speed;}
void Entity::mDn()
{rect.y += speed;}
void Entity::mLt()
{rect.x -= speed;}
void Entity::mRt()
{rect.x += speed;}

    
void Entity::shoot(lsrID laserType)
{
    //change this later ganghaps
    //soundVector[1]->play();
    int port = (entityID == PLAYER ? rect.w / 2 + rect.w / 2 : rect.w / 2 - rect.w);
    if (isAlive)
    {
        laserray.push_back(Laser(rect.x + port, rect.y + rect.h / 2, laserType));
    }
}

void Entity::entGen()
{
    livingEntities.push_back(this);
    // std::cout << livingEntities.size() << '\n';
}

void Entity::killMe()
{
    isAlive = false;
}

void Entity::drawMarker()
{
    psurface->put_rect(rect.x, rect.y, rect.w, rect.h, 255, 255, 255);
}

void Entity::drawMarker(int r, int g, int b)
{
    psurface->put_rect(rect.x, rect.y, rect.w, rect.h, r, g, b);
}
#endif

