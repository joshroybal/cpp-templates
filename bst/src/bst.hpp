// binary search tree
// recursive implementations
#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

template<class Type> class BST
{
   public:
      BST() : root(0) {}
      ~BST();
      void Insert(const Type&);
      void Remove(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
      int Height() const;
   private:
      struct Node;
      Node* root;
      Node* insert(Node*, const Type&);
      Node* locate(Node*) const;
      Node* remove(Node*, const Type&);
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::ifstream&, Node*);
      Node* defoliate(Node*);
      int h(const Node*) const;
};

template<class Type> struct BST<Type>::Node
{  
   Type data;
   Node* left;
   Node* right;
   Node(const Type& x) : data(x), left(0), right(0) {}
};

// class destructor
template<class Type> BST<Type>::~BST()
{
   root = defoliate(root);
}

// template class public accessor methods
template<class Type> void BST<Type>::Insert(const Type& x)
{
   root = insert(root, x);
}

template<class Type> void BST<Type>::Remove(const Type& x)
{
   root = remove(root, x);
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

// template class private methods

template<class Type> 
typename BST<Type>::Node* BST<Type>::insert(Node* p, const Type& x)
{  
   if (p == 0) return new Node(x);
   if (x < p->data)  p->left = insert(p->left, x);
   else if (x > p->data) p->right = insert(p->right, x);
   return p;
}

template<class Type> 
typename BST<Type>::Node* BST<Type>::locate(Node* p) const
{
   /* recurse down to find the leftmost leaf */
   if (p->left != 0) p = locate(p->left);
   return p; 
}

template<class Type> 
typename BST<Type>::Node* BST<Type>::remove(Node* p, const Type& x)
{
   if (p == 0) return p;
   // If the key to be deleted is smaller than the root's key, 
   // then it lies in left subtree 
   if (x < p->data) p->left = remove(p->left, x); 
   // If the key to be deleted is greater than the root's key, 
   // then it lies in right subtree 
   else if (x > p->data) p->right = remove(p->right, x); 
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
      p->data = leaf->data; 
      // Delete the inorder successor 
      p->right = remove(p->right, leaf->data); 
   } 
   return p;    
}

template<class Type>
void BST<Type>::preorder(const Node* p) const
{
   if (p == 0) return;
   std::cout << p->data << std::endl;
   preorder(p->left);
   preorder(p->right);
}

template<class Type>
void BST<Type>::inorder(const Node* p) const
{
   if (p == 0) return;
   inorder(p->left);
   std::cout << p->data << std::endl;
   inorder(p->right);
}

template<class Type>
void BST<Type>::postorder(const Node* p) const
{
   if (p == 0) return;
   postorder(p->left);
   postorder(p->right);
   std::cout << p->data << std::endl;
}

template<class Type>
typename BST<Type>::Node* BST<Type>::defoliate(Node* p)
{
   if ( !p ) return p;
   p->left = defoliate(p->left);
   p->right = defoliate(p->right);
   delete p;
}

template<class Type>
void BST<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   if (p == 0) {
      ofstr << "(null)" << std::endl;  
      return;
   }
   ofstr << p->data << std::endl;
   serialize(ofstr, p->left);
   serialize(ofstr, p->right);
}

template<class Type>
typename BST<Type>::Node* BST<Type>::deserialize(std::ifstream& ifstr, Node* p)
{
   std::string x;
   if ( ifstr >> x && x != "(null)") {
      Type y;
      std::istringstream isstr(x);
      isstr >> y;
      p = new Node(y);
      p->left = deserialize(ifstr, p->left);
      p->right = deserialize(ifstr, p->right);
   }
   return p;
}

template<class Type> int BST<Type>::h(const Node* p) const
{
   if ( !p ) return -1;

   int hl = h(p->left);
   int hr = h(p->right);

   if ( hl > hr ) return 1 + hl;
   else return 1 + hr;   
}

#endif
