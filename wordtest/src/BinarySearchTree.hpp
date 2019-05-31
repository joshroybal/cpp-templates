// binary search tree
// recursive implementations
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
// #include <cstdlib>

template<class Type> 
class BinarySearchTree
{
   public:
      BinarySearchTree() : root(0) {}
      ~BinarySearchTree();
      void Insert(const Type&);
      void Remove(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
      int Height() const;
   protected:
      struct Node;
      Node* root;
      void destroy(Node*);
      int h(const Node*) const;
      Node* insert(Node*, const Type&);
      Node* locate(Node*) const;
      Node* remove(Node*, const Type&);
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::ifstream&, Node*);
};

template<class Type> 
struct BinarySearchTree<Type>::Node
{  
   Type key;
   Node* left;
   Node* right;
   Node(const Type& key) : key(key), left(0), right(0) {}
};

// class destructor
template<class Type> 
BinarySearchTree<Type>::~BinarySearchTree()
{
   destroy(root);
}

// template class public accessor methods
template<class Type> void 
BinarySearchTree<Type>::Insert(const Type& key)
{
   root = insert(root, key);
}

template<class Type> 
void BinarySearchTree<Type>::Remove(const Type& key)
{
   root = remove(root, key);
}

template<class Type> 
void BinarySearchTree<Type>::PreOrder() const
{
   preorder(root);
}

template<class Type> 
void BinarySearchTree<Type>::InOrder() const
{
   inorder(root);
}

template<class Type> 
void BinarySearchTree<Type>::PostOrder() const
{
   postorder(root);
}

template<class Type> 
void BinarySearchTree<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ofstream::out);
   serialize(ofstr, root);
   ofstr.close();
}

template<class Type> 
void BinarySearchTree<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ifstream::in);
   root = deserialize(ifstr, root);
   ifstr.close();
}

template<class Type> 
int BinarySearchTree<Type>::Height() const
{
   return h(root);
}

// template class protected methods
template<class Type>
void BinarySearchTree<Type>::destroy(Node* p)
{
   if ( !p ) return;
   destroy(p->left);
   destroy(p->right);
   delete p;
}

template<class Type> 
int BinarySearchTree<Type>::h(const Node* p) const
{
   if ( !p ) return -1;

   int hl = h(p->left);
   int hr = h(p->right);

   if ( hl > hr ) return 1 + hl;
   else return 1 + hr;   
}

template<class Type> 
typename BinarySearchTree<Type>::Node* BinarySearchTree<Type>::insert(Node* p, const Type& key)
{  
   if (p == 0) return new Node(key);
   if (key < p->key)  p->left = insert(p->left, key);
   else if (key > p->key) p->right = insert(p->right, key);
   return p;
}

template<class Type> 
typename BinarySearchTree<Type>::Node* BinarySearchTree<Type>::locate(Node* p) const
{
   /* recurse down to find the leftmost leaf */
   if (p->left != 0) p = locate(p->left);
   return p; 
}

template<class Type> 
typename BinarySearchTree<Type>::Node* BinarySearchTree<Type>::remove(Node* p, const Type& key)
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
         Node* leaf = p->right;
         delete p;
         return leaf; 
      } else if (p->right == NULL) { 
         Node* leaf = p->left;
         delete p;
         return leaf; 
      } 
      // node with two children: Get the inorder successor (smallest 
      // in the right subtree) 
      Node* leaf = locate(p->right);
      // Copy the inorder successor's content to this node 
      p->key = leaf->key; 
      // Delete the inorder successor 
      p->right = remove(p->right, leaf->key); 
   } 
   return p;    
}

template<class Type>
void BinarySearchTree<Type>::preorder(const Node* p) const
{
   if (p == 0) return;
   std::cout << p->key << std::endl;
   preorder(p->left);
   preorder(p->right);
}

template<class Type>
void BinarySearchTree<Type>::inorder(const Node* p) const
{
   if (p == 0) return;
   inorder(p->left);
   std::cout << p->key << std::endl;
   inorder(p->right);
}

template<class Type>
void BinarySearchTree<Type>::postorder(const Node* p) const
{
   if (p == 0) return;
   postorder(p->left);
   postorder(p->right);
   std::cout << p->key << std::endl;
}

template<class Type>
void BinarySearchTree<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   if (p == 0) {
      ofstr << "(null)" << std::endl;  
      return;
   }
   ofstr << p->key << std::endl;
   serialize(ofstr, p->left);
   serialize(ofstr, p->right);
}

template<class Type>
typename BinarySearchTree<Type>::Node* BinarySearchTree<Type>::deserialize(std::ifstream& ifstr, Node* p)
{
   std::string key;
   if ( ifstr >> key && key != "(null)") {
      Type y;
      std::istringstream isstr(key);
      isstr >> y;
      p = new Node(y);
      p->left = deserialize(ifstr, p->left);
      p->right = deserialize(ifstr, p->right);
   }
   return p;
}

#endif
