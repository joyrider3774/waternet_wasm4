#ifndef commonvars_h
#define commonvars_h

#include <stdint.h>
#include "wasm4.h"
#define INDEX_BLACK 4U
#define maxBoardWidth 12U
#define maxBoardHeight 14U

#define maxBoardBgWidth 14U
#define maxBoardBgHeight 16U

#define maxBoardSize (maxBoardWidth * maxBoardHeight)

#define tileSize 8

#define gsGame 0
#define gsTitle 1
#define gsLevelSelect 2
#define gsLevelsCleared 3
#define gsHelpRotate 4
#define gsHelpRotate2 5
#define gsHelpRotateSlide 6
#define gsHelpRotateSlide2 7
#define gsHelpSlide 8
#define gsHelpSlide2 9
#define gsIntro 10

#define gsInitDiff 50

#define gsInitGame (gsInitDiff + gsGame)
#define gsInitTitle (gsInitDiff + gsTitle)
#define gsInitLevelSelect (gsInitDiff + gsLevelSelect)
#define gsInitLevelsCleared (gsInitDiff + gsLevelsCleared)
#define gsInitHelpRotate (gsInitDiff + gsHelpRotate)
#define gsInitHelpRotate2 (gsInitDiff + gsHelpRotate2)
#define gsInitHelpRotateSlide (gsInitDiff + gsHelpRotateSlide)
#define gsInitHelpRotateSlide2 (gsInitDiff + gsHelpRotateSlide2)
#define gsInitHelpSlide (gsInitDiff + gsHelpSlide)
#define gsInitHelpSlide2 (gsInitDiff + gsHelpSlide2)
#define gsInitIntro (gsInitDiff + gsIntro)


#define diffVeryEasy 0
#define diffEasy 1
#define diffNormal 2
#define diffHard 3
#define diffVeryHard 4
#define diffRandom 5
#define diffCount 6

#define gmRotate 0
#define gmSlide 1
#define gmRotateSlide 2
#define gmCount 3

#define mmStartGame 0
#define mmHelp 1
#define mmOptions 2
#define mmCredits 3
#define mmCount 4

#define opMusic 0
#define opSound 1
#define opColor 2
#define opColorInvert 3
#define opCount 4

#define tsMainMenu 0
#define tsGameMode 1
#define tsDifficulty 2
#define tsOptions 3
#define tsCredits 4

#define levelCount 25

#define arrowDown 122
#define arrowUp 120
#define arrowLeft 123
#define arrowRight 121
#define leftMenu 118

#define frameRate 60
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128
#define SCREEN_Y_OFFSET 16

extern uint8_t startPos, menuPos, 
        maxLevel, selectedLevel, boardX, boardY, difficulty, 
        gameState, boardWidth, boardHeight, boardSize,
        levelDone, titleStep, gameMode, posAdd, 
        mainMenu, option, PREVGAMEPAD1;
        
extern int16_t selectionX, selectionY;
extern uint16_t moves;
extern uint32_t randomSeedGame;
extern unsigned char level[maxBoardSize];

#endif