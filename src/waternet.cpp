
#include <stdint.h>
#include <cinttypes>
#include "wasm4.h"
#include "palettes.h"
#include "commonvars.h"
#include "intro.h"
#include "levelselect.h"
#include "helpscreens.h"
#include "sound.h"
#include "cursor.h"
#include "printfuncs.h"
#include "game.h"
#include "titlescreen.h"
#include "levelscleared.h"
#include "savestate.h"
#include "level.h"
#include "helperfuncs.h"

//intialisation of game & global variables
void start()
{
    PREVGAMEPAD1 = *GAMEPAD1;
	option = 0;
    difficulty = diffNormal;
    selectedLevel = 1;
    mainMenu = mmStartGame;
    gameState = gsInitIntro;
    titleStep = tsMainMenu;
    gameMode = gmRotate;

    //has to be called first because initsound and initmusic read savestate sound to set intial flags
    initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    setPalInverse(getInverseColorSaveState());
    setPalIndex(getActiveColorSaveState());
 }

void update()
{
	processSound();
    //gamestate handling
    switch (gameState)
    {
        case gsInitTitle:
        case gsTitle:
            titleScreen();
            break;
        case gsInitLevelSelect:
        case gsLevelSelect:
            levelSelect();
            break;
        case gsInitGame:
        case gsGame:
            game();
            break;
        case gsInitLevelsCleared:
        case gsLevelsCleared:
            levelsCleared();
            break;
        case gsInitHelpSlide:
        case gsHelpSlide:
            helpSlide();
            break;
        case gsInitHelpSlide2:
        case gsHelpSlide2:
            helpSlide2();
            break;
        case gsHelpRotateSlide:
        case gsInitHelpRotateSlide:
            helpRotateSlide();
            break;
        case gsInitHelpRotateSlide2:
        case gsHelpRotateSlide2:
            helpRotateSlide2();
            break;
        case gsInitHelpRotate:
        case gsHelpRotate:
            helpRotate();
            break;
        case gsInitHelpRotate2:
        case gsHelpRotate2:
            helpRotate2();
            break;
        case gsInitIntro:
        case gsIntro:
            intro();
            break;
    } 
	PREVGAMEPAD1 = *GAMEPAD1;
	frames_drawn++;
 }