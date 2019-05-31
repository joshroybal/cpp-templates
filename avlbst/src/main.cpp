#include <cstdlib>
#include <ctime>
#include "bst.hpp"
#include "avl.hpp"

int random(int);
void initialize(int [], int);
void shuffle(int [], int);
template<class Type> void displayTree(AVL<Type>*);

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
   if (tmp <= 0 || tmp > 5000) {
      std::cerr << "0 < n <= 5000" << std::endl;
      return 1;
   }
   
   const int N = tmp;
   int arr[N];
  
   // test for Type = int
   AVL<int>* Integers = new AVL<int>();

   // insert randomly shuffled series into numeric tree
   srand(time(0));
   initialize(arr, N);
   shuffle(arr, N);
   for (int i = 0; i < N; i++) {
      std::cout << arr[i] << std::endl;
      Integers->Insert(arr[i]);
   }

   displayTree(Integers);
   Integers->Serialize("integers.dat");
   std::cout << "tree serialized to file" << std::endl;
   // node removal test
   std::cout << "node removal tests" << std::endl;
   for (int i = 0; i < N; i++) {
      int rnd = random(N);
      std::cout << rnd << std::endl;
      Integers->Remove(rnd);
   }
   std::cout << "tree after pruning" << std::endl;
   displayTree(Integers);
   delete Integers;
   std::cout << "tree deleted" << std::endl;
   Integers = new AVL<int>();
   Integers->Deserialize("integers.dat");
   std::cout << "tree de-serialized from file" << std::endl;
   displayTree(Integers);
   Integers->Search(7);
   Integers->Search(2001);
   delete Integers;
   std::cout << "tree deleted" << std::endl;

   // test Type = std::string
   AVL<std::string>* Strings = new AVL<std::string>();

   std::ifstream ifstr("strings", std::ifstream::in);
   std::string str;
   int i = 0;
   while ( i < N ) {
      if ( ifstr >> str ) Strings->Insert(str);
      ++i;
   }
   ifstr.close();
   displayTree(Strings);
   Strings->Serialize("strings.dat");
   std::cout << "tree serialized to file" << std::endl;
   // node removal test
   ifstr.open("strings", std::ifstream::in);
   i = 0;
   while ( i < N ) {
      ifstr >> str;
      if ( i%2 ) Strings->Remove(str);
      ++i;
   }
   ifstr.close();
   std::cout << "tree after pruning" << std::endl;
   displayTree(Strings);
   delete Strings;
   std::cout << "tree deleted" << std::endl;
   Strings = new AVL<std::string>();
   Strings->Deserialize("strings.dat");
   std::cout << "tree de-serialized from file" << std::endl;
   displayTree(Strings);
   Strings->Search("broadcastings");
   Strings->Search("castle");
   delete Strings;
   std::cout << "tree deleted" << std::endl;

   return 0;
}

// generate pseudo-random integer x in range 1 <= x <= n
int random(int n)
{
   return 1 + n * (rand() / 2147483647.0F);
}

void initialize(int arr[], int n)
{
   for (int i = 0; i < n; i++) arr[i] = i+1;
}

void shuffle(int arr[], int n)
{
   for (int i = 0; i < n; i++) {
      int rndidx = n * (rand() / 2147483647.0F);
      int tmp = arr[i];
      arr[i] = arr[rndidx];
      arr[rndidx] = tmp;
   }
}

template<class Type>
void displayTree(AVL<Type>* Tree)
{
   std::cout << "\npre-order" << std::endl;
   Tree->PreOrder();
   std::cout << "in-order" << std::endl;
   Tree->InOrder();
   std::cout << "post-order" << std::endl;
   Tree->PostOrder();
   std::cout << "h = " << Tree->Height() << std::endl;
   std::cout << "size = " << Tree->Size() << std::endl;
   Tree->Min();
   Tree->Max();
   std::cout << std::endl;
}
