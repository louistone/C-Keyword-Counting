/*
 *This program will promt the user to enter a file time.
 *It will print out the frequncy of C++ keyword shown in
 *the file.    Source Code from CS 106L Course Reader Stanford University
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <sstream>
#include <set>

using namespace std;

/*
 *Prompts the user for filename
 */
void OpenUserFile(ifstream& fileStream);

/*
 *Returns a string containing the contents of the file
 *passed in as a parameter
 */
string GetFileContents(ifstream& file);

/*
 *Returns a map from keywords to the frequency at which 
 *those keywords appear in the input text string. Keywords
 *not contained in the text will not appear in the map.
 */
map<string, size_t>GenerateKeywordReport(string contents);

int main()
{
    /*Prompt the user for a file and open it as a stream.*/
    ifstream input;
    OpenUserFile(input);

    /*Generate the report based on the contents of the file.*/
    map<string, size_t>report = GenerateKeywordReport(GetFileContents(input));

    /*Print a summary.*/
    for(map<string,size_t>::iterator itr =report.begin();itr!=report.end();++itr)
        cout<<"Keyword "<<itr->first<<" occurred "<<itr->second<<" times."<<endl;
}

void OpenUserFile(ifstream& input){
    while(true){
        cout<<"Enter filename: ";
        string filename;
        cin>>filename;
    
        input.open(filename.c_str());
        if(input.is_open()) return;

        cout<<"Sorry, I can't find the file "<<filename<<endl;
        input.clear();
    }
}

string GetFileContents(ifstream& input)
{
    /*String which will hold the file contents*/
    string result;
    
    /*Keep reading a line of the file until no data remains.*/
    string line;
    while(getline(input,line))
        result +=line+"\n";
    
    return result;
}

set<string> LoadKeywords(){
    ifstream input("keyword.txt");
    set<string> result;

    string keyword;
    while(input>>keyword)
        result.insert(keyword);
    
    return result;
}

void PreprocessString(string& text)
{
    for(size_t k=0;k<text.size();++k)
        if(ispunct(text[k])&&text[k]!='_')//If we need to change it...
            text[k]=' ';//...replace it with a space
}

map<string, size_t> GenerateKeywordReport(string fileContents)
{
    /*Load the set of keywords from disk.*/
    set<string> keywords = LoadKeywords();
    
    /*Preprocess the string to allow for easier parsing.*/
    PreprocessString(fileContents);

    /*Populate a stringstream with the file contents.*/
    stringstream tokenizer;
    tokenizer<<fileContents;

    /*Loop over the words in the file, building up the report.*/
    map<string, size_t>result;

    string word;
    while(tokenizer>>word)
        if(keywords.count(word))
            ++result[word];
    
    return result;
}
