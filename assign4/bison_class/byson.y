 /* directives, preamble code etc. */

%token CHARACTER DIGIT
%{
  #include<iostream>
  int yylex(void);
  void yyerror(const char* err_txt)
  {
    std::cerr << "OUCH: " << err_txt << '\n';
  }
%}

%%

 output_chatter : output_chatter CHARACTER { std::cout << "Got a character!\n";  }
          | output_chatter DIGIT {std::cout << "NUMBER!\n";}
          | %empty
 /* grammar rules */
%%
 /* anything pt here is copied unaltered to the generated c file */
int main()
{
  yyparse();//calls yylex()

}
