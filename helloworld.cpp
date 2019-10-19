#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "httpclient.hpp"
using namespace std;

int main()
{
   vector<string> msg {"Hello", "C++", "World", "from", "VS Code!", "and the C++ extension!"};

   for (const string& word : msg)
   {
      cout << word << " ";
   }
   cout << endl;
   int num = 10;
   pthread_t tid[num];
   char* url = "https://www.example.com/";
   for(int i = 0;i<num;i++){
      tid[i] = requestInThread(url);
   }

   for(int i=0;i<num;i++){
      pthread_join(tid[i],NULL);
      printf("thrad terminal %d",i);
   }
   return 0;
}