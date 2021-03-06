#include <stdio.h>
#include <sys/types.h>
#define RIFF_ENTRY(R, DIR, ENT) ((R)->root[(DIR)].entry + (ENT))

typedef struct RIFFEntry_t {
    char fourCC[4];
    char fourCC2[4];
    off_t start;
    unsigned int size;

    int entries;

    int entry;

    int parent;
} RIFFEntry;

typedef struct {
    FILE *f;

    RIFFEntry *root;
    unsigned int entryMemCount;
} RIFFFile;

extern const char RIFFMagic[4];
extern const char LISTFourCC[4];

int isRIFF(char fourCC[4]);
int isLIST(char fourCC[4]);
int isNode(char fourCC[4]);
int isLeaf(char fourCC[4]);
int isEntry(char fourCC[4]);
int isMuxed(short int type);
RIFFFile *riff_init();
off_t riff_entry_offset(RIFFFile *r, int index);
int riff_entry_seekto(RIFFFile *r, int index);
RIFFFile *riff_open(const char *filename);
void riff_close(RIFFFile *r);
int do_traverse(RIFFFile *r,
                const char *pattern,
                int (*match_cb)(RIFFFile *r, int dir, int ent, void *priv),
                void *priv,
                int matchAll,
                int dir);
int riff_traverse(RIFFFile *r,
                  const char *pattern,
                  int (*match_cb)(RIFFFile *r, int dir, int ent, void *priv),
                  void *priv);
int print_entry_cb(RIFFFile *r, int dir, int ent, void *priv);
