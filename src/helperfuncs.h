#ifndef helperfuncs_h
#define helperfuncs_h

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wasm4.h"

extern uint32_t frames_drawn;

#define Color uint32_t
#define ColorIndex uint8_t
#define Image uint8_t

typedef struct Palette Palette;
struct Palette 
{
	Color Col1;
	Color Col2;
	Color Col3;
	Color Col4;
};

void setImageFrame(Image* data, uint8_t frame);
uint8_t* imageImage(Image* data);
uint8_t imageFrame(Image* data);
uint8_t imageType(Image* data);
uint16_t imageHeight(Image* data);
uint16_t imageWidth(Image* data);

void rect_offset(int32_t x, int32_t y, uint32_t width, uint32_t height);
void setPalette(Palette pal);
uint32_t getRandomSeed();
void randomSeed(unsigned int seed);
void clear(ColorIndex Index);
void setBackForeGroundColor(ColorIndex BackgroundIndex, ColorIndex ForGroundIndex);
void setBackGroundColor(ColorIndex Index);
void getDrawColor(ColorIndex *Index1, ColorIndex *Index2, ColorIndex *Index3, ColorIndex *Index4);
void setDrawColor(ColorIndex Index1, ColorIndex Index2, ColorIndex Index3, ColorIndex Index4);
void setBlockTilesAsBackground();
void set_bkg_tile_xy(uint32_t x, uint32_t y, uint32_t tile);
void set_bkg_data(Image* tiles);
Image* get_bkg_data();
void set_bkg_tiles(uint32_t x, uint32_t y, Image *map);
void drawImage( uint32_t x , uint32_t y, Image* img);
uint8_t random_u8(uint8_t val);
bool buttonReleased(int Button);
void updatePrevInputs();
void resetPrevMousePos();
bool mouseMoved();
bool mouseMovedAtleastOnce();
bool mouseButtonReleased(int Button);
bool mouseInGameBounds();
bool anyButtonReleased();
#endif