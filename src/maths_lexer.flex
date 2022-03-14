%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */

// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
#include "maths_parser.tab.hpp"
#include <string>
%}


%%
"int"             {return VARTYPE_INT;}
"while"           { return TOK_WHILE; }
"if"              { return TOK_IF; }
"else"            { return TOK_ELSE; }
"return"          {return TOK_RETURN;}
"break"           {return TOK_BREAK;}   

[0-9]+                   {yylval.number = std::strtod(yytext,0);
                           return TOK_N;}

[a-zA-Z]+                  {yylval.string = new std::string(yytext); 
                           return TOK_VAR;}

[*]               { return TOK_MUL; }
[\/]              { return TOK_DIVIDE;}
[\%]              { return TOK_MOD; }
[+]               { return TOK_PLUS; }
[-]               { return TOK_MINUS; }

"*="              {return TOK_MULASSIGN; }
"/="              {return TOK_DIVASSIGN; }
"+="              {return TOK_ADDASSIGN; }
"-="              {return TOK_SUBASSIGN; }
"%="              {return TOK_MODASSIGN; }
"="               {return TOK_EQASSIGN; }

"=="              { return TOK_EQ; }
"!="             { return TOK_NEQ; }
"<="              { return TOK_LE; }
">="              { return TOK_GE; }
">"               { return TOK_G; }
"<"               { return TOK_L; }

[&]               { return TOK_BIT_AND; }
[|]               { return TOK_BIT_OR; }

[(]               { return TOK_LBRACKET; }
[)]               { return TOK_RBRACKET; }
[\{]              { return TOK_LCBRACKET; }
[\}]              { return TOK_RCBRACKET; }
[;]               { return TOK_SEMICOLON; }
      
[ \t\r\n]+        {;}
. {fprintf(stderr, "Invalid token\n");exit(1);}


%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
