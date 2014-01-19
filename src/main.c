#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

// Prototypes

void show_help(const char *progname);

// Code

void show_help(const char *progname) {
  printf("Usage: %s [file] [options]\n", progname);
  printf("Options:\n");
  printf("  -h, --help            Show this message.\n");
  printf("  -d DIR, --dest DIR    Output putrefied file to DIR.\n");
}

int main(const int argc, const char **argv) {
  if (argc < 2) {
    printf("File required. Type %s -h for more information.\n", argv[0]);
    return EXIT_FAILURE;
  }

  options_t options;

  int i;
  for (i = 2; i < argc; i++) {
    if (strncmp(argv[i], OPT_HELP, strlen(OPT_HELP)) == 0
	|| strncmp(argv[i], OPT_HELP_LONG, strlen(OPT_HELP_LONG)) == 0) {
      show_help(argv[0]);
      return EXIT_SUCCESS;
    }
    
    if (strncmp(argv[i], OPT_DEST, strlen(OPT_DEST)) == 0
	|| strncmp(argv[i], OPT_DEST_LONG, strlen(OPT_DEST_LONG)) == 0) {
      options.dest = argv[++i];
    }
  }

  const char* path = argv[1];

  printf("File: '%s', Options: dest=%s\n", path, options.dest);

  return EXIT_SUCCESS;
}
