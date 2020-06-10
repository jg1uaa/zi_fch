// code by SASANO Takayoshi, CC-BY-SA

#include <stdint.h>

extern uint8_t Xsize_Ascii;
extern uint8_t Ysize_Ascii;

#if !defined(CODETYPE)
#define	CODETYPE	CODETYPE_ASCII
#endif

#define	ASCII_START	0x00020

#if CODETYPE == CODETYPE_ASCII
#define	ASCII_END	0x0007f
#else
#define	ASCII_END	0x00100
#endif

#define	GLYPHPTR_ENTRY	ASCII_END
extern uint8_t *Glyph_ptr[GLYPHPTR_ENTRY];

int parse_command(uint8_t *, uint32_t);

#define	MIN_CMDLEN		6

#define	CMD_SETGLYPH		0
#define	CMD_SETASCIISIZE	1
#define	CMD_SETKANJISIZE	2
