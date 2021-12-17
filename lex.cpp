#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "LexicalAnalyzer.h"

using namespace std;

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
  string fileName;

  cout << "Enter file name: ";

  // keep prompting until user has typed in a valid file name
  while (true)
  {
    cin >> fileName;
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
    // parse line to get tokens
    for (int x = 0; x < readLine.length(); x++)
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
    }
  }
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

// returns true if argument is a symbol
bool LexicalAnalyzer::isSymbol(char ch)
{
  if (ch == '(' || ch == ')' || ch == ',' || ch == '{' || ch == '}' || ch == '+' ||
      ch == '-' || ch == '*' || ch == '/' || ch == '&' || ch == '!' || ch == '|' || ch == ';')
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
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a VAR keyword
bool LexicalAnalyzer::isVar(string currentToken)
{
  if (currentToken == "int" || currentToken == "float" || currentToken == "long" || currentToken == "double" || currentToken == "char" || currentToken == "string" || currentToken == "bool" || currentToken == "signed" || currentToken == "unsigned")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a left parentesis
bool LexicalAnalyzer::isParenL(string currentToken)
{
  if (currentToken == "(")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a right parentesis
bool LexicalAnalyzer::isParenR(string currentToken)
{
  if (currentToken == ")")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a left curly brace
bool LexicalAnalyzer::isCurlL(string currentToken)
{
  if (currentToken == "{")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a right curly brace
bool LexicalAnalyzer::isCurlR(string currentToken)
{
  if (currentToken == "}")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns true if argument is a SEMICOLON
bool LexicalAnalyzer::isSemicolon(string currentToken)
{
  if (currentToken == ";")
  {
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
    cout << "Comments:         " << currentToken << endl;
  }
  // checks if token is a function keyword
  else if (isFunction(currentToken))
  {
    cout << "Functions or Classes :         " << currentToken << endl;
  }

  else if (isAssignmentOperator(currentToken))
  {
    cout << "Assignment Operators :         " << currentToken << endl;
  }

  // checks if token is a if keyword
  else if (isStatement(currentToken))
  {
    cout << "Statements :               " << currentToken << endl;
  }

  // checks if token is a VAR keyword
  else if (isVar(currentToken))
  {
    cout << "Variables :             " << currentToken << endl;
  }

  // checks if token is a semicolon
  else if (isSemicolon(currentToken))
  {
    cout << "Semicolons :    " << currentToken << endl;
  }

  // checks if token is a left parentesis
  else if (isParenL(currentToken))
  {
    cout << "Open parenthesis :            " << currentToken << endl;
  }

  else if (isParenR(currentToken))
  {
    cout << "Closed parenthesis :            " << currentToken << endl;
  }

  // checks if token is left curly
  else if (isCurlL(currentToken))
  {
    cout << "Open curly braces :             " << currentToken << endl;
  }

  // checks if token is right curly
  else if (isCurlR(currentToken))
  {
    cout << "Closed curly braces :             " << currentToken << endl;
  }
}
