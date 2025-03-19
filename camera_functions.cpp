#include "main.hpp"
// Initializes camera properties based on settings
void InitCamera(Camera3D &camera, const CameraSettings &cameraSettings)
{
    camera.position = cameraSettings.camPosition;
    camera.target = cameraSettings.camTarget;
    camera.up = cameraSettings.camUp;
    camera.fovy = cameraSettings.camFOVY;
    camera.projection = cameraSettings.camProjection;
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

// Updates camera position based on player position
void UpdatePlayerCamera(Player &player, Camera3D &camera)
{
    camera.position = {};
    camera.target = {};
}

// Resets the camera to its default position and settings
void ResetCamera(Camera3D &camera, CameraSettings camSettings)
{
    camera.position = camSettings.camPosition;
    camera.target = camSettings.camTarget;
    camera.up = camSettings.camUp;
    camera.fovy = camSettings.camFOVY;
}
void ResetCamera(Camera3D* camera, CameraSettings camSettings)
{
    camera->position = camSettings.camPosition;
    camera->target = camSettings.camTarget;
    camera->up = camSettings.camUp;
    camera->fovy = camSettings.camFOVY;
}
void IncreaseCameraPOSX(Camera3D& camera, int amount)
{
    camera.position.x++;
}
void IncreaseCameraPOSY(Camera3D& camera, int amount)
{
    camera.position.y++;
}
void IncreaseCameraPOSZ(Camera3D& camera, int amount)
{
    camera.position.z++;
}

void IncreaseCameraTargetX(Camera3D& camera, int amount)
{
    camera.target.x++;
}
void IncreaseCameraTargetY(Camera3D& camera, int amount)
{
    camera.target.y++;
}
void IncreaseCameraTargetZ(Camera3D& camera, int amount)
{
    camera.target.z++;
}