#include <cstdlib>
#include <ctime>
#include "avl.hpp"

int random(int);
void initialize(int [], int);
void shuffle(int [], int);
template<class Type> void displayTree(BST<Type>*);

int main(int argc, char* argv[]) {
   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " n\n";
      return 1;
   }
   std::string nstr(argv[1]);
   std::istringstream isstr(nstr);
   int n;
   isstr >> n;
   if (n < 0) {
      std::cerr << "n must be postive\n";
      return 1;
   }
   const int LIM = n;
   srand(time(0));
   // test template class for case Type is int
   BST<int>* Integers = new BST<int>();
   int* arr = new int[LIM];
   initialize(arr, LIM);
   shuffle(arr, LIM);
   for (int i = 0; i < LIM; i++) {
      std::cout << arr[i] << ' ';
      Integers->Insert(arr[i]);
   }
   std::cout << std::endl;
   delete [] arr;
   displayTree(Integers);
   std::stringstream internalFile;
   Integers->Serialize(internalFile);
   std::cout << "tree serialized to internal file" << std::endl;

   // node removal test
   std::cout << "node removal tests" << std::endl;
   for (int i = 0; i < LIM; i++) {
      int rnd = random(LIM);
      std::cout << rnd << ' ';
      Integers->Remove(rnd);
   }
   std::cout << "\ntree after pruning" << std::endl;
   displayTree(Integers);
   delete Integers;   
   std::cout << "tree deleted" << std::endl;
   
   std::cout << internalFile.str() << std::endl;
   
   Integers = new BST<int>();
   Integers->Deserialize(internalFile);
   std::cout << "tree de-serialized from internal file" << std::endl;
   displayTree(Integers);
   Integers->Serialize("integers.dat");
   std::cout << "tree serialized to external file" << std::endl;   
   delete Integers;
   std::cout << "tree deleted" << std::endl;

   // external file de-serialization test
   Integers = new BST<int>();
   Integers->Deserialize("integers.dat");
   displayTree(Integers);
   delete Integers;
   std::cout << "tree deleted" << std::endl;

   
   // test template class for Type is std::string
   BST<std::string>* Strings = new BST<std::string>();
   
   std::ifstream ifstr("words.txt", std::ifstream::in);
   std::string str;
   n = 0;
   while ( ifstr >> str && n < LIM ) {
      Strings->Insert(str);
      ++n;
   }
   ifstr.close();
   
   displayTree(Strings);
   std::stringstream wordFile;
   Strings->Serialize(wordFile);
   std::cout << "tree serialized to internal file" << std::endl;

   // node removal test
   ifstr.open("words.txt", std::ifstream::in);
   n = 0;
   while ( ifstr >> str && n < LIM ) {
      if ( n%2 ) Strings->Remove(str);
      ++n;
   }
   ifstr.close();
   std::cout << "tree after pruning" << std::endl;
   displayTree(Strings);   
   delete Strings;
   std::cout << "tree deleted" << std::endl;

   std::cout << wordFile.str() << std::endl;

   Strings = new BST<std::string>();
   Strings->Deserialize(wordFile);
   std::cout << "tree de-serialized from internal file" << std::endl;
   displayTree(Strings);
   Strings->Serialize("strings.dat");
   std::cout << "tree serialized to external file" << std::endl;
   delete Strings;
   std::cout << "tree deleted" << std::endl;
   
   // external file de-serialization test
   Strings = new BST<std::string>();
   Strings->Deserialize("strings.dat");
   displayTree(Strings);
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
void displayTree(BST<Type>* Tree)
{
   std::cout << "\npre-order" << std::endl;
   Tree->PreOrder();
   std::cout << "\nin-order" << std::endl;
   Tree->InOrder();
   std::cout << "\npost-order" << std::endl;
   Tree->PostOrder();
   std::cout << "\nlevel-order" << std::endl;
   Tree->LevelOrder();
   std::cout << "\nh = " << Tree->Height() << std::endl;
   std::cout << "size = " << Tree->Size() << std::endl;
   Tree->Min();
   Tree->Max();
   std::cout << std::endl;
}
