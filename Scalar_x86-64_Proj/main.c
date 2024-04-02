#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdint.h> 

// Assembly function declaration
extern double stencil_kernel_asm(double* X, double* Y, int size);

// Function declarations
void init_X(double* X, int size);
void stencil_kernel_c(double* X, double* Y, int size);


void init_X(double* X, int size) {
    // For intitializing Random Number Generator
    srand(time(NULL));

    // Fill X vector at random
    for (int i = 0; i < size; i++) {
        X[i] = (double)rand();
    }
}

void stencil_kernel_c(double* X, double* Y, int size) {
    // Process the array using C
    int n = size - 1;
    int i;
    int count = 0;
    for (i = 3; i <= n; i++) {

        if (i - 3 < 0 || i + 3 >= size) {
            break;
        }
        else {
            Y[count] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
            count++;
        }


    }
}

int main() {
    int size;

    printf("Please enter the size of the array: ");
    scanf_s(" %d", &size);
    for (int m = 0; m < 30; m++) {
        double* X = malloc(size * sizeof(double));
        int Y_size = size - 6;
        double* Assembly_Yout = malloc(Y_size * sizeof(double));
        double* C_Yout = malloc(Y_size * sizeof(double));

        // Fill X with random numbers

        init_X(X, size);

        // Print X for debugging
        printf("X array:\n");
        for (int i = 0; i < 10; i++) {
            printf("%lf ", X[i]);
        }
        printf("\n");


        // C function

        clock_t t;
        t = clock();
        for (int i = 0; i < 100; i++) {
            stencil_kernel_c(X, C_Yout, size);
        }
        t = clock() - t;
        double c_time_taken = ((double)t) / CLOCKS_PER_SEC;

        printf("ACHIEVED C TIME: %lf sec\n", c_time_taken);

        // Print the result from the C function
        printf("Results from C function:\n");
        for (int i = 0; i < 10; i++) {
            printf("%lf\n", C_Yout[i]);
        }
        printf("\n");


        // Assembly Function

        clock_t a;
        a = clock();
        for (int i = 0; i < 100; i++) {
            stencil_kernel_asm(X, Assembly_Yout, Y_size);
        }
        a = clock() - a;
        double a_time_taken = ((double)a) / CLOCKS_PER_SEC;
        printf("ACHIEVED ASSEMBLY TIME: %Lf sec\n", a_time_taken);

        // Print the result from the assembly function
        printf("Result from Assembly function:\n");
        for (int i = 0; i < 10; i++) {
            printf("%lf\n", Assembly_Yout[i]);
        }
        printf("\n");

        // Free allocated memory
        free(X);
        free(C_Yout);
        free(Assembly_Yout);
    }
    return 0;
}


