#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Komentari u stilu C++-a mogu da se koriste samo od C99 standarda i kasnije.
// Alternativno, GCC omogucava njihovu upotrebu u C89 modu sa GNU prosirenjima.
// (Kompajlirati sa -std=gnu89)

int main() {
	/* Za _Bool tip vaze ocekivana pravila konverzije: ne-nula vrednosti se
	 * pretvaraju u 1 (true) pri dodeli. */
	_Bool x = 5;

	printf("x: %d\n", x);

	/* Alternativno, mozemo koristiti bool, true i false makro-e iz stdbool.h
	   zaglavlja za rad sa logickim tipovima */

	bool y = true, z = false;

	printf("y: %d\tz: %d\n", y, z);

	/* Definicija promenljivih unutar for petlji je moguca */
	for (int i = 0; i < 13; i++) {
		printf("Na ");
	}

	printf("Batman!\n");

	return 0;
}
