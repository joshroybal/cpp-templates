#include <cstdlib>
#include "bst.hpp"
// #include "avl.hpp"

int main(int argc, char* argv[]) {
   const int LIM = 10;
   // test template class for case Type is int
   BST<int>* Numbers = new BST<int>();
   for (int i = 0; i < LIM; i++) Numbers->Insert(rand()%LIM);
   std::cout << "pre-order" << std::endl;
   Numbers->PreOrder();
   std::cout << "in-order" << std::endl;
   Numbers->InOrder();
   std::cout << "post-order" << std::endl;
   Numbers->PostOrder();
   std::cout << "level-order" << std::endl;
   Numbers->LevelOrder();
   std::cout << "h = " << Numbers->Height() << std::endl;
   std::cout << "serialization" << std::endl;
   Numbers->Serialize("numbers.dat");
   delete Numbers;
   std::cout << "tree deleted" << std::endl;
   Numbers = new BST<int>();
   std::cout << "de-serialization" << std::endl;
   Numbers->Deserialize("numbers.dat");
   std::cout << "pre-order" << std::endl;
   Numbers->PreOrder();
   std::cout << "in-order" << std::endl;
   Numbers->InOrder();
   std::cout << "post-order" << std::endl;
   Numbers->PostOrder();
   std::cout << "level-order" << std::endl;
   Numbers->LevelOrder();
   std::cout << "h = " << Numbers->Height() << std::endl;
   std::cout << "serialization" << std::endl;
   Numbers->Serialize("numbers.dat");
   delete Numbers;
   std::cout << "tree deleted" << std::endl;
   // test template class for Type is std::string
   BST<std::string>* Words = new BST<std::string>();
   std::ifstream ifstr("words.txt", std::ifstream::in);
   std::string str;
   int n = 0;
   while ( ifstr >> str && n < LIM ) {
      Words->Insert(str);
      ++n;
   }
   ifstr.close();
   std::cout << "pre-order" << std::endl;
   Words->PreOrder();
   std::cout << "in-order" << std::endl;
   Words->InOrder();
   std::cout << "post-order" << std::endl;
   Words->PostOrder();
   std::cout << "level-order" << std::endl;
   Words->LevelOrder();
   std::cout << "h = " << Words->Height() << std::endl;
   std::cout << "serialization" << std::endl;
   Words->Serialize("strings.dat");
   delete Words;
   std::cout << "tree deleted" << std::endl;
   Words = new BST<std::string>();
   std::cout << "de-serialization" << std::endl;
   Words->Deserialize("strings.dat");
   std::cout << "pre-order" << std::endl;
   Words->PreOrder();
   std::cout << "in-order" << std::endl;
   Words->InOrder();
   std::cout << "post-order" << std::endl;
   Words->PostOrder();
   std::cout << "level-order" << std::endl;
   Words->LevelOrder();
   std::cout << "h = " << Words->Height() << std::endl;
   delete Words;
   std::cout << "tree deleted" << std::endl;
   return 0;
}
