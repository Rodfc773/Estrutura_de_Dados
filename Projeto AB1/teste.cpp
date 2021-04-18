#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int * ptr;
    int ** pptr;

    int valor = 10;

    ptr = &valor;
    pptr = &ptr;

    printf("Endereço de ptr = %x", &ptr);
    printf("Endereço de pptr = %x", &pptr);

    printf("Valor ptr = %d", *ptr);
    printf("Valor pptr = %d", **pptr);

    return 0;
}
