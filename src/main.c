#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

// Prototypes

options_t *get_options(int argc, const char **argv);

void initialize_options(options_t *options);

void show_help(const char *progname);

// Code

void show_help(const char *progname) {
  printf("Usage: %s [options]\n", progname);
  printf("Options:\n");
  printf("  -i file, --input file     File to putrefy.\n");
  printf("  -o file, --output file    Output putrefied file to DIR.\n");
  printf("  -h, --help                Show this message.\n");
}

options_t *get_options(int argc, const char **argv) {
  options_t *options = (options_t *)malloc(sizeof(options_t));
  initialize_options(options);

  int i;
  for (i = 1; i < argc; i++) {
    if (strncmp(argv[i], OPT_HELP, strlen(OPT_HELP)) == 0
	|| strncmp(argv[i], OPT_HELP_LONG, strlen(OPT_HELP_LONG)) == 0) {
      options->show_help = true;
    }
    
    if (strncmp(argv[i], OPT_INPUT, strlen(OPT_INPUT)) == 0
	|| strncmp(argv[i], OPT_INPUT_LONG, strlen(OPT_INPUT_LONG)) == 0) {
      options->infile = argv[++i];
    }

    if (strncmp(argv[i], OPT_OUTPUT, strlen(OPT_OUTPUT)) == 0
	|| strncmp(argv[i], OPT_OUTPUT_LONG, strlen(OPT_OUTPUT_LONG)) == 0) {
      options->outfile = argv[++i];
    }    
  }

  return options;
}

void initialize_options(options_t *options) {
  options->show_help = false;
  options->infile = NULL;
  options->outfile = NULL;
}

int main(const int argc, const char **argv) {
  options_t *options = get_options(argc, argv);

  printf("Options: show_help='%n', infile='%s', outfile='%s'\n",
	 options->show_help,
	 options->infile,
	 options->outfile);

  return EXIT_SUCCESS;
}
