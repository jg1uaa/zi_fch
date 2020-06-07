// code by SASANO Takayoshi, CC-BY-SA

#include <stdint.h>

extern uint8_t Xsize_Ascii;
extern uint8_t Ysize_Ascii;

#define	ASCII_START	0x00020
#define	ASCII_END	0x0007f

#define	GLYPHPTR_ENTRY	ASCII_END
extern uint8_t *Glyph_ptr[GLYPHPTR_ENTRY];

int parse_command(uint8_t *, uint32_t);

#define	MIN_CMDLEN		6

#define	CMD_SETGLYPH		0
#define	CMD_SETASCIISIZE	1
#define	CMD_SETKANJISIZE	2
