#ifndef level_h
#define level_h

#include <stdint.h>
void drawLevel();
void drawLevel(uint8_t x1, uint8_t y1, uint8_t xend, uint8_t yend );
void moveBlockDown(uint8_t aTile);
void moveBlockUp(uint8_t aTile);
void moveBlockRight(uint8_t aTile);
void moveBlockLeft(uint8_t aTile);
void rotateBlock(uint8_t aTile);
void updateConnected();
void initLevel(uint32_t aRandomSeed);
uint8_t isLevelDone();

#endif