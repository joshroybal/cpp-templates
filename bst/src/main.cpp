#include <cstdlib>
#include "bst.hpp"

int main(int argc, char* argv[]) {
   if ( argc < 2 ) {
      std::cerr << "Usage: " << argv[0] << " n" << std::endl;
      return 1;
   }
  
   // error trap invalid input 
   std::istringstream isstr(argv[1]);
   int tmp;
   isstr >> tmp;
   if ( !isstr.eof() ) {
      std::cerr << "error reading integer" << std::endl;
      return 1;
   }
   if (tmp <= 0 || tmp > 1000) {
      std::cerr << "0 < n <= 1000" << std::endl;
      return 1;
   }
   
   const int N = tmp;
  
   // test for Type = int
   BST<int>* Integers = new BST<int>();

   // insert randomly shuffled series into numeric tree
   int* rnd = new int[N];
   for (int i = 0; i < N; i++) rnd[i] = i+1;
   for (int i = 0; i < N; i++) {
      int idx = N * (rand() / 2147483647.0F);
      if (idx != i) {
         tmp = rnd[i];
         rnd[i] = rnd[idx];
         rnd[idx] = tmp;
      }
   }
   for (int i = 0; i < N; i++) {
      std::cout << rnd[i] << std::endl;
      Integers->Insert(rnd[i]);
   }
   delete [] rnd;

   std::cout << "pre-order" << std::endl;
   Integers->PreOrder();
   std::cout << "in-order" << std::endl;
   Integers->InOrder();
   std::cout << "post-order" << std::endl;
   Integers->PostOrder();
   std::cout << "h = " << Integers->Height() << std::endl;
   Integers->Serialize("integers.dat");
   std::cout << "tree serialized to file" << std::endl;
   // node removal test
   for (int i = 0; i < N; i++) {
      int rnd = N * (rand() / 2147483647.0F);
      Integers->Remove(rnd);
   }
   std::cout << "tree after pruning" << std::endl;
   std::cout << "pre-order" << std::endl;
   Integers->PreOrder();
   std::cout << "in-order" << std::endl;
   Integers->InOrder();
   std::cout << "post-order" << std::endl;
   Integers->PostOrder();
   std::cout << "h = " << Integers->Height() << std::endl;
   delete Integers;
   std::cout << "tree deleted" << std::endl;
   Integers = new BST<int>();
   Integers->Deserialize("integers.dat");
   std::cout << "tree de-serialized from file" << std::endl;
   std::cout << "pre-order" << std::endl;
   Integers->PreOrder();
   std::cout << "in-order" << std::endl;
   Integers->InOrder();
   std::cout << "post-order" << std::endl;
   Integers->PostOrder();
   std::cout << "h = " << Integers->Height() << std::endl;
   delete Integers;
   std::cout << "tree deleted" << std::endl;

   // test Type = std::string
   BST<std::string>* Strings = new BST<std::string>();

   std::ifstream ifstr("strings", std::ifstream::in);
   std::string str;
   int i = 0;
   while ( i < N ) {
      if ( ifstr >> str ) Strings->Insert(str);
      ++i;
   }
   std::cout << "pre-order" << std::endl;
   Strings->PreOrder();   
   std::cout << "in-order" << std::endl;
   Strings->InOrder();
   std::cout << "post-order" << std::endl;
   Strings->PostOrder();   
   std::cout << "h = " << Strings->Height() << std::endl;
   Strings->Serialize("strings.dat");
   std::cout << "tree serialized to file" << std::endl;
   // node removal test
   ifstr.open("strings", std::ifstream::in);
   i = 0;
   while ( i < N ) {
      if ( i%2 )
         if ( ifstr >> str ) Strings->Remove(str);
      ++i;
   }
   std::cout << "tree after pruning" << std::endl;
   std::cout << "pre-order" << std::endl;
   Strings->PreOrder();   
   std::cout << "in-order" << std::endl;
   Strings->InOrder();
   std::cout << "post-order" << std::endl;
   Strings->PostOrder();   
   std::cout << "h = " << Strings->Height() << std::endl;
   delete Strings;
   Strings = new BST<std::string>();
   std::cout << "tree deleted" << std::endl;
   Strings->Deserialize("strings.dat");
   std::cout << "tree de-serialized from file" << std::endl;
   std::cout << "pre-order" << std::endl;
   Strings->PreOrder();   
   std::cout << "in-order" << std::endl;
   Strings->InOrder();
   std::cout << "post-order" << std::endl;
   Strings->PostOrder();   
   std::cout << "h = " << Strings->Height() << std::endl;
   delete Strings;
   std::cout << "tree deleted" << std::endl;

   return 0;
}
