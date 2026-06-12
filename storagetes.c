#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h> // Diperlukan untuk posix_fadvise

#define BLOCK_SIZE (1024 * 1024)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Cara pakai: %s <jumlah_dalam_MB>\n", argv[0]);
        return 1;
    }

    long long mb_to_test = atoll(argv[1]);
    const char *filename = "test_storage_real.bin";

    char *buffer = (char *)malloc(BLOCK_SIZE);
    if (buffer == NULL) return 1;
    for (int i = 0; i < BLOCK_SIZE; i++) buffer[i] = (char)(i % 256);

    printf("==========================================\n");
    printf("     REAL STORAGE SPEED TEST (NO CACHE)   \n");
    printf("==========================================\n");

    // 1. TEST WRITE
    printf("[1/3] Menguji kecepatan TULIS (Write)...\n");
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) { free(buffer); return 1; }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long long i = 0; i < mb_to_test; i++) {
        fwrite(buffer, 1, BLOCK_SIZE, fp);
    }
    fflush(fp);
    fsync(fileno(fp)); 
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double write_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("[✓] Tulis selesai! Kecepatan: %.2f MB/s\n\n", (double)mb_to_test / write_time);
    fclose(fp);

    // ---------------------------------------------------------
    // TRIK UTAMA: Bersihkan cache RAM khusus untuk file ini saja
    // ---------------------------------------------------------
    int fd = open(filename, O_RDONLY);
    // Memaksa kernel membuang file ini dari RAM Cache
    posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED); 
    close(fd);
    // ---------------------------------------------------------

    // 2. TEST READ
    printf("[2/3] Menguji kecepatan BACA murni (Read)...\n");
    fp = fopen(filename, "rb");

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (long long i = 0; i < mb_to_test; i++) {
        fread(buffer, 1, BLOCK_SIZE, fp);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    double read_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("[✓] Baca selesai!  Kecepatan: %.2f MB/s\n\n", (double)mb_to_test / read_time);
    fclose(fp);

    // 3. CLEANUP
    printf("[3/3] Menghapus file sampah tes...\n");
    unlink(filename);
    free(buffer);
    printf("==========================================\n");
    return 0;
}

