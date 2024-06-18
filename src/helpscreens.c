#include <stdint.h>

#include "commonvars.h"
#include "helperfuncs.h"
#include "printfuncs.h"
#include "cursor.h"
#include "sound.h"
#include "palettes.h"

uint8_t incY = 0;

//LEGEND STATE
void inithelpLegend() 
{
    setPaletteGame();
    setBlockTilesAsBackground();
    SelectMusic(musTitle, 1);
}

//LEGEND + FINISH LEVEL STATE
void helpLegend(uint8_t nextState) 
{
    if ((gameState == gsInitHelpSlide) ||
        (gameState == gsInitHelpRotate) ||
        (gameState == gsInitHelpRotateSlide))
    {
        inithelpLegend();
        gameState -= gsInitDiff;
    }
   
    clear(INDEX_BLACK);
    switch(gameState)
	{
		case gsHelpSlide:
			printMessage(4, 0, "HELP: SLIDE");
			break;
		case gsHelpRotate:
			printMessage(4, 0, "HELP: ROTATE");
			break;
		case gsHelpRotateSlide:
			printMessage(4, 0, "HELP: ROSLID");
			break;
	}
	
	set_bkg_tile_xy(19, 0, 78);
	set_bkg_tile_xy(1, 1, 33);
	printMessage(2, 1, ":WATER SOURCE");
	set_bkg_tile_xy(1, 2, 11);
	set_bkg_tile_xy(2, 2, 6);
	set_bkg_tile_xy(3, 2, 12);
	printMessage(4, 2, ":NOT FILLED");
	set_bkg_tile_xy(1, 3, 27);
	set_bkg_tile_xy(2, 3, 22);
	set_bkg_tile_xy(3, 3, 28);
	printMessage(4, 3, ":FILLED");

	if((gameState == gsHelpRotateSlide) ||
	(gameState == gsHelpSlide))
	{
		set_bkg_tile_xy(1, 4, 121);
		printMessage(2, 4, ":SLIDE ROW RIGHT");
		set_bkg_tile_xy(1, 5, 123);
		printMessage(2, 5, ":SLIDE ROW LEFT");
		set_bkg_tile_xy(1, 6, 122);
		printMessage(2, 6, ":SLIDE COL DOWN");
		set_bkg_tile_xy(1, 7, 120);
		printMessage(2, 7, ":SLIDE COL UP");
	}

	printMessage(0, 9, "LEVEL FINISH:");

	if((gameState == gsHelpSlide) ||
	(gameState == gsHelpRotateSlide))
	{
		//arrows top
		set_bkg_tile_xy(2, 10, 122);
		set_bkg_tile_xy(3, 10, 122);
		set_bkg_tile_xy(4, 10, 122);

		//arrows left / right row 1
		set_bkg_tile_xy(1, 11, 121);
		set_bkg_tile_xy(5, 11, 123);

		//arrows left / right row 2
		set_bkg_tile_xy(1, 12, 121);
		set_bkg_tile_xy(5, 12, 123);

		//arrows left / right row 3
		set_bkg_tile_xy(1, 13, 121);
		set_bkg_tile_xy(5, 13, 123);

		//arrows bottom
		set_bkg_tile_xy(2, 14, 120);
		set_bkg_tile_xy(3, 14, 120);
		set_bkg_tile_xy(4, 14, 120);
	}
	set_bkg_tile_xy(2, 11, 25);
	set_bkg_tile_xy(3, 11, 23);
	set_bkg_tile_xy(4, 11, 27);
	printMessage(7, 11, "ALL WATER");

	set_bkg_tile_xy(2, 12, 28);
	set_bkg_tile_xy(3, 12, 33);
	set_bkg_tile_xy(4, 12, 22);
	printMessage(7, 12, "PIPES ARE");

	set_bkg_tile_xy(2, 13, 29);
	set_bkg_tile_xy(3, 13, 20);
	set_bkg_tile_xy(4, 13, 23);
	printMessage(7, 13, "FILLED");

    if (buttonReleased(BUTTON_1))
    {
        playMenuAcknowlege();
        gameState = nextState;
    }
}


void initHelpDoSlideRotate()
{
    setPaletteGame();
    setBlockTilesAsBackground();
    SelectMusic(musTitle, 1);

    //DRAW CURSOR SPRITES
    initCursors();

    if(gameState == gsInitHelpRotateSlide2)
        incY = 7;
    else
        incY = 0;

    if((gameState == gsInitHelpRotateSlide2) ||
      (gameState == gsInitHelpSlide2))
    {
        setCursorPos(0, 2, 5 + incY);
        setCursorPos(1, 13, 5 + incY);
    }

    if((gameState == gsInitHelpRotateSlide2) ||
      (gameState == gsInitHelpRotate2))
    {
        setCursorPos(2, 3, 4);
        setCursorPos(3, 14, 4);
    }

    showCursors();
}

void helpDoSlideRotate(uint8_t nextState)
{
    if ((gameState == gsInitHelpSlide2) ||
        (gameState == gsInitHelpRotate2) ||
        (gameState == gsInitHelpRotateSlide2))
    {
        initHelpDoSlideRotate();
        gameState -= gsInitDiff;
    }
   
	clear(INDEX_BLACK);
	
	set_bkg_tile_xy(19, 0, 77);
	
	switch(gameState)
	{
		case gsHelpSlide2:
			printMessage(4, 0, "HELP: SLIDE");
			break;
		case gsHelpRotate2:
			printMessage(4, 0, "HELP: ROTATE");
			break;
		case gsHelpRotateSlide2:
			printMessage(4, 0, "HELP: ROSLID");
	}

	if((gameState == gsHelpRotateSlide2) || 
		(gameState == gsHelpRotate2))
		printMessage(7, 2, "ROTATE");
	
	if((gameState == gsHelpRotateSlide2) || 
		(gameState == gsHelpSlide2))
		printMessage(8, 2 + incY, "SLIDE");

	// 'A' + '=>'
	set_bkg_tile_xy(8, 5, 119);
	set_bkg_tile_xy(10, 5, 118);

	// 'A' + '=>'
	set_bkg_tile_xy(8, 5 + incY, 119);
	set_bkg_tile_xy(10, 5 + incY, 118);


	if((gameState == gsHelpSlide2) || 
		(gameState == gsHelpRotateSlide2))
	{
		//1st grid
		//Top Arrows
		set_bkg_tile_xy(3, 3, 122);
		set_bkg_tile_xy(4, 3, 122);
		set_bkg_tile_xy(5, 3, 122);

		//arrows 1st row
		set_bkg_tile_xy(2, 4, 121);
		set_bkg_tile_xy(6, 4, 123);

		//arrows 2nd row
		set_bkg_tile_xy(2, 5, 121);
		set_bkg_tile_xy(6, 5, 123);

		//arrows 3rd row
		set_bkg_tile_xy(2, 6, 121);
		set_bkg_tile_xy(6, 6, 123);

		//arrows bottom
		set_bkg_tile_xy(3, 7, 120);
		set_bkg_tile_xy(4, 7, 120);
		set_bkg_tile_xy(5, 7, 120);

		//2nd grid

		//Top Arrows
		set_bkg_tile_xy(14, 3, 122);
		set_bkg_tile_xy(15, 3, 122);
		set_bkg_tile_xy(16, 3, 122);
		
		//arrows 1st row
		set_bkg_tile_xy(13, 4, 121);
		set_bkg_tile_xy(17, 4, 123);
		
		//arrows 2nd row
		set_bkg_tile_xy(13, 5, 121);
		set_bkg_tile_xy(17, 5, 123);

		//arrows 3rd row
		set_bkg_tile_xy(13, 6, 121);
		set_bkg_tile_xy(17, 6, 123);

		//bottoms arrows
		set_bkg_tile_xy(14, 7, 120);
		set_bkg_tile_xy(15, 7, 120);
		set_bkg_tile_xy(16, 7, 120);
	}
	
	if (gameState == gsHelpRotateSlide2)
	{
		//3rd grid
		//Top Arrows
		set_bkg_tile_xy(3, 3 + incY, 122);
		set_bkg_tile_xy(4, 3 + incY, 122);
		set_bkg_tile_xy(5, 3 + incY, 122);

		//arrows 1st row
		set_bkg_tile_xy(2, 4 + incY, 121);
		set_bkg_tile_xy(6, 4 + incY, 123);

		//arrows 2nd row
		set_bkg_tile_xy(2, 5 + incY, 121);
		set_bkg_tile_xy(6, 5 + incY, 123);
		
		//arrows 3rd row
		set_bkg_tile_xy(2, 6 + incY, 121);
		set_bkg_tile_xy(6, 6 + incY, 123);
	
		//arrows bottom
		set_bkg_tile_xy(3, 7 + incY, 120);
		set_bkg_tile_xy(4, 7 + incY, 120);
		set_bkg_tile_xy(5, 7 + incY, 120);

		//4nd grid

		//Top Arrows
		set_bkg_tile_xy(14, 3 + incY, 122);
		set_bkg_tile_xy(15, 3 + incY, 122);
		set_bkg_tile_xy(16, 3 + incY, 122);

		//arrows 1st row
		set_bkg_tile_xy(13, 4 + incY, 121);
		set_bkg_tile_xy(17, 4 + incY, 123);

		//arrows 2nd row
		set_bkg_tile_xy(13, 5 + incY, 121);
		set_bkg_tile_xy(17, 5 + incY, 123);

		//arrows 3rd row
		set_bkg_tile_xy(13, 6 + incY, 121);
		set_bkg_tile_xy(17, 6 + incY, 123);

		//bottoms arrows
		set_bkg_tile_xy(14, 7 + incY, 120);
		set_bkg_tile_xy(15, 7 + incY, 120);
		set_bkg_tile_xy(16, 7 + incY, 120);
	}

	//1st grid
	if ((gameState == gsHelpRotate2) ||
		(gameState == gsHelpRotateSlide2))
	{
		//1st grid
		set_bkg_tile_xy(3, 4, 12);
		set_bkg_tile_xy(4, 4, 7);
		set_bkg_tile_xy(5, 4, 27);

		set_bkg_tile_xy(3, 5, 28);
		set_bkg_tile_xy(4, 5, 33);
		set_bkg_tile_xy(5, 5, 22);

		set_bkg_tile_xy(3, 6, 29);
		set_bkg_tile_xy(4, 6, 20);
		set_bkg_tile_xy(5, 6, 23);

		//2nd
		set_bkg_tile_xy(14, 4, 25);
		set_bkg_tile_xy(15, 4, 23);
		set_bkg_tile_xy(16, 4, 27);
		
		set_bkg_tile_xy(14, 5, 28);
		set_bkg_tile_xy(15, 5, 33);
		set_bkg_tile_xy(16, 5, 22);

		set_bkg_tile_xy(14, 6, 29);
		set_bkg_tile_xy(15, 6, 20);
		set_bkg_tile_xy(16, 6, 23);

	}

	if ((gameState == gsHelpSlide2) ||
		(gameState == gsHelpRotateSlide2))
	{
		set_bkg_tile_xy(3, 4 + incY, 9);
		set_bkg_tile_xy(4, 4 + incY, 7);
		set_bkg_tile_xy(5, 4 + incY, 11);

		set_bkg_tile_xy(3, 5 + incY, 17);
		set_bkg_tile_xy(4, 5 + incY, 38);
		set_bkg_tile_xy(5, 5 + incY, 12);

		set_bkg_tile_xy(3, 6 + incY, 13);
		set_bkg_tile_xy(4, 6 + incY, 4);
		set_bkg_tile_xy(5, 6 + incY, 7);

		//2nd grid
		set_bkg_tile_xy(14, 4 + incY, 25);
		set_bkg_tile_xy(15, 4 + incY, 23);
		set_bkg_tile_xy(16, 4 + incY, 27);
	
		set_bkg_tile_xy(14, 5 + incY, 28);
		set_bkg_tile_xy(15, 5 + incY, 33);
		set_bkg_tile_xy(16, 5 + incY, 22);

		set_bkg_tile_xy(14, 6 + incY, 29);
		set_bkg_tile_xy(15, 6 + incY, 20);
		set_bkg_tile_xy(16, 6 + incY, 23);
	}
	drawCursors();
    updateCursorFrame();
   
    if (buttonReleased(BUTTON_1))
    {
        playMenuAcknowlege();
        gameState = nextState;
        hideCursors();
    }
}


//LEGEND + FINISHLEVEL STATE
void helpRotateSlide() 
{
    helpLegend(gsInitHelpRotateSlide2);
}

//ACTIONS SLIDE + ROTATE
void helpRotateSlide2() 
{
    helpDoSlideRotate(gsInitTitle);
}

//LEGEND + FINISHLEVEL STATE
void helpRotate()
{
    helpLegend(gsInitHelpRotate2);
}

//ACTIONS ROTATE
void helpRotate2()
{
    helpDoSlideRotate(gsInitTitle);
}

//LEGEND STATE
void helpSlide()
{
    helpLegend(gsInitHelpSlide2);
}

//ACTIONS SLIDE
void helpSlide2()
{
    helpDoSlideRotate(gsInitTitle);
}