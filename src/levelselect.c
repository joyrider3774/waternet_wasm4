#include <stdint.h>
#include "wasm4.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "savestate.h"
#include "sound.h"
#include "level.h"
#include "palettes.h"


void drawLevelSelect() 
{
    clear(INDEX_BLACK);
    //LEVEL:
    printMessage(maxBoardBgWidth  , 0 , "LEVEL:");
    
    //[LEVEL NR] 2 chars
    printNumber(maxBoardBgWidth + 4 , 1 , selectedLevel, 2);
    
    //B:BACK
    printMessage(maxBoardBgWidth  , 7 , "b:");
    printMessage(maxBoardBgWidth  , 8 , "BACK");
    
    //A:PLAY
    printMessage(maxBoardBgWidth  , 4 , "a:");
    printMessage(maxBoardBgWidth  , 5 , "PLAY");

	//LEFT:PREV
    printMessage(maxBoardBgWidth  , 10 , "LEFT:");
    printMessage(maxBoardBgWidth  , 11 , "PREV");

	//RIGHT:NEXT
    printMessage(maxBoardBgWidth  , 13 , "RIGHT:");
    printMessage(maxBoardBgWidth  , 14, "NEXT");

    //Locked & Unlocked keywoard
    uint8_t tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);
    if(!tmpUnlocked)
        printMessage(maxBoardBgWidth , 2 , "LOCKED");
    else
        printMessage(maxBoardBgWidth , 2 , "OPEN");
    
    drawLevelFull();
}


void initLevelSelect()
{
    setBlockTilesAsBackground();
    SelectMusic(musTitle, 1);
    setPaletteGame();
}

void levelSelect()
{
    if(gameState == gsInitLevelSelect)
    {
        initLevelSelect();
        gameState -= gsInitDiff;
    }
    drawLevelSelect();
    uint8_t tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);

    if (buttonReleased(BUTTON_2) || (!anyButtonReleased() && mouseButtonReleased(MOUSE_LEFT) &&
		(*MOUSE_X >= (int16_t)maxBoardBgWidth * 8) && (*MOUSE_X < ((int16_t)maxBoardBgWidth + 4)*8) && 
		(*MOUSE_Y >= SCREEN_Y_OFFSET + 7 * 8 ) && (*MOUSE_Y < SCREEN_Y_OFFSET + 9 * 8 )) || 
		(!anyButtonReleased() && mouseButtonReleased(MOUSE_RIGHT) && mouseInGameBounds()))
    {
        playMenuBackSound();
        gameState = gsInitTitle;
    }
    if (buttonReleased(BUTTON_1) || (!anyButtonReleased() && mouseButtonReleased(MOUSE_LEFT) && 
		(((*MOUSE_X >= (int16_t)maxBoardBgWidth * 8) && (*MOUSE_X < ((int16_t)maxBoardBgWidth + 4)*8) && 
		(*MOUSE_Y >= SCREEN_Y_OFFSET + 4 * 8 ) && (*MOUSE_Y < SCREEN_Y_OFFSET + 6 * 8)) || 
		((*MOUSE_X >= 0) && (*MOUSE_X < ((int16_t)maxBoardBgWidth)*8) && 
		(*MOUSE_Y >= SCREEN_Y_OFFSET) && (*MOUSE_Y < SCREEN_Y_OFFSET + ((int16_t)maxBoardBgHeight *8) )))))
    {
        if(tmpUnlocked)
        {
            gameState = gsInitGame;
            playMenuAcknowlege();
        }
        else
        {
            playErrorSound();
        }
    }
    if (buttonReleased(BUTTON_LEFT) || (!anyButtonReleased() && mouseButtonReleased(MOUSE_LEFT) && 
		(*MOUSE_X >= (int16_t)maxBoardBgWidth * 8) && (*MOUSE_X < ((int16_t)maxBoardBgWidth + 5)*8) && 
		(*MOUSE_Y >= SCREEN_Y_OFFSET + 10 * 8 ) && (*MOUSE_Y < SCREEN_Y_OFFSET + 12 * 8 )))
    {
        if (difficulty == diffRandom)
        {
            playMenuSelectSound();
            randomSeedGame = getRandomSeed();
            initLevel(randomSeedGame);
        }
        else
        {
            if (selectedLevel > 1)
            {
                playMenuSelectSound();
                selectedLevel--;
                initLevel(randomSeedGame);
            }
        } 
    }
    if (buttonReleased(BUTTON_RIGHT) || (!anyButtonReleased() && mouseButtonReleased(MOUSE_LEFT) && 
		(*MOUSE_X >= (int16_t)maxBoardBgWidth * 8) && (*MOUSE_X < ((int16_t)maxBoardBgWidth + 6)*8) && 
		(*MOUSE_Y >= SCREEN_Y_OFFSET + 13 * 8 ) && (*MOUSE_Y < SCREEN_Y_OFFSET + 15 * 8 )))
    {
        if (difficulty == diffRandom)
        {
            playMenuSelectSound();
            //need new seed based on time
            randomSeedGame = getRandomSeed();
            initLevel(randomSeedGame);
        }
        else
        {
            if (selectedLevel < maxLevel)
            {
                playMenuSelectSound();
                selectedLevel++;
                initLevel(randomSeedGame);
            }
        }
    }
}
