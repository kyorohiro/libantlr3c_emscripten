#include <stdio.h>
#include <antlr3.h>
#include "CalcLexer.h"
#include "CalcParser.h"


int run(pANTLR3_BASE_TREE tree) {
  pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
  if(tok == NULL) {
    int len = tree->getChildCount(tree);
    int ret = 0;
    for(int i = 0; i < len; i++) {
        int v = run((pANTLR3_BASE_TREE)tree->getChild(tree, i));
        printf("ret = %d\r\n", v);
        ret += v;
    }
    return ret;
  }
  switch(tok->type) {
    case INT:{
        char* s = (char*) tree->getText(tree)->chars;
        //printf("int : t:%d; v=%s\r\n", tok->type, s);
        return atoi(s);
      }
      break;
    case PLUS:
      //printf("plus : %d\r\n", tok->type);
      return run((pANTLR3_BASE_TREE)tree->getChild(tree, 0)) + run((pANTLR3_BASE_TREE)tree->getChild(tree, 1));
    case MINUS:
      //printf("minus : %d\r\n", tok->type);
      return run((pANTLR3_BASE_TREE)tree->getChild(tree, 0)) - run((pANTLR3_BASE_TREE)tree->getChild(tree, 1));
    case TIMES:
      //printf("times : %d\r\n", tok->type);
      return run((pANTLR3_BASE_TREE)tree->getChild(tree, 0)) * run((pANTLR3_BASE_TREE)tree->getChild(tree, 1));
      break;
    default:
      printf("def : %d\r\n", tok->type);
  }
  return 0;
}

int main(int argc, char** argv) {
  char* src = "1+1\r\n""1+1\r\n";

  pANTLR3_INPUT_STREAM  input = antlr3StringStreamNew((pANTLR3_UINT8)src, ANTLR3_ENC_8BIT, strlen(src),(pANTLR3_UINT8)"ABCD");
  pCalcLexer lex = CalcLexerNew(input);
  pANTLR3_COMMON_TOKEN_STREAM tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
  pCalcParser parser = CalcParserNew(tokens);

  CalcParser_gprog_return r = parser->gprog(parser);
  pANTLR3_BASE_TREE tree = r.tree;
  int v = run(tree);
  printf("result: %d \r\n", v);

  return 0;
}
