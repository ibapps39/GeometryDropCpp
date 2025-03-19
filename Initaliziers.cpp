#pragma once
#include "main.hpp"

void InitFPSCamera(Camera3D& camera)
{
    CameraSettings initCameraSettings = {
        .camPosition = {0,0,0},
        .camProjection = CAMERA_FIRST_PERSON,
        .camFOVY = 0,
        .camSettingsLabel = "InitialFPS",
        .camUp = {0,0,0},
        .camTarget = {0}
    };
    camera.position = initCameraSettings.camPosition;
    camera.projection = initCameraSettings.camProjection;
    camera.fovy = initCameraSettings.camFOVY;
    camera.target = initCameraSettings.camTarget;
    camera.up = initCameraSettings.camUp;
}

void Init3DCamera(Camera3D& camera)
{
    camera.position = {0};
    camera.projection = 0;
    camera.fovy = 0;
    camera.target = {0};
    camera.up = {0};
}

void Init3DCamera(Camera3D& camera, CameraSettings& camSettings)
{
    camera.position = camSettings.camPosition;
    camera.projection = camSettings.camProjection;
    camera.fovy = camSettings.camFOVY;
    camera.target = camSettings.camTarget;
    camera.up = camSettings.camUp;
}

void InitZeroPlayer(Player& player)
{
    player.playerName = "\0";
    player.playerCamera = {0};
    player.playerScore = 0.00;
    player.previousPOS = {0};
    player.velocity = {0};
}
void InitPlayer(Player& player, PlayerSettings settings)
{
    player.playerName = settings.playerName;
    player.playerCamera = settings.playerCamera;
    player.playerScore = settings.playerScore;
    player.previousPOS = settings.playerPOS;
    player.velocity = settings.playerVelocity;
}

Camera3D Create3DCamera()
{
    Camera3D camera;
    Init3DCamera(camera);
    return camera;
}
Camera3D Create3DCamera(CameraSettings& camSettings)
{
    Camera3D camera;
    Init3DCamera(camera, camSettings);
    return camera;
}
Camera3D CreateFPSCamera()
{
    Camera3D camera;
    InitFPSCamera(camera);
    return camera;
}
Player CreatePlayer() {
    Player player;
    InitZeroPlayer(player);
    return player;
}

Player CreatePlayer(PlayerSettings playerSettings)
{
    Player player;
    InitPlayer(player, playerSettings);
    return player;
}
Player CreatePlayer(Player player, PlayerSettings playerSettings)
{
    InitPlayer(player, playerSettings);
    return player;
}
void InitGame()
{
    

}