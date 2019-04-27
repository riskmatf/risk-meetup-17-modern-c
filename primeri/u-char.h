#ifndef __U_CHAR_H__
#define __U_CHAR_H__

typedef unsigned int uchar;

enum Keys {
	U_BACKSPACE = 127
};

#define U_INVALID_MASK 0x10000000U

void u_prev_char_pos(const char *str, int *idx);
void u_set_char_raw(char *str, int *idx, uchar  uch);

/*
 * Returns width of @uch (normally 1 or 2, 4 for invalid chars (<xx>))
 */
int u_char_width(uchar uch);

int u_char_size(uchar uch);

uchar u_get_char(const char *str, int *idx);

extern const char * const utf8_skip;

static inline char *u_next_char(const char *str)
{
	return (char *) (str + utf8_skip[*((const unsigned char *) str)]);
}

size_t u_strlen(const char *str);

/*
 * @str  null-terminated UTF-8 string
 *
 * Retuns width of @str.
 */
int u_str_width(const char *str);

/*
 * @str  null-terminated UTF-8 string
 * @len  number of characters to measure
 *
 * Retuns width of the first @len characters in @str.
 */
int u_str_nwidth(const char *str, int len);

#endif