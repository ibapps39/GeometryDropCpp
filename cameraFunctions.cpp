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