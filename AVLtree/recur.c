#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "SVdict.h"

struct sv_dict {
  char* key;
  void* val;
  int bal;
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
  if (d != NULL && d->val != NULL) {    
    if (strcmp(d->key, key) == 0)
      return 1;
    else if (strcmp(d->key, key) < 0)
      return hasKey(d->right, key);
    else
      return hasKey(d->left, key);
  }
  return 0;
}

int addOrUpdate(SVdict d, char* key, void* val) { //ADD BALANCING
  if (d->key != NULL) {
    if (strcmp(d->key, key) == 0) {
      d->val = val;
      return 1;
    }
    else if (strcmp(d->key, key) < 0) {
      if (d->right != NULL)
	return addOrUpdate(d->right, key, val);
      else {
	d->right = makeSVdict();
	d->right->key = key;
	d->right->val = val;
	return 0;
      }
    }
    else {
      if (d->left != NULL)
	return addOrUpdate(d->left, key, val);
      else {
	d->left = makeSVdict();
	d->left->key = key;
	d->left->val = val;
	return 0;
      }
    }
  }
  //If the key was NULL, we are dealing with an
  //empty tree, so we can work with the root directly
  else {
    d->key = key;
    d->val = val;
    d->bal = 0;
    return 0;
  }
}

void* lookup(SVdict d, char* key) {
  if (d != NULL && d->val != NULL) {
    if (strcmp(d->key, key) == 0)
      return d->val;
    else if (strcmp(d->key, key) < 0)
      return lookup(d->right, key);
    else
      return lookup(d->left, key);
  }
  else
    return NULL;
}

int RemKey(SVdict d, char* key, SVdict parent) {
  //Finds desired key-------------------------------
  if (d != NULL && strcmp(d->key, key) != 0) {    
    if (strcmp(d->key, key) < 0)
      return RemKey(d->right, key, d);
    else
      return RemKey(d->left, key, d);
  }
  //------------------------------------------------

  //If you get here your search has concluded, -----------
  //this section of code only runs on the last recusion---
  if (d == NULL) //key is not in the tree
    return 0;
  else { //d has key you are looking for
    int left = (strcmp(parent->key, key) > 0) ? 1 : 0;
    
    if (d->right == NULL) {
      if (left == 1)
	parent->left = d->left;
      else
	parent->right = d->left;
    }
    else if (d->left == NULL) {
      if (left == 1)
	parent->left = d->right;
      else
	parent->right = d->right;
    }
    else { 
      //You poor fool, this thing you were trying to ---------
      //remove has both left and right subtrees. Get ready. --
      SVdict temp = d->right;
      while (temp->left != NULL)
	temp = temp->left;
      remKey(d, temp->key);

      temp->right = d->right;
      temp->left = d->left;
      if (left == 1)
	parent->left = temp;
      else
	parent->right = temp;
      free(d);
      //------------------------------------------------------
    }
    return 1;
  }
  //------------------------------------------------------
}

int remKey(SVdict d, char* key) {
  //Finds desired key-------------------------------
  if (d != NULL && strcmp(d->key, key) != 0) {    
    if (strcmp(d->key, key) < 0)
      return RemKey(d->right, key, d);
    else
      return RemKey(d->left, key, d);
  }
  //------------------------------------------------

  //This code is only accessed when the ************
  //root is the key being looked for****************
  if (d->right == NULL && d->left == NULL) {
    d->key = NULL;
    d->val = NULL;
  }
  else if (d->right == NULL) {
    d->val = d->left->val;
    d->key = d->left->key;
    d->right = d->left->right;
    d->left = d->left->left;
  }
  else if (d->left == NULL) {
    d->val = d->right->val;
    d->key = d->right->key;
    d->right = d->right->left;
    d->left = d->right->right;
  }
  else {
    SVdict temp;
    temp = d->right;
    while (temp->left != NULL)
      temp = temp->left;
    remKey(d, temp->key);

    d->val = temp->val;
    d->key = temp->key;
  }
  //************************************************
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
  preorderKeys(dict);
  remKey(dict, "GOOD");
  preorderKeys(dict);
  char* key = "GOD";
  printf("\nHas %s: %d\n", key, hasKey(dict, key));
  printf("Lookup %s: %d\n", key, lookup(dict, key));
}
