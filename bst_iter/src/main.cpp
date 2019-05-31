#include <cstdlib>
#include <ctime>
#include "bst.hpp"

int main(int argc, char* argv[]) {
   const int LIM = 1000;
   // test template class for case Type is int
   BST<int>* Numbers = new BST<int>();
   srand(time(0));
   for (int i = 0; i < LIM; i++) Numbers->Insert(short(rand()));
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
   std::cout << "defoliation" << std::endl;
   delete Numbers;
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
   std::cout << "defoliation" << std::endl;
   delete Numbers;
   // test template class for Type is std::string
   BST<std::string>* Words = new BST<std::string>();
   std::ifstream ifstr("words.txt", std::ifstream::in);
   std::string str;
   while ( ifstr >> str ) Words->Insert(str); 
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
   Words->Serialize("words.dat");
   std::cout << "defoliation" << std::endl;
   delete Words;
   Words = new BST<std::string>();
   std::cout << "de-serialization" << std::endl;
   Words->Deserialize("words.dat");
   std::cout << "pre-order" << std::endl;
   Words->PreOrder();
   std::cout << "in-order" << std::endl;
   Words->InOrder();
   std::cout << "post-order" << std::endl;
   Words->PostOrder();
   std::cout << "level-order" << std::endl;
   Words->LevelOrder();   
   std::cout << "h = " << Words->Height() << std::endl;
   std::cout << "defoliation" << std::endl;
   delete Words;
   return 0;
}
