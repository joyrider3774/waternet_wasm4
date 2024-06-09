#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

constexpr uint8_t musGame = 1;
constexpr uint8_t musTitle = 2;
constexpr uint8_t musLevelClear = 3;
constexpr uint8_t musAllLevelsClear = 4;

void initSound();
void SelectMusic(uint8_t musicFile, uint8_t loop);
void initMusic();
void soundTimer();
void playGameAction();
void playMenuAcknowlege();
void playMenuBackSound();
void playMenuSelectSound();
void playErrorSound();
void playGameMoveSound();
void setMusicOn(uint8_t value);
void setSoundOn(uint8_t value);
void musicTimer();
void processSound();
uint8_t isMusicOn();
uint8_t isSoundOn();


#endif