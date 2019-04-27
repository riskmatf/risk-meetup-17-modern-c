// Prevesti sa gcc 13-attributes.c -o 13 -O2 -Wall
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define autodestroy(type) __attribute__((cleanup(type##_destroy))) struct type

struct person {
    char *name;
    char *surname;
    short age;
};

struct person *person_new(char *name, char *surname, short age) {
    struct person *p = malloc(sizeof(struct person));
    p->name = name;
    p->surname = surname;
    p->age = age;
    return p;
}

__attribute__((deprecated(
    "This function is deprecated and will be removed in future versions. "
    "Use person_display instead."
)))
void person_print(const struct person *p) {
    printf("%s %s %hd\n", p->name, p->surname, p->age);    
}

__attribute__((nonnull))
void person_display(const struct person *p) {
    printf("%s %s %hd\n", p->name ? : "", p->surname ? : "", p->age);
}

void person_destroy(void *p) {
    free(*(void **)p);
}

/* Cistim funkcijama zovemo one funkcije koje ne izazivaju bocne efekte
 * (eng. side-effects). Ako oznacimo f sa `pure`, f(x - 2) se racuna samo
 * jednom. Koja je vremenska slozenost ove funkcije sa i bez `pure` atributa?
 * 
 * Savet: pokrenuti program gdb-om i uporediti disasemblovanu funkciju f sa i
 * bez atributa `pure` */
__attribute__((pure))
int f(int x) {
    if (x <= 1) { return 1; }
    return f(x - 2) + f(x - 2);
}


int main() {
    autodestroy(person) *p = person_new("Dusan", "Gvozdenovic", 20);

    // person_print(p);

    person_display(p);

    /* Pri ovakvom pozivu, GCC bi sada trebao da upozori da prosledjujemo NULL
     * Tamo gde se ocekuje ne-NULL pokazivac */
    // person_display(NULL);

    int x;
    printf("Unesite x: ");
    scanf("%d", &x);
    printf("%d\n", f(x));

    return 0;
}