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



adjustedMessage2D AdjustMessage(const worldMessage &details)
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



void GroundFallThroughProtection(Vector3& target, Vector3& ground, int offset)
{
    // BOTTOM
    if (target.y < ground.y) {
        target.y = ground.y+offset;
    }
}