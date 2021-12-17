#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "LexicalAnalyzer.h"

using namespace std;

  // calculate global variables
  int comments = 0; 
  int variables = 0;
  int function_classes = 0;
  int statements = 0;
  int libs = 0;
  int open_parent = 0;
  int off_parent = 0;
  int open_curly = 0;
  int off_curly = 0;
  int semicolon = 0;
  int lines = 0;
  int total = 0;

int main()
{
  LexicalAnalyzer lexicalAnalyzer;
  ifstream myFile;

  lexicalAnalyzer.getFileName(myFile);
  lexicalAnalyzer.scanFile(myFile);

  return 0;
}


// allows user to enter a file name to open
void LexicalAnalyzer::getFileName(ifstream &myFile)
{
  string fileName = "input.txt";

  // cout << "Enter file name: ";

  // keep prompting until user has typed in a valid file name
  while (true)
  {
    // cin >> fileName;
    myFile.open(fileName);

    if (!myFile)
    {
      cout << "Invalid file name, Please enter a valid file name: ";
    }
    else
    {
      break;
    }
  }
}

// goes through file line by line to analyze tokens
void LexicalAnalyzer::scanFile(ifstream &myFile)
{
  string currentToken;
  string readLine;
  char lookahead;
  string myNumber = "";
  string myString = "";
  int tempX;


  // continue to go through input file line by line
  while (getline(myFile, readLine))
  {
    lines = lines +1;
    // parse line to get tokens
    for (int x = 0; x <= readLine.length(); x++)
    {
      tempX = x;
      lookahead = readLine[x];

      // add character to vector to keep track of token
      token.push_back(readLine[x]);
      // analyze token since white space is read
      if (isWhiteSpace(lookahead))
      {
        token.pop_back();
        analyzeToken(token);
        token.clear();
      }

      // checks if token is a left parentesis
      if (isParenL(readLine[x]))
      {
        // cout << "Open parenthesis :            " << readLine[x] << endl;
      }

      if (isParenR(readLine[x]))
      {
        // cout << "Closed parenthesis :            " << readLine[x] << endl;
      }

      // checks if token is left curly
      if (isCurlL(readLine[x]))
      {
        // cout << "Open curly braces :             " << readLine[x] << endl;
      }

      // checks if token is right curly
      if (isCurlR(readLine[x]))
      {
        // cout << "Closed curly braces :             " << readLine[x] << endl;
      }
      
      // checks if token is a semicolon
      if (isSemicolon(readLine[x]))
      {
        // cout << "Semicolons :    " << readLine[x] << endl;
      }

    }
  }

  // display all calculates.
  cout << "### Lexical Analysis Starting... ###" << endl;
  cout << "Comments : " << comments << endl;
  cout << "Variables : " << variables << endl;
  cout << "Function or Classes : " << function_classes << endl;
  cout << "Statements : " << statements << endl;
  cout << "Modules : " << libs << endl;
  cout << "open parenthesis : " << open_parent << endl;
  cout << "open curly braces : " << open_curly << endl;
  cout << "semicolon : " << semicolon << endl;
  cout << "lines : " << lines << endl;
  total = comments + variables + function_classes + statements + libs + open_parent + open_curly + semicolon + lines;
  cout << "totals : " << total << endl;
  if ((off_curly == open_curly) && (off_parent == open_parent)){
    cout << "Bracket balance successful!" << endl;
  }
  else{
    cout << "Bracket balance unsuccessful!" << endl;
  }
  cout << "### Lexical Analysis Ending... ###" << endl;

  // cout << "### Syntax Analysis Starting... ###" << endl;
  // cout << "### Syntax Analysis Ending... ###" << endl;

}


//******************************************************************************

// returns true if argument is a whitespace
bool LexicalAnalyzer::isWhiteSpace(char ch)
{
  if (ch == ' ' || ch == '\n' || ch == '\0')
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a FUNCTION keyword
bool LexicalAnalyzer::isFunction(string currentToken)
{
  if (currentToken == "class" || currentToken == "void" || currentToken == "main()" || currentToken == "main")
  {
    function_classes = function_classes +1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a IF keyword
bool LexicalAnalyzer::isLib(string currentToken)
{
  if (currentToken[0] == '#')
  {
    libs = libs +1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a IF keyword
bool LexicalAnalyzer::isStatement(string currentToken)
{
  if (currentToken == "if" || currentToken == "else" || currentToken == "while" || currentToken == "for" || currentToken == "switch")
  {
    statements = statements +1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a variable keyword
bool LexicalAnalyzer::isVar(string currentToken)
{
  if (currentToken == "int" || currentToken == "float" || currentToken == "long" || currentToken == "double" || currentToken == "char" || currentToken == "string" || currentToken == "bool" || currentToken == "signed" || currentToken == "unsigned")
  {
    variables = variables + 1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a left parentesis
bool LexicalAnalyzer::isParenL(char currentToken)
{
  if (currentToken == '(')
  {
    open_parent = open_parent + 1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a right parentesis
bool LexicalAnalyzer::isParenR(char currentToken)
{
  if (currentToken == ')')
  {
    off_parent = off_parent +1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a left curly brace
bool LexicalAnalyzer::isCurlL(char currentToken)
{
  if (currentToken == '{')
  {
    open_curly = open_curly +1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a right curly brace
bool LexicalAnalyzer::isCurlR(char currentToken)
{
  if (currentToken == '}')
  {
    off_curly = off_curly + 1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a SEMICOLON
bool LexicalAnalyzer::isSemicolon(char currentToken)
{
  if (currentToken == ';')
  {
    semicolon = semicolon +1;
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a ASSIGNMENT operator
bool LexicalAnalyzer::isAssignmentOperator(string currentToken)
{
  if (currentToken == "+" || currentToken == "-" || currentToken == "=" || currentToken == "*" || currentToken == "/" || currentToken == "%" || currentToken == "++" || currentToken == "--" || currentToken == "==" || currentToken == "!=" || currentToken == "<" || currentToken == ">" || currentToken == "<=" || currentToken == ">=")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if a argument is a COMMENT symbol (/* or //)
bool LexicalAnalyzer::isComment(string currentToken)
{
  if (currentToken == "//" || currentToken == "/*")
  {
    comments = comments + 1;
    return true;
  }
  else
  {
    return false;
  }
}


// figures out token type of argument
void LexicalAnalyzer::analyzeToken(vector<char> token)
{
  string currentToken;
  for (int x = 0; x < token.size(); x++)
  {
    currentToken += token[x];
  }
  // checks if token is a function keyword
  if (isComment(currentToken))
  {
    // cout << "Comments:         " << currentToken << endl;
  }
  // checks if token is a function keyword
  else if (isFunction(currentToken))
  {
    // cout << "Functions or Classes :         " << currentToken << endl;
  }

  else if (isAssignmentOperator(currentToken))
  {
    // cout << "Assignment Operators :         " << currentToken << endl;
  }

  // checks if token is a if keyword
  else if (isStatement(currentToken))
  {
    // cout << "Statements :               " << currentToken << endl;
  }

  // checks if token is a VAR keyword
  else if (isVar(currentToken))
  {
    // cout << "Variables :             " << currentToken << endl;
  }

  // checks if token is lib
  else if (isLib(currentToken))
  {
    // cout << "Libs :             " << currentToken << endl;
  }
}



