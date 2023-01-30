#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>

#define ERROR -100
#define OK 100
#define WRONG 0

int file_with_double_quotation(char str[]);
int get_file(char str[]);
int file_input(char str[]);
int well_done();
int error(void(*func)());
void invalid_input();
void invalid_address();
void file_already_existed();
int go_to_address(char path[]);
int create_file();

/////////////////////////////////////////MAIN
int main()
{
    char command[30];
    create_file();
    return 0;
}
////////////////////////////////////////////////////////////////GENERAL
//////////////////////////////////////////input file
int file_with_double_quotation(char str[])
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
int get_file(char str[])
{
    scanf(" %c",&str[0]);
    if(str[0]=='"')
    {
        if(file_with_double_quotation(str)==ERROR)
            return ERROR;
        return OK;
    }else
    {
        scanf("%s",&str[1]);
        return OK;
    }
}
int file_input(char str[])
{
    if(get_file(str)==ERROR)
        return ERROR;
    if(str[0]=='/')
        strcpy(str,&str[1]);
    if(str[strlen(str)-1]=='/')
        str[strlen(str)-1]='\0';
    return OK;
}
////////////////////////////////////////

////////////////////////////////////////////////////////////////RESPONSES
int well_done()
{
    char str[100];
    fgets(str,100,stdin);
    if(strlen(str)!=1)
        printf("additional inputs were ignored\n");
    return OK;
}

int error(void(*func)())
{
    char str[100];
    fgets(str,100,stdin);
    func();
    return ERROR;
}

void invalid_input()
{
    printf("Invalid input\n");
}

void invalid_address()
{
    printf("invalid address\n");
}

void file_already_existed()
{
    printf("file already existed\n");
}
////////////////////////////////////////////////CREATE_FILE

int go_to_address(char path[])
{
    char path2[100];
    int bound=strlen(path);
    int i=0;
    for(;i<bound;i++)
    {
        if(path[i]=='/')
        {
            if(strcmp(path2,"root"))
            {
                return ERROR;
            }
            mkdir(path2);
            path2[i]=path[i];
            path2[i+1]='\0';
            break;
        }
        path2[i]=path[i];
        path2[i+1]='\0';
    }
    for(;i<bound;i++)
    {
        if(path[i]=='/')
        {
            mkdir(path2);
        }
        path2[i]=path[i];
        path2[i+1]='\0';
    }
    strcpy(path,path2);
    ////////
    strcat(path2,"alo123emtehanmikonim");
    FILE* fptr;
    if((fptr=fopen(path2,"w"))==NULL)
    {
        fclose(fptr);
        remove(path2);
        return ERROR;
    }
    fclose(fptr);
    remove(path2);
    return OK;
}
int create_file()
{
    char path[100];
    char flag[50];
    scanf("%s",flag);
    if(strcmp(flag,"--file"))
        return error(*invalid_input);
    if(file_input(path)==ERROR)
        return error(*invalid_input);
    if(go_to_address(path)==ERROR)
        return error(*invalid_address);
    ////////
    FILE* fptr;
    if((fptr=fopen(path,"r"))!=NULL)
    {
        fclose(fptr);
        return error(*file_already_existed);
    }
    ///////
    fptr=fopen(path,"w");
    fclose(fptr);
    return well_done();
}
//////////////////////////////////////////////////////INSERT

/*int path_validation(char str[])
{
    FILE* fptr=fopen(str,"w");
    if(fptr==NULL)
    {
        fclose(fptr);
        remove(str);
        return ERROR;
    }
    fclose(fptr);
    fptr=fopen(str,"r");
    if(fptr==NULL)
    {
        fclose(fptr);
        return WRONG;
    }
    fclose(fptr);
    return OK;
}

int position_validation(int line,int pos,char str[])
{
    FILE* fptr=fopen(str,"r");
    char c;
    int cur_line=1;
    int cur_pos=0;
    while(cur_line<line)
    {
        if(fscanf(fptr,"%c",&c)==0)
        {
            fclose(fptr);
            return ERROR;
        }
        if(c=='\n')
        {
            cur_line++;
        }
    }
    while(cur_pos<pos)
    {
        if(fscanf(fptr,"%c",&c)==0 || c=='\n')
        {
            fclose(fptr);
            return ERROR;
        }
    }
    fclose(fptr);
    return OK;
}

int insert()
{
    char flag[100];
    char path[100];
    int line,pos;
    char input_str[1000];
    int str_check=0,file_check=0,pos_check=0;
    for(int i=0;i<3;i++)
    {
        scanf("%s",flag);
        if(strcmp(flag,"--file")==0)
        {
            if(file_check!=0)
            {
                printf("invalid input\n");
                fgets(input_str,1000,stdin);
                return ERROR
            }
            file_check++;
            get_str(flag);
            file_input(flag);
            if(path_validation(flag)==ERROR)
            {
                printf("wrong address");
                fgets(input_str,1000,stdin);
                return ERROR;
            }
            if(path_validation(flag)==WRONG)
            {
                printf("no such file found");
                fgets(input_str,1000,stdin);
                return ERROR;
            }
        }
    }
}*/


