#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

// Prototypes

void show_help(char *progname);

// Code

void show_help(char *progname) {
  printf("Usage: %s [options]\n", progname);
  printf("Options:\n");
  printf("  -i file, --input file     File to putrefy.\n");
  printf("  -o file, --output file    Output putrefied file to DIR.\n");
  printf("  -h, --help                Show this message.\n");
}

int main(int argc, char **argv) {
  char *inpath = NULL;
  char *outpath = NULL;

  int i;
  for (i = 1; i < argc; i++) {
    if (strncmp(argv[i], OPT_HELP, strlen(OPT_HELP)) == 0
	|| strncmp(argv[i], OPT_HELP_LONG, strlen(OPT_HELP_LONG)) == 0) {
      show_help(argv[0]);
      return EXIT_SUCCESS;
    }

    if (strncmp(argv[i], OPT_INPUT, strlen(OPT_INPUT)) == 0
	|| strncmp(argv[i], OPT_INPUT_LONG, strlen(OPT_INPUT_LONG)) == 0) {

      if (i + 1 == argc) {
	printf("No input file provided.\n");
	return EXIT_FAILURE;
      }

      inpath = argv[++i];
    }

    if (strncmp(argv[i], OPT_OUTPUT, strlen(OPT_OUTPUT)) == 0
	|| strncmp(argv[i], OPT_OUTPUT_LONG, strlen(OPT_OUTPUT_LONG)) == 0) {

      if (i + 1== argc) {
	printf("No output file provided.\n");
	return EXIT_FAILURE;
      }

      outpath = argv[++i];
    }
  }

  if (inpath == NULL) {
    printf("Input file required.\n");
    return EXIT_FAILURE;
  }

  if (outpath == NULL) {
    printf("Output file required.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
