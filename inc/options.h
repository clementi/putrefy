#if !defined(__OPTIONS_H__)
#define __OPTIONS_H__

#define OPT_HELP "-h"
#define OPT_HELP_LONG "--help"
#define OPT_DEST "-d"
#define OPT_DEST_LONG "--dest"

typedef struct options_t {
  const char *dest;
} options_t;

#endif