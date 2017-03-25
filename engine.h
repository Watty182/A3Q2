#ifndef _ENGINE_H
#define _ENGINE_H

// defines Boolean to either false or true
typedef enum BOOL {false, true} Boolean;

//==============================================================
// Prototypes
//==============================================================

Boolean search(const char *);
Boolean insert(const char *);
Boolean delete(const char *);
void wipeTable(void);
int size(void);
char * firstItem(void);
char * nextItem(void);
char * loadDict(char*, const char*);

#endif