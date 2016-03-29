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
  char* check;
  
  while (d != NULL && d->val != NULL) {
    check = d->key;
    
    if (strcmp(check, key) == 0)
      return 1;
    else if (strcmp(check, key) > 0)
      d = d->right;
    else
      d = d->left;
  }
  return 0;
}

int addOrUpdate(SVdict d, char* key, void* val) {
  char* check;
  
  while (d != NULL && d->key != NULL) {
    printf("MEH\n");
    check = d->key;
    
    if (strcmp(check, key) == 0) {
      d->val = val;
      return 1;
    }
    else if (strcmp(check, key) > 0) {
      printf("Moo\n");
      if (d->right == NULL)
	d->right = makeSVdict();
      d = d->right;
    }
    else {
      d = d->left;
    }
  }
  if (d == NULL) {
    printf("Meesh\n");
    d = makeSVdict();
  }
  d->key = key;
  d->val = val;
  
  return 0;
}

int main() {
  SVdict dict = makeSVdict();
  addOrUpdate(dict, "ASS", (int*) 3);
  printf("\t%s\n", dict->key);
  addOrUpdate(dict, "BASS", (int*) 4);
  printf("\t%s\n", dict->right->key);
  addOrUpdate(dict, "APPLE", (int*) 7);
  printf("Has ASS: %d\nHas AND: %d\nHas BASS: %d\nHas APPLE: %d\n",
	 hasKey(dict, "ASS"), hasKey(dict, "AND"),
	 hasKey(dict, "BASS"), hasKey(dict, "APPLE"));
}
