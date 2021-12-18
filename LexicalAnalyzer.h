#include <string>
#include <iostream>
#include <vector>

using namespace std;

class LexicalAnalyzer{
  public:
    // lexical analysis
    void getFileName(ifstream &);
    void scanFile(ifstream &);
    void analyzeToken(vector<char>);
    void list_dir(const char*);
    bool isFunction(string); // class, void, int, float, double etc.
    bool isStatement(string); // if , while , for, switch...
    bool isLib(string); // #include
    bool isAssignmentOperator(string); //  +,=,/,* ...
    bool isParenL(char); // (
    bool isParenR(char); // )
    bool isCurlL(char); // {
    bool isCurlR(char); // }
    bool isSemicolon(char);// ;
    bool isComment(string); //  /* */ , //
    bool isWhiteSpace(char); // calculating all spaces.
    bool isSymbol(char); // calculating all symbols.
    bool isVar(string); // variables int,double,char,string,bool...
    bool syntaxCheck(string,int); // syntax check only for while,if and for
    void isCorrect(char*); // syntax check only for while,if and for
  private:
    vector<char> token;
};
