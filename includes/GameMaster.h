//GameMaster.h
#ifndef GAMEMASTER_H
#define GAMEMASTER_H

//so little time, so many questions
static Entity * globalBossPointer = NULL;
    
class GameMaster
{

// ▒▐█▀▀▀░░▒▄█▀▄░▒▐██▄▒▄██▌▒▐█▀▀ ░░▒▐██▄▒▄██▌░▒▄█▀▄░▒▄█▀▀█▒█▀█▀█▒▐█▀▀▒▐█▀▀▄ 
// ▒▐█▒▀█▌▒▐█▄▄▐█░▒█░▒█░▒█░▒▐█▀▀ ██░▒█░▒█░▒█░▒▐█▄▄▐█▒▀▀█▄▄░░▒█░░▒▐█▀▀▒▐█▒▐█ 
// ▒▐██▄█▌▒▐█░▒▐█▒▐█░░░░▒█▌▒▐█▄▄ ░░▒▐█░░░░▒█▌▒▐█░▒▐█▒█▄▄█▀░▒▄█▄░▒▐█▄▄▒▐█▀▄▄ 
    
public:
    //maybe just give him a reference vector or something idk
    inline GameMaster()//std::vector < Image * > & imageVector
        :spawnTimer(getTicks(), 2000), gameTimer(getTicks(), 20000),
         fleetTimer(getTicks(), 4500),
         activeFleet(NULL), bossPointer(NULL), deadFleets(0)
    {
        alienTable.push_back(new Image("images/galaxian/turtle.gif"));
        alienTable.push_back(new Image("images/galaxian/clam.gif"));
        alienTable.push_back(new Image("images/galaxian/metroid.gif"));
    }
    // inline GameMaster(int titleTimer)
    //     :spawnTimer(getTicks(), titleTimer)
    // {
    //     alienTable.push_back(new Image("images/galaxian/metroid.gif"));
    //     alienTable.push_back(new Image("images/galaxian/GalaxianPurpleAlien.gif"));
    //     alienTable.push_back(new Image("images/galaxian/GalaxianFlagship.gif"));
    // }
    ~GameMaster()
    {
        alienTable.clear();
    }
    //this is so goddamn bad
    inline void gameClock(std::vector < Entity * > & livingEntities)
    {
        //std::cout << activeFleet << '\n';
        if (gameTimer.canDo() && deadFleets == 3)
        {
            spawnBoss(livingEntities);
        }
        else
        {
            if (spawnTimer.canDo())
            {
                spawnEnemy(livingEntities);
                //std::cout << "spawned enemy\n";
            }
            else if (fleetTimer.canDo())
            {
                spawnFleet(livingEntities);   
            }
        }
    }
    inline void spawnFleet(std::vector < Entity * > & livingEntities)
    {
        if  (activeFleet == NULL)
        {
            activeFleet = new Fleet(alienTable[0], 5, 5);
            livingEntities.push_back(activeFleet);            
        }
        else if (activeFleet->isAlive)
        {
            //reset timer, set active fleet to null   
            activeFleet = NULL;
            fleetTimer.resetTimer();
            ++deadFleets;
        }
    }
    inline void spawnEnemy(std::vector < Entity * > & livingEntities)
    {
        int c = rand() % alienTable.size();
        if (alienTable[c] != NULL)
        {livingEntities.push_back(new Alien(alienTable[c], W + 50, rand() % H));}
        // switch (rand() % 5)
        // {
        //     //grunt, basic alien, easy
        //     case 1:
        //         livingEntities.push_back(new Alien(testImage, W + 50, rand() % H));
        //         break;
        //         //hostile alien, more difficult, shoots faster
        //     case 2:
        //         livingEntities.push_back(new Alien(testImage, W + 50, rand() % H));
        //         break;
        //         //sniper, hangs back and fires large beam
        //     case 3:
        //         livingEntities.push_back(new Alien(testImage, W + 50, rand() % H));
        //         break;
        //         //orb flinger, may or may not pwn
        //     case 4:
        //         livingEntities.push_back(new Alien(testImage, W + 50, rand() % H));
        //         break;
        // }
    }
    inline void spawnBoss(std::vector < Entity * > & livingEntities)
    {
        if (bossPointer == NULL)
        {
            // std::cout << "spawned skeletron\n";
            bossPointer = new SKELETRON(), globalBossPointer = bossPointer;
            livingEntities.push_back(bossPointer);
        }
    }
    Image * operator[](const int i) const
    {
        return alienTable[i];
    }
private:
    //const int MAXALIENS = 30;
    Entity * activeFleet;
    Entity * bossPointer;
    std::vector < Image * > alienTable;
    Timer gameTimer;
    Timer fleetTimer;
    Timer spawnTimer;
    int deadFleets;
};

#endif


