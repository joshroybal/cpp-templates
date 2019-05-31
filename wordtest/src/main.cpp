#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"
#include "BinarySearchTree.hpp"
#include "AVLTree.hpp"

int main(int argc, char* argv[])
{
   if ( argc < 2 ) {
      std::cerr << "Usage: " << argv[0] << " sll|dll|bst|avl" << std::endl;
      return 1;
   }

   std::string flag(argv[1]);

   if ( flag == "sll" ) {
      SinglyLinkedList<std::string>* sll = new SinglyLinkedList<std::string>();
      std::string key;
      while ( std::cin >> key ) sll->Insert(key);
      sll->Print();
      delete sll;
   } 
   else if ( flag == "dll" ) {
      DoublyLinkedList<std::string>* dll = new DoublyLinkedList<std::string>();
      std::string key;
      while ( std::cin >> key ) dll->Insert(key);
      dll->Print();
      delete dll;
   }
   else if ( flag == "bst" ) {
      BinarySearchTree<std::string>* bst = new BinarySearchTree<std::string>();
      std::string key;
      while ( std::cin >> key ) bst->Insert(key);
      bst->InOrder();
      delete bst;
   }   
   else if ( flag == "avl" ) {
      AVLTree<std::string>* avl = new AVLTree<std::string>();
      std::string key;
      while ( std::cin >> key ) avl->Insert(key);
      avl->InOrder();
      std::cout << "h = " << avl->Height() << std::endl;
      delete avl;
   }      
   else {
      ;
   }
   return 0;
}
