#include <stdio.h>
#include <stdlib.h>

/* Ovo je implementacija dvostruko povezane, kruzne liste, na nacin koji je
 * objasnjen na predavanju. Za vise informacija o upotrebi procitati
 * dokumentacione komentare iz zaglavlja */
#include "list.h"

#define array_len(array) (sizeof(array) / sizeof((array)[0]))

int main() {
    struct int_list {
        struct list_head head;
        int value;
    };

    /* Tehnika odrzavanja listi podataka koja je ovde navedena se popularno naziva
     * "X-makroi". Prvo definisemo list(X) makro koji izlistava elemente, a
     * zatim definisemo i X. Kada hocemo da ispisemo listu, jednostavno
     * pustimo da preprocesor zameni list(X) u kodu. Ukoliko lista treba da se
     * ispise na vise mesta, list zadrzavamo a menjamo samo X makro kako nam odgovara.
     *
     * Pokrenuti gcc -E list-demo.c i videti kako je inicijalizovan niz list */
    #define list(X) X(-1) X(3) X(5) X(-12) X(0) X(7)
    #define X(INT) { .value = (INT) },

    struct int_list list[] = { list(X) };
    
    #undef X
    #undef list

    // Ova implementacija liste zahteva da se svaki cvor inicijalizuje
    // pokazivacima na samog sebe. U samostalnoj definiciji bismo to verovatno
    // uradili sa LIST_HEAD_INIT makroom ali posto smo alocirali elemente
    // u nizu, to radimo rucno
    struct list_head *head = &list[0].head;
    head->next = head->prev = head;

    for (size_t i = 1; i < array_len(list); i++) {
        struct list_head *node = &list[i].head;
        node->next = node->prev = node;
        list_add_tail(node, head);
    }

    // TODO: Izmeniti list_for_each_entry makro tako da se pos promenljiva
    // definise unutar for petlje. (Uputstvo: koristiti typeof operator)
    struct int_list *pos;
    list_for_each_entry(pos, head->prev, head) { // Zasto head->prev a ne head?
        printf("%d\n", pos->value);
    }
    
    return 0;
} 