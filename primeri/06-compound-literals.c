#include <stdio.h>

struct person {
    char *name;
    char *surname;
    short age;
};

void person_print(struct person *p) {
    printf("%s %s %hd\n", p->name, p->surname, p->age);
}

int main() {
    struct person p = { "Dusan", "Gvozdenovic", 20 };
    person_print(&p);
    // Alternativno smo mogli napisati samo ovo
    person_print(&(struct person){ "Dusan", "Gvozdenovic", 20 });
    return 0;
}