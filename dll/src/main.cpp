#include <sstream>
#include <cstdlib>
#include <ctime>
#include "list.hpp"

template <class Type> void display(const List<Type>*);

int main(int argc, char* argv[]) {
   if ( argc < 2 ) {
      std::cerr << "Usage: " << argv[0] << " option" << std::endl;
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

   srand(time(0));
   
   List<int>* Integers = new List<int>();
   
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
   for (int i = 0; i < N; i++) Integers->Insert(rnd[i]);
   delete [] rnd;
   
   display(Integers);
   Integers->Serialize("integers.dat");
   std::cout << "list serialized to file" << std::endl;
   Integers->Reverse();
   std::cout << "list reversed" << std::endl;
   display(Integers);
   // node removal test
   for (int i = 0; i < N; i++) {
      int z = N * (rand() / 2147483647.0F);
      Integers->Remove(z);
   }
   std::cout << "list after node removals" << std::endl;
   display(Integers);
   delete Integers;
   Integers = new List<int>();
   Integers->Deserialize("integers.dat");
   std::cout << "list de-serialized from file" << std::endl;
   display(Integers);
   delete Integers;
   // test Type = std::string
   List<std::string>* Strings = new List<std::string>();
   std::string str;
   std::ifstream ifstr("words", std::ifstream::in);
   int i = 0;
   while ( i < N ) {
      if ( ifstr >> str ) Strings->Insert(str);
      ++i;
   }
   ifstr.close();
   display(Strings);
   Strings->Serialize("strings.dat");
   std::cout << "list serialized to file" << std::endl;
   Strings->Reverse();
   std::cout << "list reversed" << std::endl;
   display(Strings);
   // node removal test
   ifstr.open("words", std::ifstream::in);
   i = 0;
   while ( i < N ) {
      if ( ifstr >> str )
         if ( i % 2 ) Strings->Remove(str);
      ++i; 
   }
   ifstr.close();
   std::cout << "list after node removals" << std::endl;
   display(Strings);
   delete Strings;
   Strings = new List<std::string>();
   Strings->Deserialize("strings.dat");
   std::cout << "list de-serialized from file" << std::endl;
   display(Strings);
   delete Strings;
   return 0;
}

template<class Type> void display(const List<Type>* DoublyLinkedList)
{
   std::cout << "head to tail" << std::endl;
   DoublyLinkedList->Print();
   std::cout << "tail to head" << std::endl;
   DoublyLinkedList->PrintBackwards();
}
