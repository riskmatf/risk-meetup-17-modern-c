#include <stdio.h>
#include <stdlib.h>

int main() {
	int c = 15;
	// Alocira c * sizeof(int) bajtova na steku. Videti: man alloca
	int *arr = alloca(sizeof(int) * c);
	printf("%d\n", arr);
	return 0;
}
