// doubly linked list
// iterative implementations
#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
#include <fstream>

template<class Type> 
class DoublyLinkedList
{
   public:
      DoublyLinkedList() : head(0) {}
      ~DoublyLinkedList();
      void Insert(const Type&);
      void Remove(const Type&);
      void Reverse();
      void Print() const;
      void PrintBackwards() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
   private:
      struct Node;
      Node* head;
      Node* tail;
      Node* locate(Node*, const Type&) const;
      Node* insert(Node*, const Type&);
      Node* remove(Node*, const Type&);
      Node* reverse(Node*);
      void print(const Node*) const;
      void serialize(std::ofstream&, Node*) const;
      Node* deserialize(std::ifstream&);
      Node* destroy(Node*);
};

// template class 
template<class Type> 
struct DoublyLinkedList<Type>::Node
{  
   Type key;
   Node* prev;
   Node* next;
   Node(const Type& key) : key(key), prev(0), next(0) {}
};

// class destructor
template<class Type> 
DoublyLinkedList<Type>::~DoublyLinkedList()
{  
   head = destroy(head);
}

// template class public access methods
template<class Type> 
void DoublyLinkedList<Type>::Insert(const Type& key)
{
   head = insert(head, key);
}

template<class Type> void 
DoublyLinkedList<Type>::Remove(const Type& key)
{
   head = remove(head, key);
}

template<class Type> 
void DoublyLinkedList<Type>::Reverse()
{
   head = reverse(head);
}

template<class Type> 
void DoublyLinkedList<Type>::Print() const
{
   print(head);
}

template<class Type> 
void DoublyLinkedList <Type>::PrintBackwards() const
{
   print(tail);
}

template<class Type> 
void DoublyLinkedList<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ios::out);
   serialize(ofstr, tail);
   ofstr.close();
}

template<class Type> 
void DoublyLinkedList<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ios::in);
   head = deserialize(ifstr);
   ifstr.close();
}

// template class private methods

template<class Type>
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::locate(Node* p, const Type& key) const
{
   while (p) {
      if (p->key == key) return p;
      p = p->next;
   }
   return 0;
}

template<class Type> 
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::insert(Node* p, const Type& key)
{
   if (p == 0) {  // list is empty
      head = new Node(key);
      tail = head;
      return head;
   }
   if (key < p->key) {   // key will be first therefore new head
      Node* link = new Node(key);
      link->prev = 0;
      link->next = head;
      head->prev = link;
      return link;
   }
   // key to be inserted in list body
   Node* _prev = p;
   while (p != 0 && key > p->key) {
      _prev = p;
      p = p->next;
   }
   Node* link = new Node(key);
   _prev->next = link;
   if (p) p->prev = link;
   else tail = link;
   link->prev = _prev;
   link->next = p;
   return head;
}

template<class Type> 
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::remove(Node* p, const Type& key)
{
   // locate target node to be deleted
   Node* link = locate(head, key);
   // bail on null pointer
   if (link == 0) return head;
   // update head node if necessary
   if (link == head) head = link->next;
   else link->prev->next = link->next;
   // update tail node if necessary
   if (link == tail) tail = link->prev;
   else link->next->prev = link->prev;
   // delete node
   delete link;
   return head;
}

template<class Type> 
typename DoublyLinkedList<Type>::Node* 
DoublyLinkedList<Type>::reverse(Node* p)
{
   while ( p ) {
      Node* tmp = p->prev;
      p->prev = p->next;
      p->next = tmp;
      p = p->prev;
   }
   Node* tmp = head;
   head = tail;
   tail = tmp;   

   return head;
}

template<class Type> 
void DoublyLinkedList<Type>::print(const Node* p) const
{
   bool flag = false;
   if (p == tail) flag = true;
   while (p) {
      std::cout << p->key << std::endl;
      if (flag) p = p->prev;
      else p = p->next;
   }
}

template<class Type> 
void DoublyLinkedList<Type>::serialize(std::ofstream& ofstr, Node* p) const
{
   while (p) {
      ofstr << p->key << std::endl;
      p = p->prev;
   }
}

template<class Type>
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::deserialize(std::ifstream& ifstr)
{
   std::string tmp;
   while ( ifstr >> tmp ) {
      std::istringstream isstr(tmp);
      Type key;
      isstr >> key;
      Insert(key);
   }
   return head;
}

template<class Type> 
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::destroy(Node* p)
{
   while (p) {
      Node *link = p;
      p = p->next;
      delete link;
   }
   return p;
}

#endif
