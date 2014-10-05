#include <stdio.h>
#include <kernel/kb.h>

#define true 1
#define false 0

void keyboardHandler(unsigned int a, ...);

unsigned char kbScanCodes[512] = 
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[' , ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    /* Shifted */
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(' , ')', '_' , '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{' , '}', '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\'', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, '7', '8', '9', 0, '4', '5', '6', 0,
    '1', '2', '3', '0', 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    /* Caps, Normal */
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{' , '}', '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\'', '~', 0,
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    /* Caps, Shifted */
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(' , ')', '_' , '+', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[' , ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

unsigned char shift = false;
unsigned char ctrl = false;
unsigned char alt = false;
unsigned char caps = false;
unsigned char num = false;
unsigned char keyBuffer[257];
unsigned char keyBuffEnd = 0;

unsigned char asciiCode;
unsigned char leds = 0;


void FlushBuffer()    /* Hardware Buffer */
{
    unsigned temp;
    do
    {
        temp = inb(0x64);
        if((temp & 0x01) != 0) 
        {
            (void)inb(0x60);
            continue;
        }
    } while((temp & 0x02) != 0);
}


int kb_special(unsigned char key) {
    static int specKeyUp = true;    //Is a key already been or being presses
    switch(key) 
    {
        case 0x36: //R-Shift down
        case 0x2A: //L-Shift down
            shift = true;
            break;
        case 0xB6: //R-Shift up
        case 0xAA: //L-Shift up
            shift = false;
            break;
        case 0x1D: //Control down
            ctrl = true;
            break;
        case 0x9D: //Control up
            ctrl = false;
            break;
        case 0x38: //Alt down
            alt = true;
            break;
        case 0xB8: //Alt up
            alt = false;
            break;
        case 0x3A: //Caps down
            if(specKeyUp == true) 
            {
                caps = !caps;
                UpdateLeds(CapsLock);
                specKeyUp = false;
            }
            break;
        case 0x45: //Num down
            if(specKeyUp == true)
            {
                num = !num;
                UpdateLeds(NumLock);
                specKeyUp = false;
            }
            break;
        case 0x46: //Scroll down
            if(specKeyUp == true)
            {
                num = !num;
                UpdateLeds(ScrollLock);
                specKeyUp = false;
            }
            break;
        case 0xBA: //Caps Up
        case 0xC5: //Num Up
        case 0xC6: //Scroll Up
            specKeyUp = true;
            break;
        case 0xE0:
            break;
        default:
            return(0);
    }
    return (1);
}

void keyboardHandler(unsigned int a, ...) {
    unsigned char scanCode;
    scanCode = inb(0x60);
    unsigned char asciiCode;

    if(!(kb_special(scanCode) | (scanCode >= 0x80))) {
        if(shift) {
            if(!caps) {
                asciiCode = kbScanCodes[scanCode + 128];
            } else {
                asciiCode = kbScanCodes[scanCode + 348];
            }
        } else {
            if(!caps) {
                asciiCode = kbScanCodes[scanCode];
            } else {
                asciiCode = kbScanCodes[scanCode + 256];
            }
        }
        if(keyBuffEnd != 256) {
            keyBuffEnd++;
        }
        keyBuffer[keyBuffEnd] = asciiCode;
    }
}

char getchar_int()
{
    int i = 0;
    while(keyBuffEnd == 0);
    
    asm("cli");
    for(; i < keyBuffEnd; i++) {
        keyBuffer[i] = keyBuffer[i+1];
    }
    keyBuffEnd--;
    asm("sti");
    putchar(keyBuffer[0]);
    return keyBuffer[0];   
}

void UpdateLeds(unsigned char led) {
    if(led == 0) {
        leds = 0;
    } else {
        if(leds == (leds|led)) {
            leds = leds^led;
        } else {
            leds = leds | led;
        }
    }
    while((inb(0x64) &2) !=0);
    outb(0x60, 0xED);
    while((inb(0x64) &2) !=0);
    outb(0x60, leds);
}

void waitKey() {
    FlushBuffer();
    while (getchar_int() == 0);
}

void initKeyboard() {
    FlushBuffer();
    asm("cli");
    interruptHandlerRegister(0x21,&keyboardHandler);
    clearIRQMask(1);
    asm("sti");
}