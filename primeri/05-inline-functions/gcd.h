#ifndef __GCD_H__
#define __GCD_H__

// Ukoliko je EXTERN definisan, zelimo da uklonimo static iz definicije f-je.
#ifdef EXTERN
#define static
#endif

static inline unsigned gcd(unsigned x, unsigned y)
{
	if (x < y) { x ^= y ^= x ^= y; }
	if (x % y == 0) { return y; }
	unsigned tmp;
	while ((tmp = x % y) != 0) {
		x = y;
		y = tmp;
	}
	return y;
}

/* Definisanje makro-a sa imenom kljucnih reci je **losa** praksa, ovde smo to
   uradili samo zato sto je to u ovom primeru zgodno. Ipak, red je da uklonimo
   tu definiciju nakon upotrebe. */
#undef static

#endif