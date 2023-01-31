#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>

#define ERROR -100
#define OK 100
#define WRONG 0

int get_file(char str[]);
int file_input(char str[]);
int check_wrong_address(char path[]);
int find_position(int line,int pos,char str[]);
int check_existance_of_file(char path[]);
int str_with_double_quotation(char str[]);
int get_str(char str[]);
int check_position(char path[],int sign,int size,int position);
int get_begining_of_file(char path[],int position,char str[]);
int get_end_of_file(char path[],int position,char str[]);
int get_str_from_file(char path[],int position,int size,char str[]);
int rebuild(char path[],char begining_str[],char str[],char end_str[]);
//////////////////////////////////////////
int well_done();
int error(void(*func)());
void invalid_input();
void invalid_address();
void file_already_existed();
void out_of_bound();
//////////////////////////////////////////
int go_to_address(char path[]);
int create_file();
int insert();
int cat();
int remove_str();
/////////////////////////////////////////MAIN
int main()
{
    char command[30];
    //create_file();
    //get_str(command);
    //printf("%s",command);
    //insert();
    //cat();
    //remove_str();
    //char path[]={"root/test.txt"};
    //get_end_of_file(path,5,command);
    /*get_str(command);
    FILE*fptr=fopen("root/test.txt","w");
    fprintf(fptr,"%s",command);
    fclose(fptr);
    char c;
    fptr=fopen("root/test.txt","r");
    for(int i=0;i<strlen(command);i++)
    {
        //fseek(fptr,i,SEEK_SET);
        fscanf(fptr,"%c",&c);
        printf("*%c%d",c,c);
    }
    fclose(fptr);*/
    /*get_end_of_file("root/test.txt",8,command);
    for(int i=0;i<strlen(command);i++)
    {
        printf("*%c",command[i]);
    }*/
    //printf("%s",command);
    return 0;
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
void no_such_file()
{
    printf("no such file found\n");
}
void no_such_position()
{
    printf("no such position\n");
}
void out_of_bound()
{
    printf("out_of_bound\n");
}
////////////////////////////////////////////////////////////////GENERAL
//////////////////////////////////////////input file
int get_file(char str[])
{
    scanf(" %c",&str[0]);
    if(str[0]=='"')
    {
        if(str_with_double_quotation(str)==ERROR)
        {
            return ERROR;
        }
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
int check_wrong_address(char str[])
{
    char path[100];
    strcpy(path,str);
    strcat(path,"alo123emtehanmikonim");
    FILE* fptr;
    if((fptr=fopen(path,"w"))==NULL)
    {
        fclose(fptr);
        remove(path);
        return ERROR;
    }
    fclose(fptr);
    remove(path);
    return OK;
}
int check_existance_of_file(char path[])
{
    FILE* fptr=fopen(path,"r");
    if(fptr==NULL)
    {
        fclose(fptr);
        return ERROR;
    }
    fclose(fptr);
    return OK;
}
int find_position(int line,int pos,char str[])
{
    FILE* fptr=fopen(str,"r");
    char c;
    int cur_line=1;
    int cur_pos=0;
    int index=0;
    while(cur_line<line)
    {
        index++;
        if(fscanf(fptr,"%c",&c)==-1)
        {
            fclose(fptr);
            return ERROR;
        }
        if(c=='\n')
        {
            cur_line++;
            //index++;
        }
    }
    while(cur_pos<pos)
    {
        index++;
        cur_pos++;
        if(fscanf(fptr,"%c",&c)==-1 || c=='\n')
        {
            fclose(fptr);
            return ERROR;
        }
    }
    fclose(fptr);
    return index;
}
int str_with_double_quotation(char str[])
{
    int i=0;
    while(1)
    {
        str[i]=fgetc(stdin);
        switch(str[i])
        {
            case '"':
                str[i]='\0';
                return OK;
            case '\n':
                fseek(stdin,-2,SEEK_END);
            case '\0':
                str[i]='\0';
                return ERROR;
            case '\\':
                i++;
                str[i]=fgetc(stdin);
                switch(str[i])
                {
                    case 'n':
                        str[i-1]='\n';
                        break;
                    case '"':
                        str[i-1]='"';
                        break;
                    case '\\':
                        str[i-1]='\\';
                        break;
                    case '\n':
                        fseek(stdin,-2,SEEK_END);
                    case '\0':
                        str[i-1]='\\';
                        str[i]='\0';
                        return ERROR;
                    default :
                        str[i-1]='\\';
                        i++;
                        break;
                }
                break;
            default :
                i++;
                break;
        }
    }
}
int get_str(char str[])
{
    scanf(" %c",&str[0]);
    if(str[0]=='"')
    {
        if(str_with_double_quotation(str)==ERROR)
            return ERROR;
        return OK;
    }else
    {
        int i=0;
        if(str[i]=='\\')
        {
            i++;
            str[i]=fgetc(stdin);
            switch(str[i])
            {
                case 'n':
                    str[i-1]='\n';
                    break;
                case '"':
                    str[i-1]='"';
                    break;
                case '\\':
                    str[i-1]='\\';
                    break;
                case '\n':
                    fseek(stdin,-2,SEEK_END);
                case '\0':
                case ' ':
                    str[i-1]='\\';
                    str[i]='\0';
                    return OK;
                default :
                    str[i-1]='\\';
                    i++;
                    break;
            }
        }else
            i++;
        while(1)
        {
            str[i]=fgetc(stdin);
            switch(str[i])
            {
                case '\n':
                    fseek(stdin,-2,SEEK_END);
                case '\0':
                case ' ':
                    str[i]='\0';
                    return OK;
                case '\\':
                    i++;
                    str[i]=fgetc(stdin);
                    switch(str[i])
                    {
                        case 'n':
                            str[i-1]='\n';
                            break;
                        case '"':
                            str[i-1]='"';
                            break;
                        case '\\':
                            str[i-1]='\\';
                            break;
                        case '\n':
                            fseek(stdin,-2,SEEK_END);
                        case '\0':
                        case ' ':
                            str[i-1]='\\';
                            str[i]='\0';
                            return OK;
                        default :
                            str[i-1]='\\';
                            i++;
                            break;
                    }
                    break;
                default :
                    i++;
                    break;
            }
        }
    }
}
int check_position(char path[],int sign,int size,int position)
{
    FILE* fptr;
    char c;
    if(size==0)
        return position;
    if(sign==-1)
    {
        position-=size;
        if(position<0)
            return ERROR;
    }else
    {
        fptr=fopen(path,"r");
        for(int i=0;i<position+size;i++)
        {
            if(fscanf(fptr,"%c",&c)==-1)
            {
                fclose(fptr);
                return ERROR;
            }
        }
        fclose(fptr);
    }
    return position;
}
int get_begining_of_file(char path[],int position,char str[])
{
    FILE* fptr=fopen(path,"r");
    for(int i=0;i<position;i++)
    {
        fscanf(fptr,"%c",&str[i]);
    }
    str[position]='\0';
    fclose(fptr);
    return OK;
}
int get_end_of_file(char path[],int position,char str[])
{
    FILE* fptr=fopen(path,"r");
    fgets(str,position,fptr);//alaki
    for(int i=0;i<10000;i++)
    {
        if(fscanf(fptr,"%c",&str[i])==-1)
        {
            str[i]='\0';
            break;
        }
    }
    //str[10000]='\0';
    fclose(fptr);
    return OK;
}
int get_str_from_file(char path[],int position,int size,char str[])
{
    FILE* fptr=fopen(path,"r");
    fgets(str,position,fptr);//alaki
    for(int i=0;i<size;i++)
    {
        fscanf(fptr,"%c",&str[i]);
    }
    str[size]='\0';
    fclose(fptr);
    return OK;
}
int rebuild(char path[],char begining_str[],char str[],char end_str[])
{
    FILE* fptr=fopen(path,"w");
    fprintf(fptr,"%s*",begining_str);
    fprintf(fptr,"%s",str);
    fprintf(fptr,"*%s",end_str);
    fclose(fptr);
    return OK;
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
    return check_wrong_address(path2);
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
int insert()
{
    char flag[100];
    char path[100];
    int line,pos,position;
    char input_str[10000];
    int str_check=0,file_check=0,pos_check=0;
    for(int i=0;i<3;i++)
    {
        scanf("%s",flag);
        if(strcmp(flag,"--file")==0)
        {
            if(file_check!=0)
                return error(*invalid_input);
            file_check++;
            if(file_input(path)==ERROR)
                return error(*invalid_input);
            if(check_wrong_address(path)==ERROR)
                return error(*invalid_address);
            if(check_existance_of_file(path)==ERROR)
                return error(*no_such_file);
            continue;
        }
        if(strcmp(flag,"--str")==0)
        {
            if(str_check!=0)
                return error(*invalid_input);
            str_check++;
            if(get_str(input_str)==ERROR)
                return error(*invalid_input);
            continue;
        }
        if(strcmp(flag,"--pos")==0)
        {
            if(fscanf(stdin,"%d:%d",&line,&pos)==-1)
                return error(*invalid_input);
            if(pos_check!=0)
                return error(*invalid_input);
            pos_check++;
            if((position=find_position(line,pos,path))==ERROR)
                return error(*no_such_position);
            continue;
        }
    }
    /////////////////
    char end_str[10001],begining_str[10001];
    get_end_of_file(path,position,end_str);
    FILE* fptr=fopen(path,"r+");
    fgets(begining_str,position,fptr);//alaki
    fprintf(fptr,"%s",input_str);
    fprintf(fptr,"%s",end_str);
    fclose(fptr);
    return well_done();
}
///////////////////////////////////////////////////////CAT
int cat()
{
    char path[100];
    char flag[50];
    scanf("%s",flag);
    if(strcmp(flag,"--file"))
        return error(*invalid_input);
    if(file_input(path)==ERROR)
        return error(*invalid_input);
    if(check_wrong_address(path)==ERROR)
        return error(*invalid_address);
    if(check_existance_of_file(path)==ERROR)
        return error(*no_such_file);
    //////////
    char c;
    FILE* fptr=fopen(path,"r");
    while(fscanf(fptr,"%c",&c)!=-1)
    {
        printf("%c",c);
    }
    printf("\n");
    fclose(fptr);
    return well_done();
}
///////////////////////////////////////////////////////REMOVE
int remove_str()
{
    char flag[100];
    char path[100];
    int line,pos,position;
    int size;
    int sign;
    int size_check=0,sign_check=0,file_check=0,pos_check=0;
    for(int i=0;i<4;i++)
    {
        scanf("%s",flag);
        if(strcmp(flag,"--file")==0)
        {
            if(file_check!=0)
                return error(*invalid_input);
            file_check++;
            if(file_input(path)==ERROR)
                return error(*invalid_input);
            if(check_wrong_address(path)==ERROR)
                return error(*invalid_address);
            if(check_existance_of_file(path)==ERROR)
                return error(*no_such_file);
            continue;
        }
        if(strcmp(flag,"--pos")==0)
        {
            if(pos_check!=0)
                return error(*invalid_input);
            pos_check++;
            if(fscanf(stdin,"%d:%d",&line,&pos)==-1)
                return error(*invalid_input);
            if((position=find_position(line,pos,path))==ERROR)
                return error(*no_such_position);
            continue;
        }
        if(strcmp(flag,"-size")==0)
        {
            if(size_check!=0)
                return error(*invalid_input);
            size_check++;
            scanf("%d",&size);
            continue;
        }
        if(strcmp(flag,"-b")==0)
        {
            if(sign_check!=0)
                return error(*invalid_input);
            sign_check++;
            sign=-1;
            continue;
        }
        if(strcmp(flag,"-f")==0)
        {
            if(sign_check!=0)
                return error(*invalid_input);
            sign_check++;
            sign=1;
            continue;
        }
    }
    if((position=check_position(path,sign,size,position))==ERROR)
        return error(*out_of_bound);
    ////////
    char end_str[10001],begining_str[10001],middle[1];
    strcpy(middle,"");
    get_begining_of_file(path,position,begining_str);
    get_end_of_file(path,position+size,end_str);
    rebuild(path,begining_str,middle,end_str);
    return well_done();
}
////////////////////////////////////////////////////////COPY

