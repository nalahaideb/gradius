//HUD.h
#ifndef HUD_H
#define HUD_H
#include <cstring>
class HUD
{
public:
    HUD(Player * player)
        :psurface(&surface), playerLives(player->getLives()),
         playerScore(player->getPlayerScore()),
         font("fonts/FreeSans.ttf", 24), livesImage(font.render("PLAYER", WHITE)),
         scoreImage(font.render("SCORE", WHITE)) 
    {
        livesRect = livesImage.getRect(), scoreRect = scoreImage.getRect();
        livesRect.x = 150, livesRect.y = 0;
        scoreRect.x = 400, scoreRect.y = 0;
    }
    inline void drawLives()
    {
        Rect rect;
        int width = 20;
        rect.y = livesRect.y;
        
        Image image("images/galaxian/GalaxianAquaAlien.gif");
        for (int i = 0; i < player->getLives(); ++i, width += 20)
        {
            rect.x = livesRect.x + livesRect.w + width;
            psurface->put_image(image, rect);
            // *(player->getImage())
        }
    }
    inline void run()
    {
        
        int_to_char(player->getPlayerScore(), s);
        Image scorePlayerImage(font.render(s, WHITE));
        Rect scorePlayerRect = scorePlayerImage.getRect();
        scorePlayerRect.x = scoreRect.x + scoreRect.w + 50, scorePlayerRect.y = scoreRect.y;
        drawLives();
        psurface->put_image(scorePlayerImage, scorePlayerRect);
        psurface->put_image(scoreImage, scoreRect);
        psurface->put_image(scoreImage, scoreRect);
        psurface->put_image(livesImage, livesRect);
    }
    //big ups robert
    inline void int_to_char(int int_, char string_[])
    {
        for (int i = 0; i < size_i(int_); ++i)
        {
            string_[i] = (int(int_ / pow(10, size_i(int_) - 1 - i)) % 10) + '0';
        }
        string_[size_i(int_)] = '\0';
    }
    inline int size_i(int i)
    {
        int s = 0;
        if (i == 0)
        {return 1;}
        while (i != 0)
        {
            i /= 10;
            s++;
        }
        {return s;}
    }
    
private:
    char s[20];
    Rect livesRect;
    Rect scoreRect;
    Font font;
    Image livesImage;
    Image scoreImage;
    Player * player;
    int playerScore;
    int playerLives;
    Surface * psurface;
    //do it later, right now we ball out like its 1999 and my initials M.J.
    //int high score
};

#endif

