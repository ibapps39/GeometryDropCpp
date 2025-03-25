#include "main.hpp"

void blockTest(BlockEntity& block, Player& player, const Vector3 InitialPOS, unsigned char t)
{
    unsigned char timerStart = 50;
    unsigned char timerEnd = 100;
    if (t <= timerStart)
    {
        block.blockCurrentPosition.y++;
    } 
    if (t <= timerEnd && t >= timerStart) {
        block.blockCurrentPosition.y--;
    }
    if (t > 100) {
        t = 0;
    }
    
    
}