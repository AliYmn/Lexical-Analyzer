#include <string>
#include <iostream>
#include <vector>

using namespace std;

class LexicalAnalyzer{
  public:
    void getFileName(ifstream &);
    void scanFile(ifstream &);
    void analyzeToken(vector<char>);
    bool isFunction(string); // class, void, int, float, double etc.
    bool isStatement(string); // if , while , for, switch...
    bool isAssignmentOperator(string); //  +,=,/,* ...
    bool isParenL(string); // (
    bool isParenR(string); // )
    bool isCurlL(string); // {
    bool isCurlR(string); // }
    bool isSemicolon(string);// ;
    bool isComment(string); //  /* */ , //
    bool isWhiteSpace(char); // calculating all spaces.
    bool isSymbol(char); // calculating all symbols.
    bool isVar(string); // variables int,double,char,string,bool...
  private:
    vector<char> token;
};
