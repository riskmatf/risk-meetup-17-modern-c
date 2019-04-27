#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// Oprez: ukoliko su __a i __b razlicitog tipa, __b ce se kastovati u tip
// promenljive __a u ternarnom operatoru.
#define min(a, b) ({ \
    typeof(a) __a = (a); \
    typeof(b) __b = (b); \
    __a < __b ? __a : __b; \
})

int main() {
    __auto_type x = min(45.0, 52); // Ekvivalentno sa double x = min(45.0, 52)
    printf("%lf\n", x);
    return 0;
}