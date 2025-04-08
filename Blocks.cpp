#include "main.hpp"

// Moves a block up and down with an outside timer
void BlockTest(BlockEntity &block, Player &player, const Vector3 InitialPOS, unsigned char t)
{
    unsigned char timerStart = 50;
    unsigned char timerEnd = 100;
    if (t <= timerStart)
    {
        block.blockCurrentPosition.y++;
    }
    if (t <= timerEnd && t >= timerStart)
    {
        block.blockCurrentPosition.y--;
    }
    if (t > 100)
    {
        t = 0;
    }
}
void BlockCollision(BlockEntity &block, Vector3 &p, float fallSpeed)
{
    // Block Vector
    Vector3 &blockCenterRef = block.blockCurrentPosition;

    // Surface area/2, since point is at center/midpoint of Block.
    float blockCenterRadius = block.size / 2.0;
    float fault_t = .01;

    // TOP
    // Z-dim cross-section, front/back
    float zBoundsMax;
    float zBoundsMin;
    // Y-dim top
    float yBoundsMax;
    float yBoundsMin;
    // X-dim cross-section, left/right sides
    float xBoundsMax;
    float xBoundsMin;

    float dist = Vector3Distance(p, block.blockCurrentPosition);
    // You're touching the block if your 
    bool touchingBlock;
    // bool onBlockLeft;
    // bool onBlockRight;
    // bool onBlockFront;
    // bool onBlockBack;

    if (block.blockType == CUBE)
    {
        zBoundsMax = (blockCenterRef.z + blockCenterRadius) + fault_t;
        zBoundsMin = (blockCenterRef.z - blockCenterRadius) - fault_t;
        
        yBoundsMax = (blockCenterRef.y + blockCenterRadius) + fault_t;
        yBoundsMin = (blockCenterRef.y) - fault_t;
        
        xBoundsMax = (blockCenterRef.x + blockCenterRadius) + fault_t;
        xBoundsMin = (blockCenterRef.x - blockCenterRadius) - fault_t;
        touchingBlock = (dist <= block.size + fault_t);
    }
    if (block.blockType == TRI_BLOCK)
    {
        // DrawCube(pos, size, size, size, RED);
        // DrawCube({pos.x, pos.y, pos.z-size}, size, size, size, YELLOW);
        // DrawCube({pos.x, pos.y, pos.z-(size*2)}, size, size, size, BLUE);
        Vector3 pos = blockCenterRef;
        Vector3 secondBlock = {pos.x, pos.y, pos.z-block.size};
        Vector3 thirdBlock = {pos.x, pos.y, pos.z-block.size*2};

        zBoundsMax = (pos.z+blockCenterRadius)+fault_t;
        zBoundsMin = (thirdBlock.z-(thirdBlock.z/2)) - fault_t;

        // So, probs could assume for just one y (pos.y+blockCenterRadius) BUT, just to be safe...
        // PROFILE THAT LATER
        yBoundsMax = 
        ( 
            ((pos.y+blockCenterRadius) + fault_t)           
            // ||
            // ((secondBlock.y+blockCenterRadius) + fault_t)   ||
            // ((thirdBlock.y+blockCenterRadius) + fault_t) 
        );

        yBoundsMin = 
        ( 
            // ((pos.y-blockCenterRadius) - fault_t)           
            // ||
            // ((secondBlock.y-blockCenterRadius) - fault_t)   
            // ||
            ((thirdBlock.y-blockCenterRadius) - fault_t) 
        );
        
        xBoundsMax = 
        ( 
            (   (pos.x+blockCenterRadius) + fault_t )           
            ||
            (   (secondBlock.x+blockCenterRadius) + fault_t )   
            ||
            (   (thirdBlock.x+blockCenterRadius) + fault_t  ) 
        );

        xBoundsMin = 
        ( 
            (   (pos.x-blockCenterRadius) - fault_t         )   
            ||
            (   (secondBlock.x-blockCenterRadius) - fault_t )   ||
            (   (thirdBlock.x-blockCenterRadius) - fault_t  ) 
        );

        touchingBlock = 
        (
            (   dist                            <= block.size + fault_t  ) ||
            (   Vector3Distance(p, secondBlock) <= block.size + fault_t  ) ||
            (   Vector3Distance(p, thirdBlock)  <= block.size + fault_t  )
        );
    }
    bool onBlockTop =   (p.y >= yBoundsMax && touchingBlock);
    bool onBlockLeft =  (p.x <= xBoundsMin && touchingBlock);
    bool onBlockRight = (p.x >= xBoundsMax && touchingBlock);
    bool onBlockFront = (p.z >= zBoundsMax && touchingBlock);
    bool onBlockBack =  (p.z <= zBoundsMin && touchingBlock);

    if (onBlockTop)
    {
        p.y += fallSpeed;
    }
    if (onBlockLeft)
    {
        p.x -= 1.0;
    }
    if (onBlockRight)
    {
        p.x += 1.0;
    }
    if (onBlockFront)
    {
        p.z += 1.0;
    }
    
    if (onBlockBack)
    {
        p.z -= 1.0;
    }

        const char* mpos = TextFormat("touchingBlock: %i", touchingBlock);
        const char* mpos2 = TextFormat("block.blockCurrentPositionPOS: %.2f, %.2f, %.2f", block.blockCurrentPosition.x, block.blockCurrentPosition.y, block.blockCurrentPosition.z);
        const char* mpos3 = TextFormat("pPOS: %.2f, %.2f, %.2f", p.x, p.y, p.z);

        AddDebugMessage(mpos, 0); // currentCount
        AddDebugMessage(mpos2, 1); // currentCount 
        AddDebugMessage(mpos3, 2); // currentCount 
}
void DrawTriBlock(Vector3 pos, unsigned char size)
{
    BlockEntity TriBlock = {
        .blockColor = RED,
        .blockCurrentPosition = pos,
        .size = size,
        .blockType = TRI_BLOCK
    };
    DrawCube(pos, size, size, size, RED);
    //Back
    DrawCube({pos.x, pos.y, pos.z-size}, size, size, size, YELLOW);
    //Diagonal
    DrawCube({pos.x, pos.y, pos.z-(size*2)}, size, size, size, BLUE);
}
void TriBlockCollision(BlockEntity &block, Vector3 &p, float fallSpeed)
{

}
// void BlockCollision4x4(BlockEntity &block, Vector3 &p, float fallSpeed) {
//     unsigned char block_adj = block.size;
//     Vector3 block_adj_pos = {block.blockCurrentPosition.x, 
//     BlockEntity adjustBlock {
//         .size = block_adj,
//         .blockCurrentPosition = 
//     }
//     BlockCollision()

// }
void DrawFourByFour(Vector3 pos, unsigned char size)
{
    BlockEntity FourByFour = {
        .blockColor = RED,
        .blockCurrentPosition = pos,
        .size = size,
        .blockType = FOUR_BY_FOUR
    };
    DrawCube(pos, size, size, size, RED);
    //Right
    DrawCube({pos.x+size, pos.y, pos.z}, size, size, size, YELLOW);
    //Back
    DrawCube({pos.x, pos.y, pos.z-size}, size, size, size, PINK);
    //Diagonal
    DrawCube({pos.x+size, pos.y, pos.z-size}, size, size, size, BLUE);
    
}
void DrawBlock(BlockEntity block, Vector3 pos)
{
    block.blockInitialPosition = pos;
    if (block.blockType == TRI_BLOCK)
    {
        DrawTriBlock(pos, block.size);
    }
    if (block.blockType == CUBE)
    {
        DrawCube(pos, block.size, block.size,  block.size, block.blockColor);
    }
    if (block.blockType == FOUR_BY_FOUR)
    {
        DrawFourByFour(pos, block.size);
    }
}
void InitBlockList(int initialCapacity);
void FreeBlockList(BlockList* list);
void AddBlockToList(BlockList* list, BlockEntity block);
void RemoveBlockAtIndex(BlockList* list, int index);
void RemoveBlockAtPosition(BlockList* list, Vector3 position, float threshold = 0.5f);
void UpdateBlocks(BlockList* list, Player& player, unsigned char timer);
void DrawBlockList(BlockList* list);
void CreateAndAddBlock(BlockList* list, Vector3 position, unsigned char size, BLOCK_TYPE type, Color color);
