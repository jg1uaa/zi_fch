// code by SASANO Takayoshi, CC-BY-SA
// ZI version 3 format by https://github.com/hagronnestad/nextion-font-editor/blob/master/Docs/Nextion%20Font%20Format%20Specification%20ZI%20version%203.md

#include <stdint.h>

#define ZI_MAGIC	0x0a00ff04
#define CODETYPE_ASCII	0x0001
#define	ZI_FORMAT	0x03

struct zi_header {
	uint32_t	identifier;
	uint16_t	codepage;
	uint8_t		xsize;
	uint8_t		ysize;
	uint8_t		start_hi;
	uint8_t		end_hi;
	uint8_t		start_low;
	uint8_t		end_low;
	uint32_t	characters;
	uint8_t		format;
	uint8_t		fontname_length1;
	uint8_t		fontname_length2;
	uint8_t		reserved1;
	uint32_t	total_length;
	uint32_t	reserved2;
} __attribute__((packed));
