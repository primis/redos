#include <kernel/arch/x86/gdt.h>

gdt_entry_t   gdt[5];
gdt_ptr_t gdtPointer;

#define GDT_NUM 20
uint32_t gdtEntry[GDT_NUM] = {
/** # | Base |  Limit |  Flags |                                             **/
    0,  0,  0x00000000, 0,
    1,  0,  0xFFFFFFFF, (GDT_CODE_PL0),
    2,  0,  0xFFFFFFFF, (GDT_DATA_PL0),
    3,  0,  0xFFFFFFFF, (GDT_CODE_PL3),
    4,  0,  0xFFFFFFFF, (GDT_DATA_PL3)
};

void gdtInit()
{
    /* Step through the Entries in the above table.                           */
    int i;
    for(i=0; i<GDT_NUM; i+=4) {
        gdtSetGate(gdtEntry[i], gdtEntry[i+1], gdtEntry[i+2], gdtEntry[i+3]);
    }

    gdtPointer.base  = (uint32_t)&gdt;           /* Pointer to the gdt itself */
    gdtPointer.limit = (sizeof(gdt_entry_t)*5) - 1; /* The last descriptor   */
    gdt_flush((uint32_t)&gdtPointer);
}

void gdtSetGate(int32_t n, uint32_t base, uint32_t lim, uint32_t flag)
{
    uint16_t flags = flag & 0xFFFF;          /* Just need the bottom 16 bits  */

    /* Create the high 32 bits of the segment                                 */
    gdt[n].hi   = lim          & 0x000F0000; /* Set Limit Bits 19 - 16        */
    gdt[n].hi  |= (flags << 8) & 0x00F0FF00; /* Set type,p,dpl,g,d/b,l,avail  */
    gdt[n].hi  |= (base >> 16) & 0x000000FF; /* Set Base Bits 23 - 16         */
    gdt[n].hi  |= base         & 0xFF000000; /* Set Base Bits 31 - 24         */

    /* Create the hi 32 bits of the segment                                   */
    gdt[n].low |= base << 16;               /* Set Base  bits 15 - 0          */
    gdt[n].low |= lim & 0x0000FFFF;         /* Set Limit bits 15 - 0          */

}

