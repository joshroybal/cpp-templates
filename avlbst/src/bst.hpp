// binary search tree
// recursive implementations
#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

template<class Type> 
class BST
{
   public:
      BST() : root(0) {}
      ~BST();
      void Search(const Type&) const;
      void Min() const;
      void Max() const;
      void Insert(const Type&);
      void Remove(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
      int Height() const;
      int Size() const;
   protected:
      struct Node;
      Node* root;
      void destroy(Node*&);
      Node* search(Node*, const Type&) const;
      Node* min(Node*) const;
      Node* max(Node*) const;
      Node* insert(Node*, const Type&);
      Node* locate(Node*) const;
      Node* remove(Node*, const Type&);
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::ifstream&, Node*);
      int h(const Node*) const;
      int size(const Node*) const;
};

template<class Type> 
struct BST<Type>::Node
{  
   Type key;
   int height;
   Node* left;
   Node* right;
   Node(const Type& _key) : key(_key), height(0), left(0), right(0) {}
};

// class destructor
template<class Type> BST<Type>::~BST()
{
   destroy(root);
}

// template class public accessor methods
template<class Type>
void BST<Type>::Search(const Type& key) const
{
   Node* target = search(root, key);
   if ( target ) std::cout << target->key << std::endl;
   else std::cout << "key not found in binary search tree" << std::endl;
}

template<class Type>
void BST<Type>::Min() const
{
   Node* minNode = min(root);
   if ( minNode ) std::cout << minNode->key << std::endl;
}

template<class Type>
void BST<Type>::Max() const
{
   Node* maxNode = max(root);
   if ( maxNode ) std::cout << maxNode->key << std::endl;
}

template<class Type> void BST<Type>::Insert(const Type& key)
{
   root = insert(root, key);
}

template<class Type> void BST<Type>::Remove(const Type& key)
{
   root = remove(root, key);
}

template<class Type> void BST<Type>::PreOrder() const
{
   preorder(root);
}

template<class Type> void BST<Type>::InOrder() const
{
   inorder(root);
}

template<class Type> void BST<Type>::PostOrder() const
{
   postorder(root);
}

template<class Type> 
void BST<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ofstream::out);
   serialize(ofstr, root);
   ofstr.close();
}

template<class Type> void BST<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ifstream::in);
   root = deserialize(ifstr, root);
   ifstr.close();
}

template<class Type> int BST<Type>::Height() const
{
   return h(root);
}

template<class Type>
int BST<Type>::Size() const
{
   return size(root);
}

// template class private methods
template<class Type>
void BST<Type>::destroy(Node*& p)
{
   if ( !p ) return;
   destroy(p->left);
   destroy(p->right);
   delete p;
}

template<class Type>
typename BST<Type>::Node* BST<Type>::search(Node* p, const Type& key) const
{
   if ( !p ) return 0;

   if (key < p->key) return search(p->left, key);
   else if (key > p->key) return search(p->right, key);
   else return p;
}

template<class Type>
typename BST<Type>::Node* BST<Type>::min(Node* p) const
{
   if ( !p ) return 0;
   if ( p->left == 0 ) return p;
   return min(p->left);
}

template<class Type>
typename BST<Type>::Node* BST<Type>::max(Node* p) const
{
   if ( !p ) return 0;
   if ( p->right == 0 ) return p;
   return max(p->right);
}

template<class Type> 
typename BST<Type>::Node* BST<Type>::insert(Node* p, const Type& key)
{  
   if ( !p ) return new Node(key);
   
   if (key < p->key)  p->left = insert(p->left, key);
   else if (key > p->key) p->right = insert(p->right, key);
   else return p; // define no duplicates in binary search tree

   p->height = 1 + std::max(h(p->left), h(p->right));

   return p;   // do not fall off the edge into undefined behavior 
}

template<class Type> 
typename BST<Type>::Node* BST<Type>::locate(Node* p) const
{
   /* recurse down to find the leftmost leaf */
   if (p->left != 0) p = locate(p->left);
   return p; 
}

template<class Type> 
typename BST<Type>::Node* BST<Type>::remove(Node* p, const Type& key)
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
void BST<Type>::preorder(const Node* p) const
{
   if (p == 0) return;
   std::cout << p->key << std::endl;
   preorder(p->left);
   preorder(p->right);
}

template<class Type>
void BST<Type>::inorder(const Node* p) const
{
   if (p == 0) return;
   inorder(p->left);
   std::cout << p->key << std::endl;
   inorder(p->right);
}

template<class Type>
void BST<Type>::postorder(const Node* p) const
{
   if (p == 0) return;
   postorder(p->left);
   postorder(p->right);
   std::cout << p->key << std::endl;
}

template<class Type>
void BST<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   if (p == 0) {
      ofstr << "(null)" << std::endl;  
      return;
   }
   ofstr << p->key << ' ' << p->height << std::endl;
   serialize(ofstr, p->left);
   serialize(ofstr, p->right);
}

template<class Type>
typename BST<Type>::Node* BST<Type>::deserialize(std::ifstream& ifstr, Node* p)
{
   std::string key;
   if ( ifstr >> key && key != "(null)") {
      Type y;
      std::istringstream isstr(key);
      isstr >> y;
      p = new Node(y);
      ifstr >> p->height;
      p->left = deserialize(ifstr, p->left);
      p->right = deserialize(ifstr, p->right);
   }
   return p;
}

template<class Type> 
int BST<Type>::h(const Node* p) const
{
   if ( !p ) return -1;
   return p->height;
}

template<class Type>
int BST<Type>::size(const Node* p) const
{
   if ( !p ) return 0;
   return 1 + size(p->left) + size(p->right);
}

#endif
