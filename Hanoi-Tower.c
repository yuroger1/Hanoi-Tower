#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void hanoi(unsigned int n,
                  char source,
                  char auxiliary,
                  char destination,
                  unsigned long long *move_count) {
  if (n == 0) {
    return;
  }

  hanoi(n - 1, source, destination, auxiliary, move_count);
  ++(*move_count);
  printf("Step %llu: Move disk %u from '%c' to '%c'\n",
         *move_count,
         n,
         source,
         destination);
  hanoi(n - 1, auxiliary, source, destination, move_count);
}

static bool parse_disk_count(const char *argument, unsigned int *result) {
  char *endptr = NULL;
  errno = 0;
  unsigned long value = strtoul(argument, &endptr, 10);

  if (errno != 0 || endptr == argument || *endptr != '\0' || value == 0 ||
      value > UINT_MAX) {
    return false;
  }

  *result = (unsigned int)value;
  return true;
}

static void print_usage(const char *program_name) {
  fprintf(stderr,
          "Usage: %s [number_of_disks]\n\n"
          "If omitted, the program solves the puzzle for 64 disks.\n",
          program_name);
}

int main(int argc, char *argv[]) {
  const unsigned int default_disks = 64U;
  unsigned int disks = default_disks;

  if (argc > 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  if (argc == 2 && !parse_disk_count(argv[1], &disks)) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  unsigned long long move_count = 0ULL;
  printf("Solving the Tower of Hanoi for %u disk%s...\n\n",
         disks,
         disks == 1 ? "" : "s");

  hanoi(disks, 'A', 'B', 'C', &move_count);

  printf("\nSolved in %llu moves.\n", move_count);
  return EXIT_SUCCESS;
}
