//custom
#include "gradius.h"
int main(int argc, char* argv[])
{
    // int n;
    // std::cout << "become god? 1 for yes 2 for no:\n";
    // std::cin >> n; godMode = (n == 1 ? true : false); 
    
    // std::cout << "enable fun (no copyright)? 1 for yes 2 for no:\n";
    // std::cin >> n; avoidCopyRight = (n == 1 ? true : false);
    srand((unsigned int) time(NULL));
    
    Music * music = new Music("sounds/music/brinstar.ogg");
    enemyLaser.on();
    music->play();
    while (!quitGame)
    {
        switch (GAME_STATE)
        {
            case TITLE:
            {
                std::cout << "IN TITLE\n";
                titleScreen();
                break;
            }
            case GAMEPLAY:
            {
                std::cout << "IN GAMEPLAY\n";
                test_image();
                gameOver();
                break;
            }
            case QUITGAME:
            {
                std::cout << "QUITTING\n";
                quitGame = true;
                break;
            }
        }
    }
    delete music;
    return 0;
}
