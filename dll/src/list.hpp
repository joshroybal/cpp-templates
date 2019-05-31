// doubly linked list
// iterative implementations
#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <fstream>

template<class Type> class List
{
   public:
      List() : head(0) {}
      ~List();
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
template<class Type> struct List<Type>::Node
{  
   Type item;
   Node* prev;
   Node* next;
   Node(const Type& x) : item(x), prev(0), next(0) {}
};

// class destructor
template<class Type> List<Type>::~List()
{  
   head = destroy(head);
}

// template class public access methods
template<class Type> void List<Type>::Insert(const Type& item)
{
   head = insert(head, item);
}

template<class Type> void List<Type>::Remove(const Type& item)
{
   head = remove(head, item);
}

template<class Type> void List<Type>::Reverse()
{
   head = reverse(head);
}

template<class Type> void List<Type>::Print() const
{
   print(head);
}

template<class Type> void List <Type>::PrintBackwards() const
{
   print(tail);
}

template<class Type> 
void List<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ios::out);
   serialize(ofstr, tail);
   ofstr.close();
}

template<class Type> void List<Type>::Deserialize(const std::string& filename)
{
   std::ifstream ifstr;
   ifstr.open(filename.c_str(), std::ios::in);
   head = deserialize(ifstr);
   ifstr.close();
}

// template class private methods

template<class Type>
typename List<Type>::Node* List<Type>::locate(Node* p, const Type& target) const
{
   while (p) {
      if (p->item == target) return p;
      p = p->next;
   }
   return 0;
}

template<class Type> 
typename List<Type>::Node* List<Type>::insert(Node* p, const Type& x)
{
   if (p == 0) {  // list is empty
      head = new Node(x);
      tail = head;
      return head;
   }
   if (x < p->item) {   // item will be first therefore new head
      Node* link = new Node(x);
      link->prev = 0;
      link->next = head;
      head->prev = link;
      return link;
   }
   // item to be inserted in list body
   Node* _prev = p;
   while (p != 0 && x > p->item) {
      _prev = p;
      p = p->next;
   }
   Node* link = new Node(x);
   _prev->next = link;
   if (p) p->prev = link;
   else tail = link;
   link->prev = _prev;
   link->next = p;
   return head;
}

template<class Type> 
typename List<Type>::Node* List<Type>::remove(Node* p, const Type& x)
{
   // locate target node to be deleted
   Node* link = locate(head, x);
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
typename List<Type>::Node* 
List<Type>::reverse(Node* p)
{
   // iterate through the list and exchange the prev and next pointers
   while ( p ) {
      Node* tmp = p->prev;
      p->prev = p->next;
      p->next = tmp;
      p = p->prev;
   }
   // fix the head and tail pointers
   Node* tmp = head;
   head = tail;
   tail = tmp;   

   return head;
}

template<class Type> void List<Type>::print(const Node* p) const
{
   bool flag = false;
   if (p == tail) flag = true;
   while (p) {
      std::cout << p->item << std::endl;
      if (flag) p = p->prev;
      else p = p->next;
   }
}

template<class Type> 
void List<Type>::serialize(std::ofstream& ofstr, Node* p) const
{
   while (p) {
      ofstr << p->item << std::endl;
      p = p->prev;
   }
}

template<class Type>
typename List<Type>::Node* List<Type>::deserialize(std::ifstream& ifstr)
{
   std::string tmp;
   while ( ifstr >> tmp ) {
      std::istringstream isstr(tmp);
      Type x;
      isstr >> x;
      Insert(x);
   }
   return head;
}

template<class Type> typename List<Type>::Node* List<Type>::destroy(Node* p)
{
   while (p) {
      Node *link = p;
      p = p->next;
      delete link;
   }
}

#endif
