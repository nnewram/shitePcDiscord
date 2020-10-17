#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <pthread.h>

enum LEVEL {ERROR=-1, SILENT, INFO};

#if defined(LOGLEVEL_SILENT)
#define LOGLEVEL SILENT
#elif defined(LOGLEVEL_ERROR)
#define LOGLEVEL ERROR
#else
#define LOGLEVEL INFO
#endif

#define logInfo(fmt, ...) \
  do { \
    if (LOGLEVEL == INFO) {\
      fprintf(stderr, fmt "\n", __VA_ARGS__); \
    } \
  } while(0)

#define logError(fmt, ...) \
  do { \
    if (LOGLEVEL == ERROR || LOGLEVEL == INFO) { \
      fprintf(stderr, "Error in file %s, line %d, function %s: " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } \
  } while(0)

const char *ENDVC = "ENDVC";
const int MAXCONN = 50;
const int BLOCKSIZ = 1024;

_Bool listening = 1; // set this to 0 at the end of program

struct VoiceBlock {
    char *data;
    size_t size;
};
