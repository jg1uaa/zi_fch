// code by SASANO Takayoshi, CC-BY-SA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "memio.h"
#include "parse.h"
#include "zi_defs.h"

#include "convert.h"

static int create_zi_header(struct zi_header *h, char *fontname, int xsize, int ysize)
{
	if (xsize == 0 || ysize == 0)
		return -1;

	memset(h, 0, sizeof(*h));
	poke_le32(&h->identifier, ZI_MAGIC);
	poke_le16(&h->codepage, CODETYPE);
	h->xsize = xsize;
	h->ysize = ysize;
	h->start_low = ASCII_START;
	h->end_low = ASCII_END - 1;
	h->characters = ASCII_END - ASCII_START;
	h->format = ZI_FORMAT;
	h->fontname_length1 = h->fontname_length2 = strlen(fontname);
	h->total_length = h->fontname_length1 +
		h->characters * ((xsize * ysize) / 8);

	return 0;
}

/* packing */
static void pack(uint8_t *out, uint8_t *in, int xsize, int ysize)
{
	int i;
	uint64_t t;

	switch (xsize) {
	case 12:
		for (i = 0; i < ysize / 2; i++) {
			t  = (in[0] << 24) | ((in[1] & 0xf0) << 16);
			t |= (in[2] << 12) | ((in[3] & 0xf0) << 4);

			out[0] = t >> 24;
			out[1] = t >> 16;
			out[2] = t >> 8;

			in += 4;
			out += 3;
		}
	default:
		memcpy(out, in, (xsize * ysize) / 8);
		break;
	}
}

/* convert (ASCII) */
void convert_ascii(char *filename, char *fontname)
{
	int i, datasize;
	uint8_t *tmp;
	FILE *fp;
	struct zi_header h;

	/* create header */
	if (create_zi_header(&h, fontname, Xsize_Ascii, Ysize_Ascii) < 0)
		return;

	datasize = (Xsize_Ascii * Ysize_Ascii) / 8;

	/* create temporary buffer */
	tmp = alloca(datasize);

	/* save result */
	fp = fopen(filename, "w");
	if (fp == NULL) {
		fprintf(stdout, "convert_ascii: file open error (%s)\n",
			filename);
		goto fin0;
	}

	if (fwrite(&h, sizeof(h), 1, fp) < 1) {
		fprintf(stdout, "convert_ascii: file write error (header)\n");
		goto fin1;
	}

	if (fwrite(fontname, strlen(fontname), 1, fp) < 1) {
		fprintf(stdout, "convert_ascii: file write error (fontname)\n");
		goto fin1;
	}

	for (i = ASCII_START; i < ASCII_END; i++) {
		if (Glyph_ptr[i] == NULL) {
			memset(tmp, 0, datasize);
		} else {
			pack(tmp, Glyph_ptr[i], Xsize_Ascii, Ysize_Ascii);
		}

		if (fwrite(tmp, datasize, 1, fp) < 1) {
			fprintf(stdout, "convert_ascii: "
				"file write error (data)\n");
			goto fin1;
		}
	}

fin1:
	fclose(fp);
fin0:
	return;
}
