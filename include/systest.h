#ifndef SYSTEST_H
#define SYSTEST_H

#define BLOCK_SIZE (1024 * 1024) // 1 MB Buffer Size

// Shared helper functions
void print_header(const char *test_name);

// Core benchmark modules
int run_ram_test(long long mb_to_test, int total_loops);
int run_storage_test(long long mb_to_test);

#endif // SYSTEST_H

