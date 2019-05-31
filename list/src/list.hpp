// singly linked list
// recursive implementations
#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <fstream>
#include <sstream>

template<class Type> class List
{
   public:
      List() : head(0) {}
      ~List();
      void Insert(const Type&);
      void Remove(const Type&);
      void Reverse();
      void Print() const;
      void Serialize(const std::string&) const;
      void Deserialize(const std::string&);
   private:
      struct Node;
      Node* head;
      Node* insert(Node*, const Type&);
      Node* remove(Node*, const Type&);
      Node* locate(Node*, const Type&) const;
      Node* reverse(Node*);
      void print(Node*) const;
      void serialize(std::ofstream&, Node*) const;
      Node* deserialize(std::ifstream&);
      Node* destroy(Node*);
};

// template class 
template<class Type> struct List<Type>::Node
{  
   Type item;
   Node* next;
   Node(const Type& x) : item(x), next(0) {}
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

template<class Type> 
void List<Type>::Serialize(const std::string& filename) const
{
   std::ofstream ofstr;
   ofstr.open(filename.c_str(), std::ios::out);
   serialize(ofstr, head);
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
typename List<Type>::Node* List<Type>::insert(Node* p, const Type& x)
{
   if (p == 0) {  // list is empty
      p = new Node(x);
      return p;
   }

   if (x < p->item) {   // item will be first therefore new head
      Node* link = new Node(x);
      link->next = p;
      head = link;
      return link;
   }

   if (p->next != 0 && x < p->next->item) {  // item will inserted in body
      Node* link = new Node(x);
      link->next = p->next;
      p->next = link;
      return head;
   }

   if (p->next == 0) {  // item will be (new) list tail
      Node* link = new Node(x);
      p->next = link;
      return head;
   }

   return insert(p->next, x);
}

template<class Type> 
typename List<Type>::Node* List<Type>::remove(Node* p, const Type& x)
{
   if ( !p ) return p;

   Node* tag = locate(p, x);


   if ( tag ) {
      if ( tag->next->item == x ) { // x found in list body
         Node* node = tag->next;
         tag->next = node->next;
         delete node;
      } else {   // fix head
         p = p->next;
         delete head;
      }
   }

   return p;
}

template<class Type>
typename List<Type>::Node* List<Type>::locate(Node* p, const Type& target) const
{
   if ( p->next == 0 ) return 0;
   if ( target == p->item || target == p->next->item ) return p;
   p = locate(p->next, target);
}

template<class Type> typename List<Type>::Node* List<Type>::reverse(Node* p)
{
   if (p == 0) return 0;
   if (p->next == 0) return p;
   Node* body = reverse(p->next);
   p->next->next = p;
   p->next = 0;
   return body;
}

template<class Type> void List<Type>::print(Node* p) const
{
   if ( !p ) return;
   std::cout << p->item << std::endl;
   print(p->next);
}

// post-order traversal reverses list for more efficient de-serialization
template<class Type> 
void List<Type>::serialize(std::ofstream& ofstr, Node* p) const
{
   if (p == 0) return;
   serialize(ofstr, p->next);
   ofstr << p->item << std::endl;
}

template<class Type> 
typename List<Type>::Node* List<Type>::deserialize(std::ifstream& ifstr)
{
   std::string tmp;
   if ( ifstr >> tmp ) {
      std::istringstream isstr(tmp);
      Type x;
      isstr >> x;
      if ( !head ) 
         head = new Node(x);
      else {
         Node* node = new Node(x);
         node->next = head;
         head = node;
      }
      head = deserialize(ifstr);
   }
   return head;
}

template<class Type> typename List<Type>::Node* List<Type>::destroy(Node* p)
{
   if ( !p ) return p;
   p->next = destroy(p->next);
   delete p;
}

#endif
