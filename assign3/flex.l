/* definitions */
%{
 #include<iostream>
 enum { T_PERIOD=1, T_INT, T_IDENTIFIERS };
%}
%option noyywrap

%%

"."	{return T_PERIOD;}
int  {std::cout << "int";}
[a-z]+ {std::cout << "word";}

%%
/* user code */

int main()
{
	yylex();
	return 0;
}
