#include "main.hpp"

// Displays player info on screen
void GetPlayerInfo(const Player &player)
{
    DrawText(TextFormat("Player Position:\nX:%.2f\nY:%.2f\nZ:%.2f", player.playerPOS.x, player.playerPOS.y, player.playerPOS.z), 450, 150, 10, RED);
    DrawText(TextFormat("Player Score: %.2f", player.playerScore), 450, 200, 10, RED);
    DrawText(TextFormat("Player Name: %s", player.playerName), 450, 210, 10, RED);
}
// Resets the player's position and body properties to default
void ResetPlayer(Player &player)
{
    player.playerPOS = {0, 1, 0};
}

void displayPoints(Vector3 &pos, int points, int fontSize, bool reset)
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

adjustedMessage2D adjustMessage(const worldMessage &details)
{
    const Vector3 worldPOS{
        details.player.playerPOS.x + details.offsets.x,
        details.player.playerPOS.y + details.offsets.y,
        details.player.playerPOS.z + details.offsets.z};
    // Convert from 3d to coordinates
    Vector2 posTranslate = GetWorldToScreen(worldPOS, details.camera);
    const char *textFormat = details.text; // TextFormat("..",...)
    int textMeasure = MeasureText(textFormat, details.fontSize);
    adjustedMessage2D message = {
        .translatedPOS = posTranslate,
        .formattedText = textFormat,
        .measuredText = textMeasure};
    return message;
}
void displayPlayerPoints(const worldMessage &wm)
{
    adjustedMessage2D msg = adjustMessage(wm);
    const char *scoreText = TextFormat("%s %d", wm.text, (int)wm.player.playerScore);
    DrawText(
        scoreText,
        msg.translatedPOS.x - msg.measuredText / 2,
        msg.translatedPOS.y,
        wm.fontSize,
        wm.textColor);
}
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

void Contain(Vector3& target, Vector3& ground)
{
    // BOTTOM
    if (target.y < ground.y) {
        target.y = ground.y+3;
    }
}