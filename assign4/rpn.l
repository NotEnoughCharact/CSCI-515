 /* eliminate the need to link in the fl library */
%option noyywrap

 /* No longer allow default characters to
    fall through scanner*/
%option nodefault


%{
  /* don't forget to include the bison-generated header file */
  #include<string>
   #include<iostream>
  using std::stoi;
  #include "rpn.tab.h"
%}

%%

[0-9]+  { yylval=stoi(yytext); return T_INT_CONSTANT; }
"+"     { return T_PLUS; }
"-"     { return T_MINUS; }
"*"     { return T_MULTIPLY; }
"/"     { return T_DIVIDE; }
\.      { return T_PRINT; }
\?      { return T_SIZE; }
[ \t\n]      /* do nothing */
.       { return T_ERROR; }

%%
