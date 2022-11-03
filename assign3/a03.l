/* definitions */
%{
 #include<iostream>
 enum { T_DEFINITE_ARTICLE=1, T_ADJECTIVE, T_IDENTIFIERS, T_NOUN, T_PREPOSITION, T_PERIOD, T_PRONOUN,  T_INTEGER, T_VERB };
%}
%option noyywrap

%%



brown|quick|lazy {return T_ADJECTIVE;}
"."	{return T_PERIOD;}
the|The  {return T_DEFINITE_ARTICLE;}
fox|dog|wall|liquid|bottles {return T_NOUN;}
jumped|see {return T_VERB;}
over|on|of {return T_PREPOSITION;}
[0-9]+ {return T_INTEGER;}
"I" {return T_PRONOUN;}

%%
/* user code */

int main()
{
  int temp;
  while(temp = yylex())
  {
    std::cout << temp;
  }
	return 0;
}
