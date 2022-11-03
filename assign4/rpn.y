 /* Define your tokens here, T_PLUS, T_MINUS, et cetera */
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_PRINT T_SIZE T_INT_CONSTANT T_ERROR

%{
  /* add all the necessary C++ header files and
     variables required to manage a stack (hint: see orig_rpn.l)
   */
   #include<stack>
   #include<string>
   #include<iostream>
   using std::cout;
   using std::cerr;
   using std::endl;
   using std::stoi;
   std::stack<int> rpnstack;
   bool stack_error(int expected);



  /* The prototype to yylex() is required since its source is
     in a separate file */
  int yylex();

  /* we must write this function. Generated code calls it */
  void yyerror(const char* err);


%}

%%
my_start_sym :
        %empty
      | my_start_sym misc_non_term_symbol

misc_non_term_symbol: T_INT_CONSTANT {rpnstack.push(yylval);}
    | T_PLUS { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(a+b);}
    | T_MINUS { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(b-a);}
    | T_MULTIPLY { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(b*a);}
    | T_DIVIDE { if(stack_error(2)) break; int a=rpnstack.top(); rpnstack.pop(); int b=rpnstack.top(); rpnstack.pop(); rpnstack.push(b/a);}
    | T_PRINT { if(stack_error(1)) break; cout << rpnstack.top() << endl; rpnstack.pop(); }
    | T_SIZE { cout << "stack=" << rpnstack.size() << endl; }
    | T_ERROR { cerr << "DOES NOT COMPUTE!" << endl; }
%%

int main(int argc, char** argv)
{
  cout << "Welcome to rpn calculator. <ctrl>-d to quit"<<endl;
  yyparse();
  yylex();
  return 0;
}

bool stack_error(int expected)
{
  if(rpnstack.size() < expected)
  {
    cerr << "Stack size to small!\n";
    return 1;
  }
  return 0;
}

void yyerror(const char* err)
{
  cerr << err << endl;
}
