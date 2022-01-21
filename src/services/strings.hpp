#include <iostream>
#include <vector>

using namespace std;

class StringsClass {
  private:
  public:
  StringsClass() {};

  vector<string> split( string line, char limitator, int start = 0 ) {
    vector<string> myStrings;
    string substring = "";
    for ( int i = 0; i < line.length() - 1; i++ ) {
      char caracter = line[i];
      if ( caracter != limitator ) {
        substring += caracter;
      }
      else {
        myStrings.push_back( substring );
        substring = "";
      }
      if ( i == line.length() - 2 ) {
        substring += line[i + 1];
        myStrings.push_back( substring );
        substring = "";
      }
    }

    return myStrings;
  }

  bool findString( string toFind, string str ) {
    size_t found = str.find( toFind.c_str() );
    return found != string::npos;
  }
};