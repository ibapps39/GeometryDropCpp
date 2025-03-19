#include "main.hpp"

int main()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const Vector3 ORIGIN = {0.0f, 0.0f, 0.0f};
    Vector3 BOX = {2000, 2000, 1000};
    Vector3 GROUND = {0,0,0};

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
    player.playerPOS = {0, 3, 0};
    camera.target = {0,0,-90};
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        camera.position = player.playerPOS;
        //Contain(player.playerPOS, BOX, GROUND);
        //Contain(camera.position, BOX, GROUND);
        if (player.playerPOS.y <= 0) player.playerPOS.y = 1;

        // if (IsKeyPressed(KEY_X)) IncreaseCameraPOSX(camera, 1.0);
        // if (IsKeyPressed(KEY_Y)) IncreaseCameraPOSY(camera, 1.0);
        // if (IsKeyPressed(KEY_Z)) IncreaseCameraPOSZ(camera, 1.0);
        // if (IsKeyPressed(KEY_X)) IncreaseCameraTargetX(camera, 1.0);
        // if (IsKeyPressed(KEY_Y)) IncreaseCameraTargetY(camera, 1.0);
        // if (IsKeyPressed(KEY_Z)) IncreaseCameraTargetZ(camera, 1.0);

        if (IsKeyPressed(KEY_Q)) camera.target = {0,0,-90};

        MovePlayer(player, 30);
        PlayerJump(player, 10, GROUND);
        
        if (IsKeyPressed(KEY_Q)) {}
        // Eh, maybe later interpolate between points and movement in MovePlayer
        // tilt down is difference between pos.y target pos.y offsets, so pos>tar y "tilt down"
        // want x and z cosntant 

        BeginDrawing();
        //BACKGROUND
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        // CAMERA FEED STARTS HERE
        DrawCylinder({0,-90,0}, BOX.x, BOX.y, BOX.z, 100, BLUE); // NORTH
        DrawPlayer(player);
        DrawCylinder({0,-10,0}, 20, 20, 1.0, 100, MAGENTA); // FLOOR
        DrawCylinder({0,20,0}, 20, 20, 1.0, 100, GREEN); // ROOF
        DrawCylinder({0,1,-90}, 20, 20, 10.0, 100, PINK); // NORTH
        
        

         // CAMERA FEED ENDS HERE
        EndMode3D();
        // UI AREA
        int fontS = 20;
        Color safetyFontColor = BLACK;
        DrawText(TextFormat("CAM Target: %f, %f, %f", camera.target.x, camera.target.y, camera.target.z), 100, 100, fontS, safetyFontColor);
        DrawText(TextFormat("CAM POS: %f, %f, %f", camera.position.x, camera.position.y, camera.position.z), 100, 100+fontS, fontS, safetyFontColor);
        DrawText(TextFormat("CAM UP: %f, %f, %f", camera.up.x, camera.up.y, camera.up.z), 100, 100+fontS*2, fontS, safetyFontColor);
        DrawText(TextFormat("CAM FOV: %f", camera.fovy), 100, 100+fontS*3, fontS, safetyFontColor);
        DrawText(TextFormat("PLAYER POS: %f, %f, %f", player.playerPOS.x, player.playerPOS.y, player.playerPOS.z), 100, 100+fontS*5, fontS, safetyFontColor);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
