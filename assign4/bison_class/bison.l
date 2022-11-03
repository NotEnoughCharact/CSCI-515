%option nodefault
%option noyywrap
%{
#include "byson.tab.h"
%}
%%


[0-9] {return DIGIT;}
[A-Za-z] {return CHARACTER;}//matches any single character
.   /* do nothing */
\n  /* do nothing */

%%
