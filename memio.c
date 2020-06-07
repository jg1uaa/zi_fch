// code by SASANO Takayoshi, CC-BY-SA

#include "memio.h"

/* read 16bit value from memory, little-endian */
uint16_t peek_le16(void *ptr)
{
	uint8_t *p = ptr;

	return (p[1] << 8) | p[0];
}

/* read 32bit value from memory, little-endian */
uint32_t peek_le32(void *ptr)
{
	uint8_t *p = ptr;

	return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

/* write 16bit value to memory, little-endian */
void poke_le16(void *ptr, uint16_t data)
{
	uint8_t *p = ptr;

	p[0] = data;
	p[1] = data >> 8;
}

/* write 32bit value to memory, little-endian */
void poke_le32(void *ptr, uint32_t data)
{
	uint8_t *p = ptr;

	p[0] = data;
	p[1] = data >> 8;
	p[2] = data >> 16;
	p[3] = data >> 24;
}
