#include "header.h"

status scan(Token *token)
{
    printf("---------------------------------------------\n");
    printf("%-10s %-15s %s\n","Line No","Token","Token Type");
    printf("---------------------------------------------\n");

    fprintf(token->output_fp,"---------------------------------------------\n");
    fprintf(token->output_fp,"%-10s %-15s %s\n","Line No","Token","Token Type");
    fprintf(token->output_fp,"---------------------------------------------\n");

    unsigned int ch;
    token->line =1;
    while(1)
    {
        ch=fgetc(token->input_fp);
        
        // File created on windows use \r\n for line breaks. This will be not fixed by Linux 
        // and macOS systems automatically. So to overcome this, we have to check for '\r' manually.
        // if found, just move one character ahead. 
        if(ch=='\r') 
            ch=fgetc(token->input_fp);
        
        if(ch=='\n')
            (token->line)++;
        
        // skips all space characters
        while(ch==' ' || ch=='\n' || ch=='\t')
        {
            ch=fgetc(token->input_fp);
            if(ch=='\n') 
                (token->line)++;
        }
        
        if( ch=='#' )
        {
            if(preprocessor_scan(ch,token))
                continue;
            else
                return FAILURE;
        }

        else if( ch=='/' ) 
        {
            if(comment_scan(ch,token))
                continue;
            else
                return FAILURE;
        }

        else if( (isalpha(ch)) || ch=='_' )
        {   
            if(word_scan(ch,token))
                continue;
            else
                return FAILURE;
        }

        else if( is_symbol(ch,token) )
        {
            if ( (ch=='(') || (ch=='{') || (ch=='['))
            {
                printf("%-10d %-15c : OPEN_BRACE\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : OPEN_BRACE\n",token->line,ch);
            }
            else if( (ch==')') || (ch=='}') || (ch==']') )
            {
                printf("%-10d %-15c : CLOSE_BRACE\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : CLOSE_BRACE\n",token->line,ch);
            }
            else
            {
                printf("%-10d %-15c : SYMBOL\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : CLOSE_BRACKET\n",token->line,ch);
            }
            continue;
        }

        else if( is_operator(ch,token) )
        {   
            if( !is_compound_operator(ch,token) )
            {
                printf("%-10d %-15c : OPERATOR\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : OPERATOR\n",token->line,ch);
            }
            continue;
        }
        else if( is_numeric_constant(ch,token) )
            continue;

        else if( is_character(ch,token) )
            continue;

        else if( is_string_literal(ch,token) )
            continue;
        
        else if(is_terminating_operator(ch,token))
            continue;
        
        else if(ch == EOF)
            break;
    }
    return SUCCESS;
}