#ifndef SAVESTATE_H
#define SAVESTATE_H

#include <stdint.h>

void initSaveState();
uint8_t lastUnlockedLevel(uint8_t mode, uint8_t diff);
uint8_t levelUnlocked(uint8_t mode, uint8_t diff, uint8_t level);
uint8_t isMusicOnSaveState();
uint8_t isSoundOnSaveState();
uint8_t getActiveColorSaveState();
uint8_t getInverseColorSaveState();
void unlockLevel(uint8_t mode, uint8_t diff, uint8_t level);
void setMusicOnSaveState(uint8_t value);
void setSoundOnSaveState(uint8_t value);
void setActiveColorSaveState(uint8_t value);
void setInverseColorSaveState(uint8_t value);
#endif