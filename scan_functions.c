#include "header.h"

status is_symbol(char ch,Token *token)
{
    for(int j=0; j<7; j++)
    {
        if(ch==symbol[j])
        {    
            return SUCCESS;
        }
    }
    return FAILURE;
}

status is_operator(char ch,Token *token)
{
    for(int j=0; j<14; j++)
    {
        if(ch==operators[j])
        {
            return SUCCESS;
        } 
    }
    return FAILURE;
}

status is_compound_operator(char ch,Token *token)
{
    int i=0,j=0;
    token->tok[i++]=ch;
    ch=fgetc(token->input_fp);
    token->tok[i++]=ch;
    token->tok[i]='\0';
 
    for(j=0; j<16; j++)
    {
        if( strcmp(token->tok,compound_operators[j]) == 0)
        {
            return SUCCESS;
        } 
    }
    if(j==16)
    {
        fseek(token->input_fp,-1,SEEK_CUR);
        return FAILURE;
    }
}
status is_numeric_constant(unsigned int ch,Token *token)
{
    
    if(ch>='0' && ch<='9')
    {
        int i=0;
        token->tok[i++]=ch;
        ch=fgetc(token->input_fp);
        while( (ch!=' ') && (ch!='\r')&& (ch!='\n') && (ch!=';') && !(is_operator(ch,token)) && !(is_symbol(ch,token)))
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i]='\0';

        printf("%-10d %-15s : NUMERIC CONSTANT\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : NUMERIC CONSTANT\n",token->line,token->tok);
        if(ch=='\n')
        {
            (token->line)++;
        }
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

        else if(is_operator(ch,token))
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
        else if(ch==';')
        {
            printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        }
        return SUCCESS;
    }
    else
        return FAILURE;
}

status is_string_literal(unsigned int ch,Token *token)
{
    if(ch == '"')
    {   
        int i=0;
        token->tok[i++]=ch;
        ch=fgetc(token->input_fp);
        while( (ch!='"'))
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i++]=ch;
        token->tok[i]='\0';

        printf("%-10d %-15s : STRING LITERAL\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : STRING LITERAL\n",token->line,token->tok);
        if(ch=='\n')
        {
            (token->line)++;
        }
        else if(ch==';')
        {
            printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            while( (ch=fgetc(token->input_fp))!='\n' );
            (token->line)++;
        }
        return SUCCESS;
    }
    else
        return FAILURE;
}
