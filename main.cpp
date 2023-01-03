/* 
Project 2 - Search
Name: Imran Khan
UIN:654046372
IDE Used: Clion on a Windows Platform
*/



#include <iostream>
#include "search.h"
using namespace std;

int main() {
  

  // map<string, set<string>> index;
  // // Use this function to call and test the functions you write inside of
  // // search.h.  If you do not call the functions here, nothing will run.
  
  /*testing function cleanToken*/
  // string test = "EGGS!";
  // cleanToken(test);
  
  /*testing function gatherTokens*/
  // set<string>index;
  // string test= "EGGS! milk, fish,      @  bread cheese";
  // index  = gatherTokens(test);
  //   for (auto itr : index)
  // {
  //   cout << itr << " ";
  // } 
  
  /*testing function buildIndex*/
  // map<string, set<string>>index;
  // string fileName  = "tiny.txt";
  // int x  = buildIndex(fileName,index);
  // cout<<x<<endl;//should be 4
  
  /*testing function findQueryMatches*/
  // set<string>index1;
  // map<string, set<string>> index;
  // string test = "vector +container";
  // index1 = findQueryMatches(index,test);
  // for (auto itr : index1)
  // {
  //   cout << itr << " ";
  // } 
  
  //----------------------------------------------------------------------------
  
  /*testing the search engine function*/
  // string filename = "cplusplus.txt";
  // cin>>filename;
  searchEngine("cplusplus.txt");
  return 0;
}

