#include <stdint.h>
#include "wasm4.h"

#include "commonvars.h"
#include "printfuncs.h"
#include "helperfuncs.h"

// function provided by @Pharap
// If the array is not big enough,
// this will cause an error message at compile time.
template<size_t size>
size_t formatInteger(char (&array)[size], uint16_t integer )
{
    constexpr size_t maxDigits = 10; 
    constexpr size_t maxCharacters = (maxDigits + 1);

    // Check the array size at compile time
    static_assert(size >= maxCharacters, "array is too small");

    constexpr size_t lastIndex = (maxCharacters - 1);

    array[lastIndex] = '\0';

    if(integer == 0)
    {
        array[lastIndex - 1] = '0';
        return 1;
    }

    size_t digits = 0;

    do
    {
        uint8_t digit = integer % 10;
        integer /= 10;

        ++digits;

        array[lastIndex - digits] = ('0' + digit);
    }
    while(integer > 0);

    return digits;
}

//print a number on levelselect or game screen
void printNumber(uint8_t ax, uint8_t ay, uint16_t aNumber, size_t maxDigits)
{
    constexpr size_t buffSize = 10; 
    char number[buffSize + 1];
    size_t digits = formatInteger(number, aNumber);
    size_t maxFor = digits;
    if (digits > maxDigits)
        maxFor = maxDigits;
    for (size_t c=0; c < maxFor; c++)
    {
        if (number[buffSize - digits + c] == '\0')
            return;
        
        set_bkg_tile_xy(uint32_t(ax + (maxDigits-digits) + c), ay, (uint32_t)(number[buffSize - digits + c] + 32));
    }
}


//print a message on the title screen on ax,ay, the tileset from titlescreen contains an alphabet
void printMessage(uint8_t ax, uint8_t ay, const char* amsg)
{
    // based on input from @Pharap
    uint32_t index = 0;
    int p = 0;
    while (1)
    {
        char fChar = amsg[p++];
        uint32_t tile = 61U;
        switch (fChar)
        { 
            case '\0':
                return;

            case '[':
                tile = 70U;
                break;

            case ']':
                tile = 64U;
                break;

            case '<':
                tile = 73U;
                break;

            case '>':
                tile = 67U;
                break;

            case '+':
                tile = 63U;
                break;

            case '*':
                tile = 62U;
                break;

            case '|':
                tile = 69U;
                break;

            case '#':
                tile = 65U;
                break;

            case ':':
                tile = 116U;
                break;

            case 'a':
                tile = 119U;
                break;

            case 'b':
                tile = 117U;
                break;
            
            default:
                if ((fChar >= 'A') &&  (fChar <= 'Z'))
                    tile = ((uint32_t)fChar + 25u);
                
                if ((fChar >= '0') && (fChar <= '9'))
                    tile = ((uint32_t)fChar + 32u);
                break;
        }
        set_bkg_tile_xy(ax + index, ay, tile);
        ++index;
    }
}

//print a message on the CongratsScreen on ax,ay, the tileset from Congrats Screen contains an alphabet in another font
void printCongratsScreen(uint8_t ax, uint8_t ay, const char* amsg)
{
    // based on input form @Pharap
    int p = 0;
    uint32_t index = 0;

    while (1)
    {
        char fChar = amsg[p++];
        uint32_t tile = 26U;
        switch (fChar) 
        {
            case '\0':
               return;

            default:
                if ((fChar >= 'A') &&  (fChar <= 'Z'))
                    tile =  uint32_t(fChar - 'A');
                break;
        }
        set_bkg_tile_xy(ax + index, ay, tile);
        ++index;
    }
}