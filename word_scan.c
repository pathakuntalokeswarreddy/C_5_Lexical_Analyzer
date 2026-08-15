#include "header.h"

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

    for(j=0; j<19 ; j++)
    {
        if( strcmp(token->tok,res_keywords[j]) == 0)
        {
            printf("%-10d %-15s : RESERVED KEYWORD\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d %-15s : RESERVED KEYWORD\n",token->line,token->tok);
            return SUCCESS;
        }
    }

    for(j=0; j<14 ; j++)
    { 
        if( strcmp(token->tok,non_res_keywords[j]) == 0)
        {
            printf("%-10d %-15s : NON RESERVED KEYWORD\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d %-15s : NON RESERVED KEYWORD\n",token->line,token->tok);
            if( is_symbol(ch,token) )
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
            }
            else if( is_operator(ch,token) )
            {   
                if( is_compound_operator(ch,token) )
                {
                    printf("%-10d %-15s : COMPOUND OPERATOR\n",token->line,token->tok);
                    fprintf(token->output_fp,"%-10d %-15s : COMPOUND OPERATOR\n",token->line,token->tok);
                }
                else
                {
                    printf("%-10d %-15c : OPERATOR\n",token->line,ch);
                    fprintf(token->output_fp,"%-10d %-15c : OPERATOR\n",token->line,ch);
                }
            }
            else if(ch ==';')
            {
                printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            }
            return SUCCESS;
        }
    }
    printf("%-10d %-15s : IDENTIFIER\n",token->line,token->tok);
    fprintf(token->output_fp,"%-10d %-15s : IDENTIFIER\n",token->line,token->tok);

    if(ch==' ')        
        while((ch=fgetc(token->input_fp) )== ' ');
            
    if( is_symbol(ch,token) )
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
        return SUCCESS;
    }
    
    else if( is_operator(ch,token) )
    {   
        if( is_compound_operator(ch,token) )
        {
            printf("%-10d %-15s : COMPOUND OPERATOR\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d %-15s : COMPOUND OPERATOR\n",token->line,token->tok);
        }
        else
        {
            printf("%-10d %-15c : OPERATOR\n",token->line,ch);
            fprintf(token->output_fp,"%-10d %-15c : OPERATOR\n",token->line,ch);
        }
        return SUCCESS;
    }
    else if( is_numeric_constant(ch,token) )
    {
        return SUCCESS;
    }
    else if(ch=='\n')
    {
        (token->line)++;
        return SUCCESS;
    }
    else if(ch==';')
    {
        printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        while( (ch=fgetc(token->input_fp))!='\n' );
        (token->line)++;
        return SUCCESS;
    } 
    
    return SUCCESS;
}