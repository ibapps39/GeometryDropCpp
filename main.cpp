#include "main.hpp"

//std::vector<char*> debugList;

int main()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const Vector3 ORIGIN = {0.0f, 0.0f, 0.0f};

    Vector3 GROUND = {0,0,0};
    int GROUND_OFFSET = 3;

    // GetFrameTime()*1000 == 16 < GetFrameTime()*1000  < 17
    const float jumpHeight = 15.0f;  // Moved out of player initialization
    const float fallSpeed = 0.3;
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

    Vector3 BlockInitialPOS = {0, 0, -10};

    BlockEntity blockCube {
        .size = 5,
        .blockInitialPosition = BlockInitialPOS,
        .blockPreviousPosition = BlockInitialPOS,
        .blockCurrentPosition = BlockInitialPOS,
        .blockType = CUBE,
        .blockColor = BLACK
    };
    BlockEntity blockTri {
        .size = 2,
        .blockInitialPosition = BlockInitialPOS,
        .blockPreviousPosition = BlockInitialPOS,
        .blockCurrentPosition = BlockInitialPOS,
        .blockType = TRI_BLOCK,
        .blockColor = BLACK
    };

    //BlockEntity block = blockCube;
    BlockEntity block = blockTri;
    
    // FIXES cursor going crazy
    DisableCursor();
    static int timer = 5;
    while (!WindowShouldClose())
    {
        // FIXES cursor going crazy
        Vector2 m = {GetMouseDelta().x, GetMouseDelta().y};
        if (((m.x > 11 || m.x < -11) || (m.y > 11 || m.y < -11)) && timer > 0) 
        {
            SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2); 
            timer--;
        } 
        
        
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        camera.position = player.playerPOS;
        GroundCollision(player.playerPOS, GROUND, GROUND_OFFSET);
        //BlockTest(block, player, block.blockInitialPosition, blockTimer);
        BlockCollision(block, player.playerPOS, fallSpeed);
        //BlockCollision_alt(block, player.playerPOS, fallSpeed);

        
        //Contain(camera.position, BOX, GROUND);
        if (player.playerPOS.y <= 0) player.playerPOS.y = 1;
        if (IsKeyPressed(KEY_Q)) camera.target = {0,0,-90};
        if (IsKeyPressed(KEY_Q) && IsKeyPressed(KEY_LEFT_SHIFT)) {
            camera.target = {0,0,-90}; player.playerPOS = initCameraSettings.camPosition;
        }
        if (IsKeyPressed(KEY_J)) player.playerPOS = block.blockCurrentPosition;
        MovePlayer(player, 30, camera);
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
        //DrawCube(block.blockCurrentPosition, block.size, block.size, block.size, block.blockColor);
        //DrawTriBlock(block.blockCurrentPosition, 5);
        DrawBlock(block, block.blockCurrentPosition);

         // CAMERA FEED ENDS HERE
        EndMode3D();
        // UI AREA
        //DrawDebugMessages();
        DrawDebugMessages();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
