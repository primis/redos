#include <kernel/ports.h>
#include <kernel/vga.h>

#define VGADATA 0x3D5
#define VGAPORT 0x3D4
#define VGALOC 0xB8000

unsigned short *vgaTextBuffer;
unsigned short vgaAttribute;
unsigned char  vgaCursorX, vgaCursorY;

void vgaScroll() {
    unsigned int blank = ' ' | vgaAttribute;
    if(vgaCursorY >= 25) { 
        int i;
        for(i=0; i<24*80; i++) {
            vgaTextBuffer[i] = vgaTextBuffer[i+80];
        }
        for(i=24*80; i<25*80; i++) {
            vgaTextBuffer[i] = blank;
        }
        vgaCursorY = 24;
    }
}

static void vgaMoveCursor(unsigned char _x, unsigned char _y) {
    unsigned short cursorLoc = (_y*80) + _x;
    outb(VGAPORT, 14);      
    outb(VGADATA, cursorLoc>>8);
    outb(VGAPORT, 15);
    outb(VGADATA, cursorLoc);
    vgaCursorX = _x;
    vgaCursorY = _y;
}

void vgaClear() {
    unsigned int blank = ' ' | vgaAttribute;
    int i;
    for(i=1;i<25*80;i++) {
        vgaTextBuffer[i] = blank;
    }
    vgaMoveCursor(0,0);
}

void vgaPutChar(char _c) {
    unsigned short *loc;
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
        *loc = (unsigned short)_c | vgaAttribute;
        vgaCursorX++;
    } 
    if (vgaCursorX >= 80) {
        vgaPutChar('\n');
    }
    vgaScroll();
    vgaMoveCursor(vgaCursorX, vgaCursorY);
}
void vgaWrite(char *_s) {
    while(*_s) {
        vgaPutChar(*_s++);
    }
}
void vgaSetAttribute(char a) {
    vgaAttribute = (a << 8);
    if(a == 0) {
        vgaAttribute = (0x4f << 8);
    }
}
void vgaInit() {
    vgaAttribute = (0x4F << 8);
    vgaTextBuffer = (unsigned short*)VGALOC;
    vgaClear();
}
