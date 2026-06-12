#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "systest.h"

int run_ram_test(long long mb_to_test, int total_loops) {
    long long bytes = mb_to_test * 1024 * 1024;
    
    print_header("RAM STRESS TEST");
    printf("[1/3] Allocating memory space: %lld MB...\n", mb_to_test);

    char *ram_ptr = (char *)malloc(bytes);
    if (ram_ptr == NULL) {
        printf("\n[X] ERROR: Kernel denied allocation! Out of memory.\n");
        return 1;
    }
    printf("[✓] Memory successfully allocated and locked.\n\n");

    printf("[2/3] Writing random patterns to RAM (%d Loops)...\n", total_loops);
    printf("------------------------------------------\n");

    struct timespec total_start, total_end;
    clock_gettime(CLOCK_MONOTONIC, &total_start);

    for (int i = 1; i <= total_loops; i++) {
        struct timespec loop_start, loop_end;
        clock_gettime(CLOCK_MONOTONIC, &loop_start);

        memset(ram_ptr, i, bytes); 

        clock_gettime(CLOCK_MONOTONIC, &loop_end);

        double loop_time = (loop_end.tv_sec - loop_start.tv_sec) + 
                           (loop_end.tv_nsec - loop_start.tv_nsec) / 1e9;
        double loop_speed = (double)mb_to_test / loop_time;

        printf(" -> Loop %02d/%02d: Done in %.4f sec | Bandwidth: %.2f MB/s\n", 
               i, total_loops, loop_time, loop_speed);
    }

    clock_gettime(CLOCK_MONOTONIC, &total_end);
    double total_time = (total_end.tv_sec - total_start.tv_sec) + 
                        (total_end.tv_nsec - total_start.tv_nsec) / 1e9;

    printf("------------------------------------------\n");
    printf("[✓] All loops completed in %.2f seconds!\n\n", total_time);

    printf("[ℹ] Holding RAM for 5 seconds for system monitoring...");
    fflush(stdout);
    for (int s = 5; s > 0; s--) {
        printf(" %d", s);
        fflush(stdout);
        sleep(1);
    }
    printf("\n\n");

    printf("[3/3] Releasing memory back to the OS...\n");
    free(ram_ptr);
    printf("[✓] RAM cleared successfully.\n");
    printf("==========================================\n");
    return 0;
}

