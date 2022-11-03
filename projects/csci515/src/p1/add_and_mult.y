%union {
  int myunion_int;
  double myunion_double;
}

%type <myunion_double> expn;

%token <myunion_int> T_INT;
%token <myunion_double> T_DOUBLE;
%token T_ADD
%token T_MULT

/* A token's level of precedence is determined by the token's 
 * relative position in the file to other tokens with precedence.
 * The higher/earlier in the file, the lower the precedence */
%left T_ADD
%left T_MULT

%{
  #include<iostream>
  using namespace std;
  int yylex();
  int yyerror(const char* err);
%}

%%

some_start_symbol : expn {cout << $1 << endl;}

expn : expn T_ADD expn  {$$=$1+$3;}
     | expn T_MULT expn {$$=$1*$3;}
     | T_INT {$$=$1;}
     | T_DOUBLE {$$=$1;}

%%

int main(int argc, char** argv)
{
  yyparse();
}

int yyerror(const char*err)
{
  cerr << err << endl;
  return 1;
}
