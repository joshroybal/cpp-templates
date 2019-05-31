#include "avl.hpp"

int random(int);
void initialize(int [], int);
void shuffle(int [], int);
template<class Type> void displayTree(AVL<Type>*);

int main(int argc, char* argv[]) {
   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " n\n";
      return 1;
   }
   std::string nstr(argv[1]);
   std::istringstream isstr(nstr);
   int n;
   isstr >> n;
   if (n < 2) {
      std::cerr << "n must be postive\n";
      return 1;
   }
   const int LIM = n;
   // test template class for case Type is int
   AVL<int>* Numbers = new AVL<int>();
   int* arr = new int[LIM];
   initialize(arr, LIM);
   shuffle(arr, LIM);
   for (int i = 0; i < LIM; i++) Numbers->Insert(arr[i]);
   delete [] arr;
   displayTree(Numbers);
   std::stringstream internalFile;
   Numbers->Serialize(internalFile);
   std::cout << "tree serialized to internal file" << std::endl;
   delete Numbers;
   std::cout << "tree deleted" << std::endl;
   
   std::cout << internalFile.str() << std::endl;
   
   Numbers = new AVL<int>();
   Numbers->Deserialize(internalFile);
   std::cout << "tree de-serialized from internal file" << std::endl;
   displayTree(Numbers);
   delete Numbers;
   std::cout << "tree deleted" << std::endl;
   
   // test template class for Type is std::string
   AVL<std::string>* Words = new AVL<std::string>();
   
   std::ifstream ifstr("words.txt", std::ifstream::in);
   std::string str;
   n = 0;
   while ( ifstr >> str && n < LIM ) {
      Words->Insert(str);
      ++n;
   }
   ifstr.close();
   
   displayTree(Words);
   std::stringstream wordFile;
   Words->Serialize(wordFile);
   std::cout << "tree serialized to internal file" << std::endl;
   delete Words;
   std::cout << "tree deleted" << std::endl;

   std::cout << wordFile.str() << std::endl;

   Words = new AVL<std::string>();
   Words->Deserialize(wordFile);
   std::cout << "tree de-serialized from internal file" << std::endl;
   displayTree(Words);
   Words->Serialize("strings.dat");
   std::cout << "tree serialized to external file" << std::endl;
   delete Words;
   std::cout << "tree deleted" << std::endl;
   
   // external file de-serialization test
   Words = new AVL<std::string>();
   Words->Deserialize("strings.dat");
   displayTree(Words);
   delete Words;
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
   std::cout << "level-order" << std::endl;
   Tree->LevelOrder();
   std::cout << "h = " << Tree->Height() << std::endl;
   // std::cout << "size = " << Tree->Size() << std::endl;
   Tree->Min();
   Tree->Max();
   std::cout << std::endl;
}
