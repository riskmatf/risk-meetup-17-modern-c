#include <cstdio>

inline unsigned gcd(unsigned x, unsigned y) {
	if (x < y) { x ^= y ^= x ^= y; }
	if (x % y == 0) { return y; }
	unsigned tmp;
	while ((tmp = x % y) != 0) {
		x = y;
		y = tmp;
	}
	return y;
}

int main() {
	unsigned a, b;
	scanf("%u%u", &a, &b);
	printf("%u\n", gcd(a, b));
	return 0;
}
