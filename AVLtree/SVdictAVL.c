//I pledge my honor I have abided by the Stevens Honor System - Taber McFarlin

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
  d->bal = 0;
  
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

void rightRotation(SVdict d) {
  char* keyTemp;
  void* valTemp;
  SVdict temp;

  //Swap------------------
  keyTemp = d->key;
  valTemp = d->val;
  d->key = d->left->key;
  d->val = d->left->val;
  d->left->key = keyTemp;
  d->left->val = valTemp;
  //-----------------------
  temp = d->left;
  d->left = d->left->left;
  temp->left = temp->right;
  temp->right = d->right;
  d->right = temp;
}

void leftRotation(SVdict d) {
  char* keyTemp;
  void* valTemp;
  SVdict temp;

  //Swap------------------
  keyTemp = d->key;
  valTemp = d->val;
  d->key = d->right->key;
  d->val = d->right->val;
  d->right->key = keyTemp;
  d->right->val = valTemp;
  //-----------------------
  temp = d->right;
  d->right = d->right->right;
  temp->right = temp->left;
  temp->left = d->left;
  d->left = temp;
}

void leftRightRotation(SVdict d) {
  leftRotation(d->left);
  rightRotation(d);
}

void rightLeftRotation(SVdict d) {
  rightRotation(d->right);
  leftRotation(d);
}

void balance(SVdict d, int nextBal, int nextBal1, int left) {
  if (abs(nextBal1) > abs(nextBal)) {
    d->bal += left;
    
    if (abs(d->bal) > 1) {
      if (d->bal > 0) {
	if (d->left->bal == 1) {
	  rightRotation(d);
	  d->bal = 0;
	  d->right->bal = 0;
	}
	else {
	  leftRightRotation(d);
	  d->bal = 0;
	  d->right->bal = 0;
	  d->left->bal = 0;
	}
      }
      else if (d->bal < 0) {
	if (d->right->bal == -1) {
	  leftRotation(d);
	  d->bal = 0;
	  d->left->bal = 0;
	}
	else {
	  rightLeftRotation(d);
	  d->bal = 0;
	  d->left->bal = 0;
	  d->right->bal = 0;
	}
      }
    }
  }
}
  
int addOrUpdate(SVdict d, char* key, void* val) { //ADD BALANCING
  if (d->key != NULL) {
    if (strcmp(d->key, key) == 0) {
      d->val = val;
      return 1;
    }
    else {
      int nextBal, returnVal, nextBal1, left = (strcmp(d->key, key) > 0) ? 1 : -1;
      if (left != 1) { //IF to go right
	if (d->right != NULL) {
	  nextBal = d->right->bal;
	  returnVal = addOrUpdate(d->right, key, val);
	  nextBal1 = d->right->bal;
	}
	else {
	  d->right = makeSVdict();
	  d->right->key = malloc(strlen(key) + 1);
	  strcpy(d->right->key, key);
	  d->right->val = val;
	  
	  d->bal -= 1;
	  return 0;
	}
      }
      else { //Else to go left
	if (d->left != NULL) { 
	  nextBal = d->left->bal;
	  returnVal = addOrUpdate(d->left, key, val);
	  nextBal1 = d->left->bal;
	}
	else {
	  d->left = makeSVdict();
	  d->left->key = malloc(strlen(key));
	  strcpy(d->left->key, key);
	  d->left->val = val;
	  
	  d->bal += 1;
	  return 0;
	}
      }

      balance(d, nextBal, nextBal1, left);
      
      return returnVal;
    }
  }
  //If the key was NULL, we are dealing with an
  //empty tree, so we can work with the root directly
  else {
    d->key = malloc(strlen(key) + 1);
    strcpy(d->key, key);
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
    int nextBal, nextBal1, left = (strcmp(d->key, key) < 0) ? -1 : 1, returnVal;
    if (left != 1) {
      if (d->right == NULL)
	nextBal = 10;
      else
	nextBal = d->right->bal;
      
      returnVal = RemKey(d->right, key, d);
      
      if (d->right == NULL)
	nextBal1 = 10;
      else
	nextBal1 = d->right->bal;
      if (nextBal != nextBal1 && (nextBal1 == 10 || abs(nextBal - nextBal1) > 0))
	d->bal += 1;
    }
    else {
      if (d->left == NULL)
	nextBal = 10;
      else
	nextBal = d->left->bal;
      
      returnVal = RemKey(d->left, key, d);

      if (d->left == NULL)
	nextBal1 = 10;
      else
	nextBal1 = d->left->bal;
      if (nextBal != nextBal1 && (nextBal1 == 10 || abs(nextBal - nextBal1) > 0))
	d->bal -= 1;
    }
    
    //balance(d, nextBal, nextBal1, -left);
    if (abs(d->bal) > 1) {
      if (d->bal > 0) {
	if (d->left->bal == 1) {
	  rightRotation(d);
	  d->bal = 0;
	  d->right->bal = 0;
	}
	else {
	  leftRightRotation(d);
	  d->bal = 0;
	  d->right->bal = 0;
	  d->left->bal = 0;
	}
      }
      else if (d->bal < 0) {
	if (d->right->bal == -1) {
	  leftRotation(d);
	  d->bal = 0;
	  d->left->bal = 0;
	}
	else {
	  rightLeftRotation(d);
	  d->bal = 0;
	  d->left->bal = 0;
	  d->right->bal = 0;
	}
      }
    }
    return returnVal;
  }
  //------------------------------------------------

  //If you get here your search has concluded, -----------
  //this section of code only runs on the last recusion---
  if (d == NULL) //key is not in the tree
    return 0;
  else { //d has key you are looking for
    int left = (strcmp(parent->key, key) > 0) ? 1 : 0;
    SVdict temp = d;
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
      temp = d->right;
      while (temp->left != NULL)
	temp = temp->left;
      remKey(d, temp->key);

      temp->right = d->right;
      temp->left = d->left;
      if (left == 1)
	parent->left = temp;
      else
	parent->right = temp;
      //------------------------------------------------------
    }
    free(d->key);
    free(d);
    
    return 1;
  }
  //------------------------------------------------------
}

int remKey(SVdict d, char* key) {
  //Finds desired key-------------------------------
  if (d != NULL && strcmp(d->key, key) != 0) {
    int nextBal, nextBal1, left = (strcmp(d->key, key) < 0) ? -1 : 1, returnVal;
    if (left != 1) {
      if (d->right == NULL)
	nextBal = 10;
      else
	nextBal = d->right->bal;
      
      returnVal = RemKey(d->right, key, d);
      
      if (d->right == NULL)
	nextBal1 = 10;
      else
	nextBal1 = d->right->bal;
      if (nextBal != nextBal1 && (nextBal1 == 10 || abs(nextBal - nextBal1) > 0))
	d->bal += 1;
    }
    else {
      if (d->left == NULL)
	nextBal = 10;
      else
	nextBal = d->left->bal;
      
      returnVal = RemKey(d->left, key, d);

      if (d->left == NULL)
	nextBal1 = 10;
      else
	nextBal1 = d->left->bal;
      if (nextBal != nextBal1 && (nextBal1 == 10 || abs(nextBal - nextBal1) > 0))
	d->bal -= 1;
    }

    //balance(d, nextBal, nextBal1, -1*left);
    return returnVal;
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
    printf("%s       \t%d\n", t->key, t->bal);
    preorderK(t->left, indent+1);
    preorderK(t->right, indent+1);
  }
  else 
    printf("*\n");
}

void preorderKeys(SVdict d) {
  preorderK(d, 0);
}

int main() {
  SVdict d = makeSVdict();
  addOrUpdate(d, "A", (int *) 1);
  addOrUpdate(d, "B", (int *) 1);
  addOrUpdate(d, "C", (int *) 1);
  addOrUpdate(d, "D", (int *) 1);
  addOrUpdate(d, "E", (int *) 1);
  addOrUpdate(d, "F", (int *) 1);
  addOrUpdate(d, "G", (int *) 1);
  addOrUpdate(d, "H", (int *) 1);
  addOrUpdate(d, "I", (int *) 1);
  addOrUpdate(d, "J", (int *) 1);
  addOrUpdate(d, "K", (int *) 1);
  addOrUpdate(d, "L", (int *) 1);
  addOrUpdate(d, "M", (int *) 1);
  addOrUpdate(d, "N", (int *) 1);
  addOrUpdate(d, "O", (int *) 1);
  addOrUpdate(d, "P", (int *) 1);
  addOrUpdate(d, "Q", (int *) 1);
  addOrUpdate(d, "R", (int *) 1);
  addOrUpdate(d, "S", (int *) 1);
  addOrUpdate(d, "T", (int *) 1);
  addOrUpdate(d, "U", (int *) 1);
  addOrUpdate(d, "V", (int *) 1);
  addOrUpdate(d, "W", (int *) 1);
  addOrUpdate(d, "X", (int *) 1);
  addOrUpdate(d, "Y", (int *) 1);
  addOrUpdate(d, "Z", (int *) 1);
  remKey(d, "R");
  preorderKeys(d);
  disposeSVdict(d);
}
