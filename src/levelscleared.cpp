#include <stdint.h>

#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "sound.h"
#include "level.h"
#include "palettes.h"

#include "congratsscreentiles.h"
#include "congratsscreenmap.h"

void initLevelsCleared()
{
    setPaletteTitle();
    set_bkg_data(&congratstiles_8x8);
    SelectMusic(musAllLevelsClear, 1);
}

void levelsCleared() 
{  
    if(gameState == gsInitLevelsCleared)
    {
        initLevelsCleared();
        gameState -= gsInitDiff;
    }

 	clear(INDEX_BLACK);
    drawImage(0, 0, &congratsscreen_8x8);
    switch (difficulty)
    {
        case diffVeryEasy:
            printCongratsScreen(2, 7, "VERY EASY LEVELS");
            break;
        
        case diffEasy:
            printCongratsScreen(4, 7, "EASY LEVELS");
            break;
    
        case diffNormal:
            printCongratsScreen(3, 7, "NORMAL LEVELS");
            break;

        case diffHard:
            printCongratsScreen(4, 7, "HARD LEVELS");
            break;
    
        case diffVeryHard:
            printCongratsScreen(2, 7, "VERY HARD LEVELS");
            break;
    }

    if (buttonReleased(BUTTON_1) || 
        buttonReleased(BUTTON_2)) 
    {
        playMenuAcknowlege();
        titleStep = tsMainMenu;
        gameState = gsInitTitle;
    }
}