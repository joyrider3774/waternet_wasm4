#include <stdint.h>
#include <stdlib.h>
#include "wasm4.h"
#include "commonvars.h"
#include "helperfuncs.h"
#include "blocktiles.h"

uint32_t frames_drawn = 0;

Image* currentTiles = nullptr;

void rect(int32_t x, int32_t y, uint32_t width, uint32_t height)
{
	rect_noffset(x, y + SCREEN_Y_OFFSET, width, height);
}

void setPalette(Palette pal)
{
	PALETTE[0] = pal.Col1;
	PALETTE[1] = pal.Col2;
	PALETTE[2] = pal.Col3;
	PALETTE[3] = pal.Col4;
	*DRAW_COLORS = 0x1234;
}

bool buttonReleased(int Button)
{
	return ((PREVGAMEPAD1 & Button) && (!(*GAMEPAD1 & Button)));
}

uint32_t getRandomSeed()
{
	return (frames_drawn * rand());
}

void randomSeed(unsigned int seed)
{
	srand(seed);
}

void set_bkg_tile_xy(uint32_t x, uint32_t y, uint32_t tile)
{
	blitSub((*currentTiles).image, x * 8, y * 8 + SCREEN_Y_OFFSET , 8, 8, 0, 8 * tile, (*currentTiles).width, (*currentTiles).flags);
}

void set_bkg_data(Image* tiles)
{
	currentTiles = tiles;
}

Image* get_bkg_data()
{
	return currentTiles;
}

void set_bkg_tiles(uint32_t x, uint32_t y, Image* map)
{
  	blit((*map).image, x, y + SCREEN_Y_OFFSET,  (*map).width, (*map).height, (*map).flags);
}

void setBlockTilesAsBackground()
{
  set_bkg_data(&blocktiles_8x8);
}

void setDrawColor(ColorIndex Index1, ColorIndex Index2, ColorIndex Index3, ColorIndex Index4)
{
	*DRAW_COLORS = (Index1 << 12) + (Index2 << 8) + (Index3 << 4) + (Index4);
}

void getDrawColor(ColorIndex *Index1, ColorIndex *Index2, ColorIndex *Index3, ColorIndex *Index4)
{
	*Index1 = (*DRAW_COLORS & 0xF000) >> 12;
	*Index2 = (*DRAW_COLORS & 0x0F00) >> 8;
	*Index3 = (*DRAW_COLORS & 0x00F0) >> 4;
	*Index4 = (*DRAW_COLORS & 0x0000F) >> 0;
}

void setForeGroundColor(ColorIndex Index)
{
	ColorIndex Index1, Index2, Index3, Index4;
	getDrawColor(&Index1, &Index2, &Index3, &Index4);
	setDrawColor(Index1, Index2, Index, Index4);
}

void setBackGroundColor(ColorIndex Index)
{
	ColorIndex Index1, Index2, Index3, Index4;
	getDrawColor(&Index1, &Index2, &Index3, &Index4);
	setDrawColor(Index1, Index2, Index3, Index);
}

void setBackForeGroundColor(ColorIndex BackgroundIndex, ColorIndex ForGroundIndex)
{
	ColorIndex Index1, Index2, Index3, Index4;
	getDrawColor(&Index1, &Index2, &Index3, &Index4);
	setDrawColor(Index1, Index2, ForGroundIndex, BackgroundIndex);
}

void clear(ColorIndex Index)
{
	ColorIndex Index1, Index2, Index3, Index4;
	getDrawColor(&Index1, &Index2, &Index3, &Index4);
    setDrawColor(Index1, Index2, Index, Index);
	rect_noffset(0,0, SCREEN_SIZE, SCREEN_SIZE);
	setDrawColor(Index1, Index2, Index3, Index4);
}

void drawImage( uint32_t x , uint32_t y, Image *img)
{
	blitSub(img->image, x, y + SCREEN_Y_OFFSET, img->width, img->height, 0, img->height * (img->frame), img->width, img->flags);
}

uint8_t random(uint8_t val)
{
	return (rand() % val);
}