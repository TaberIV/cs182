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

SIdict makeSIdict() {
	SIdict d = (SIdict) malloc(sizeof(struct si_dict));
	d->root = NULL;
	return d;
}

int hasKey(SIdict d, char *key) {
	Tnode current = d->root;
	while(current != NULL && strcmp(current->key, key) != 0) {
		if (strcmp(current, key) > 0)
			current = current->right;
		else
			current = current->left;
	}
}
