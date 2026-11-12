
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#ifdef __linux__
#include <sched.h>
#endif

#define MAX_LENGTH 256

static int data_type;

static int compare(const char *a, const char *b)
{
    if (data_type == 1) {
        double x = strtod(a, NULL);
        double y = strtod(b, NULL);

        return (x > y) - (x < y);
    }

    return strcmp(a, b);
}

static int is_sorted(char (*a)[MAX_LENGTH], size_t n)
{
    for (size_t i = 1; i < n; i++) {
        if (compare(a[i - 1], a[i]) > 0)
            return 0;
    }

    return 1;
}

static int enable_frugal_scheduling(void)
{
#ifdef __linux__
    struct sched_param param = {0};

    if (sched_setscheduler(0, SCHED_IDLE, &param) == 0)
        return 0;
#endif

    return setpriority(PRIO_PROCESS, 0, 19);
}

static void frugal_sort(char (*a)[MAX_LENGTH], size_t n)
{
    unsigned long long swaps = 0;

    while (!is_sorted(a, n)) {
        size_t i = (size_t)rand() % n;
        size_t j = (size_t)rand() % n;

        char temp[MAX_LENGTH];

        memcpy(temp, a[i], MAX_LENGTH);
        memcpy(a[i], a[j], MAX_LENGTH);
        memcpy(a[j], temp, MAX_LENGTH);

        swaps++;
    }

    printf("\nRandom swaps: %llu\n", swaps);
}

int main(void)
{
    size_t n;

    printf("Select data type:\n");
    printf("1. Numbers\n");
    printf("2. Characters / Strings\n");
    printf("Choice: ");

    if (scanf("%d", &data_type) != 1 ||
        (data_type != 1 && data_type != 2)) {
        fprintf(stderr, "Invalid data type\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of elements: ");

    if (scanf("%zu", &n) != 1 || n == 0 || n > 10000) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }

    char (*a)[MAX_LENGTH] = calloc(n, sizeof(*a));

    if (a == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    printf("Enter %zu elements:\n", n);

    for (size_t i = 0; i < n; i++) {
        if (scanf("%255s", a[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(a);
            return EXIT_FAILURE;
        }

        if (data_type == 1) {
            char *end;
            strtod(a[i], &end);

            if (end == a[i] || *end != '\0') {
                fprintf(stderr, "Invalid number\n");
                free(a);
                return EXIT_FAILURE;
            }
        }
    }

    srand((unsigned int)time(NULL));

    if (enable_frugal_scheduling() != 0)
        perror("Scheduling priority");

    frugal_sort(a, n);

    printf("Sorted: ");

    for (size_t i = 0; i < n; i++)
        printf("%s ", a[i]);

    printf("\n");

    free(a);
    return EXIT_SUCCESS;
}
