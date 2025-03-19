#include "main.hpp"
// Draws the player and its body with defined positions and dimensions
void DrawPlayer(const Player &player)
{
    const Vector3 &pos = player.playerPOS;

    // Player Body
    DrawCube( {pos.x, pos.y, pos.z}, 2, 2, 2, RED );
}

// Player movement logic based on key input
void MovePlayer(Player &player, const float units)
{
    float deltaOffset = units * GetFrameTime();
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        deltaOffset *= 2;
    }
    if (IsKeyDown(KEY_W))
    {
        player.playerPOS.z -= deltaOffset;
    }
    if (IsKeyDown(KEY_S))
    {
        player.playerPOS.z += deltaOffset;
    }
    if (IsKeyDown(KEY_A))
    {
        player.playerPOS.x -= deltaOffset;
    }
    if (IsKeyDown(KEY_D))
    {
        player.playerPOS.x += deltaOffset;
    }
}

// Player jump mechanic based on key press
void PlayerJump(Player &player, const float jumpHeight, Vector3& ground)
{
    bool canJump = player.playerPOS.y < jumpHeight;
    bool canFall = player.playerPOS.y > ground.y;

    if (IsKeyDown(KEY_SPACE) && canJump)
    {
        player.playerPOS.y += 0.5f;
    }
    else if (canFall)
    {
        player.playerPOS.y -= 0.05f;
    }
}