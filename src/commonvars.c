#include <stdint.h>

#include "wasm4.h"
#include "commonvars.h"

uint8_t startPos, menuPos, 
        maxLevel, selectedLevel, boardX, boardY, difficulty, 
        gameState, boardWidth, boardHeight, boardSize,
        levelDone, titleStep, gameMode, posAdd, 
        mainMenu, option, PREVGAMEPAD1;
 
int16_t selectionX, selectionY;
uint16_t moves;
unsigned char level[maxBoardSize];
uint32_t randomSeedGame;