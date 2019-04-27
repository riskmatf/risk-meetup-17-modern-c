#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("A non negative integer argument is required!\n");
		return 0;
	}

	unsigned n = atoi(argv[1]);
	int a[n];

	printf("%d\n", a[n - 1]);

	return 0;
}
