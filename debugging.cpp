#pragma once
#include "main.hpp"

    // DEBUG
    const char* debugMessages[MAX_DEBUG_MESSAGES];
    int debugMessagesCount = 0;
    //
void UpdateCameraSettingsRuntime(Camera3D& camera, CameraSettings& settings)
{
    // Check for input to modify camera settings
        // Position adjustments
        if (IsKeyDown(KEY_X)) settings.camPosition.x += GetFrameTime() * 10.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_X)) settings.camPosition.x -= GetFrameTime() * 10.0f;
        
        if (IsKeyDown(KEY_Y)) settings.camPosition.y += GetFrameTime() * 10.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_Y)) settings.camPosition.y -= GetFrameTime() * 10.0f;
        
        if (IsKeyDown(KEY_Z)) settings.camPosition.z += GetFrameTime() * 10.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_Z)) settings.camPosition.z -= GetFrameTime() * 10.0f;
        
        // Target adjustments
        if (IsKeyDown(KEY_U)) settings.camTarget.x += GetFrameTime() * 10.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_U)) settings.camTarget.x -= GetFrameTime() * 10.0f;
        
        if (IsKeyDown(KEY_I)) settings.camTarget.y += GetFrameTime() * 10.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_I)) settings.camTarget.y -= GetFrameTime() * 10.0f;
        
        if (IsKeyDown(KEY_O)) settings.camTarget.z += GetFrameTime() * 10.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_O)) settings.camTarget.z -= GetFrameTime() * 10.0f;
        
        // FOV adjustments
        if (IsKeyDown(KEY_F)) settings.camFOVY += GetFrameTime() * 20.0f;
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_F)) settings.camFOVY -= GetFrameTime() * 20.0f;
        
        DrawText(TextFormat("Current Camera Settings:\n"), 100, 200, 25, BLACK);
        DrawText(TextFormat("Position: +/- xyz keys {%.2f, %.2f, %.2f}\n", settings.camPosition.x, settings.camPosition.y, settings.camPosition.z), 
        100, 230, 25, BLACK);
        DrawText(TextFormat("Target: uio keys {%.2f, %.2f, %.2f}\n", settings.camTarget.x, settings.camTarget.y, settings.camTarget.z), 
        100, 260, 25, BLACK);
        DrawText(TextFormat("FOV f key: %.2f\n", settings.camFOVY), 100, 290, 25, BLACK);
}
void DisplayPoints(Vector3 &pos, int points, int fontSize, bool reset)
{
    const char *pointText = TextFormat("+%i", points);
    int textWidth = MeasureText(pointText, fontSize);
    static unsigned char alpha = 255;
    for (size_t i = 255; i >= 0; i--)
    {
        DrawText(pointText, pos.x - textWidth / 2, pos.y, fontSize, {255, 255, 255, alpha});
    }
    if (reset)
    {
        alpha = 255;
    }
}
// Handles camera mode switch based on key press
void CameraTests(Camera &camera)
{
    if (IsKeyPressed(KEY_V))
        camera.projection = CAMERA_FIRST_PERSON;
    if (IsKeyPressed(KEY_B))
        camera.projection = CAMERA_FREE;
    if (IsKeyPressed(KEY_N))
        camera.projection = CAMERA_ORBITAL;
    if (IsKeyPressed(KEY_M))
        camera.projection = CAMERA_ORTHOGRAPHIC;
    if (IsKeyPressed(KEY_O))
        camera.projection = CAMERA_THIRD_PERSON;
    if (IsKeyPressed(KEY_P))
        camera.projection = CAMERA_PERSPECTIVE;
}

// Displays the current camera projection mode and controls
void GetCameraProjectionInfo(Camera &camera)
{
        /*
        if (IsKeyPressed(KEY_V))
        camera.projection = CAMERA_FIRST_PERSON;
        if (IsKeyPressed(KEY_B))
            camera.projection = CAMERA_FREE;
        if (IsKeyPressed(KEY_N))
            camera.projection = CAMERA_ORBITAL;
        if (IsKeyPressed(KEY_M))
            camera.projection = CAMERA_ORTHOGRAPHIC;
        if (IsKeyPressed(KEY_O))
            camera.projection = CAMERA_THIRD_PERSON;
        if (IsKeyPressed(KEY_P))
            camera.projection = CAMERA_PERSPECTIVE;
    */
    const char *projectionNames[] = {
        "Perspective", 
        "Free/Orthographic", 
        "Orbital",
        "First Person", 
        "Third Person"
    };

    DrawText("Camera Projection Controls:", 50, 290, 10, RED);
    DrawText("v = First Person, b = Free, n = Orbital", 50, 300, 10, RED);
    DrawText("m = Orthographic, o = Third Person, p = Perspective", 50, 310, 10, RED);

    if (camera.projection >= 0 && camera.projection < 5)
    {
        DrawText(TextFormat("Current Projection: %s", projectionNames[camera.projection]), 50, 320, 10, RED);
    }
    else
    {
        DrawText("Current Projection: Unknown", 50, 330, 10, RED);
    }

    if (camera.projection == 1)
    {
        static const char *subMode = "";
        if (IsKeyPressed(KEY_M))
            subMode = "Orthographic";
        if (IsKeyPressed(KEY_B))
            subMode = "Free";
        DrawText(TextFormat("Sub-mode: %s", subMode), 50, 340, 10, RED);
    }
}
// Display camera and player info on screen
void DrawCameraInfo(const Camera3D &camera, const Player &player)
{
    DrawText("WSAD, move camera forward/back/left/right", 50, 80, 10, RED);
    DrawText("CTRL/Space - Down/Up", 50, 90, 10, RED);
    DrawText("Mouse, pivot angle", 50, 100, 10, RED);
    DrawText(TextFormat("CAM_POS:\nX:%.2f \nY:%.2f \nZ:%.2f", camera.position.x, camera.position.y, camera.position.z), 50, 120, 10, RED);
    DrawText(TextFormat("Target:%.2f \nUp:%.2f \nFOVY:%.2f", camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z, camera.fovy), 50, 180, 10, RED);
    DrawText("Q for RESET PLAYER_1", 50, 230, 10, RED);
    DrawText("Z for RESET CAMERA", 50, 240, 10, RED);
    DrawText("LEFT/RIGHT BRACKET for CAM SWITCH", 50, 250, 10, RED);
    GetCameraProjectionInfo(const_cast<Camera &>(camera));
    GetPlayerInfo(player);
}

void DrawDebugMessages()
{
    // DrawText(debugMessages[0], 100, 100, 20, BLACK);
    // DrawText(debugMessages[1], 100, 130, 20, BLACK);
    // DrawText(debugMessages[2], 100, 160, 20, BLACK);
    // DrawText(debugMessages[3], 100, 190, 20, BLACK);
    // DrawText(debugMessages[4], 100, 220, 20, BLACK);
    int yPOS = 100;
    int fontSize = 20;
    for (int i = 0; i < debugMessagesCount; i++)
    {
        DrawText(debugMessages[i], 100, yPOS, fontSize, BLACK);
        yPOS += fontSize;
    }
}

void AddDebugMessage(const char* message, int position)
{
    // NEW
    if(debugMessages[position] == nullptr)
    {
        printf("\ndebugMessages[position] == nullptr:\nBEGIN:\n message: {\n%s\n}\n position: %i \nEND\n", message, position);
        debugMessages[position] = message;
        debugMessagesCount++;
    } else 
    // JUST INSERT
    if(debugMessages[position] != nullptr)
    {
        printf("\ndebugMessages[position] != nullptr:\nBEGIN:\n message: {\n%s\n}\n position: %i \nEND\n", message, position);
        debugMessages[position] = message;
    }
}