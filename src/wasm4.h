//
// WASM-4: https://wasm4.org/docs

#pragma once

#include <stdint.h>

#define WASM_EXPORT(name) __attribute__((export_name(name)))
#define WASM_IMPORT(name) __attribute__((import_name(name)))

WASM_EXPORT("start") void start ();
WASM_EXPORT("update") void update ();

// ┌───────────────────────────────────────────────────────────────────────────┐
// │                                                                           │
// │ Memory Addresses                                                          │
// │                                                                           │
// └───────────────────────────────────────────────────────────────────────────┘
#define PALETTE ((uint32_t*)0x04)
#define DRAW_COLORS ((uint16_t*)0x14)
#define GAMEPAD1 ((const uint8_t*)0x16)
#define GAMEPAD2 ((const uint8_t*)0x17)
#define GAMEPAD3 ((const uint8_t*)0x18)
#define GAMEPAD4 ((const uint8_t*)0x19)
#define MOUSE_X ((const int16_t*)0x1a)
#define MOUSE_Y ((const int16_t*)0x1c)
#define MOUSE_BUTTONS ((const uint8_t*)0x1e)
#define FRAMEBUFFER ((uint8_t*)0xa0)

#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_ENTER 4
#define BUTTON_UNUSED 8
#define BUTTON_LEFT 16
#define BUTTON_RIGHT 32
#define BUTTON_UP 64
#define BUTTON_DOWN 128

/** Copies pixels to the framebuffer. */
WASM_IMPORT("blit")
void blit (const uint8_t* data, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t flags);

/** Copies a subregion within a larger sprite atlas to the framebuffer. */
WASM_IMPORT("blitSub")
void blitSub (const uint8_t* data, int32_t x, int32_t y, uint32_t width, uint32_t height,
    uint32_t srcX, uint32_t srcY, uint32_t stride, uint32_t flags);

#define BLIT_2BPP 1
#define BLIT_1BPP 0
#define BLIT_FLIP_X 2
#define BLIT_FLIP_Y 4
#define BLIT_ROTATE 8

/** Draws a rectangle. */
WASM_IMPORT("rect")
void rect_noffset (int32_t x, int32_t y, uint32_t width, uint32_t height);

// ┌───────────────────────────────────────────────────────────────────────────┐
// │                                                                           │
// │ Sound Functions                                                           │
// │                                                                           │
// └───────────────────────────────────────────────────────────────────────────┘

/** Plays a sound tone. */
WASM_IMPORT("tone")
void do_tone (uint32_t frequency, uint32_t duration, uint32_t volume, uint32_t flags);

#define TONE_PULSE1 0
#define TONE_PULSE2 1
#define TONE_TRIANGLE 2
#define TONE_NOISE 3
#define TONE_MODE1 0
#define TONE_MODE2 4
#define TONE_MODE3 8
#define TONE_MODE4 12
#define TONE_PAN_LEFT 16
#define TONE_PAN_RIGHT 32
#define TONE_NOTE_MODE 64

// ┌───────────────────────────────────────────────────────────────────────────┐
// │                                                                           │
// │ Storage Functions                                                         │
// │                                                                           │
// └───────────────────────────────────────────────────────────────────────────┘

/** Reads up to `size` bytes from persistent storage into the pointer `destPtr`. */
WASM_IMPORT("diskr")
uint32_t diskr (void* dest, uint32_t size);

/** Writes up to `size` bytes from the pointer `srcPtr` into persistent storage. */
WASM_IMPORT("diskw")
uint32_t diskw (const void* src, uint32_t size);

/** Prints a message to the debug console. */
WASM_IMPORT("trace") void trace (const char* str);

/** Prints a message to the debug console. */
__attribute__((__format__ (__printf__, 1, 2)))
WASM_IMPORT("tracef") void tracef (const char* fmt, ...);

#define SCREEN_SIZE 160

//added these for convienence
#define Color uint32_t
#define ColorIndex uint8_t

typedef struct Image Image;
struct Image
{
  uint32_t width;
  uint32_t height;
  uint32_t flags;
  uint32_t frame;
  const uint8_t image[];
} ;
