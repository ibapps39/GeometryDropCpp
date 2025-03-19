#include "main.hpp"

int main()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const Vector3 ORIGIN = {0.0f, 0.0f, 0.0f};

    // GetFrameTime()*1000 == 16 < GetFrameTime()*1000  < 17

    const float jumpHeight = 6.0f;  // Moved out of player initialization
    const float playerSpeed = 30.0; // in pixels

    InitWindow(1000, 1000, "3D Test");
    SetTargetFPS(FRAME_RATE);

    // Initial Camera Settings
    CameraSettings initCameraSettings = {
        .camPosition = {0,3,0},
        .camProjection = CAMERA_PERSPECTIVE,
        .camFOVY = 45,
        .camSettingsLabel = "InitialFPS",
        .camUp = {0,1,0},
        .camTarget = {0,20,0}
    };

    Camera3D camera = Create3DCamera(initCameraSettings);
    Player player = CreatePlayer();
    camera.target = {0,0,-90};
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, camera.projection);
        // if (IsKeyPressed(KEY_X)) IncreaseCameraPOSX(camera, 1.0);
        // if (IsKeyPressed(KEY_Y)) IncreaseCameraPOSY(camera, 1.0);
        // if (IsKeyPressed(KEY_Z)) IncreaseCameraPOSZ(camera, 1.0);
        if (IsKeyPressed(KEY_X)) IncreaseCameraTargetX(camera, 1.0);
        if (IsKeyPressed(KEY_Y)) IncreaseCameraTargetY(camera, 1.0);
        if (IsKeyPressed(KEY_Z)) IncreaseCameraTargetZ(camera, 1.0);
        MovePlayer(player, 30);
        PlayerJump(player, 10);
        
        if (IsKeyPressed(KEY_Q)) {}
        // Eh, maybe later interpolate between points and movement in MovePlayer
        // tilt down is difference between pos.y target pos.y offsets, so pos>tar y "tilt down"
        // want x and z cosntant 

        BeginDrawing();
        //BACKGROUND
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        // CAMERA FEED STARTS HERE
        DrawPlayer(player);
        DrawCylinder({0,0,0}, 20, 20, 1.0, 100, RED); // FLOOR
        DrawCylinder({0,20,0}, 20, 20, 1.0, 100, GREEN); // ROOF
        DrawCylinder({0,1,-90}, 20, 20, 10.0, 100, PINK); // NORTH
        

         // CAMERA FEED ENDS HERE
        EndMode3D();
        // UI AREA
        int fontS = 20;
        DrawText(TextFormat("Target: %f, %f, %f", camera.target.x, camera.target.y, camera.target.z), 100, 100+fontS*i fontS, RED);
        DrawText(TextFormat("POS: %f, %f, %f", camera.position.x, camera.position.y, camera.position.z), 100, 100+fontS*i, fontS, RED);
        DrawText(TextFormat("UP: %f, %f, %f", camera.up.x, camera.up.y, camera.up.z), 100, 100+fontS*i, fontS, RED);
        DrawText(TextFormat("FOV: %f", camera.fovy), 100, 100+fontS*i, fontS, RED);
        DrawText(TextFormat("FOV: %f", camera.fovy), 100, 100+fontS*i, fontS, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
