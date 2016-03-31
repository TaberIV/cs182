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
  if (d != NULL) {
    SVdict right = d->right;
    SVdict left = d->left;
    free(d->key);
    free(d);
    disposeSVdict(right);
    disposeSVdict(left);
  }
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

int addOrUpdate(SVdict d, char* key, void* val) { //ADD BALANCING
  SVdict prev = NULL;
  
  while (d != NULL && d->val != NULL) {
    if (strcmp(d->key, key) == 0) {
      d->val = val;
      return 1;
    }
    else {
      prev = d;
      
      if (strcmp(d->key, key) < 0)
	d = d->right;
      else
	d = d->left;
    }
  }
  //either d is null, or we were dealing with an empty tree, in which case prev = NULL
  if (prev != NULL) {
    if (strcmp(prev->key, key) < 0) {
      prev->right = makeSVdict();
      d = prev->right;
    }
    else {
      prev->left = makeSVdict();
      d = prev->left;
    }
  }
  d->val = val;
  d->key = (char*) malloc(sizeof(key));
  strcpy(d->key, key);
  
  return 0;
}

void* lookup(SVdict d, char* key) {
  while (d != NULL && d->val != NULL) {
    if (strcmp(d->key, key) == 0)
      return d->val;
    else if (strcmp(d->key, key) < 0)
      d = d->right;
    else
      d = d->left;
  }
  return NULL;
}

int remKey(SVdict d, char* key) {
  SVdict prev = NULL, root = d;

  while (d != NULL && strcmp(d->key, key) != 0) {
    prev = d;
    
    if (strcmp(d->key, key) < 0)
      d = d->right;
    else
      d = d->left;
  }

  if (d == NULL)
    return 0;

  SVdict temp;
  if (d->left == NULL)
    temp = d->right;
  else if (d->right == NULL)
    temp = d->left;
  else {
    temp = d->right;
    while (temp->left != NULL)
      temp = temp->left;
    remKey(root, key);
  }

  if (strcmp(prev->key, d->key) < 0)
    prev->right = temp;
  else
    prev->left = temp;
  
  return 1;
}

void preorderK(SVdict t, int indent) {
  for (int i = 0; i < indent; i++)
    printf(" "); /* print a blank of indentation */
  if (t != NULL) {
    printf("%s\n", t->key);
    preorderK(t->left, indent+1);
    preorderK(t->right, indent+1);
  } else 
    printf("*\n");
}

void preorderKeys(SVdict d) {
  preorderK(d, 0);
}

int main() {
  SVdict dict = makeSVdict();
  addOrUpdate(dict, "GOOD", (int*) 1);
  addOrUpdate(dict, "BAD", (int*) 3);
  addOrUpdate(dict, "ASS", (int*) 7);
  addOrUpdate(dict, "UGLY", (int*) 32);
  addOrUpdate(dict, "GOD", (int*) 1);
  addOrUpdate(dict, "BA", (int*) 3);
  addOrUpdate(dict, "dASS", (int*) 7);
  addOrUpdate(dict, "fUGLY", (int*) 32);
  remKey(dict, "ASS");
  preorderKeys(dict);
  
}
