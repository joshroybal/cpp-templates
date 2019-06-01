// binary search tree
// recursive implementations
#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>

template <class Type> 
class AVL
{
   public:
      AVL() : root(0) {}
      ~AVL();
      void Search(const Type&) const;
      void Min() const;
      void Max() const;
      void Insert(const Type&);
      void Remove(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
      void LevelOrder() const;
      void Serialize(std::stringstream&) const;
      void Serialize(const std::string&) const;
      void Deserialize(std::stringstream&);
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
      Node* rotate_left(Node*);
      Node* rotate_right(Node*);
      Node* remove(Node*, const Type&);
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void levelorder(const Node*) const;
      void serialize(std::stringstream&, const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::stringstream&, Node*);
      Node* deserialize(std::ifstream&, Node*);
      int h(const Node*) const;
      int size(const Node*) const;
      int balance(const Node*) const;
      void print_node(const Node*) const;
};

template <class Type> 
struct AVL<Type>::Node
{  
   Type key;
   int height;
   Node* left;
   Node* right;
   Node(const Type& _key) : key(_key), height(0), left(0), right(0) {}
};

// class destructor
template <class Type> 
AVL<Type>::~AVL()
{
   destroy(root);
}

// template class public accessor methods
template <class Type>
void AVL<Type>::Search(const Type& key) const
{
   Node* target = search(root, key);
   if ( target ) std::cout << target->key << std::endl;
   else std::cout << "key not found in binary search tree" << std::endl;
}

template <class Type>
void AVL<Type>::Min() const
{
   Node* minNode = min(root);
   if ( minNode ) std::cout << "min = " << minNode->key << std::endl;
   else std::cout << "empty tree" << std::endl;
}

template <class Type>
void AVL<Type>::Max() const
{
   Node* maxNode = max(root);
   if ( maxNode ) std::cout << "max = " << maxNode->key << std::endl;
   else std::cout << "empty tree" << std::endl;
}

template <class Type> 
void AVL<Type>::Insert(const Type& key)
{
   root = insert(root, key);
}

template <class Type> 
void AVL<Type>::Remove(const Type& key)
{
   root = remove(root, key);
}

template <class Type> 
void AVL<Type>::PreOrder() const
{
   preorder(root);
}

template <class Type> 
void AVL<Type>::InOrder() const
{
   inorder(root);
}

template <class Type> 
void AVL<Type>::PostOrder() const
{
   postorder(root);
}

template <class Type> 
void AVL<Type>::LevelOrder() const
{
   levelorder(root);
}

template <class Type> 
void AVL<Type>::Serialize(std::stringstream& internalFile) const
{
   serialize(internalFile, root);
}

template <class Type> 
void AVL<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ofstream::out);
   serialize(ofstr, root);
   ofstr.close();
}

template <class Type>
void AVL<Type>::Deserialize(std::stringstream& internalFile)
{
   root = deserialize(internalFile, root);
}

template <class Type> 
void AVL<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ifstream::in);
   root = deserialize(ifstr, root);
   ifstr.close();
}

template <class Type> 
int AVL<Type>::Height() const
{
   return h(root);
}

template <class Type>
int AVL<Type>::Size() const
{
   return size(root);
}

// template class private methods
template <class Type>
void AVL<Type>::destroy(Node*& p)
{
   if ( !p ) return;
   destroy(p->left);
   destroy(p->right);
   delete p;
}

template <class Type>
typename AVL<Type>::Node* AVL<Type>::search(Node* p, const Type& key) const
{
   if ( !p ) return 0;

   if (key < p->key) return search(p->left, key);
   else if (key > p->key) return search(p->right, key);
   else return p;
}

template <class Type>
typename AVL<Type>::Node* AVL<Type>::min(Node* p) const
{
   if ( !p ) return 0;
   if ( p->left == 0 ) return p;
   return min(p->left);
}

template <class Type>
typename AVL<Type>::Node* AVL<Type>::max(Node* p) const
{
   if ( !p ) return 0;
   if ( p->right == 0 ) return p;
   return max(p->right);
}

template <class Type> 
typename AVL<Type>::Node* AVL<Type>::insert(Node* p, const Type& key)
{  
   if ( !p ) return new Node(key);
   
   if (key < p->key)  p->left = insert(p->left, key);
   else if (key > p->key) p->right = insert(p->right, key);
   else return p; // define no duplicates in binary search tree

   p->height = 1 + std::max(h(p->left), h(p->right));

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

template <class Type> 
typename AVL<Type>::Node* AVL<Type>::rotate_left(Node* p)
{
   Node* q = p->right;
   Node* localtemp = q->left;

   q->left = p;
   p->right = localtemp;

   p->height = 1 + std::max(h(p->left), h(p->right));
   q->height = 1 + std::max(h(q->left), h(q->right));

   return q;
}

template <class Type> 
typename AVL<Type>::Node* AVL<Type>::rotate_right(Node* p)
{
   Node* q = p->left;
   Node* localtemp = q->right;

   q->right = p;
   p->left = localtemp;

   p->height = 1 + std::max(h(p->left), h(p->right));
   q->height = 1 + std::max(h(q->left), h(q->right));   

   return q;
}

template <class Type> 
typename AVL<Type>::Node* AVL<Type>::remove(Node* p, const Type& key)
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
         Node* node = p->right;
         delete p;
         return node; 
      } else if (p->right == NULL) { 
         Node* node = p->left;
         delete p;
         return node; 
      } 
      Node* node = max(p->left);
      p->key = node->key;
      p->left = remove(p->left, node->key);
      /*
      Node* node = min(p->right);
      p->key = node->key;
      p->right = remove(p->right, node->key);
      */
   }

   // If the tree had only one node then return  
   if ( !p ) return p;

   p->height = 1 + std::max(h(p->left), h(p->right));

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

template <class Type>
void AVL<Type>::preorder(const Node* p) const
{
   if (p == 0) return;
   print_node(p);
   preorder(p->left);
   preorder(p->right);
}

template <class Type>
void AVL<Type>::inorder(const Node* p) const
{
   if (p == 0) return;
   inorder(p->left);
   print_node(p);
   inorder(p->right);
}

template <class Type>
void AVL<Type>::postorder(const Node* p) const
{
   if (p == 0) return;
   postorder(p->left);
   postorder(p->right);
   print_node(p);
}

template <class Type> 
void AVL<Type>::levelorder(const Node* p) const
{
	if ( !p ) return;
   
   std::queue<const Node*> levelqueue;

	levelqueue.push(p);
	int l = 1;
	while (!levelqueue.empty()) {
		const Node* node = levelqueue.front();
		levelqueue.pop();
		print_node(node);
      if (node->left) levelqueue.push(node->left);
		if (node->right) levelqueue.push(node->right);
	}	
}

// pre-order
template <class Type>
void AVL<Type>::serialize(std::stringstream& internalFile, const Node* p) const
{
   if ( !p ) {
      internalFile << "# ";
      return;
   }

   internalFile << p->key << ' ';
   serialize(internalFile, p->left);
   serialize(internalFile, p->right);
}

// pre-order
template <class Type>
void AVL<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   if (p == 0) {
      ofstr << "# ";  
      return;
   }
   ofstr << p->key << ' ';
   serialize(ofstr, p->left);
   serialize(ofstr, p->right);
}

// de-serialize from internal file (stringstream)
template <class Type>
typename AVL<Type>::Node* AVL<Type>::deserialize
(std::stringstream& internalFile, Node* p)
{
   std::string str;
   if ( internalFile >> str && str != "#" ) {
      std::istringstream isstr(str);
      Type key;
      isstr >> key;
      p = new Node(key);
      p->left = deserialize(internalFile, p->left);
      p->right = deserialize(internalFile, p->right);
      p->height = 1 + std::max(h(p->left), h(p->right));
   }
   return p;
}

// de-serialize from external file (ifstream)
template <class Type>
typename AVL<Type>::Node* AVL<Type>::deserialize(std::ifstream& ifstr, Node* p)
{
   std::string str;
   if ( ifstr >> str && str != "#") {
      std::istringstream isstr(str);
      Type key;
      isstr >> key;
      p = new Node(key);
      p->left = deserialize(ifstr, p->left);
      p->right = deserialize(ifstr, p->right);
      p->height = 1 + std::max(h(p->left), h(p->right));
   }
   return p;
}

template <class Type> 
int AVL<Type>::h(const Node* p) const
{
   if ( !p ) return -1;
   return p->height;
}

template <class Type>
int AVL<Type>::size(const Node* p) const
{
   if ( !p ) return 0;
   return 1 + size(p->left) + size(p->right);
}

template <class Type>
int AVL<Type>::balance(const Node* p) const
{
   if ( !p ) return 0;
   return h(p->left) - h(p->right);
}

template <class Type>
void AVL<Type>::print_node(const Node* p) const
{
   // short form
   std::cout << p->key << ' ';
   // long form
   // std::cout << p->key << ' ';
   // std::cout << p->height << ' ';
   // std::cout << balance(p) << std::endl;
}

#endif
