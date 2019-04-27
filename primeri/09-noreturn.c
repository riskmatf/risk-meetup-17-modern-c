#include <stdio.h>
#include <stdlib.h>

_Noreturn int exit_gracefully(char *reason, int code) {
    printf("A fatal error occured! Message: %s\n"
            "Program will now exit.", reason);
    exit(code);
}

int main() {
    exit_gracefully("Random error", EXIT_FAILURE);
    printf("This should not be printed!\n");
    return 0;
}
