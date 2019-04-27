#include <stdlib.h>

#include "u-char.h"

#define __unlikely(x) __builtin_expect(!!(x), 0)

static const signed char len_tab[256] = {
	/*   0-127  0xxxxxxx */
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	/* 128-191  10xxxxxx (invalid first byte) */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	/* 192-223  110xxxxx */
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

	/* 224-239  1110xxxx */
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,

	/* 240-244  11110xxx (000 - 100) */
	4, 4, 4, 4, 4,

	/* 11110xxx (101 - 111) (always invalid) */
	-1, -1, -1,

	/* 11111xxx (always invalid) */
	-1, -1, -1, -1, -1, -1, -1, -1
};

/* fault-tolerant equivalent to len_tab, from glib */
static const char utf8_skip_data[256] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1
};
const char * const utf8_skip = utf8_skip_data;

static unsigned int first_byte_mask[4] = { 0x7f, 0x1f, 0x0f, 0x07 };

void u_prev_char_pos(const char *str, int *idx) {
	const unsigned char *s = (const unsigned char *)str;
	int c, len, i = *idx;
	uchar ch;

	ch = s[--i];
	len = len_tab[ch];
	if (len != 0) {
		/* start of byte sequence or invelid u-char*/
		goto one;
	}

	c = 1;
	while (1) {
		if (i == 0) {
			/* first byte of the sequence is missing */
			break;
		}

		ch = s[--i];
		len = len_tab[ch];
		c++;

		if (len == 0) {
			if (c < 4)
				continue;

			/* too long sequence */
			break;
		}
		if (len != c) {
			/* incorrect length */
			break;
		}

		/* ok */
		*idx = i;
		return;
	}
one:
	*idx = *idx - 1;
	return;
}

void u_set_char_raw(char *str, int *idx, uchar uch) {
	int i = *idx;

	if (uch <= 0x0000007fU) {
		str[i++] = uch;
		*idx = i;
	} else if (uch <= 0x000007ffU) {
		str[i + 1] = (uch & 63) | 0x80; uch >>= 6;
		str[i + 0] = uch | 0x000000c0U;
		i += 2;
		*idx = i;
	} else if (uch <= 0x0000ffffU) {
		str[i + 2] = (uch & 63) | 0x80; uch >>= 6;
		str[i + 1] = (uch & 63) | 0x80; uch >>= 6;
		str[i + 0] = uch | 0x000000e0U;
		i += 3;
		*idx = i;
	} else if (uch <= 0x0010ffffU) {
		str[i + 3] = (uch & 63) | 0x80; uch >>= 6;
		str[i + 2] = (uch & 63) | 0x80; uch >>= 6;
		str[i + 1] = (uch & 63) | 0x80; uch >>= 6;
		str[i + 0] = uch | 0x000000f0U;
		i += 4;
		*idx = i;
	} else {
		/* must be an invalid u-char*/
		str[i++] = uch & 0xff;
		*idx = i;
	}
}

int u_char_size(uchar  uch) {
	if (uch <= 0x0000007fU) {
		return 1;
	} else if (uch <= 0x000007ffU) {
		return 2;
	} else if (uch <= 0x0000ffffU) {
		return 3;
	} else if (uch <= 0x0010ffffU) {
		return 4;
	} else {
		return 1;
	}
}

uchar u_get_char(const char *str, int *idx) {
	const unsigned char *s = (const unsigned char *)str;
	int len, i, x = 0;
	uchar  ch, u;

	if (idx)
		s += *idx;
	else
		idx = &x;
	ch = s[0];

	/* ASCII optimization */
	if (ch < 128) {
		*idx += 1;
		return ch;
	}

	len = len_tab[ch];
	if (len < 1)
		goto invalid;

	u = ch & first_byte_mask[len - 1];
	for (i = 1; i < len; i++) {
		ch = s[i];
		if (len_tab[ch] != 0)
			goto invalid;
		u = (u << 6) | (ch & 0x3f);
	}
	*idx += len;
	return u;
invalid:
	*idx += 1;
	u = s[0];
	return u | U_INVALID_MASK;
}

size_t u_strlen(const char *str) {
	size_t len;
	for (len = 0; *str; len++)
		str = u_next_char(str);
	return len;
}

int u_char_width(uchar u)
{
	if (unlikely(u < 0x20))
		goto control;

	/* Combining Diacritical Marks */
	if (u >= 0x300U && u <= 0x36fU)
		goto zero;

	if (u < 0x1100U)
		goto narrow;

	/* Hangul Jamo init. consonants */
	if (u <= 0x115fU)
		goto wide;

	/* Zero-width characters */
	if (u == 0x200bU || u == 0x200cU || u == 0x200dU)
		goto zero;

	/* angle brackets */
	if (u == 0x2329U || u == 0x232aU)
		goto wide;

	if (u < 0x2e80U)
		goto narrow;
	/* CJK ... Yi */
	if (u < 0x302aU)
		goto wide;
	if (u <= 0x302fU)
		goto narrow;
	if (u == 0x303fU)
		goto narrow;
	if (u == 0x3099U)
		goto narrow;
	if (u == 0x309aU)
		goto narrow;
	/* CJK ... Yi */
	if (u <= 0xa4cfU)
		goto wide;

	/* Hangul Syllables */
	if (u >= 0xac00U && u <= 0xd7a3U)
		goto wide;

	/* CJK Compatibility Ideographs */
	if (u >= 0xf900U && u <= 0xfaffU)
		goto wide;

	/* CJK Compatibility Forms */
	if (u >= 0xfe30U && u <= 0xfe6fU)
		goto wide;

	/* Fullwidth Forms */
	if (u >= 0xff00U && u <= 0xff60U)
		goto wide;

	/* Halfwidth Forms */
	if (u >= 0xff61U && u <= 0xffdfU)
		goto narrow;

	/* Fullwidth Forms */
	if (u >= 0xffe0U && u <= 0xffe6U)
		goto wide;

	/* Halfwidth Forms */
	if (u >= 0xffe8U && u <= 0xffeeU)
		goto narrow;

	/* CJK extra stuff */
	if (u >= 0x20000U && u <= 0x2fffdU)
		goto wide;

	/* ? */
	if (u >= 0x30000U && u <= 0x3fffdU)
		goto wide;

	/* invalid bytes in unicode stream are rendered "<xx>" */
	if (u & U_INVALID_MASK)
		goto invalid;
zero:
	return 0;
narrow:
	return 1;
wide:
	return 2;
control:
	/* special case */
	if (u == 0)
		return 1;

	/* print control chars as <xx> */
invalid:
	return 4;
}

int u_str_width(const char *str)
{
	int w = 0;

	while (*str) {
		w += len_tab[(int)*str];
		str += len_tab[(int)*str];
	}
	return w;
}

int u_str_nwidth(const char *str, int len)
{
	int w = 0;

	while (len > 0) {
		if (*str == 0) { break; }
		w += len_tab[(int)*str];
		str += len_tab[(int)*str];
		len--;
	}
	return w;
}
