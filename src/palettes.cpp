#include "wasm4.h"
#include "palettedefines.h"
#include "palettes.h"
#include "helperfuncs.h"

uint8_t palIndex = 0;
uint8_t inverseColors = 0;
Palette pal;

void copyPalette(Palette* dst, Palette* src)
{
	(*dst).Col1 = (*src).Col1;
	(*dst).Col2 = (*src).Col2;
	(*dst).Col3 = (*src).Col3;
	(*dst).Col4 = (*src).Col4;
}

uint8_t  getMaxPalettes()
{
    return maxColorSelections;
}

void setPalIndex(uint8_t index)
{
  palIndex = index;
  //only possible to change on title
  setPaletteTitle();
}

void setPalInverse(uint8_t value)
{
    inverseColors = value;
    //only possible to change on title
    setPaletteTitle();
}

uint8_t getPalInverse()
{
    return inverseColors;
}

uint8_t getPalIndex()
{
  return palIndex;
}


void setPaletteTitle()
{

    switch(palIndex)
    {
		case 0: copyPalette(&pal, &GB_PALETTE); break;
        case 1: copyPalette(&pal, &BLACK_WHITE_PALETTE_TITLE); break;
		case 2: copyPalette(&pal, &GBC_PALETTE_TITLE); break;
		case 3: copyPalette(&pal, &RED_PALETTE_TITLE); break;
		case 4: copyPalette(&pal, &WHITE_BLUE_PALETTE_TITLE); break;
		case 5: copyPalette(&pal, &TROPICAL_PALETTE_TITLE); break;
    }
    
    if(inverseColors)
    {
        Color tmp0 = pal.Col1;
        Color tmp1 = pal.Col2;
        Color tmp2 = pal.Col3;
        Color tmp3 = pal.Col4;

        pal.Col4 = tmp0;
        pal.Col3 = tmp1;
        pal.Col2 = tmp2;
        pal.Col1 = tmp3;
    }
    
    setPalette(pal);
}

void setPaletteGame()
{
    switch(palIndex)
    {

        case 0: copyPalette(&pal, &GB_PALETTE); break;
		case 1: copyPalette(&pal, &BLACK_WHITE_PALETTE_GAME); break;
		case 2: copyPalette(&pal, &GBC_PALETTE_GAME); break;
		case 3: copyPalette(&pal, &RED_PALETTE_GAME); break;
		case 4: copyPalette(&pal, &WHITE_BLUE_PALETTE_GAME); break;
		case 5: copyPalette(&pal, &TROPICAL_PALETTE_GAME); break;
    }
    
    if(inverseColors)
    {
        Color tmp0 = pal.Col1;
        Color tmp1 = pal.Col2;
        Color tmp2 = pal.Col3;
        Color tmp3 = pal.Col4;
		
        pal.Col4 = tmp0;
        pal.Col3 = tmp1;
        pal.Col2 = tmp2;
        pal.Col1 = tmp3;
    }
    
    setPalette(pal);
}

const char* getPaletteName()
{
  switch(palIndex)
  {
        case 0: return "COLOR  GB";
        case 1: return "COLOR  BW";
        case 2: return "COLOR  GBC";
        case 3: return "COLOR  RED";
        case 4: return "COLOR  BLUE";  
        case 5: return "COLOR  FIRE";
        default: return "";
  }   
}