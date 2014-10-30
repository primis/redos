#include <kernel/ports.h>
#include <kernel/vga.h>

#define VGADATA 0x3D5
#define VGAPORT 0x3D4
#define VGALOC 0xB8000

uint16_t *vgaTextBuffer;
uint16_t vgaAttribute;
uint8_t  vgaCursorX, vgaCursorY;

void vgaScroll() 
{
    uint32_t blank = ' ' | vgaAttribute;    // Blank is Space OR'd with color
    int i;
    for(i=0; i<24*80; i++) {            // Move everything up a line
        vgaTextBuffer[i] = vgaTextBuffer[i+80];
    }
    for(i=24*80; i<25*80; i++) {
        vgaTextBuffer[i] = blank;       // Replace last line with blanks.
    }
    vgaCursorY = 24;
}

static void vgaMoveCursor(uint8_t _x, uint8_t _y) 
{
    unsigned short cursorLoc = (_y*80) + _x;
    outb(VGAPORT, 14);              // Tell VGA we're moving Cursor      
    outb(VGADATA, cursorLoc>>8);    // First 8 Bits
    outb(VGAPORT, 15);              // Tell VGA we're moving Cursor (2nd half)
    outb(VGADATA, cursorLoc);       // Last 8 Bits
    vgaCursorX = _x;
    vgaCursorY = _y;
}

void vgaClear() 
{
    int i;
    for(i=0;i<24;i++) {
        vgaScroll();    // Scroll up 24 times. Making entire scren blank.
    }
    vgaMoveCursor(0,0); // Set cursor since scroll moves it to 24 instead of 0.
}

void vgaPutChar(int8_t _c) 
{
    uint16_t *loc;
    if (_c == 0x08 && vgaCursorX) { // Backspace
        vgaCursorX--;
        vgaPutChar(' ');
        vgaCursorX--;
    } else if (_c == 0x09) {        // Tabstop
        vgaCursorX = (vgaCursorX + 8) & ~(7);
    } else if (_c == '\r') {        // Carriage Return
        vgaCursorX = 0;
    } else if (_c == '\n') {        // New Line
        vgaCursorY++;
        vgaCursorX = 0;
    } else if (_c == '\f') {        // Form Feed
        vgaClear();
    } else if (_c >= ' ') {
        loc = vgaTextBuffer + vgaCursorX + (vgaCursorY * 80);
        *loc = (uint16_t)_c | vgaAttribute;
        vgaCursorX++;
    } 
    if (vgaCursorX >= 80) {
        vgaPutChar('\n');
    }
    if(vgaCursorY >=24) {
        vgaScroll();    // Scroll up a line if we hit the bottom of the screen.
    }
    vgaMoveCursor(vgaCursorX, vgaCursorY);
}
void vgaWrite(int8_t *_s)
{
    while(*_s) {
        vgaPutChar(*_s++);
    }
}
void vgaSetAttribute(int8_t _a)
{
    vgaAttribute = (_a << 8);
    if(_a == 0) {
        vgaAttribute = (0x4f << 8);
    }
}
void vgaInit() 
{
    vgaAttribute = (0x4F << 8);
    vgaTextBuffer = (uint16_t*)VGALOC;
    vgaClear();
}
