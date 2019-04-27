#include <stdio.h>

// Koji su potencijalni problemi sa ovakvom definicijom makro-a max?
// #define max(a, b) ((a) < (b) ? (a) : (b))

#define max(type, fst, args...) ({ \
	type _max = (fst); \
	type _arr[] = { args }; \
	for (size_t i = 0; i < sizeof(_arr) / sizeof(_arr[0]); i++) { \
		if (_arr[i] > _max) { _max = _arr[i]; } \
	} \
	_max; \
})

int main() {
	printf("%d\n", max(int, -6, 4, 59, 27));
	return 0;
}
