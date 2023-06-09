#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * map= (TreeMap *)malloc(sizeof(TreeMap));
    map->root=NULL;
    map->current=NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(!tree->root){
    tree->root=createTreeNode(key,value);
  }
  else{
    tree->current=tree->root;
    while(tree->current)
    {
      if( is_equal(tree, tree->current->pair->key,key))
      {
        return;
      }
      if(tree->lower_than(tree->current->pair->key,key))
      { //HACIA DERECHA
        if( !tree->current->right){
          
          tree->current->right=createTreeNode(key,value);
          tree->current->right->parent=tree->current;
          tree->current=tree->current->right;
          return;
        }
        tree->current=tree->current->right;
      }
      else{
        if( !tree->current->left){
          tree->current->left= createTreeNode(key,value);
          tree->current->left->parent=tree->current;
          tree->current=tree->current->left;
          return;
        }
        
        //HACIA IZQUIERDA
        tree->current=tree->current->left;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) {
        return NULL;
    }
    struct TreeNode* current = x;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    tree->current=tree->root;
  if(tree->root==NULL)
    return NULL;
  //si existe key
  while(tree->current != NULL)
  {
      if(is_equal(tree, tree->current->pair->key,key)){
        return(tree->current->pair);
      }

      if(tree->lower_than(tree->current->pair->key,key))
      {
        tree->current=tree->current->right;
      }
      else{
        tree->current=tree->current->left;
      }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  if (tree == NULL || tree->root == NULL) {
          return NULL;
      }
      struct TreeNode* current = tree->root;
      while (current->left != NULL) {
          current = current->left;
      }
      struct Pair* pair = (struct Pair*)malloc(sizeof(struct Pair));
      pair->key =current->pair->key;
      pair->value = current->pair->value;
      return pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree->current == NULL) {
          // dirijete al nodo minimo
          firstTreeMap(tree);
          
      } else if (tree->current->right != NULL) {
          // va a el nodo minimo de el subnodo derecho
          tree->current = tree->current->right;
          while (tree->current->left != NULL) {
              tree->current = tree->current->left;
          }
      } else {
          // va al primer ancestro que es un hijo izquierdo
          while (tree->current->parent != NULL && tree->current->parent->right == tree->current) {
              tree->current = tree->current->parent;
          }
          tree->current = tree->current->parent;
      }
      
      if (tree->current == NULL) {
          return NULL;
      } else {
          return tree->current->pair; 
      }
}
