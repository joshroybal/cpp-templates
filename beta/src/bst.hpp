// binary search tree
// iterative implementations
#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>

template<class Type> class BST
{
   public:
      BST() : root(0) {}
      ~BST();
		int Height() const;
      void Insert(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
		void LevelOrder() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
   protected:
      struct Node;
      Node* root;
      void destroy(Node*);
		int h(const Node*) const;
      Node* insert(Node*, const Type&);
      Node* rotate_left(Node*);
      Node* rotate_right(Node*);
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void levelorder(const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::ifstream&, Node*);
};

template<class Type> struct BST<Type>::Node
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

template<class Type> int BST<Type>::Height() const
{
	return h(root);
}

template<class Type> void BST<Type>::Insert(const Type& key)
{
   root = insert(root, key);
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

template<class Type> void BST<Type>::LevelOrder() const
{
	levelorder(root);
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

// template class private methods
template<class Type>
void BST<Type>::destroy(Node* p)
{
   if ( !p ) return; // nothing to do

   std::stack<Node*> treestack;
   treestack.push(p);
   while ( !treestack.empty() ) {
      Node* node = treestack.top();      
      treestack.pop();
      if (node->right) treestack.push(node->right);
      if (node->left) treestack.push(node->left);
      delete node;
   }
}

template<class Type> int BST<Type>::h(const Node* p) const
{
   if ( !p ) return -1;
   return p->height;

   /*
   // Base Case 
   if (!p) return -1; 
  
   // create an empty queue for level order tarversal 
   std::queue<const Node*> q; 
  
   // queue up root and initialize height 
   q.push(p); 
   int height = 0;
  
   while ( true ) { 
      // n (queue size) indicates number of nodes at current lelvel. 
      int n = q.size(); 
      if (n == 0) return height;
  
      height++; 
  
      // dequeue current level nodes and enqueue next level nodes
      while (n > 0) { 
         const Node* node = q.front();
         q.pop();
         if ( node->left ) q.push(node->left); 
         if ( node->right ) q.push(node->right); 
         n--;
      } 
   }    
   */
}

template<class Type>
typename BST<Type>::Node* BST<Type>::insert(Node* p, const Type& key)
{
   Node* curr = p;
   Node* prev = 0;
   while (curr) {
      prev = curr;
      if (key < curr->key) curr = curr->left;
      else if (key > curr->key) curr = curr->right;
      else return p; // ignore duplicates
   }

   if ( !prev ) return new Node(key);

   if (key < prev->key) prev->left = new Node(key);
   else if (key > prev->key) prev->right = new Node(key);
   else return p; // ignore duplicates

   // prev->height = 1 + std::max(h(prev->left), h(prev->right));

   return p;
}

template<class Type>
void BST<Type>::preorder(const Node* p) const
{  
   if (p == 0) return;  // inductive basis
   std::stack<const Node*> treestack;
   treestack.push(p);
   while ( !treestack.empty() ) {
      const Node* node = treestack.top();      
      std::cout << node->key << std::endl;
      treestack.pop();
      if (node->right) treestack.push(node->right);
      if (node->left) treestack.push(node->left);
   }
}

template<class Type>
void BST<Type>::inorder(const Node* p) const
{
   if (p == 0) return;  // inductive basis
   std::stack<const Node*> treestack;
   const Node* node = p;
   while (node || !treestack.empty() ) {
      while (node) {
         treestack.push(node);
         node = node->left;
      }
      node = treestack.top();
      treestack.pop();
      std::cout << node->key << std::endl;
      node = node->right;
   }
}

template<class Type>
void BST<Type>::postorder(const Node* p) const
{
   if (p == 0) return;
   std::stack<const Node*> treestack;
   const Node* curr = p;
   while (true) {
      if ( curr ) {
         if ( curr->right ) treestack.push(curr->right);
         treestack.push(curr);
         curr = curr->left;
         continue;
      }
      if ( treestack.empty() ) return;
      curr = treestack.top();
      treestack.pop();
      if ( curr->right && !treestack.empty() 
            && curr->right == treestack.top() ) {
         treestack.pop();
         treestack.push(curr);
         curr = curr->right;
      } else {
         std::cout << curr->key << std::endl;
         curr = 0;
      }
   }
}

template<class Type> void BST<Type>::levelorder(const Node* p) const
{
	std::queue<const Node*> levelqueue;

	levelqueue.push(p);
	int l = 1;
	while (!levelqueue.empty()) {
		const Node* node = levelqueue.front();
		levelqueue.pop();
		std::cout << node->key << std::endl;
		if (node->left) levelqueue.push(node->left);
		if (node->right) levelqueue.push(node->right);
	}	
}

// pre-order
template<class Type>
void BST<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   if ( !p ) return;
   std::queue<const Node*> q;
   q.push(p);
   while ( !q.empty() ) {
      const Node* node = q.front();
      q.pop();
      if (node) {
         ofstr << node->key << std::endl;
         q.push(node->left);
         q.push(node->right);
      } else {
         ofstr << "(null)" << std::endl;
      }
   }
}

// pre-order (actually deserializes to level order ??)
template<class Type>
typename BST<Type>::Node* BST<Type>::deserialize(std::ifstream& ifstr, Node* p)
{   
   int bn;
   std::queue<Node*> q;
   std::string key;
   Type y;

   ifstr >> key;
   std::istringstream isstr(key);
   isstr >> y;
   p = new Node(y);
   Node* cur = p;
   q.push(cur);
   while ( !q.empty() ) {
      Node* node = q.front();
      q.pop();
      if ( !(ifstr >> key) ) break;
      if ( key != "(null)" ) {
         std::istringstream isstr(key);
         isstr >> y;
         cur = new Node(y);
         q.push(cur);
         node->left = cur;
      }
      if ( !(ifstr >> key ) ) break;
      if ( key != "(null)" ) {
         std::istringstream isstr(key);
         isstr >> y;
         cur = new Node(y);
         q.push(cur);
         node->right = cur;
      }
   }
   return p;
}

#endif
