#ifndef DHASH_H_INCLUDED
#define DHASH_H_INCLUDED
#include "stdlib.h"

void dstart();
void dend();

void * dmalloc(size_t sz,char *file, int line);
void * dcalloc(size_t n,size_t sz,char *file, int line);
void * drealloc(void * p,size_t sz,char *file, int line);
char * dstrdup(const char * s ,char *file, int line);
wchar_t * dwcsdup(const wchar_t* s, char* file, int line);
void dfree(void * p);

#if defined(_MSC_VER)
#pragma warning ( disable : 4996)
#define BNLONGLONGPATTERN "%lld"
#define BNULONGLONGPATTERN "%llu"
#define F_PAT_TYPE (double)
#else
#define BNLONGLONGPATTERN "%I64d"
#define BNULONGLONGPATTERN "%I64u"
#define F_PAT_TYPE (float)
#endif

#endif // DHASH_H_INCLUDED
