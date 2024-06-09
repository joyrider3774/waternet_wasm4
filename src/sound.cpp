#include <stdint.h>
#include <string.h>
#include "wasm4.h"

#include "commonvars.h"
#include "sound.h"

//I (joyrider3774) created the music in this tool : https://onlinesequencer.net
//music uses one channel  only using simple notes
//sound uses one channel  only

//MUSIC PLAYING CONCEPT based on
//      Sheep it up! - A tiny GB/GBC game for the bitbitjam4 game jam
//      by Dr. Ludos (http://www.ludoscience.com)

//frequency table, the same one as on arduino tones devices
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

constexpr uint8_t sfxSustain = 100 * 5 / frameRate;
uint8_t music_note, music_tempo, music_loop, prev_music, music_sustain_note, music_on, sound_on, sfx_sustain;
uint8_t sfx_setting_note, sfx_sustain_zero_set, music_sustain_zero_set, selecting_music;
uint8_t musicArray[255];
unsigned long music_length;

//Here is kind of "quick'n dirty" custom music player made using solely using channel of the GB
//The main parameters of the channel are set manually, then this table defines "notes", as in "frequencies" 
const uint16_t music_notes_gb[11] ={
    0, //for silence
    NOTE_C4, //C  4
    NOTE_CS4, //C# 4
    NOTE_D4, //D  4
    NOTE_DS4, //D# 4
    NOTE_E4, //E  4
    NOTE_DS6, //D# 6
    NOTE_D6, //D 6
    NOTE_E6, //E 6
    NOTE_F6, //F 6
    NOTE_E4, //E 4
};

//helper defines
#define P   0
#define C4  1
#define C4S 2 
#define D4  3
#define D4S 4
#define E4  5
#define D6S 6
#define D6  7
#define E6  8
#define F6  9
#define F4  10
#define PAUSE 15
#define PAUSE2 6
#define PAUSE3 14
#define PAUSE4 13

//Here is the "partition" table. 
//https://onlinesequencer.net/2498607
const uint8_t music_levelsCleared[96] ={
    D6,PAUSE4,
    D6S,PAUSE4,
    D6,PAUSE4,
    P,PAUSE4,
    D6,PAUSE4,
    E6,PAUSE4,
    F6,PAUSE4,
    E6,PAUSE4,
    E6,PAUSE4,
    E6,PAUSE4,
    D6,PAUSE4,
    P,PAUSE4,
    D6S,PAUSE4,
    E6,PAUSE4,
    D6S,PAUSE4,
    P,PAUSE4,
    E6,PAUSE4,
    F6,PAUSE4,
    E6,PAUSE4,
    P,PAUSE4,
    D6,PAUSE4,
    D6S,PAUSE4,
    D6,PAUSE4,
    E6,PAUSE4,
    E6,PAUSE4,
    D6S,PAUSE4,
    D6S,PAUSE4,
    D6,PAUSE4,
    D6,PAUSE4,
    D6S,PAUSE4,
    E6,PAUSE4,
    D6S,PAUSE4,
    P,PAUSE4,
    E6,PAUSE4,
    D6S,PAUSE4,
    E6,PAUSE4,
    D6S,PAUSE4,
    D6S,PAUSE4,
    E6,PAUSE4,
    P,PAUSE4,
    E6,PAUSE4,
    F6,PAUSE4,
    D6S,PAUSE4,
    E6,PAUSE4,
    P,PAUSE4,
    F6,PAUSE4,
    E6,PAUSE4,
    F6,PAUSE4
};


//https://onlinesequencer.net/2484974
const uint8_t music_won[16] ={
  D6S, PAUSE2,
  D6,  PAUSE2,
  D6S, PAUSE2,
  E6 , PAUSE2,
  D6S, PAUSE2,
  E6 , PAUSE2,
  F6 , PAUSE2 << 2,
  P, PAUSE2  
};

//https://onlinesequencer.net/2485064
const uint8_t music_game[198] ={ 
    P, PAUSE3,
    C4, PAUSE3,
    C4S, PAUSE3,
    P, PAUSE3,
    C4, PAUSE3,
    C4S, PAUSE3,
    C4S, PAUSE3,
    D4, PAUSE3,
    P, PAUSE3,
    D4S, PAUSE3,
    D4, PAUSE3,
    P, PAUSE3,
    D4S, PAUSE3,
    E4, PAUSE3,
    P, PAUSE3,
    D4S, PAUSE3,
    E4, PAUSE3,
    E4, PAUSE3,
    F4, PAUSE3,
    P, PAUSE3,

    C4, PAUSE3,
    C4S, PAUSE3,
    P, PAUSE3,
    C4, PAUSE3,
    C4S, PAUSE3,
    C4S, PAUSE3,
    D4, PAUSE3,
    P, PAUSE3,
    D4S, PAUSE3,
    D4, PAUSE3,
    P, PAUSE3,
    D4S, PAUSE3,
    E4, PAUSE3,
    P, PAUSE3,
    D4S, PAUSE3,
    E4, PAUSE3,
    E4, PAUSE3,
    F4, PAUSE3,
    P, PAUSE3,

    D4, PAUSE3,
    C4, PAUSE3,
    E4, PAUSE3,
    D4, PAUSE3,
    P,  PAUSE3,
    E4, PAUSE3,
    P,  PAUSE3,
    E4, PAUSE3,
    D4, PAUSE3,
    P,  PAUSE3,
    D4S, PAUSE3,
    D4S, PAUSE3,
    E4, PAUSE3,
    P, PAUSE3,
    E4, PAUSE3,
    D4S, PAUSE3,
    D4, PAUSE3,
    C4, PAUSE3,
    D4S, PAUSE3,
    E4,PAUSE3,
    D4,PAUSE3,
    P,PAUSE3,
    D4S,PAUSE3,
    D4,PAUSE3,
    C4,PAUSE3,
    P,PAUSE3,
    D4,PAUSE3,
    C4,PAUSE3,
    E4,PAUSE3,
    D4,PAUSE3,
    P,PAUSE3,
    E4,PAUSE3,
    P,PAUSE3,
    E4,PAUSE3,
    D4,PAUSE3,
    P,PAUSE3,
    D4S,PAUSE3,
    D4S,PAUSE3,
    E4,PAUSE3,
    P,PAUSE3,
    E4,PAUSE3,
    D4,PAUSE3,
    C4,PAUSE3,
    C4S,PAUSE3,
    D4S,PAUSE3,
    F4,PAUSE3,
    E4,PAUSE3,
    D4,PAUSE3,
    D4S,PAUSE3,
    D4S,PAUSE3,
    P, PAUSE3,
    E4,PAUSE3,
    D4,PAUSE3,
    D4,PAUSE3,
    P, PAUSE3,
    D4S,PAUSE3,
    C4S,PAUSE3,
    C4S,PAUSE3,
    P, PAUSE3,
    D4,PAUSE3
};

//https://onlinesequencer.net/2484977
const uint8_t music_intro[98] = {
    C4,  PAUSE,
    C4,  PAUSE * 2,
    D4,  PAUSE,
    D4S, PAUSE,
    C4,  PAUSE,
    P,   PAUSE * 8,
    
    C4,  PAUSE,
    C4,  PAUSE * 2,
    D4,  PAUSE,
    D4S, PAUSE,
    C4,  PAUSE,
    D4,  PAUSE,
    C4,  PAUSE,
    C4S, PAUSE,
    P,   PAUSE * 4,

    C4,  PAUSE,
    C4,  PAUSE * 2,
    D4,  PAUSE,
    D4S, PAUSE,
    C4,  PAUSE,
    P,   PAUSE * 8,
    
    C4,  PAUSE,
    C4,  PAUSE * 2,
    D4,  PAUSE,
    D4S, PAUSE,
    C4,  PAUSE,
    D4,  PAUSE,
    C4,  PAUSE,
    C4S, PAUSE,
    P,   PAUSE * 4,

    D4,  PAUSE,
    D4,  PAUSE, 
    C4S, PAUSE,
    C4,  PAUSE,
    D4S, PAUSE,
    C4S, PAUSE,
    D4,  PAUSE,
    D4S, PAUSE,
    C4S, PAUSE,
    D4S, PAUSE,
    D4,  PAUSE,
    D4,  PAUSE,
    D4,  PAUSE,
    E4,  PAUSE,
    C4,  PAUSE,
    C4S, PAUSE,
    E4,  PAUSE,
    D4,  PAUSE * 3,
    P,   PAUSE * 4
};


void setMusicOn(uint8_t value)
{
    music_on = value;
}

void processSound()
{
    if (sfx_setting_note || selecting_music)
    {
        return;
    }
    
    musicTimer();
    if(sfx_sustain == 0)
    {
        if (!sfx_sustain_zero_set)
        {
            do_tone(0, sfx_sustain, 100, TONE_PULSE2 | TONE_NOTE_MODE);
            sfx_sustain_zero_set = 1;
        }
    }
    else
    {
        sfx_sustain--;
    }
}


void SelectMusic(uint8_t musicFile, uint8_t loop)
{
    if (prev_music != musicFile)
    {
        selecting_music = 1;
		prev_music = musicFile;
		memset(musicArray, 0, sizeof(musicArray));
		switch (musicFile) 
		{
			case musTitle:
				memcpy(musicArray, music_intro, sizeof(music_intro));
				music_length = sizeof(music_intro);
				break;
			case musLevelClear:
				memcpy(musicArray, music_won, sizeof(music_won));
				music_length = sizeof(music_won);
				break;
			case musAllLevelsClear:
				memcpy(musicArray, music_levelsCleared, sizeof(music_levelsCleared));
				music_length = sizeof(music_levelsCleared);
				break;
			case musGame:
				memcpy(musicArray, music_game, sizeof(music_game));
				music_length = sizeof(music_game);
				break;
		}
		music_note = 0;
		music_tempo = 0;
		music_loop = loop;
		music_sustain_zero_set = 1;
		music_sustain_note = 0;
        selecting_music = 0;
    }
}

void playNote()
{    
    if(music_note < music_length)
    {
        do_tone(music_notes_gb[musicArray[music_note]], 50, 10, TONE_PULSE2);
        music_sustain_note = 0;

        //Set the new delay to wait
        music_tempo = musicArray[music_note + 1];

        //Skip to the next note
        music_note += 2;
               
        if (music_note > music_length - 1)
        {
            if(music_loop)
            {
                music_note = 0;
            }
            else
            {
                #ifdef SEGA
                playSegaMusTone(0);
                #endif
            }
        }
    }
}


void musicTimer()
{
    //for nintendo systems as sega one checks it earlier
    if (selecting_music)
    {
        return;
    }

    //Play some music
    if (music_tempo == 0)
    {
        if(music_on)
        {
            playNote();
        }
    }
    //Else wait for the next note to play
    else 
    {
        music_tempo--;
        if(music_sustain_note == 0)
        {
            if (!music_sustain_zero_set)
            {
                music_sustain_zero_set = 1;
            }
        }
        else
        {
            music_sustain_note--;
        }
    }
}

void initMusic()
{
	music_sustain_note = 0;
	prev_music = 0;
	music_note = 0;
	music_length = 0;
	music_tempo = 0;
	music_loop = 0;
	//set to 1 so nothing plays until a music was selected
	selecting_music = 1;
	music_sustain_zero_set = 1;
}

void setSoundOn(uint8_t value)
{
    sound_on = value;
}

uint8_t isMusicOn()
{
    return music_on;
}

uint8_t isSoundOn()
{
    return sound_on;
}

void initSound()
{
    sound_on = 0;
}

void playSound(uint16_t tone)
{
    if(!sound_on)
	{
        return;
	}
    do_tone(tone, sfxSustain, 100, TONE_PULSE1);
}


void playGameMoveSound()
{
    playSound(750);
}

void playErrorSound()
{
    playSound(210);
}

void playMenuSelectSound()
{
    playSound(1250);
}

void playMenuBackSound()
{
   playSound(1000);
}

void playMenuAcknowlege()
{
    playSound(900);
}

void playGameAction()
{
    playSound(600);
}
