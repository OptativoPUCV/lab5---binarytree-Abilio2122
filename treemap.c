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
#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un par de elementos
struct Pair {
    int key;
    int value;
};

// Estructura para representar un nodo del árbol
struct TreeNode {
    int key;
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Estructura para representar el árbol en sí
struct TreeMap {
    struct TreeNode* root;
};

// Función para crear un nuevo nodo del árbol
struct TreeNode* newTreeNode(int key, int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Función para crear un nuevo árbol
struct TreeMap* newTreeMap() {
    struct TreeMap* tree = (struct TreeMap*)malloc(sizeof(struct TreeMap));
    tree->root = NULL;
    return tree;
}

// Función para agregar un elemento al árbol
void put(struct TreeMap* tree, int key, int value) {
    struct TreeNode* node = newTreeNode(key, value);
    if (tree->root == NULL) {
        tree->root = node;
        return;
    }
    struct TreeNode* current = tree->root;
    struct TreeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            current->value = value;
            free(node);
            return;
        }
    }
    if (key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

// Función para encontrar el siguiente elemento del árbol
  struct Pair* nextTreeMap(struct TreeMap* tree) {
      static struct TreeNode* current = NULL;
      if (tree == NULL || tree->root == NULL) {
          return NULL;
      }
      if (current == NULL) {
          current = tree->root;
          while (current->left != NULL) {
              current = current->left;
          }
          struct Pair* pair = (struct Pair*)malloc(sizeof(struct Pair));
          pair->key = current->key;
          pair->value = current->value;
          return pair;
      }
      if (current->right != NULL) {
          current = current->right;
          while (current->left != NULL) {
              current = current->left;
          }
          struct Pair* pair = (struct Pair*)malloc(sizeof(struct Pair));
          pair->key = current->key;
          pair->value = current->value;
          return pair;
      } else {
          struct TreeNode* parent = NULL;
          while (current != NULL && current == parent->right) {
              parent = current;
              current = current->right;
          }
          current = parent;
          if (current == NULL) {
              return NULL;
          }
          struct Pair* pair = (struct Pair*)malloc(sizeof(struct Pair));
          pair->key = current->key;
          pair->value = current->

}
