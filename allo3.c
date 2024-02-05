#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE_XI 3
#define SIZE_H 144
#define SIZE_A 10
#define SIZE_GBYTE (1LL << 30)

// Global variables to simulate COMMON blocks in Fortran
float xi[SIZE_XI], h[SIZE_H];
float xj[SIZE_XI], hj[SIZE_H];

// Function prototypes
void f(int n, float A[]);
void report_memory(const char *variable_name, intptr_t variable_loc, const char *description);

int main() {
    float A[SIZE_A] = {0};
    float *B1, *B2;
    float x = 0;

    // Allocating memory for B1 and B2
    B1 = (float *)malloc(SIZE_GBYTE * sizeof(float));
    B2 = (float *)malloc(SIZE_GBYTE * sizeof(float));

    // Report memory locations
    report_memory("xi", (intptr_t)xi, "blank COMMON");
    report_memory("xj", (intptr_t)xj, "labeled COMMON jj");
    report_memory("A ", (intptr_t)A, "local stack array");
    report_memory("B1", (intptr_t)B1, "Allocated heap array");
    report_memory("B2", (intptr_t)B2, "Allocated heap array");
    report_memory("x ", (intptr_t)&x, "local stack variable");

    // Call to function f
    f(SIZE_A, A);

    // Cleanup
    free(B1);
    free(B2);

    return 0;
}

void f(int n, float A[]) {
    A[n - 1] = 1;
}

void report_memory(const char *variable_name, intptr_t variable_loc, const char *description) {
    printf("%-3s %-11lld %-18lld %s\n", variable_name, variable_loc / SIZE_GBYTE, variable_loc, description);
}
