#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "systest.h"

void print_header(const char *test_name) {
    printf("==========================================\n");
    printf("       SYSTEM BENCHMARK TOOL - %s       \n", test_name);
    printf("==========================================\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("==========================================\n");
        printf("         SYSTEM TEST UTILITY (v1.0)       \n");
        printf("==========================================\n");
        printf("Usage:\n");
        printf("  %s ram <Size_MB> <Loops>\n", argv[0]);
        printf("  %s storage <Size_MB>\n\n", argv[0]);
        printf("Examples:\n");
        printf("  %s ram 5120 10\n", argv[0]);
        printf("  %s storage 2048\n", argv[0]);
        printf("==========================================\n");
        return 1;
    }

    if (strcmp(argv[1], "ram") == 0) {
        if (argc < 4) {
            printf("[X] Syntax Error. Use: %s ram <MB> <Loops>\n", argv[0]);
            return 1;
        }
        long long mb = atoll(argv[2]);
        int loops = atoi(argv[3]);
        return run_ram_test(mb, loops);
    } 
    else if (strcmp(argv[1], "storage") == 0) {
        if (argc < 3) {
            printf("[X] Syntax Error. Use: %s storage <MB>\n", argv[0]);
            return 1;
        }
        long long mb = atoll(argv[2]);
        return run_storage_test(mb);
    } 
    else {
        printf("[X] Error: Unknown command '%s'. Select 'ram' or 'storage'.\n", argv[1]);
        return 1;
    }

    return 0;
}

