#pragma once

// Include necessary libraries
#include "raylib.h"  // For Raylib types and functions
#include "raymath.h" // For Raymath functions

// For Error Handling
#include <stdio.h>


// Constants
#define FRAME_RATE 60
#define FRAME_X 800
#define FRAME_Y 800

// PROTOTYPE
#if __cplusplus >= 202302L // C++23
    #if __has_include(<memory>)
        #include <memory>
        #define HAS_UNIQUE 1
    #else 
        #define HAS_UNIQUE 0
    #endif
#endif

// Struct Definitions
// Camera struct to store camera settings and label
typedef struct
{
    Camera3D camera;
    const char *cameraLabel;
} CameraName;


// Player data, including shape and score
typedef struct
{
    Vector3 playerPOS;
    double playerScore;
    const char* playerName;
    Camera3D playerCamera;
    Vector3 previousPOS;    // Store previous position
    Vector3 velocity;       // Store velocity vector
    float playerAngle;
} Player;

typedef struct
{
    Vector3 playerPOS;
    double playerScore;
    const char* playerName;
    Camera3D playerCamera;
    Vector3 previousPOS;       // Store previous position
    Vector3 playerVelocity;    // Store velocity vector
    float playerAngle;
} PlayerSettings;

typedef enum BLOCK_TYPE {
    TRI_BLOCK,
    CUBE,
    RAMP,
    FOUR_BY_FOUR
} BLOCK_TYPE;

typedef struct BlockEntity {
    unsigned char size;
    Color blockColor;
    Vector3 blockInitialPosition;
    Vector3 blockPreviousPosition;
    Vector3 blockCurrentPosition;
    BLOCK_TYPE blockType;
} BlockEntity;

// Global block list
typedef struct {
    BlockEntity* blocks;    // Array of blocks
    int count;              // Current number of blocks
    int capacity;           // Maximum number of blocks that can be rendered
} BlockList;

// Camera settings for player and its camera
typedef struct
{
    Vector3 camPosition;
    Vector3 camTarget;
    Vector3 camUp;
    float camFOVY;
    int camProjection;
    const char *camSettingsLabel;
} CameraSettings;

// Information text positioning and color
typedef struct VectorOffSets
{
    unsigned char x;
    unsigned char y;
    unsigned char z;
} vectorOffsets;

typedef struct WorldMessage
{
    const Player &player;
    const Camera &camera;
    const vectorOffsets offsets;
    const char *text;
    const int fontSize;
    const Color textColor;
} worldMessage;

typedef struct AdjustedMessage2D
{
    Vector2 translatedPOS;
    const char *formattedText;
    int measuredText;
} adjustedMessage2D;

// DEBUG
#define MAX_DEBUG_MESSAGES 10
extern const char* debugMessages[MAX_DEBUG_MESSAGES];
//
// void debugDisplay(const char* dtext, Camera& camera);
// void debugDisplay(const char* dtexts[], Camera& camera);
// void debugDisplay(const char* dtext, Camera& camera, int posY);

void DrawDebugMessages();
void AddDebugMessage(const char* message, int position);

// Initializers
#if HAS_UNIQUE > 0
void Init3DCamera(std::unique_ptr<Camera3D> camera);
#endif
void InitFPSCamera(Camera3D& camera);
void Init3DCamera(Camera3D& camera);
void Init3DCamera(Camera3D& camera, CameraSettings& camSettings);
void InitPlayer(Player& player);
Camera3D Create3DCamera();
Camera3D Create3DCamera(CameraSettings& CameraSettings);
Camera3D CreateFPSCamera();
Player CreatePlayer();
Player CreatePlayer(PlayerSettings playerSettings);
Player CreatePlayer(Player player, PlayerSettings playerSettings);

// Camera related functions
void InitCamera(Camera3D &camera, const CameraSettings &cameraSettings);
void CameraTests(Camera &camera);
void GetCameraProjectionInfo(Camera &camera);
void GetPlayerInfo(const Player &player);
void DrawCameraInfo(const Camera3D &camera, const Player &player);
void CameraInfo(Camera3D &camera);
void UpdatePlayerCamera(Player &player);
void ResetCamera(Camera3D &camera);
void IncreaseCameraPOSX(Camera3D& camera, int amount);
void IncreaseCameraPOSY(Camera3D& camera, int amount);
void IncreaseCameraPOSZ(Camera3D& camera, int amount);
void IncreaseCameraTargetX(Camera3D& camera, int amount);
void IncreaseCameraTargetY(Camera3D& camera, int amount);
void IncreaseCameraTargetZ(Camera3D& camera, int amount);

// Game Info
float playersDist(const Player &player, const Player &opponent);
adjustedMessage2D AdjustMessage(const worldMessage &details);
void debugPlayer(Player player, Camera& camera);
void displayDebugText(const char* dtext, Camera& camera);

// Draw Player
void DrawPlayer(const Player &player);

// Player Movement and Interaction
void MoveCamera(Camera3D &camera);
void MovePlayer(Player &player, const float units, Camera &camera);
void PlayerJump(Player &player, const float jumpHeight, const float fallSpeed, Vector3& ground);

void UpdateCameraSettingsRuntime(Camera3D& camera, CameraSettings& settings);

// MASTER
void GroundCollision(Vector3& player, Vector3& GROUND, int GROUND_OFFSET);
void BlockTest(BlockEntity& block, Player& player, const Vector3 InitialPOS, unsigned char t);
void BlockCollision(BlockEntity& block, Vector3& p, float fallSpeed);
void BlockCollision_alt(BlockEntity& block, Vector3& p, float fallSpeed);

void MOUSE_LOCK(int desiredPositionX, int desiredPositionY);

void DrawBlock(BlockEntity block, Vector3 pos);
void DrawTriBlock(Vector3 pos, unsigned char size);
void DrawFourByFour(Vector3 pos, unsigned char size);



// void InitBlockList(int initialCapacity);
// void FreeBlockList(BlockList* list);
// void AddBlockToList(BlockList* list, BlockEntity block);
// void RemoveBlockAtIndex(BlockList* list, int index);
// void RemoveBlockAtPosition(BlockList* list, Vector3 position, float threshold = 0.5f);
// void UpdateBlocks(BlockList* list, Player& player, unsigned char timer);
// void DrawBlockList(BlockList* list);
// void CreateAndAddBlock(BlockList* list, Vector3 position, unsigned char size, BLOCK_TYPE type, Color color);