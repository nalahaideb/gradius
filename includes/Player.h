//Player.h
#ifndef PLAYER_H
#define PLAYER_H


class Player: public Entity
{
// ▒▐█▀█▒██░░░░▒▄█▀▄░▒▀▄░░░░░▄▀▒▐█▀▀▒▐█▀▀▄▒█▒█▒█ 
// ▒▐█▄█▒██░░░▒▐█▄▄▐█░░▒▀▄░▄▀░░▒▐█▀▀▒▐█▒▐█░▀░▀░▀ 
// ▒▐█░░▒██▄▄█▒▐█░▒▐█░░░░▒█░░░░▒▐█▄▄▒▐█▀▄▄▒▄▒▄▒▄ 

public:
    Player(Image * image = NULL, entID PLAYA = PLAYER)
        :Entity(image, PLAYA, 0, H / 2),
         fireTimer(getTicks(), 200), laser(new Sound("sounds/WideBeamImpact.wav")) 
    {
        speed = 5;
        entityID = PLAYER;
        //pls disable me :D 
        // if (!godMode)
        // {STATE = INVULN;}
        laser->on();
        rect.x = 0, rect.y = 200;
    }
    ~Player()
    {delete laser;}
    //methods
    inline bool canFire()
    {
        return (fireTimer.canDo() ? true : false);
    }
    
    inline int getLives() const
    {return lives;}
    inline void lostLife()
    {
        --lives;
    }
    inline void playerControl(KeyPressed & keypressed);
    static inline void resetLives()
    {lives = 5;}
    static inline void resetScore()
    {score = 0;}
    inline void incPlayerScore(const int x)
    {score += x;}
    int getPlayerScore() const
    {return score;}
    Timer fireTimer;
private:
    static int lives;
    static int score;
    Sound * laser;
};
//player controls
//passes control from keypressed to the keyboard to determine movement
void Player::playerControl(KeyPressed & keypressed)
{
    if (keypressed[SPACE] && canFire())
    {
        shoot(playerLaserID);
        delay(5);
        laser->play();
    }
    if (keypressed[DOWNARROW] && rect.y+ rect.h <= H)
    {
        mDn();
        delay(10);
    }
    else if (keypressed[UPARROW] && rect.y > 0)
    {
        mUp();
        delay(10);
    }
    else if (keypressed[RIGHTARROW] && rect.x + rect.w <= W)
    {
        mRt();
        delay(10);
    }
    else if (keypressed[LEFTARROW] && rect.x > 0)
    {   
        mLt();
        delay(10);
    }
}

#endif

