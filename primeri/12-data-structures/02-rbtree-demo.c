#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "rbtree.h"

struct person {
    char *name;
    char *surname;
    int age;
};

struct person_node {
    struct person person;
    struct rb_node node;
};

int person_compare(struct person *p, struct person *q) {
    /* U GNU-C-u, operand za "jeste" granu u ternarnom operatoru moze biti
     * izostavljen i tada se uzima vrednost "upita" za tacno, bez ponovnog
     * racunanja.
     * Vise na: https://gcc.gnu.org/onlinedocs/gcc/Conditionals.html
     */
    int cmp;
    if (cmp = strcmp(p->name ? : "", q->name ? : "")) { return cmp; }
    if (cmp = strcmp(p->surname ? : "", q->surname ? : "")) { return cmp; }
    return p->age - q->age;
}

void person_print(struct person *p) {
    printf("Name: %s\nSurname: %s\nAge: %hd\n", p->name, p->surname, p->age);
}

struct person_node *person_node_new(char *name, char *surname, int age) {
    struct person_node *node = malloc(sizeof(struct person_node));
    node->person.name = name;
    node->person.surname = surname;
    node->person.age = age;
    node->node.rb_left = node->node.rb_right = NULL;
    node->node.rb_parent_color = RB_RED;
    return node;
}

void person_node_destroy(struct person_node *node) {
    free(node);
}

void person_tree_destroy(struct rb_node *node) {
    if (!node) { return; }
    person_tree_destroy(node->rb_left);
    person_tree_destroy(node->rb_right);
    person_node_destroy(rb_entry(node, struct person_node, node));
}

void person_node_add(struct rb_root *root, struct person_node *node) {
    struct rb_node **link = &root->rb_node, *parent = NULL;
    while(*link) {
        parent = *link;
        struct person *p = &rb_entry(*link, struct person_node, node)->person;
        int cmp = person_compare(&node->person, p);
        if (cmp == 0) { return; } // Already exists
        link = cmp > 0 ? &(*link)->rb_right : &(*link)->rb_left;
    }
    rb_link_node(&node->node, parent, link);
    rb_insert_color(&node->node, root);
}

struct person_node *person_find(struct rb_root *root, struct person *person) {
    struct rb_node *link = root->rb_node;
    while(link) {
        struct person_node *p = rb_entry(link, struct person_node, node);
        int cmp = person_compare(person, &p->person);
        if (cmp == 0) { return p; }
        link = cmp > 0 ? link->rb_right : link->rb_left;
    }
    return NULL;
}

#define list(PERSON) \
    PERSON("Marko", "Markovic", 23) \
    PERSON("Nemanja", "Nikolic", 25) \
    PERSON("Petar", "Petrovic", 20) \
    PERSON("Negovan", "Duzdovsic", 20) \
    PERSON("Stevan", "Stevanovic", 27) \
    PERSON("Jovan", "Markovic", 33) \
    PERSON("Tomislav", "Savic", 25) \
    PERSON("Vuk", "Vukmirovic", 27)

int main() {
    struct rb_root root = RB_ROOT;

    #define PERSON(NAME, SURNAME, AGE) \
        person_node_add(&root, person_node_new((NAME), (SURNAME), (AGE)));

    list(PERSON)

    #undef PERSON

    struct person_node *iter;
    struct rb_node *pos;

    // Obilazak stabla
    rb_for_each_entry(iter, pos, &root, node) {
        person_print(&iter->person);
    }

    struct person p = { "Marko", "Markovic", 23 };

    printf("%s %s %hd :: %s\n", p.name, p.surname, p.age,
        person_find(&root, &p) ? "Postoji" : "Ne postoji");

    person_tree_destroy(root.rb_node);
    rb_root_empty(&root);

    return 0;
}
