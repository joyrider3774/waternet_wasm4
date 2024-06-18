#include <stdint.h>
#include "wasm4.h"
#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "palettes.h"

#include "titlescreenmap.h"

#define frameDelay ((uint8_t)(frameRate*1.5))

uint16_t frames;
float titlePosY;


void initIntro()
{
    setPaletteTitle();
    setBlockTilesAsBackground();
    titlePosY = SCREEN_HEIGHT;
    frames = 0;   
}

void intro() 
{
    if (gameState == gsInitIntro)
    {
        initIntro();
        gameState -= gsInitDiff;
    }

	frames++;
    clear(INDEX_BLACK);
    if (frames < frameDelay)
    {
        //20-12
        printMessage(8 >> 1, 7, "WILLEMS DAVY");
    }
    else
    {
        if (frames < frameDelay *2)
        {
            //20-8
            printMessage(12 >> 1, 7, "PRESENTS");
        }
        else
        {
            drawImage(0, (uint32_t)titlePosY, titlescreen_8x8);
            if(titlePosY > 0)
            {
                titlePosY -= (float)60/(float)frameRate;
            }
            else
            {
                gameState = gsInitTitle;
            }
        }
    }
    
    if (buttonReleased(BUTTON_1) || 
        buttonReleased(BUTTON_2)) 
    {            
        gameState = gsInitTitle;
    }
}
