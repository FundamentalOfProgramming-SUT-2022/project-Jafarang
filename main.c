#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>

#define ERROR -100
#define OK 100
#define WRONG 0

int input_with_double_quotation(char str[]);
int get_str(char str[]);
void input_for_create_file(char str[]);
int create_file();

////////////////////////////////////////
int main()
{
    char command[30];
    create_file();
    return 0;
}
////////////////////////////////////////
int input_with_double_quotation(char str[])
{
    gets(str);
    int bound=strlen(str);
    for(int i=bound-1;i>0;i--)
    {
        if(str[i]=='"')
        {
            str[i]='\0';
            strcpy(str,&str[1]);
            return OK;
        }
    }
    return ERROR;
}
int get_str(char str[])
{
    scanf(" %c",&str[0]);
    if(str[0]=='"')
    {
        if(input_with_double_quotation(str)==ERROR)
            return ERROR;
        return OK;
    }else
    {
        scanf("%s",str);
        return OK;
    }
}
////////////////////////////////////////////////
void input_for_create_file(char str[])
{
    if(str[0]=='/')
        strcpy(str,&str[1]);
    if(str[strlen(str)-1]=='/')
        str[strlen(str)-1]='\0';
}
int create_file()
{
    char path[100];
    char path2[100];
    scanf(" --file");
    if(get_str(path)==ERROR)
    {
        printf("Invalid input\n");
        return ERROR;
    }
    input_for_create_file(path);
    /////////
    int bound=strlen(path);
    for(int i=0;i<bound;i++)
    {
        if(path[i]=='/')
        {
            mkdir(path2);
        }
        path2[i]=path[i];
        path2[i+1]='\0';
    }
    ////////
    FILE* fptr;
    if((fptr=fopen(path,"r"))!=NULL)
    {
        printf("file already exists\n");
        fclose(fptr);
        return WRONG;
    }
    fptr=fopen(path,"w");
    fclose(fptr);
    return OK;
}





