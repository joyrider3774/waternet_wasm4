#include <stdint.h>
#include <string.h>
#include "wasm4.h"

#include "fulltitlescreenmap.h"
#include "commonvars.h"
#include "helperfuncs.h"
#include "sound.h"
#include "printfuncs.h"
#include "savestate.h"
#include "level.h"
#include "palettes.h"


bool setMouseSelection()
{
	if (!mouseMovedAtleastOnce())
		return false;
	
	switch(titleStep)
	{
		case tsMainMenu:
			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 9) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 10 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 11*8))
			{
				if(mouseMoved())
					mainMenu = mmStartGame;
				return true;
			}

			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 5) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 11 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 12*8))
			{
				if(mouseMoved())
					mainMenu = mmHelp;
				return true;
			}

			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 7) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 12 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 13*8))
			{
				if(mouseMoved())
					mainMenu = mmOptions;
				return true;
			}

			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 7) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 13 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 14*8))
			{
				if(mouseMoved())
					mainMenu = mmCredits;
				return true;
			}
			break;

		case tsDifficulty:
			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 9) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 8 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 9*8))
			{
				if(mouseMoved())
					difficulty = diffVeryEasy;
				return true;
			}

			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 4) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 9 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 10*8))
			{
				if(mouseMoved())
					difficulty = diffEasy;
				return true;
			}

			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 6) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 10 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 11*8))
			{
				if(mouseMoved())
					difficulty = diffNormal;
				return true;
			}

			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 4) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 11 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 12*8))
			{
				if(mouseMoved())
					difficulty = diffHard;
				return true;
			}

			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 9) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 12 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 13*8))
			{
				if(mouseMoved())
					difficulty = diffVeryHard;
				return true;
			}

			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 6) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 13 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 14*8))
			{
				if(mouseMoved())
					difficulty = diffRandom;
				return true;
			}

			if ((*MOUSE_X >= 6*8) && (*MOUSE_X < (6 + 4) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 14 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 15*8))
			{
				if(mouseMoved())
					difficulty = 6;
				return true;
			}
			break;	
		case tsGameMode:
        	if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 6) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 10 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 11*8))
			{
				if(mouseMoved())
					gameMode = gmRotate;
				return true;
			}

			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 5) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 11 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 12*8))
			{
				if(mouseMoved())
					gameMode = gmSlide;
				return true;
			}

			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 6) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 12 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 13*8))
			{
				if(mouseMoved())
					gameMode = gmRotateSlide;
				return true;
			}

			if ((*MOUSE_X >= 7*8) && (*MOUSE_X < (7 + 4) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 13 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 14*8))
			{
				if(mouseMoved())
					gameMode = 3;
				return true;
			}
			break;
		case tsCredits:
			return mouseInGameBounds();
			break;
		case tsOptions:
			if ((*MOUSE_X >= 5*8) && (*MOUSE_X < (5 + 9) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 10 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 11*8))
			{
				if(mouseMoved())
					option = opMusic;
				return true;
			}

			if ((*MOUSE_X >= 5*8) && (*MOUSE_X < (5 + 9) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 11 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 12*8))
			{
				if(mouseMoved())
					option = opSound;
				return true;
			}

			if ((*MOUSE_X >= 5*8) && (*MOUSE_X < (5 + ((int16_t)strlen(getPaletteName()))) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 12 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 13*8))
			{
				if(mouseMoved())
					option = opColor;
				return true;
			}

			if ((*MOUSE_X >= 5*8) && (*MOUSE_X < (5 + 10) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 13 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 14*8))
			{
				if(mouseMoved())
					option = opColorInvert;
				return true;
			}

			if ((*MOUSE_X >= 5*8) && (*MOUSE_X < (5 + 4) * 8 ) && (*MOUSE_Y >= SCREEN_Y_OFFSET + 14 * 8) && (*MOUSE_Y < SCREEN_Y_OFFSET + 15*8))
			{
				if(mouseMoved())
					option = 4;
				return true;
			}
			break;
		default:
			break; 
	}
	return false;      
}

void drawTitleScreen()
{
    clear(INDEX_BLACK);
    
	drawImage(0, 0, titlescreen2_8x8);

    switch (titleStep)
    {
        case tsMainMenu:
			printMessage(6, 8, "MAIN MENU");
            printMessageWithSelectedColor(7, 10, "START", mainMenu + 10);
            printMessageWithSelectedColor(7, 11, "HELP", mainMenu + 10);
            printMessageWithSelectedColor(7, 12, "OPTIONS", mainMenu + 10);
            printMessageWithSelectedColor(7, 13, "CREDITS", mainMenu + 10);
            break;
        case tsDifficulty:
            printMessageWithSelectedColor(6, 8, "VERY EASY", difficulty + 8);
            printMessageWithSelectedColor(6, 9, "EASY", difficulty + 8);
            printMessageWithSelectedColor(6, 10, "NORMAL", difficulty + 8);
            printMessageWithSelectedColor(6, 11, "HARD", difficulty + 8);
            printMessageWithSelectedColor(6, 12, "VERY HARD", difficulty + 8);
            printMessageWithSelectedColor(6, 13, "RANDOM", difficulty + 8);
			printMessageWithSelectedColor(6, 14, "BACK", difficulty + 8);
            break;
        case tsGameMode:
            if (mainMenu == mmStartGame)
                printMessage(4, 8, "SELECT  MODE");
            else
                printMessage(6, 8, "MODE HELP");
            printMessageWithSelectedColor(7, 10, "ROTATE", gameMode + 10);
            printMessageWithSelectedColor(7, 11, "SLIDE", gameMode + 10);
            printMessageWithSelectedColor(7, 12, "ROSLID", gameMode + 10);
			printMessageWithSelectedColor(7, 13, "BACK", gameMode + 10);
            break;
        case tsCredits:
            printMessage(7, 8, "CREDITS");            
            printMessage(5, 11, "CREATED BY");
            printMessage(4, 12, "WILLEMS DAVY");
            printMessage(4, 13, "JOYRIDER3774");
            break;
        case tsOptions:
            printMessage(6, 8, "OPTIONS");            
         
            if(isMusicOn())
                printMessageWithSelectedColor(5, 10, "MUSIC  ON", option + 10);
            else
                printMessageWithSelectedColor(5, 10, "MUSIC  OFF", option + 10);

            if(isSoundOn())
                printMessageWithSelectedColor(5, 11, "SOUND  ON", option + 10);
            else
                printMessageWithSelectedColor(5, 11, "SOUND  OFF", option + 10);
            
            printMessageWithSelectedColor(5, 12, getPaletteName(), option + 10);
            
            if(getPalInverse())
                printMessageWithSelectedColor(5, 13, "INVERT ON", option + 10);
            else
                printMessageWithSelectedColor(5, 13, "INVERT OFF", option + 10);
            printMessageWithSelectedColor(5, 14, "BACK", option + 10);
			break;
    }

	setDrawColor(2,0,0,0);
    //set menu tile
    switch (titleStep)
    {
        case tsMainMenu:
            set_bkg_tile_xy(6, 10 + mainMenu, leftMenu);
            break;
        case tsGameMode:
            set_bkg_tile_xy(6, 10 + gameMode, leftMenu);
            break;
        case tsDifficulty:
            set_bkg_tile_xy(5, 8 + difficulty, leftMenu);
            break;
        case tsOptions:
            set_bkg_tile_xy(4, 10 + option, leftMenu);
            break;
    }
	setDrawColor(1,2,3,4);
}

void initTitleScreen()
{   
    setBlockTilesAsBackground();
    SelectMusic(musTitle, 1);
    setPaletteTitle();
}

void titleScreen()
{
    if(gameState == gsInitTitle)
    {
        initTitleScreen();
        gameState -= gsInitDiff;
    }

    drawTitleScreen();

    if (buttonReleased(BUTTON_UP))
    {
        switch (titleStep)
        {
            case tsMainMenu:
                if(mainMenu > mmStartGame)
                {
                    playMenuSelectSound();
                    mainMenu--;
                }
                break;
            case tsGameMode:
                if(gameMode > gmRotate)
                {
                    playMenuSelectSound();
                    gameMode--;
                }
                break;
            case tsDifficulty:
                if(difficulty > diffVeryEasy)
                {
                    playMenuSelectSound();
                    difficulty--;
                }
                break;
            case tsOptions:
                if(option > opMusic)
                {
                    playMenuSelectSound();
                    option--;
                }
                break;
        }
    }

    if (buttonReleased(BUTTON_DOWN))
    {
        switch (titleStep) 
        {
            case tsMainMenu:
                if(mainMenu < mmCount-1)
                {
                    playMenuSelectSound();
                    mainMenu++;
                }
                break;
            case tsGameMode:
                if(gameMode < gmCount)
                {
                    playMenuSelectSound();
                    gameMode++;
                }
                break; 
            case tsDifficulty:
                if(difficulty < diffCount)
                {
                    playMenuSelectSound();
                    difficulty++;
                }
                break;
            case tsOptions:
                if(option < opCount)
                {
                    playMenuSelectSound();
                    option++;
                }
                break;
        }
    }

    if (buttonReleased(BUTTON_2) || (!anyButtonReleased() && mouseButtonReleased(MOUSE_RIGHT) && mouseInGameBounds()))
    {

        switch (titleStep)
        {
            case tsOptions:
            case tsCredits:
        		if(!buttonReleased(BUTTON_2))
					resetPrevMousePos();
		        titleStep = tsMainMenu;
                playMenuBackSound();
                break;
            case tsGameMode:
            case tsDifficulty:
				if(!buttonReleased(BUTTON_2))
					resetPrevMousePos();
				titleStep--;
                playMenuBackSound();
                break;
        }
    }
    bool mouseok = setMouseSelection();

    if (buttonReleased(BUTTON_1) || (!anyButtonReleased() && mouseButtonReleased(MOUSE_LEFT) && mouseok))
    {
		if(!buttonReleased(BUTTON_1))
			resetPrevMousePos();
        playMenuAcknowlege();
        uint8_t i;
		switch(mainMenu)
        {
            case mmOptions:
                if(titleStep != tsOptions)
                {
                    titleStep = tsOptions;
                }
                else
                {
                    switch(option)
                    {
                        case opMusic:
                            setMusicOn(!isMusicOn());
                            setMusicOnSaveState(isMusicOn());
                            break;
                        case opSound:
                            setSoundOn(!isSoundOn());
                            setSoundOnSaveState(isSoundOn());
                            break;
                         case opColorInvert:
                            setPalInverse(!getPalInverse());
                            setInverseColorSaveState(getPalInverse());
                            break;
                        case opColor:
                            i = getPalIndex();
                            if (i < getMaxPalettes())
                                i++;
                            else
                                i = 0;
                            setPalIndex(i);
                            setActiveColorSaveState(i);
                            break;
						case 4: //back
							titleStep = tsMainMenu;
                			playMenuBackSound();
							break;
                    }
                }
                break;

            case mmCredits:
                if(titleStep != tsCredits)
                {
                    titleStep = tsCredits;
                }
                else
                {
                    titleStep = tsMainMenu;
                }
                break;

            case mmHelp:
                if (titleStep < tsGameMode)
                {
                    titleStep++;
                }
                else
                {
                    switch (gameMode)
                    {
                        case gmRotate:
                            gameState = gsInitHelpRotate;
                            break;
                        case gmSlide:
                            gameState = gsInitHelpSlide;
                            break;
                        case gmRotateSlide:
                            gameState = gsInitHelpRotateSlide;
                            break;
						case 3: // back
							titleStep--;
                			playMenuBackSound();
							break;
                    }
                }
                break;
            case mmStartGame:
				//back
				if((titleStep == tsGameMode) && (gameMode == 3))
				{
					titleStep--;
	               	playMenuBackSound();
				}
				else
				{
					if (titleStep < tsDifficulty)
					{
						titleStep++;
					}
					else
					{
						//back
						if(difficulty == 6)
						{
							titleStep--;
							playMenuBackSound();
						}
						else
						{
						
							if (difficulty == diffRandom)
								selectedLevel = 1;
							else
								selectedLevel = lastUnlockedLevel(gameMode, difficulty);
							
							if (gameMode == gmRotate)
								posAdd = 0;
							else
								posAdd = 1;
							//set randomseet to systime here
							//it will be reused all the time
							//with the level generating
							//but not when going back from
							//level playing to level selector
							//when calling init level there
							randomSeedGame = getRandomSeed();
							initLevel(randomSeedGame);

							gameState = gsInitLevelSelect;
						}
					}
				}
                break;
        }
    }
}
