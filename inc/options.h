#if !defined(__OPTIONS_H__)
#define __OPTIONS_H__

#include <stdbool.h>

#define OPT_INPUT "-i"
#define OPT_INPUT_LONG "--input"
#define OPT_OUTPUT "-o"
#define OPT_OUTPUT_LONG "--output"
#define OPT_DEST "-d"
#define OPT_DEST_LONG "--dest"
#define OPT_HELP "-h"
#define OPT_HELP_LONG "--help"

typedef struct options_t {
  bool show_help;
  const char *infile;
  const char *outfile;
} options_t;

#endif
