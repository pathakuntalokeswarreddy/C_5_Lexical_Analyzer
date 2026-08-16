#include "header.h"

//This function scans Identifiers and Keywords
status word_scan(unsigned int ch,Token *token)
{
    int i=0,j=0;
    token->tok[i++]=ch;
  
    ch=fgetc(token->input_fp);
    while( (ch != ' ') && (ch != '\n') && (ch != '\r') && (ch != ';')  &&  (!(is_symbol(ch,token))) && (!(is_operator(ch,token)))  ) 
    {
        token->tok[i++]=ch; 
        ch=fgetc(token->input_fp);  
    }
    token->tok[i]='\0'; 
    
    // Match the scanned word with the Reserved_Keyword list
    // and stop when a match is found
    for(j=0; j<19 ; j++)
    {
        if( strcmp(token->tok,res_keywords[j]) == 0)
        {
            printf("%-10d %-15s : RESERVED KEYWORD\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d %-15s : RESERVED KEYWORD\n",token->line,token->tok);
            ungetc(ch,token->input_fp);
            return SUCCESS;
        }
    }

    // Match the scanned word with the Non_Reserved_Keyword list
    // and stop when a match is found
    for(j=0; j<14 ; j++)
    {  
        if( strcmp(token->tok,non_res_keywords[j]) == 0)
        {
            printf("%-10d %-15s : NON RESERVED KEYWORD\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d %-15s : NON RESERVED KEYWORD\n",token->line,token->tok);
            ungetc(ch,token->input_fp);
            return SUCCESS; 
        }
    }

    // If no keyword matches from the lists, then the scanned word is an identifier
    printf("%-10d %-15s : IDENTIFIER\n",token->line,token->tok);
    fprintf(token->output_fp,"%-10d %-15s : IDENTIFIER\n",token->line,token->tok);
    ungetc(ch,token->input_fp);
    return SUCCESS;
}