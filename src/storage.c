#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "systest.h"

int run_storage_test(long long mb_to_test) {
    const char *filename = "test_storage_speed.bin";

    print_header("STORAGE BENCHMARK");
    printf("Target File : %lld MB -> %s\n\n", mb_to_test, filename);

    char *buffer = (char *)malloc(BLOCK_SIZE);
    if (buffer == NULL) {
        printf("[X] ERROR: Insufficient RAM for I/O buffer allocation.\n");
        return 1;
    }
    for (int i = 0; i < BLOCK_SIZE; i++) buffer[i] = (char)(i % 256);

    printf("[1/3] Evaluating pure WRITE speed...\n");
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("[X] ERROR: Permission denied or storage is full!\n");
        free(buffer);
        return 1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long long i = 0; i < mb_to_test; i++) {
        fwrite(buffer, 1, BLOCK_SIZE, fp);
    }
    fflush(fp);
    fsync(fileno(fp)); 
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double write_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("[✓] Write completed! Speed: %.2f MB/s\n\n", (double)mb_to_test / write_time);
    fclose(fp);

    int fd = open(filename, O_RDONLY);
    posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED); 
    close(fd);

    printf("[2/3] Evaluating pure READ speed...\n");
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        free(buffer);
        return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (long long i = 0; i < mb_to_test; i++) {
        fread(buffer, 1, BLOCK_SIZE, fp);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double read_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("[✓] Read completed!  Speed: %.2f MB/s\n\n", (double)mb_to_test / read_time);
    fclose(fp);

    printf("[3/3] Purging temporary test files...\n");
    unlink(filename);
    free(buffer);
    printf("==========================================\n");
    return 0;
}

