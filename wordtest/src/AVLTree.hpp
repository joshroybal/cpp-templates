// AVLTree balanced binary search tree
// iterative implementations
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

template<class Type> 
class AVLTree
{
   public:
      AVLTree() : root(0) {}
      ~AVLTree();
		int Height() const;
      int Size() const;
      Type Min() const;
      Type Max() const;
      void Search(const Type&) const;
      void Insert(const Type&);
      void Remove(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
   private:
      struct Node;
      Node* root;
      int node_height(const Node*) const;
      int balance_factor(const Node*) const;
		int h(const Node*) const;
      int size(const Node*) const;
      Type minimum(const Node*) const;
      Type maximum(const Node*) const;
      Node* search(Node*, const Type&) const;
      Node* insert(Node*, const Type&);
      Node* rotate_left(Node*);
      Node* rotate_right(Node*);
      Node* locate(Node*) const;
      Node* remove(Node*, const Type&);
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::ifstream&, Node*);
      void destroy(Node*);
};

template<class Type> 
struct AVLTree<Type>::Node
{  
   Type key;
   int bal_no;
   int height;
   Node* left;
   Node* right;
   Node(const Type& key) : key(key), left(0), right(0), bal_no(0), height(0) {}
   Node(const Type& key, int bn) : key(key), left(0), right(0), bal_no(bn), 
      height(0) {}
};

// class destructor
template<class Type> 
AVLTree<Type>::~AVLTree()
{
   destroy(root);
}

// template class public accessor methods

template<class Type> 
int AVLTree<Type>::Height() const
{
	return h(root);
}

template<class Type>
int AVLTree<Type>::Size() const
{
   return size(root);
}

template<class Type>
Type AVLTree<Type>::Min() const
{
   return minimum(root);
}

template<class Type>
Type AVLTree<Type>::Max() const
{
   return maximum(root);
}

template<class Type>
void AVLTree<Type>::Search(const Type& key) const
{
   Node* node = search(root, key);

   if ( node ) std::cout << "key = " << node->key << std::endl;
   else std::cout << "key not found" << std::endl;
}
   
template<class Type> 
void AVLTree<Type>::Insert(const Type& key)
{
   root = insert(root, key);
}

template<class Type> 
void AVLTree<Type>::Remove(const Type& key)
{
   root = remove(root, key);
}

template<class Type> 
void AVLTree<Type>::PreOrder() const
{
   preorder(root);
}

template<class Type> 
void AVLTree<Type>::InOrder() const
{
   inorder(root);
}

template<class Type> 
void AVLTree<Type>::PostOrder() const
{
   postorder(root);
}

template<class Type> 
void AVLTree<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ofstream::out);
   serialize(ofstr, root);
   ofstr.close();
}

template<class Type> 
void AVLTree<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ifstream::in);
   root = deserialize(ifstr, root);
   ifstr.close();
}

// template class private methods
template<class Type>
int AVLTree<Type>::node_height(const Node* p) const
{
   if ( !p ) return -1;
   return p->height;
}

template<class Type>
int AVLTree<Type>::balance_factor(const Node* p) const
{
   return node_height(p->left) - node_height(p->right);
}

template<class Type> 
int AVLTree<Type>::h(const Node* p) const
{
   if ( !p ) return -1;

   int hl = h(p->left);
   int hr = h(p->right);

   if ( hl > hr ) return 1 + hl;
   else return 1 + hr;
}

template<class Type>
int AVLTree<Type>::size(const Node* p) const
{
   if ( !p ) return 0;
   return 1 + size(p->left) + size(p->right);
}

template<class Type>
Type AVLTree<Type>::minimum(const Node* p) const
{
   if ( p->left == 0 ) return p->key;
   return minimum(p->left);
}

template<class Type>
Type AVLTree<Type>::maximum(const Node* p) const
{
   if ( p->right == 0 ) return p->key;
   return maximum(p->right);
}

template<class Type>
typename AVLTree<Type>::Node* AVLTree<Type>::search(Node* p, const Type& key) const
{
   if ( !p ) return p;

   if ( key < p->key )
      return search(p->left, key);
   else if ( key > p->key )
      return search(p->right, key);
   else
      return p;
}

template<class Type>
typename AVLTree<Type>::Node* AVLTree<Type>::insert(Node* p, const Type& key)
{
   if ( !p ) return new Node(key);

   if (key < p->key) 
      p->left = insert(p->left, key);
   else if (key > p->key) 
      p->right = insert(p->right, key);
   else 
      return p;

   p->height = 1 + std::max(node_height(p->left), node_height(p->right));
   p->bal_no = balance_factor(p);

   // Left Left Case
   if (p->bal_no > 1 && p->left->bal_no > 0)
      return rotate_right(p);

   // Right Right Case
   if (p->bal_no < -1 && p->right->bal_no < 0)
      return rotate_left(p);

   // Left Right Case
   if (p->bal_no > 1 && p->left->bal_no < 0) {
      p->left = rotate_left(p->left);
      return rotate_right(p);
   }

   // Right Left Case
   if (p->bal_no < -1 && p->right->bal_no > 0) {
      p->right = rotate_right(p->right);
      return rotate_left(p);
   }

   // return the (unchanged) node pointer
   return p;
}

template<class Type> 
typename AVLTree<Type>::Node* AVLTree<Type>::rotate_left(Node* p)
{
   Node* q = p->right;
   Node* localtemp = q->left;

   q->left = p;
   p->right = localtemp;

   p->height = std::max(h(p->left), h(p->right)) + 1;
   q->height = std::max(h(q->left), h(q->right)) + 1;   

   return q;
}

template<class Type> 
typename AVLTree<Type>::Node* AVLTree<Type>::rotate_right(Node* p)
{
   Node* q = p->left;
   Node* localtemp = q->right;

   q->right = p;
   p->left = localtemp;

   p->height = std::max(h(p->left), h(p->right)) + 1;
   q->height = std::max(h(q->left), h(q->right)) + 1;
   
   return q;
}

template<class Type> 
typename AVLTree<Type>::Node* AVLTree<Type>::locate(Node* p) const
{
   while (p->left) p = p->left;
   return p;
}

template<class Type> 
typename AVLTree<Type>::Node* AVLTree<Type>::remove(Node* p, const Type& key)
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

   // AVLTree maintenance section
   // If the tree had only one node then return  
   if ( !p ) return p;
  

   p->height = 1 + std::max(node_height(p->left), node_height(p->right));
   p->bal_no = balance_factor(p);
  
   // If this node becomes unbalanced, then there are four cases  
   // Left Left Case
   if (p->bal_no > 1 && p->left->bal_no > 0)
      return rotate_right(p);

   // Right Right Case
   if (p->bal_no < -1 && p->right->bal_no < 0)
      return rotate_left(p);

   // Left Right Case
   if (p->bal_no > 1 && p->left->bal_no < 0) {
      p->left = rotate_left(p->left);
      return rotate_right(p);
   }

   // Right Left Case
   if (p->bal_no < -1 && p->right->bal_no > 0) {
      p->right = rotate_right(p->right);
      return rotate_left(p);
   }  

   return p;    
}

template<class Type>
void AVLTree<Type>::preorder(const Node* p) const
{  
   if ( !p ) return;
   std::cout << p->key << std::endl;
   preorder(p->left);
   preorder(p->right);
}

template<class Type>
void AVLTree<Type>::inorder(const Node* p) const
{
   if ( !p ) return;
   inorder(p->left);
   std::cout << p->key << std::endl;
   inorder(p->right);
}

template<class Type>
void AVLTree<Type>::postorder(const Node* p) const
{
   if ( !p ) return;
   postorder(p->left);
   postorder(p->right);
   std::cout << p->key << std::endl;
}

// pre-order
template<class Type>
void AVLTree<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   if ( !p ) {
      ofstr << "(null)" << std::endl;  
      return;
   }
   ofstr << p->key << ' ' << p->bal_no << std::endl;
   serialize(ofstr, p->left);
   serialize(ofstr, p->right);   
}

// pre-order
template<class Type>
typename AVLTree<Type>::Node* AVLTree<Type>::deserialize(std::ifstream& ifstr, Node* p)
{
   std::string key;
   if ( ifstr >> key && key != "(null)") {
      Type y;
      std::istringstream isstr(key);
      isstr >> y;
      int bn;
      ifstr >> bn;
      p = new Node(y, bn);
      p->left = deserialize(ifstr, p->left);
      p->right = deserialize(ifstr, p->right);
   }
   return p;
}

// pre-order
template<class Type> 
void AVLTree<Type>::destroy(Node* p)
{
   if ( !p ) return;
   destroy(p->left);
   destroy(p->right);
   delete p;
}

#endif
