#include <sstream>
#include <cstdlib>
#include <ctime>
#include "list.hpp"

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
   
   Integers->Print();
   Integers->Serialize("integers.dat");
   std::cout << "list serialized to file" << std::endl;
   Integers->Reverse();
   std::cout << "list reversed" << std::endl;
   Integers->Print();
   // node removal test
   for (int i = 0; i < N; i++) {
      int z = N * (rand() / 2147483647.0F);
      Integers->Remove(z);
   }
   std::cout << "list after node removals" << std::endl;
   Integers->Print();
   delete Integers;
   Integers = new List<int>();
   Integers->Deserialize("integers.dat");
   std::cout << "list de-serialized from file" << std::endl;
   Integers->Print();
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
   Strings->Print();
   Strings->Serialize("strings.dat");
   std::cout << "list serialized to file" << std::endl;
   Strings->Reverse();
   std::cout << "list reversed" << std::endl;
   Strings->Print();
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
   Strings->Print();
   delete Strings;
   Strings = new List<std::string>();
   Strings->Deserialize("strings.dat");
   std::cout << "list de-serialized from file" << std::endl;
   Strings->Print();
   delete Strings;
   return 0;
}
