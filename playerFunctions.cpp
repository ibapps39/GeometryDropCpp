#include "main.hpp"
// Draws the player and its body with defined positions and dimensions
void DrawPlayer(const Player &player)
{
    const Vector3 &pos = player.playerPOS;

    // Player Body
    DrawCube( {pos.x, pos.y, pos.z}, 2, 2, 2, RED );
}

// Player movement logic based on key input
// Player movement logic based on key input and relative to camera's direction
void MovePlayer(Player &player, const float units, Camera &camera)
{
    float deltaOffset = units * GetFrameTime();

    if (IsKeyDown(KEY_LEFT_SHIFT))  // Sprint logic
    {
        deltaOffset *= 2;
    }

    // Calculate the forward direction based on the camera's position and target
    Vector3 cameraDirection = Vector3Subtract(camera.target, camera.position);
    cameraDirection.y = 0.0f;  // Remove any vertical component, so we only get horizontal movement
    Vector3Normalize(cameraDirection); // Normalize the direction vector
    
    // Calculate the yaw (horizontal rotation) from the camera direction vector
    float currentAngle = atan2f(cameraDirection.z, cameraDirection.x); // Calculate the yaw angle in radians

    // Calculate movement directions based on the camera's yaw angle
    float forwardDirectionX = cosf(currentAngle); // Cosine for X (right/left)
    float forwardDirectionZ = sinf(currentAngle); // Sine for Z (forward/backward)

    // Handle forward/backward movement (W/S)
    if (IsKeyDown(KEY_W)) 
    {
        player.playerPOS.x += forwardDirectionX * deltaOffset; // Move in the forward direction
        player.playerPOS.z += forwardDirectionZ * deltaOffset; // Move in the forward direction
    }
    if (IsKeyDown(KEY_S))
    {
        player.playerPOS.x -= forwardDirectionX * deltaOffset; // Move in the opposite direction
        player.playerPOS.z -= forwardDirectionZ * deltaOffset; // Move in the opposite direction
    }

    // Handle left/right strafe (A/D) - perpendicular to the camera's yaw
    if (IsKeyDown(KEY_A))
    {
        player.playerPOS.x -= deltaOffset; // Strafe left (negative Z direction)
        //player.playerPOS.z += forwardDirectionX * deltaOffset; // Strafe left (positive X direction)
    }
    if (IsKeyDown(KEY_D))
    {
        player.playerPOS.x += deltaOffset; // Strafe right (positive Z direction)
        //player.playerPOS.z -= forwardDirectionX * deltaOffset; // Strafe right (negative X direction)
    }
}


// Player jump mechanic based on key press
void PlayerJump(Player &player, const float jumpHeight, const float fallSpeed, Vector3& ground)
{
    bool canJump = player.playerPOS.y < jumpHeight;
    bool canFall = player.playerPOS.y > ground.y;

    if (IsKeyDown(KEY_SPACE) && canJump)
    {
        player.playerPOS.y += fallSpeed;
    }
    else if (canFall && player.playerPOS.y - fallSpeed > 1)
    {
        player.playerPOS.y -= fallSpeed;
    }
}