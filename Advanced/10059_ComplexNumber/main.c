#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
 
int main() {
    complex (*FUNC[])(complex *, complex *) = {
        complex_add, complex_sub, complex_mul
    };
    int cmd;
    float x, y, p, q;
    while (scanf("%d %f %f %f %f", &cmd, &x, &y, &p, &q) == 5) {
        complex *A = (complex *) malloc(sizeof(complex));
        complex *B = (complex *) malloc(sizeof(complex));
        init(A, x, y), init(B, p, q);
        complex C = FUNC[cmd](A, B);
        complex_print(&C);
    }
    return 0;
}
