#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "SIdict.h"

#define MAXKEYCHARS 32  

/* SIdict represented by binary search tree. 

   Each function assumes the preconditions that 
   the dictionary and key parameters are non-null.
*/

typedef struct tnode* Tnode;
struct tnode { char key[MAXKEYCHARS]; 
               int val; 
               Tnode left; 
               Tnode right; };

struct si_dict { Tnode root; };

