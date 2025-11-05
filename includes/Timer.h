//Timer.h
#ifndef TIMER_H
#define TIMER_H

// extern Surface surface(W, H);
class Timer
{
// ▒█▀█▀█▒▐██▒▐██▄▒▄██▌▒▐█▀▀▒▐█▀▀▄▒█▒█▒█ 
// ░░▒█░░░▒█▌░▒█░▒█░▒█░▒▐█▀▀▒▐█▒▐█░▀░▀░▀ 
// ░▒▄█▄░▒▐██▒▐█░░░░▒█▌▒▐█▄▄▒▐█▀▄▄▒▄▒▄▒▄ 
public:
    //i think end and interval do the same thing. whatever
    inline Timer(int timeStart = 0, int timeInterval = 0)
        :start(timeStart), interval(timeInterval)//, end(getTicks() + interval)
    {}

    inline void setInterval(const int i)
    {
        interval = i;
    }
    inline void resetTimer()
    {
        start = getTicks();
    }
    // inline int setInterval(const int i)
    // {
    //     return &interval;
    // }
    inline bool canDo()
    {
        if (getTicks() >= start + interval)
        {
            start = getTicks();
            return true;
        }
        else
        {return false;}
    }
    inline void print()
    {
        std::cout << "start = " << start
                  << " interval = " << interval << " canDo " << canDo() << " current ticks " << getTicks() << '\n'; 
    }
private:
    int start;
    int interval;
    //int end;
};
#endif

