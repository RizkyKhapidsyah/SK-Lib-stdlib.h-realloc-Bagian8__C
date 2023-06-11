#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/*
    Source by CPPReference (https://en.cppreference.com)
    Modified For Learn by RK
    I.D.E : VS2022
*/

void print_storage_info(const int* next, const int* prev, int ints) {
    if (next) {
        printf("%s location: %p. Size: %d ints (%ld bytes).\n", (next != prev ? "New" : "Old"), (void*)next, ints, ints * sizeof(int));
    } else {
        printf("Allocation failed.\n");
    }      
}

int main() {
    const int pattern[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    const int pattern_size = sizeof pattern / sizeof(int);
    int* next = NULL, * prev = NULL;

    if ((next = (int*)malloc(pattern_size * sizeof * next))) { // mengalokasikan sebuah array 
        memcpy(next, pattern, sizeof pattern); // mengisi array
        print_storage_info(next, prev, pattern_size);
    } else {
        return EXIT_FAILURE;
    }
    
    // Alokasikan ulang dalam siklus menggunakan nilai berikut sebagai ukuran penyimpanan baru.
    const int realloc_size[] = { 10, 12, 512, 32768, 65536, 32768 };

    for (int i = 0; i != sizeof realloc_size / sizeof(int); ++i) {
        if ((next = (int*)realloc(prev = next, realloc_size[i] * sizeof(int)))) {
            print_storage_info(next, prev, realloc_size[i]);
            assert(!memcmp(next, pattern, sizeof pattern));  // pola dipegang
        } else { // jika realloc gagal, pointer asli perlu dibebaskan 
            free(prev);
            return EXIT_FAILURE;
        }
    }

    free(next); // akhirnya, membebaskan penyimpanan
    return EXIT_SUCCESS;

    _getch();
    return 0;
}