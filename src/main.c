#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>

#include "options.h"

// Prototypes

void show_help(char *progname);

int compare_indices(const void *first_index, const void *second_index);

bool contains(long value, long *byte_indices, long length);

// Code

void show_help(char *progname) {
  printf("Usage: %s [options]\n", progname);
  printf("Options:\n");
  printf("  -i file, --input file     File to putrefy.\n");
  printf("  -o file, --output file    Output putrefied file to file.\n");
  printf("  -r rate, --rate rate      The rate of putrefaction, between 0 and 1 inclusive.\n");
  printf("  -v, --verbose             Verbose output.\n");
  printf("  -h, --help                Show this message.\n");
}

int compare_indices(const void *first_index, const void *second_index) {
  return *(long *)first_index = *(long *)second_index;
}

bool contains(long value, long *byte_indices, long length) {
  long i;
  for (i = 0L; i < length; i++) {
    if (byte_indices[i] == value) {
      return true;
    }
  }

  return false;
}

int main(int argc, char **argv) {
  char *inpath = NULL;
  char *outpath = NULL;
  double rate = -1.0;
  bool verbose = false;

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

      if (i + 1 == argc) {
	printf("No output file provided.\n");
	return EXIT_FAILURE;
      }

      outpath = argv[++i];
    }

    if (strncmp(argv[i], OPT_RATE, strlen(OPT_RATE)) == 0
	|| strncmp(argv[i], OPT_RATE_LONG, strlen(OPT_RATE_LONG)) == 0) {
      
      if (i + 1 == argc) {
	printf("No putrefaction rate provided.\n");
	return EXIT_FAILURE;
      }

      rate = atof(argv[++i]);
      if (rate < 0.0) {
	printf("Putrefaction rate must be between 0 and 1 inclusive.\n");
	return EXIT_FAILURE;
      }
    }

    if (strncmp(argv[i], OPT_VERBOSE, strlen(OPT_VERBOSE)) == 0
	|| strncmp(argv[i], OPT_VERBOSE_LONG, strlen(OPT_VERBOSE_LONG)) == 0) {
      verbose = true;
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

  if (rate < 0.0) {
    printf("Putrefaction rate required.\n");
    return EXIT_FAILURE;
  }
  else {
    printf("Putrefaction rate = %g\n", rate);
  }

  if (access(inpath, R_OK) != -1) {
    FILE *infile = fopen(inpath, "rb");
    fseek(infile, 0L, SEEK_END);
    long infile_length = ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    long byte_index_count = (long)(rate * infile_length);
    if (verbose) {
      printf("%ld bytes will be putrefied\n", byte_index_count);
    }

    long *byte_indices = (long *)malloc(sizeof(long) * byte_index_count);

    long i;
    for (i = 0L; i < byte_index_count; i++) {
      byte_indices[i] = rand() % infile_length;
    }

    qsort(byte_indices, byte_index_count, sizeof(long), compare_indices);

    srand(time(NULL));

    FILE *outfile = fopen(outpath, "wb");

    int byte;
    for (i = 0L; i < infile_length; i++) {
      if (contains(i, byte_indices, byte_index_count)) {
	printf("Dirty byte at %ld\n", i);
      }
      byte = fgetc(infile);
      fputc(byte, outfile);
    }

    free(byte_indices);

    fclose(infile);
    fclose(outfile);
  }
  else {
    printf("Cannot access %s.\n", inpath);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
