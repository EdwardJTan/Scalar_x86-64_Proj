#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void stencil_kernel_asm(float* X, float* Y, int n); // External declaration for assembly version

#define N 1000000 // Maximum length of the vector

// C version of the stencil kernel
void stencil_kernel_c(float* X, float* Y, int n) {
    for (int i = 3; i < n - 3; ++i) {
        Y[i] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
    }
}

int main() {
    int n_values[] = { 1 << 20, 1 << 24, 1 << 30 }; // Vector sizes
    clock_t start, end;

    for (int i = 0; i < 3; ++i) {
        int n = n_values[i];
        float* X = (float*)malloc(n * sizeof(float));
        float* Y = (float*)malloc(n * sizeof(float));

        if (X == NULL || Y == NULL) {
            fprintf(stderr, "Failed to allocate memory for X or Y\n");
            return 1; // Or handle the error appropriately
        }

        // Initialize vector X with some values
        for (int j = 0; j < n; ++j) {
            X[j] = (float)(j + 1);
        }

        // Time the C version of the kernel
        start = clock();
        stencil_kernel_c(X, Y, n); // Call the C version
        end = clock();

        // Display the first ten elements of vector Y for the C version
        printf("C Version (n = %d): ", n);
        for (int j = 0; j < 10; ++j) {
            printf("%.2f ", Y[j]);
        }
        printf("\n");

        // Display the time taken by the C version
        printf("Time taken by C version: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

        
        // Time the assembly version of the kernel
        start = clock();
        stencil_kernel_asm(X, Y, n); // Call the assembly version
        end = clock();

        // Display the first ten elements of vector Y for the assembly version
        printf("Assembly Version (n = %d): ", n);
        for (int j = 0; j < 10; ++j) {
            printf("%.2f ", Y[j]);
        }
        printf("\n");

        // Display the time taken by the assembly version
        printf("Time taken by assembly version: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
        

        free(X);
        free(Y);
    }

    return 0;
}

