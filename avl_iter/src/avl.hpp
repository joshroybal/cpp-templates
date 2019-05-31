// AVL balanced binary search tree
// iterative implementations
#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>

template<class Type> class AVL
{
   public:
      AVL() : root(0) {}
      ~AVL();
		int Height() const;
      void Min() const;
      void Max() const;
      void Insert(const Type&);
      // void Remove(const Type&);
      void PreOrder() const;
      void InOrder() const;
      void PostOrder() const;
		void LevelOrder() const;
      void Serialize(std::stringstream&) const;
      void Serialize(const std::string&) const;
      void Deserialize(std::stringstream&);
      void Deserialize(const std::string&);
   private:
      struct Node;
      Node* root;
      void destroy(Node*);
		int h(const Node*) const;
      Type min() const;
      Type max() const;
      int height(const Node*) const;
      Node* insert(Node*, const Type&);
      Node* rotate_left(Node*);
      Node* rotate_right(Node*);
      int balance(const Node*) const;
      // Node* locate(Node*) const;
      // Node* remove(Node*, const Type&);   // recursive
      void preorder(const Node*) const;
      void inorder(const Node*) const;
      void postorder(const Node*) const;
      void levelorder(const Node*) const;
      void serialize(std::stringstream&, const Node*) const;
      void serialize(std::ofstream&, const Node*) const;
      Node* deserialize(std::stringstream&, Node*);
      Node* deserialize(std::ifstream&, Node*);
};

template<class Type> struct AVL<Type>::Node
{  
   Type key;
   int height;
   Node* left;
   Node* right;
   Node(const Type& x) : key(x), height(0), left(0), right(0) {}
   Node(const Type& x, int h) : key(x), height(0), left(0), right(0) {}
};

// class destructor
template<class Type> AVL<Type>::~AVL()
{
   destroy(root);
}

// template class public accessor methods
template<class Type> int AVL<Type>::Height() const
{
	return h(root);
}

template <class Type>
void AVL<Type>::Min() const
{
   if (root) std::cout << "min = " << min() << std::endl;
   else std::cout << "empty tree" << std::endl;
}

template <class Type>
void AVL<Type>::Max() const
{
   if (root) std::cout << "max = " << max() << std::endl;
   else std::cout << "empty tree" << std::endl;
}

template<class Type> void AVL<Type>::Insert(const Type& x)
{
   root = insert(root, x);
}

/*
template<class Type> void AVL<Type>::Remove(const Type& x)
{
   root = remove(root, x);
}
*/

template<class Type> void AVL<Type>::PreOrder() const
{
   preorder(root);
}

template<class Type> void AVL<Type>::InOrder() const
{
   inorder(root);
}

template<class Type> void AVL<Type>::PostOrder() const
{
   postorder(root);
}

template<class Type> void AVL<Type>::LevelOrder() const
{
	levelorder(root);
}

template<class Type> 
void AVL<Type>::Serialize(std::stringstream& internalFile) const
{
   serialize(internalFile, root);
}

template<class Type> 
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

template<class Type> 
void AVL<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ifstream::in);
   root = deserialize(ifstr, root);
   ifstr.close();
}

// template class private methods
template<class Type>
void AVL<Type>::destroy(Node* p)
{
   if ( !p ) return;  // inductive basis
   std::stack<Node*> treestack;
   treestack.push(p);
   while ( !treestack.empty() ) {
      Node* node = treestack.top();      
      treestack.pop();
      if (node->right) treestack.push(node->right);
      if (node->left) treestack.push(node->left);
      delete node;
   }
	return;
}

template<class Type> int AVL<Type>::h(const Node* p) const
{
   // Base Case 
   if (!p) return -1; 
  
   // create an empty queue for level order tarversal 
   std::queue<const Node*> q; 
  
   // queue up root and initialize height 
   q.push(p); 
   int height = -1;
  
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
}

template <class Type>
Type AVL<Type>::min() const
{
   Node* current = root;
   while ( current->left ) current = current->left;
   return current->key;
}

template <class Type>
Type AVL<Type>::max() const
{
   Node* current = root;
   while ( current->right ) current = current->right;
   return current->key;
}

template<class Type> 
int AVL<Type>::height(const Node* node) const
{
   if ( !node ) return -1;
   return node->height;
}

template<class Type>
typename AVL<Type>::Node* AVL<Type>::insert(Node* p, const Type& key)
{
   std::stack<Node*> path;
   Node* curr = p;
   Node* prev = 0;
   while (curr) {
      prev = curr;
      path.push(prev);
      if (key < curr->key) curr = curr->left;
      else if (key > curr->key) curr = curr->right;
      else return p; // ignore duplicates
   }

   if ( !prev ) return new Node(key);

   if (key < prev->key) prev->left = new Node(key);
   else if (key > prev->key) prev->right = new Node(key);
   else return p; // ignore duplicates

   while ( !path.empty() ) {
      Node* node = path.top();
      path.pop();
      node->height = 1 + std::max(height(node->left), height(node->right));
      Node* tag = node;

      // if (balance(node) >= -1 && balance(node) <= 1) continue;
      
      // Left Left Case  
      if (balance(node) > 1 && balance(node->left) > 0)
         node = rotate_right(node);  
      
      // Right Right Case  
      if (balance(node) < -1 && balance(node->right) < 0)
         node = rotate_left(node);  
     
      // Left Right Case  
      if (balance(node) > 1 && balance(node->left) < 0) {
         node->left = rotate_left(node->left);  
         node = rotate_right(node);  
      }
     
      // Right Left Case  
      if (balance(node) < -1 && balance(node->right) > 0) {
         node->right = rotate_right(node->right);  
         node = rotate_left(node);  
      }
      
      if ( !path.empty() ) {
         Node* parent = path.top();
         if (parent->left == tag) parent->left = node;
         else if (parent->right == tag) parent->right = node;
      } else {
         p = node;
      }
   }   
   
   return p;
}

template<class Type> typename AVL<Type>::Node* AVL<Type>::rotate_left(Node* p)
{
   Node* q = p->right;
   Node* localtemp = q->left;

   q->left = p;
   p->right = localtemp;

   p->height = 1 + std::max(h(p->left), h(p->right));
   q->height = 1 + std::max(h(q->left), h(q->right));

   return q;
}

template<class Type> typename AVL<Type>::Node* AVL<Type>::rotate_right(Node* p)
{
   Node* q = p->left;
   Node* localtemp = q->right;

   q->right = p;
   p->left = localtemp;

   p->height = 1 + std::max(h(p->left), h(p->right));
   q->height = 1 + std::max(h(q->left), h(q->right));   

   return q;
}

template<class Type> 
int AVL<Type>::balance(const Node* p) const
{
   if ( !p ) return 0;
   return height(p->left) - height(p->right);
}

/*
template<class Type> 
typename AVL<Type>::Node* AVL<Type>::locate(Node* p) const
{
   while (p->left) p = p->left;
   return p;
}

template<class Type> 
typename AVL<Type>::Node* AVL<Type>::remove(Node* p, const Type& x)
{
   if (p == 0) return p;
   // If the key to be deleted is smaller than the root's key, 
   // then it lies in left subtree 
   if (x < p->key) p->left = remove(p->left, x); 
   // If the key to be deleted is greater than the root's key, 
   // then it lies in right subtree 
   else if (x > p->key) p->right = remove(p->right, x); 
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
*/

template<class Type>
void AVL<Type>::preorder(const Node* p) const
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
void AVL<Type>::inorder(const Node* p) const
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
void AVL<Type>::postorder(const Node* p) const
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

template<class Type> void AVL<Type>::levelorder(const Node* p) const
{
	if ( !p ) return;
   
   std::queue<const Node*> levelqueue;

	levelqueue.push(p);
	int l = 1;
	while (!levelqueue.empty()) {
		const Node* node = levelqueue.front();
		levelqueue.pop();
		std::cout << node->key << ' ';
      std::cout << node->height << ' ';
      std::cout << balance(node) << std::endl;
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

// pre-order (level-order?)
template<class Type>
void AVL<Type>::serialize(std::ofstream& ofstr, const Node* p) const
{
   /*
   // pre-order serialization
   if ( !p ) return;

   std::stack<const Node*> treeStack;
   treeStack.push(p);

   while ( !treeStack.empty() ) {
      const Node* node = treeStack.top();
      treeStack.pop();
      if ( node ) {
         ofstr << node->key << ' ';
         treeStack.push(node->right);
         treeStack.push(node->left);
      } else {
         ofstr << "# ";
      }
   }
   */

   // level-order serialization
   if ( !p ) return;
   std::queue<const Node*> q;
   q.push(p);
   while ( !q.empty() ) {
      const Node* node = q.front();
      q.pop();
      if (node) {
         ofstr << node->key << ' ';
         q.push(node->left);
         q.push(node->right);
      } else {
         ofstr << "# ";
      }
   }
}

template <class Type>
typename AVL<Type>::Node* AVL<Type>::deserialize
(std::stringstream& internalFile, Node* p)
{
   std::string keystr;
   if ( internalFile >> keystr && keystr != "#" ) {
      std::istringstream keystream(keystr);
      Type key;
      keystream >> key;
      p = new Node(key);
      // internalFile >> p->height;
      p->left = deserialize(internalFile, p->left);
      p->right = deserialize(internalFile, p->right);
      p->height = 1 + std::max(height(p->left), height(p->right));
   }
   return p;
}

// pre-order (actually deserializes to level order ??)
template<class Type>
typename AVL<Type>::Node* AVL<Type>::deserialize(std::ifstream& ifstr, Node* p)
{   
   std::queue<Node*> q;
   std::string x;
   Type y;

   ifstr >> x;
   std::istringstream isstr(x);
   isstr >> y;
   p = new Node(y);
   Node* cur = p;
   q.push(cur);
   while ( !q.empty() ) {
      Node* node = q.front();
      q.pop();
      if ( !(ifstr >> x) ) break;
      if ( x != "#" ) {
         std::istringstream isstr(x);
         isstr >> y;
         cur = new Node(y);
         q.push(cur);
         node->left = cur;
      }
      if ( !(ifstr >> x ) ) break;
      if ( x != "#" ) {
         std::istringstream isstr(x);
         isstr >> y;
         cur = new Node(y);
         q.push(cur);
         node->right = cur;
      }
   }
   return p;
}

#endif
