#include "main.hpp"

// Moves a block up and down with an outside timer
void BlockTest(BlockEntity &block, Player &player, const Vector3 InitialPOS, unsigned char t)
{
    unsigned char timerStart = 50;
    unsigned char timerEnd = 100;
    if (t <= timerStart)
    {
        block.blockCurrentPosition.y++;
    }
    if (t <= timerEnd && t >= timerStart)
    {
        block.blockCurrentPosition.y--;
    }
    if (t > 100)
    {
        t = 0;
    }
}
void BlockCollision(BlockEntity &block, Vector3 &p, float fallSpeed)
{
    // Block Vector
    Vector3 &bv = block.blockCurrentPosition;
    // Surface area/2, since point is at center/midpoint of Block.
    float bsh = block.size / 2.0;
    float fault_t = .01;

    // TOP
    // Z-dim cross-section, front/back
    float z_area_MAX = (bv.z + bsh) + fault_t;
    float z_area_MIN = (bv.z - bsh) - fault_t;
    // Y-dim top
    float y_area_MAX = (bv.y + block.size) + fault_t;
    float y_area_MIN = (bv.y) - fault_t;
    // X-dim cross-section, left/right sides
    float x_area_MAX = (bv.x + bsh) + fault_t;
    float x_area_MIN = (bv.x - bsh) - fault_t;

    float dist = Vector3Distance(p, block.blockCurrentPosition);

    bool touchingBlock = ((x_area_MIN <= p.x) && (p.x <= x_area_MAX) &&
                          (z_area_MIN <= p.z) && (p.z <= z_area_MAX));

    if (touchingBlock)
    {
        bool onBlockTop = (p.y >= y_area_MAX);
        if (onBlockTop)
        {
            p.y += fallSpeed;
        }
    }
    bool onBlockLeft = (p.x <= x_area_MIN && dist <= block.size);
    if (onBlockLeft)
    {
        p.x -= 1.0;
    }
    DrawText(TextFormat("dist: %.2f", dist), 200, 600, 20, GREEN);
}
void BlockCollision_alt(BlockEntity &block, Vector3 &p, float fallSpeed)
{
    Vector3 &bpos = block.blockCurrentPosition;
    float halfBlock = block.size / 2.0;
    float fault = 0.01f;

    BoundingBox blockBox = {
        .min = {
            .x = bpos.x - halfBlock - fault,
            .y = bpos.y - halfBlock - fault,
            .z = bpos.z - halfBlock - fault},
        .max = {.x = bpos.x + halfBlock + fault, .y = bpos.y + halfBlock + fault, .z = bpos.z + halfBlock + fault}};
    BoundingBox pBox = {
        .min = {
            .x = p.x,
            .y = p.y,
            .z = p.z},
        .max = {.x = p.x, .y = p.y, .z = p.z}};
    if (CheckCollisionBoxes(blockBox, pBox))
    {
        if (Vector3Distance(blockBox.min, pBox.min) <= 1)
        {
            p.y--;
        }
        if (Vector3Distance(blockBox.max, pBox.max) <= 1)
        {
            p.y += fallSpeed;
        }
    }
}