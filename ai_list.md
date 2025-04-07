```cpp
#include "main.hpp"
#include <cstring> // For memcpy

// Define maximum blocks limit
#define MAX_BLOCKS 1000

// Global block list
typedef struct {
    BlockEntity* blocks;    // Array of blocks
    int count;              // Current number of blocks
    int capacity;           // Maximum capacity of the array
} BlockList;

// Initialize the block list
BlockList InitBlockList(int initialCapacity = 10) {
    BlockList list;
    list.capacity = initialCapacity;
    list.count = 0;
    list.blocks = (BlockEntity*)malloc(sizeof(BlockEntity) * initialCapacity);
    return list;
}

// Free the block list
void FreeBlockList(BlockList* list) {
    if (list->blocks != NULL) {
        free(list->blocks);
        list->blocks = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

// Add a block to the list
bool AddBlockToList(BlockList* list, BlockEntity block) {
    // Check if we need to resize the array
    if (list->count >= list->capacity) {
        int newCapacity = list->capacity * 2;
        BlockEntity* newBlocks = (BlockEntity*)realloc(list->blocks, sizeof(BlockEntity) * newCapacity);
        
        if (newBlocks == NULL) {
            // Allocation failed
            return false;
        }
        
        list->blocks = newBlocks;
        list->capacity = newCapacity;
    }
    
    // Add the new block
    list->blocks[list->count] = block;
    list->count++;
    
    return true;
}

// Remove a block at a specific index
bool RemoveBlockAtIndex(BlockList* list, int index) {
    if (index < 0 || index >= list->count) {
        return false;
    }
    
    // Shift elements to fill the gap
    for (int i = index; i < list->count - 1; i++) {
        list->blocks[i] = list->blocks[i + 1];
    }
    
    list->count--;
    return true;
}

// Remove a block based on position (approximate match)
bool RemoveBlockAtPosition(BlockList* list, Vector3 position, float threshold = 0.5f) {
    for (int i = 0; i < list->count; i++) {
        float distance = Vector3Distance(list->blocks[i].blockCurrentPosition, position);
        if (distance < threshold) {
            return RemoveBlockAtIndex(list, i);
        }
    }
    
    return false;
}

// Update all blocks in the list
void UpdateBlocks(BlockList* list, Player& player, unsigned char timer) {
    for (int i = 0; i < list->count; i++) {
        // Update block logic here if needed
        // For now, just checking collision with player
        BlockCollision(list->blocks[i], player.playerPOS, 0.1f);
    }
}

// Draw all blocks in the list
void DrawBlockList(BlockList* list) {
    for (int i = 0; i < list->count; i++) {
        DrawBlock(list->blocks[i], list->blocks[i].blockCurrentPosition);
    }
}

// Create a new block and add it to the list
bool CreateAndAddBlock(BlockList* list, Vector3 position, unsigned char size, BLOCK_TYPE type, Color color) {
    BlockEntity newBlock = {
        .size = size,
        .blockColor = color,
        .blockInitialPosition = position,
        .blockPreviousPosition = position,
        .blockCurrentPosition = position,
        .blockType = type
    };
    
    return AddBlockToList(list, newBlock);
}
```