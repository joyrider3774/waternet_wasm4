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
    printMessage(maxBoardBgWidth  , 6 , "b:");
    printMessage(maxBoardBgWidth  , 7 , "BACK");
    
    //A:PLAY
    printMessage(maxBoardBgWidth  , 4 , "a:");
    printMessage(maxBoardBgWidth  , 5 , "PLAY");
    
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

    if (buttonReleased(BUTTON_2))
    {
        playMenuBackSound();
        gameState = gsInitTitle;
    }
    if (buttonReleased(BUTTON_1))
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
    if (buttonReleased(BUTTON_LEFT))
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
    if (buttonReleased(BUTTON_RIGHT))
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
