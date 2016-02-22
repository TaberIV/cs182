/* E. Taber McFarlin
	I pledge my honor I have abided by the Stevens Honor System.
*/
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
struct tnode { char *key;
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
  
  while (current != NULL && strcmp(current->key, key) != 0) {
    if (strcmp(current->key, key) > 0)
      current = current->right;
    else
      current = current->left;
  }
  
  return (current != NULL);
}

int addOrUpdate(SIdict d, char *key, int val) {
  Tnode current = d->root;
  Tnode previous;
 
  while (current != NULL && strcmp(current->key, key) != 0) {
    previous = current;
    
    if (strcmp(current->key, key) > 0)
      current = current->right;
    else
      current = current->left;
  }

  if (current == NULL) {
    Tnode n = (Tnode) malloc(sizeof(struct tnode));
    n->key = key;
    n->val = val;

    if (d->root == NULL)
      d->root = n;
    
    else {
      if (strcmp(key, previous->key) < 0)
	previous->right = n;
      else
	previous->left = n;
    }

    return 0;
  }

  else {
    current->val = val;
    return 1;
  }
}

int lookup(SIdict d, char* key) {
  if (d->root->key == key)
    return d->root->val;
  else {
    SIdict d2 = makeSIdict();
    
    if (strcmp(d->root->key, key) > 0)
      d2->root = d->root->left;
    else
      d2->root = d->root->right;
    
    return lookup(d2, key);
  }
}

int remKey(SIdict d, char* key) {
  Tnode current = d->root;
  Tnode previous;
 
  while (current != NULL && strcmp(current->key, key) != 0) {
    previous = current;
    
    if (strcmp(current->key, key) > 0)
      current = current->right;
    else
      current = current->left;
  }
  
  if (current == NULL)
    return 0;
  else {
    Tnode temp;
    if (current->left == NULL)
      temp = current->right;
    else if (current->right == NULL)
      temp = current->left;
    else {
      temp = current->right;
      while (temp->left != NULL)
	temp = temp->left;
      
      remKey(d, temp->key);
    }

    if (strcmp(previous->key, current->key) < 0)
      previous->right = temp;
    else
      previous->left = temp;
    
    return 1;
  }
}

int main() {
  SIdict dict = makeSIdict();
  char k[3] = "00";
  char l[3] = "01";
  char m[3] = "10";
  
  printf("%d\n", addOrUpdate(dict, k, 0));
  printf("%d\n", addOrUpdate(dict, l, 7));
  printf("%d\n", addOrUpdate(dict, k, 1));
  printf("%d\n", remKey(dict, l));
  printf("%s\n", dict->root->key);
}
