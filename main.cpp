#include "main.hpp"

int main()
{
    
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const Vector3 ORIGIN = {0.0f, 0.0f, 0.0f};

    Vector3 GROUND = {0,0,0};
    int GROUND_OFFSET = 3;

    // GetFrameTime()*1000 == 16 < GetFrameTime()*1000  < 17
    const float jumpHeight = 10.0f;  // Moved out of player initialization
    const float fallSpeed = 0.5;
    const float playerSpeed = 30.0; // in pixels

    InitWindow(FRAME_X, FRAME_Y, "3D Test");
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

    Vector3 BlockInitialPOS = {0, -2, -10};
    BlockEntity block {
        .size = 5,
        .blockColor = BLACK,
        .blockInitialPosition = BlockInitialPOS,
        .blockPreviousPosition = BlockInitialPOS,
        .blockCurrentPosition = BlockInitialPOS
    };

    static int lockMouse = 100; 
    static unsigned char blockTimer = 0;
    while (!WindowShouldClose())
    {
        blockTimer++;
        if (lockMouse > 0) { camera.target = {0,0,-90}; lockMouse--;} // Lock Mouse should be a function
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        camera.position = player.playerPOS;
        GroundCollision(player.playerPOS, GROUND, GROUND_OFFSET);
        //BlockTest(block, player, block.blockInitialPosition, blockTimer);
        BlockCollision(block, player.playerPOS, fallSpeed);

        
        //Contain(camera.position, BOX, GROUND);
        if (player.playerPOS.y <= 0) player.playerPOS.y = 1;
        if (IsKeyPressed(KEY_Q)) camera.target = {0,0,-90};
        if (IsKeyPressed(KEY_Q) && IsKeyPressed(KEY_LEFT_SHIFT)) {
            camera.target = {0,0,-90}; player.playerPOS = initCameraSettings.camPosition;
        }
        MovePlayer(player, 30);
        PlayerJump(player, jumpHeight, fallSpeed, GROUND);

        BeginDrawing();
        //BACKGROUND
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
        // CAMERA FEED STARTS HERE
        DrawPlayer(player);
        DrawCylinder({0,-10,0}, 20, 20, 1.0, 100, MAGENTA); // FLOOR
        DrawCylinder({0,20,0}, 20, 20, 1.0, 100, GREEN); // ROOF
        DrawCylinder({0,1,-90}, 20, 20, 10.0, 100, PINK); // NORTH
        DrawCube(block.blockCurrentPosition, block.size, block.size, block.size, block.blockColor);
        

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
