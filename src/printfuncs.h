#ifndef PRINTFUNCS_H
#define PRINTFUNCS_H

#include <stdint.h>
#include <stddef.h>

void printDebugCpuRamLoad();
void printDebug(uint8_t ax, uint8_t ay, const char* amsg);
void printNumber(uint8_t ax, uint8_t ay, uint16_t aNumber, size_t maxDigits);
void printMessage(uint8_t ax, uint8_t ay, const char* amsg);
void printCongratsScreen(uint8_t ax, uint8_t ay, const char* amsg);
void printMessageWithSelectedColorMousePos(uint8_t ax, uint8_t ay, const char* amsg);
void printMessageWithSelectedColor(uint8_t ax, uint8_t ay, const char* amsg, uint8_t selectedy);

#endif