/* 
Project 2 - Search
Name: Imran Khan
UIN:654046372
IDE Used: Clion on a Windows Platform
*/

/*
For milestone 6 to work the if-statement in the building index has to be uncommented it is commented right now so that the test cases may work accordingly its inside the while loop and for loop . In milestone 6 i removed all the stoppingwords from my txt file and the unique vales decrease in the map so the user can not search up useless words and the map is clean from it also
*/

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

/*This is a part 2 of the clean token function this checks is there is a letter in the string and if so then we do not remove the numbers in the string. It is a boolean function and returns a true or false value accordingly*/
bool containsLetter(string str) {

  for (int i = 0; i < str.size(); i++) {

    if (isalpha(str.at(i))) {

      return true;

    }

  }

  return false;

}
/*In this function the code helps clean a string from punctuations and makes it readable in the serach function first we would remove all the punctuations and then check for numbers if they need to be removed also. The front and the back of the string are cleaned seperately*/
string cleanToken(string s) {
  
 //checks if there is a letter
  if(containsLetter(s)){
    while(ispunct(s[0])|| s[0] == ' '){
    s.erase(0,1);//erases it

      }
  }
  else{//checks for an empty string
    s = "";
    return s;
  }

  if(s.length() == 0){
    return "";
  }

  //for back side of the string
  while(ispunct(s[s.length()-1])){
    s.erase(s.length()-1,1);
  }

  //makes the string to lower for processing
  transform(s.begin(), s.end(), s.begin(), ::tolower);

  // cout<<s<<endl;//for testing purposes
  return s;  // returns the string
}



/*In this function we get a whole line of text as a string and use the previoys clean token function to help clean it word by word wherever there is a space it makes a seperation of words for cleaning and passes it to the other function for deep cleaning. A set of the line is returned which is used to cross reference it to the map in the next function*/
set<string> gatherTokens(string text) {
  set<string> tokens;
    

  //for the text
  stringstream s(text);
  string temp2;
  string temp;

  //gets the whole line
  while(getline(s, temp,' ')){
    temp2 = cleanToken(temp);
    if(temp2.empty()==0){
      tokens.insert(temp2);//inserts it into the set
    }
    
  }    
    
  return tokens;  //returns the set
}



/*This function is part of milestone 6 and is used in reading the extrra file name and returning the set as a parameter*/
void readingStoppingWords(string filename, set<string>&words){
  
  filename= "stoppingwords.txt";
  string lines;
  ifstream infile(filename);
  
  while (infile.good()) {
    getline(infile, lines);
    words.insert(lines);
  }
  
}


/*In this function we read the given file handed down by the user and then we run through it and if the file is of invalid name we stop the program but if it valid we get each line and run it through gather tokens where it is cleaned and then it is processed as a key into the map and the url is used as the set and where we find tha word again we add that url to the set of urls and then keep it for reference and process it when we search through the map*/
int buildIndex(string filename, map<string, set<string>>& index) {
  set<string>stoppingwords;
  set<string> temp;
  set<string> temp2;
  //reading the file
  ifstream infile(filename);
  string secondline;
  string firstline;
  int numberOfLines = 0;//counting the number of urls

  string fileStop;
  
  readingStoppingWords(fileStop,stoppingwords);//this is for milestone 6

  
  //reading the file
  if(infile.fail()){

    exit(0);
    
  }

  //runs the file till its unvalid
  while (infile.good()) {
      
     
    getline(infile, firstline);//the url is stored in the variable firstline

    if(infile.good()==false){
      break;
    }
    
    getline(infile, secondline);//the keys are stored in the variable secondline
    numberOfLines++;//counts the number of urls
    

    temp = gatherTokens(secondline);
    
    for(auto& str: temp){//str =  key
      // if(stoppingwords.count(str)==0){//it means its inside
   
    
        if(index.count(str) != 0){
  
          index[str].insert(firstline);//inserts it into the map
  
        }
        else{
  
          temp2.insert(firstline);//adding in url if not present
          index[str] = temp2;
  
        }
      // }
    }
    
    temp.clear();
    temp2.clear();
      
    }

  return numberOfLines;//returns the number of urls
  numberOfLines = 0;
}


/*In this function we take in the string with the + or - attached to them adnd then we isolate the urls accordingly to the function we need to use if nothing is provided then no operation is provided to the string but if a + is used then we have to find the url that contains both or many of those valus in them and if a - is included in the string then we have to find the url which does not contain that vale but the value before it its like a set (union and intersection)*/
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
  set<string> result;
  set<string> temp1;
  string temp_s;
    
    
  

  istringstream sample(sentence);

  while(sample >> temp_s){

    transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);//makes it lower
    temp1.clear();

    if(isalpha(temp_s[0])){//checks the first index of the string
      set_union(begin(result), end(result),
      begin(index[cleanToken(temp_s)]), end(index[cleanToken(temp_s)]),
      inserter(temp1, end(temp1))); 
      result = temp1;
    } 
    else if (temp_s[0] == '-'){//checks the first index of the string
      set_difference(begin(result), end(result),
      begin(index[cleanToken(temp_s)]), end(index[cleanToken(temp_s)]),
      inserter(temp1, end(temp1))); 
      result = temp1;
     }
    else if (temp_s[0] == '+'){//checks the first index of the string
      set_intersection(begin(result), end(result),
      begin(index[cleanToken(temp_s)]), end(index[cleanToken(temp_s)]),
      inserter(temp1, end(temp1)));
      result = temp1;
    } 
    

    }
    
  return result;  // TODO:  update this.
}



/*In this last function we use all the other functions that we made and search up the urls which containd the words the user wants us to find and then we display them the mathcing urls acordingly. We only take the file name as the parameter and we run though the file and isolate it by urls and keys in the map then we search through it and show the users the number of urls found accordingly like a search engine. It exits out of the program if enter is pressed*/
void searchEngine(string filename) {

  map<string,set<string>> buildingData;
  set<string> totalvalues;
  string findingValue;
  int noOfPages = 0;
  int uniqueTerms = 0;
  int counter = 0;

  
  noOfPages = buildIndex(filename,buildingData);
  uniqueTerms = buildingData.size(); 


  
  cout<<"Stand by while building index..."<<endl;
  cout<<"Indexed "<< noOfPages <<" pages containing "<< uniqueTerms <<" unique terms"<<endl;
  cout<<endl;

  
  //using a do while statement
  do {
    
    counter = 0;
    cout<<"Enter query sentence (press enter to quit): ";
    getline(cin, findingValue);

    //cleans if the first word starts with + or -
    if(findingValue[0] == '-' || findingValue[0] == '+'){
      
      findingValue.erase(0,1);
      
    }
   
    totalvalues = findQueryMatches(buildingData, findingValue);
    
    //counts the number of urls found
    for (auto it = totalvalues.begin(); it !=totalvalues.end(); ++it){ 
      
      ++counter;
      
    }

    
    if(counter == 0){
      counter = 0;
    }

    
    if(findingValue.length() != 0){
      
      cout<<"Found "<<counter<<" matching pages"<<endl;

      //prints out the urls
      for (auto it = totalvalues.begin(); it !=totalvalues.end(); ++it){ 
      cout << *it<<endl;
        
      }
      
      cout<<endl;
      
    }

} while (findingValue.length() != 0);//if enter is pressed

  cout << "Thank you for searching!" << endl;
}