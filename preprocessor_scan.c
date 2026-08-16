#include "header.h"  

status preprocessor_scan(unsigned int ch,Token *token)
{
    int i=0,j=0;
    token->tok[i++]=ch;

    // Extracts a preprocessor directive from the input stream and validates it.
    if( ch =='#' )
    {
        ch=fgetc(token->input_fp);
        while( (ch != ' ') && (ch != '\n') && (ch != '\r') && (ch != '<') && (ch != '"') )
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i]='\0';
        
        for(j=0; j<7 ; j++)
        {
            if( strcmp(token->tok,directives[j]) == 0)
            {
                printf("%-10d %-15s : PRE-PROCESSOR\n",token->line,token->tok);
                fprintf(token->output_fp,"%-10d %-15s : PRE-PROCESSOR\n",token->line,token->tok);
                break;
            }
        }
        //completing "for loop" without breaking, indicates extracted directive is invalid
        if(j==7)
        {
            printf("%-10d %-15s : PRE-PROCESSOR (ERROR)\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d %-15s : PRE-PROCESSOR (ERROR)\n",token->line,token->tok);
        }

        // Skip spaces after the preprocessor directive
        // and move ch to the next valid character 
        if(ch == ' ')
            while((ch=fgetc(token->input_fp)) == ' ');
        

        if( (ch=='<') || (ch=='"') )
            header_scan(ch,token);
        else if( ((ch >='a') && (ch <='z')) || (ch >='A') && (ch <='Z') )
            macro_scan(ch,token);
        else if( is_numeric_constant(ch,token) )
            return SUCCESS;

        else if(ch=='\n')
            (token->line)++;
        else if(is_terminating_operator(ch,token))
            return SUCCESS;

        return SUCCESS;
    }
}

//This function scans single-line and Multi-line comments
status comment_scan(unsigned int ch,Token *token)
{
    int i=0,j=0;
    token->tok[i++]=ch;

    ch=fgetc(token->input_fp);
    if(ch=='/')
    {
        while( (ch != '\n') && (ch != '\r'))
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i]='\0';

        printf("%-10d COMMENT: %s\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d COMMENT: %s\n",token->line,token->tok);

    }
    else if(ch=='*')
    {
        token->tok[i++]=ch;

        unsigned int prev;
        ch=fgetc(token->input_fp);
        token->tok[i++]=ch;
        prev=ch;

        while( (ch != '/') && (prev!='*'))
        {  
            prev=ch; 
            ch=fgetc(token->input_fp);
            token->tok[i++]=ch;             
        }
        token->tok[i]='\0';
 
        printf("%-10d MULTI-LINE COMMENT: %s\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d COMMENT: %s\n",token->line,token->tok);
    }
}

//This function scans header file name
// and reports HEADER(ERROR) if the syntax is invalid
status header_scan(unsigned int ch,Token *token)
{
    int i=0,flag=0;
    token->tok[i++]=ch;
    ch=fgetc(token->input_fp);
    while( (ch != '>') && (ch != '"') )
    {
        token->tok[i++]=ch;
        ch=fgetc(token->input_fp);
        if(ch=='\r') ch=fgetc(token->input_fp);
        if(ch=='\n' || ch==';')
        {
            flag=1;
            break;
        }   
    }
    if(flag)
    {
        token->tok[i]='\0';
        printf("%-10d %-15s : HEADER (ERROR)\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : HEADER (ERROR)\n",token->line,token->tok);
        if(ch=='\n') 
            (token->line)++;
        else
            is_terminating_operator(ch,token);
    }
    else
    {
        token->tok[i++]=ch;
        token->tok[i]='\0';
        printf("%-10d %-15s : HEADER\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : HEADER\n",token->line,token->tok);
    }

    return SUCCESS;
}

//This Function scans MACROS and their respective Values
status macro_scan(unsigned int ch,Token *token)
{
    int i=0;
    token->tok[i++]=ch;
    ch=fgetc(token->input_fp);
    while( (ch != ' ') )
    {
        token->tok[i++]=ch;
        ch=fgetc(token->input_fp);
    }
    token->tok[i]='\0';
    printf("%-10d %-15s : MACRO\n",token->line,token->tok);
    fprintf(token->output_fp,"%-10d %-15s : MACRO\n",token->line,token->tok);
    
    //skips white spaces
    while( (ch=fgetc(token->input_fp)) == ' ');

    if(ch=='\n')
    {
        (token->line)++;
        return SUCCESS;
    }
    else if(is_terminating_operator(ch,token))
    {
        return SUCCESS;
    }
    else
    {
        i=0;
        while( !((ch == ' ') || (ch == ';') || (ch == '\n') || (ch == '\r')) )
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i]='\0';
        printf("%-10d %-15s : MACRO VALUE\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : MACRO VALUE\n",token->line,token->tok);
    }
    ungetc(ch,token->input_fp);  
}