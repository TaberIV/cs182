#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "SVdict.h"

struct sv_dict {
  char* key;
  void* val;
  SVdict left;
  SVdict right;
};

SVdict makeSVdict() {
  SVdict d = (SVdict) malloc(sizeof(struct sv_dict));
  d->key = NULL;
  d->val = NULL;
  d->left = NULL;
  d->right = NULL;
  
  return d;
}

void disposeSVdict(SVdict d) {
  free(d);
}

int hasKey(SVdict d, char* key) {  
  while (d != NULL && d->val != NULL) {    
    if (strcmp(d->key, key) == 0)
      return 1;
    else if (strcmp(d->key, key) < 0)
      d = d->right;
    else
      d = d->left;
  }
  return 0;
}

int addOrUpdate(SVdict d, char* key, void* val) {  
  while (d != NULL && d->key != NULL) {    
    if (strcmp(d->key, key) == 0) {
      printf("1");
      d->val = val;
      return 1;
    }
    else if (strcmp(d->key, key) < 0) {
      printf("Go right\n");
      if (d->right == NULL) {
	d->right = makeSVdict();
	d->right->key = key;
	d->right->val = val;

	return 0;
      }
      else
	d = d->right;
    }
    else {
      printf("Go left\n");
      if (d->left == NULL) {
	d->left = makeSVdict();
	d->left->key = key;
	d->left->val = val;
	
	return 0;
      }
    }
  }
}

int main() {
  SVdict dict = makeSVdict();
  addOrUpdate(dict, "ASS", (int*) 3);
  addOrUpdate(dict, "BASS", (int*) 4);
  assert((strcmp("BASS", dict->right->key) == 0));
  addOrUpdate(dict, "APPLE", (int*) 7);
}
