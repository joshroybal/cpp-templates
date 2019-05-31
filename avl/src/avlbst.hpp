// AVL balanced binary search tree
// iterative implementations
#ifndef AVL_HPP
#define AVL_HPP

#include "bst.hpp"

template <class Type> 
class AVL : public BST<Type>
{
   public:
      void Insert(const Type&);
      void Remove(const Type&);
   private:
      typename AVL::Node* insert(typename AVL::Node*, const Type&);
      typename AVL::Node* remove(typename AVL::Node*, const Type&);
      typename AVL::Node* rotate_left(typename AVL::Node*);
      typename AVL::Node* rotate_right(typename AVL::Node*);
      int balance(const typename AVL::Node*) const;
};

// template class public accessor methods
template<class Type> 
void AVL<Type>::Insert(const Type& key)
{
   this->root = insert(this->root, key);
}

template<class Type> 
void AVL<Type>::Remove(const Type& key)
{
   this->root = remove(this->root, key);
}

// template class private methods
template<class Type>
typename AVL<Type>::Node* AVL<Type>::insert(typename AVL::Node* p, const Type& key)
{
   if ( !p ) return new typename AVL::Node(key);

   if (key < p->key) p->left = insert(p->left, key);
   else if (key > p->key) p->right = insert(p->right, key);
   else return p;

   p->height = 1 + std::max(this->h(p->left), this->h(p->right));

   // Left Left Case
   if (balance(p) > 1 && balance(p->left) > 0)
      return rotate_right(p);

   // Right Right Case
   if (balance(p) < -1 && balance(p->right) < 0)
      return rotate_left(p);

   // Left Right Case
   if (balance(p) > 1 && balance(p->left) < 0) {
      p->left = rotate_left(p->left);
      return rotate_right(p);
   }

   // Right Left Case
   if (balance(p) < -1 && balance(p->right) > 0) {
      p->right = rotate_right(p->right);
      return rotate_left(p);
   }

   // Thou shalt not trail off the edge into defined behavior.
   return p;
}

template<class Type> 
typename AVL<Type>::Node* AVL<Type>::remove(typename AVL::Node* p, const Type& key)
{
   if (p == 0) return p;
   // If the key to be deleted is smaller than the root's key, 
   // then it lies in left subtree 
   if (key < p->key) p->left = remove(p->left, key); 
   // If the key to be deleted is greater than the root's key, 
   // then it lies in right subtree 
   else if (key > p->key) p->right = remove(p->right, key); 
   // if key is same as root's key, then This is the node 
   // to be deleted 
   else { 
      // node with only one child or no child 
      if (p->left == 0) { 
         typename AVL::Node* leaf = p->right;
         delete p;
         return leaf; 
      } else if (p->right == NULL) { 
         typename AVL::Node* leaf = p->left;
         delete p;
         return leaf; 
      } 
      // node with two children: Get the inorder successor (smallest 
      // in the right subtree) 
      typename AVL::Node* leaf = this->locate(p->right);
      // Copy the inorder successor's content to this node 
      p->key = leaf->key; 
      // Delete the inorder successor 
      p->right = remove(p->right, leaf->key); 
   }

   // If the tree had only one node then return  
   if ( !p ) return p;
  
   p->height = 1 + std::max(this->h(p->left), this->h(p->right));

   // Left Left Case
   if (balance(p) > 1 && balance(p->left) > 0)
      return rotate_right(p);

   // Right Right Case
   if (balance(p) < -1 && balance(p->right) < 0)
      return rotate_left(p);

   // Left Right Case
   if (balance(p) > 1 && balance(p->left) < 0) {
      p->left = rotate_left(p->left);
      return rotate_right(p);
   }

   // Right Left Case
   if (balance(p) < -1 && balance(p->right) > 0) {
      p->right = rotate_right(p->right);
      return rotate_left(p);
   }  

   return p;    
}

template<class Type> 
typename AVL<Type>::Node* AVL<Type>::rotate_left(typename AVL::Node* p)
{
   typename AVL::Node* q = p->right;
   typename AVL::Node* localtemp = q->left;

   q->left = p;
   p->right = localtemp;

   p->height = std::max(this->h(p->left), this->h(p->right)) + 1;
   q->height = std::max(this->h(q->left), this->h(q->right)) + 1;

   return q;
}

template<class Type> 
typename AVL<Type>::Node* AVL<Type>::rotate_right(typename AVL::Node* p)
{
   typename AVL::Node* q = p->left;
   typename AVL::Node* localtemp = q->right;

   q->right = p;
   p->left = localtemp;

   p->height = std::max(this->h(p->left), this->h(p->right)) + 1;
   q->height = std::max(this->h(q->left), this->h(q->right)) + 1;

   return q;
}

template<class Type> 
int AVL<Type>::balance(const typename AVL::Node* node) const
{
   if ( !node ) return 0;
   return this->h(node->left) - this->h(node->right);
}

#endif
