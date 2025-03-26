#include "main.hpp"

// Moves a block up and down with an outside timer
void BlockTest(BlockEntity& block, Player& player, const Vector3 InitialPOS, unsigned char t)
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
void BlockCollision(BlockEntity& block, Vector3& p, float fallSpeed)
{
    Vector3& bv = block.blockCurrentPosition;
    float bsh = block.size/2;
    float fault_t = .01;
    float z_area_MAX = (bv.z + bsh) + fault_t;
    float z_area_MIN = (bv.z - bsh) - fault_t;
    float y_area_MIN = (bv.y + bsh) + fault_t;
    float x_area_MAX = (bv.x + bsh) + fault_t;
    float x_area_MIN = (bv.x - bsh) - fault_t;

    bool onBlock = {
        (x_area_MIN <= p.x) && (p.x <= x_area_MAX) &&
        y_area_MIN < p.y &&
        (z_area_MIN <= p.z) && (p.z <= z_area_MAX)
    };
    bool onBlockTop = (p.y >= y_area_MIN);

    if (onBlock)
    {
        p.y += fallSpeed;
    }
    
}