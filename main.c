#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

#define ERROR -100
#define OK 100
#define WRONG 0

char clipboard[10001];

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
int find_real_position(char path[],int position);
//////////////////////////////////////////
int well_done();
int error(void(*func)());
void invalid_input();
void invalid_address();
void file_already_existed();
void out_of_bound();
void bad_flags();
void invalid_depth();
//////////////////////////////////////////
int go_to_address(char path[]);
int create_file();
int insert();
int cat();
int remove_str();
int copy();
int cut();
int paste();
int find();
int str_for_find_with_double_quotation(char str[]);
int get_str_for_find(char str[]);
int search(char *str1,char *str2,int pos);
int get_option(int *at,int* count, int* byword, int* all);
int find_start_word(char str[],int pos);
int start_search(char input_str[],char file[],int mode,int at);
int different_modes(int mode,int sar,int tedad,char str[],int at);
int get_option_for_replace(int* at, int* all);
int asle_replace(char path[],int sar,int tah,char replace_str[]);
int different_modes_for_replace(int mode,int sar,char path[],int at,char replace_str[],int tedad,int tah);
int start_search_for_replace(char input_str[],char file[],int mode,int at,char replace_str[],char path[]);
int replace();
int grep();
int asle_auto_indent(char file[],int sar,int tah,int indent);
int pair_up(char file[],int pos,int indent);
int auto_indent();
int compare();
int asle_tree(char path[],int depth,int limit);
int tree();
/////////////////////////////////////////MAIN
int main()
{
    clipboard[0]='\0';
    char command[30];
    while(1)
    {
        scanf("%s",command);
        if(strcmp(command,"createfile")==0)
        {
            create_file();
            continue;
        }
        if(strcmp(command,"insertstr")==0)
        {
            insert();
            continue;
        }
        if(strcmp(command,"cat")==0)
        {
            cat();
            continue;
        }
        if(strcmp(command,"removestr")==0)
        {
            remove_str();
            continue;
        }
        if(strcmp(command,"copystr")==0)
        {
            copy();
            continue;
        }
        if(strcmp(command,"cutstr")==0)
        {
            cut();
            continue;
        }
        if(strcmp(command,"pastestr")==0)
        {
            paste();
            continue;
        }
        if(strcmp(command,"find")==0)
        {
            find();
            continue;
        }
        if(strcmp(command,"replace")==0)
        {
            replace();
            continue;
        }
        if(strcmp(command,"grep")==0)
        {
            grep();
            continue;
        }
        if(strcmp(command,"auto_indent")==0)
        {
            auto_indent();
            continue;
        }
        if(strcmp(command,"compare")==0)
        {
            compare();
            continue;
        }
        if(strcmp(command,"tree")==0)
        {
            tree();
            continue;
        }
        if(strcmp(command,"exit")==0)
        {
            return 0;
        }else
        {
            error(*invalid_input);
            continue;
        }
    }
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
void bad_flags()
{
    printf("bad flags\n");
}
void invalid_depth()
{
    printf("invalid depth\n");
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
    }else if(str[0]=='\n')
        return ERROR;
    else
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
    int real_position=find_real_position(path,position);
    FILE* fptr=fopen(path,"r+");
    fseek(fptr,real_position,SEEK_SET);
    for(int i=0;i<10000;i++)
    {
        if(fscanf(fptr,"%c",&str[i])==-1)
        {
            str[i]='\0';
            break;
        }
    }
    str[10000]='\0';
    fclose(fptr);
    return OK;
}
int get_str_from_file(char path[],int position,int size,char str[])
{
    int real_position=find_real_position(path,position);
    FILE* fptr=fopen(path,"r");
    fseek(fptr,real_position,SEEK_SET);
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
    fprintf(fptr,"%s",begining_str);
    fprintf(fptr,"%s",str);
    fprintf(fptr,"%s",end_str);
    fclose(fptr);
    return OK;
}
int find_real_position(char path[],int position)
{
    FILE* fptr=fopen(path,"r");
    for(int i=0;i<position;i++)
    {
        fgetc(fptr);
    }//alaki
    int real_position=ftell(fptr);
    fclose(fptr);
    return real_position;
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
    printf("done\n");
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
    char end_str[10001];
    int real_position=find_real_position(path,position);
    get_end_of_file(path,position,end_str);
    FILE* fptr=fopen(path,"r+");
    fseek(fptr,real_position,SEEK_SET);
    fprintf(fptr,"%s",input_str);
    fprintf(fptr,"%s",end_str);
    //printf("%s",input_str);
    fclose(fptr);
    printf("done\n");
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
    printf("done\n");
    return well_done();
}
////////////////////////////////////////////////////////COPY
int copy()
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
    //////////
    get_str_from_file(path,position,size,clipboard);
    printf("done\n");
    return well_done();
}
////////////////////////////////////////////////////////////////////CUT
int cut()
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
    /////////////////
    get_str_from_file(path,position,size,clipboard);
    char end_str[10001],begining_str[10001],middle[1];
    strcpy(middle,"");
    get_begining_of_file(path,position,begining_str);
    get_end_of_file(path,position+size,end_str);
    rebuild(path,begining_str,middle,end_str);
    printf("done\n");
    return well_done();
}
/////////////////////////////////////////////////////////////PASTE
int paste()
{
    char flag[100];
    char path[100];
    int line,pos,position;
    int file_check=0,pos_check=0;
    for(int i=0;i<2;i++)
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
    }
    /////////////////
    char end_str[10001];
    int real_position=find_real_position(path,position);
    get_end_of_file(path,position,end_str);
    FILE* fptr=fopen(path,"r+");
    fseek(fptr,real_position,SEEK_SET);
    fprintf(fptr,"%s",clipboard);
    fprintf(fptr,"%s",end_str);
    fclose(fptr);
    printf("done\n");
    return well_done();
}
//////////////////////////////taghyir e raviye
/////////////////////////////////////////////////////////////////////FIND
int search(char *str1,char *str2,int pos)
{
    if(strlen(str1)==0)
    {
        if(str1[1]=='\0')
        {
            for(int i=0;i<strlen(str2);i++)
            {
                if(str2[i]==' ' ||str2[i]=='\n')
                    return pos+i;
            }
            return pos+strlen(str2);
        }
        return pos;
    }
    int tah;
    int limit=strlen(str2)-strlen(str1)+1;
    for(int i=0;i<limit;i++)
    {
        if(str2[i]==' ' || str2[i]=='\n')
        {
            limit=i;
            break;
        }
    }
    /////////////
    for(int i=limit-1;i>=0;i--)
    {
        if(strncmp(str1,&str2[i],strlen(str1))==0)
        {
            if((tah=search(&str1[strlen(str1)+1],&str2[i+strlen(str1)],pos+i+strlen(str1)))!=ERROR)
                return tah;
        }
    }
    return ERROR;
}
int get_str_for_find(char str[])
{
    scanf(" %c",&str[0]);
    if(str[0]=='"')
    {
        if(str_for_find_with_double_quotation(str)==ERROR)
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
                    str[i+1]='\0';
                    str[i+2]='2';
                    return OK;
                case '*':
                    str[i-1]='*';
                    break;
                default :
                    str[i-1]='\\';
                    i++;
                    break;
            }
        }else
            i++;
        if(str[0]=='*')
            str[0]=='\0';
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
                    str[i+1]='\0';
                    str[i+2]='2';
                    return OK;
                case '*':
                    str[i]='\0';
                    i++;
                    break;
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
                            str[i+1]='\0';
                            str[i+2]='2';
                            return OK;
                        case '*':
                            str[i-1]='*';
                            break;
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
int str_for_find_with_double_quotation(char str[])
{
    int i=0;
    while(1)
    {
        str[i]=fgetc(stdin);
        switch(str[i])
        {
            case '"':
                str[i]='\0';
                str[i+1]='\0';
                str[i+2]='2';
                return OK;
            case '\n':
                fseek(stdin,-2,SEEK_END);
            case '\0':
                str[i]='\0';
                return ERROR;
            case '*':
                str[i]='\0';
                i++;
                break;
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
                    case '*':
                        str[i-1]='*';
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
int get_option(int* at,int* count, int* byword, int* all)
{
    //char input[1000];
    char flag[100];
    //fgets(input,1000,stdin);
    //fseek(stdin,-2,SEEK_CUR);
    //int pos=0;
    char c;
    while(1)
    {
        scanf("%c",&c);
        //pos++;
        if(c==' ')
            continue;
        if(c=='\n')
            return OK;
        if(c=='-')
        {
            scanf("%s",flag);
            //pos+=strlen(flag);
            if(strcmp(flag,"at")==0)
            {
                if(*at!=-10)
                    return ERROR;
                scanf("%d",at);
                continue;
            }
            if(strcmp(flag,"all")==0)
            {
                if(*all!=0)
                    return ERROR;
                (*all)++;
                continue;
            }
            if(strcmp(flag,"byword")==0)
            {
                if(*byword!=0)
                    return ERROR;
                (*byword)++;
                continue;
            }
            if(strcmp(flag,"count")==0)
            {
                if(*count!=0)
                    return ERROR;
                (*count)++;
                continue;
            }
            return error(*invalid_input);
        }
    }
}
int find_start_word(char str[],int pos)
{
    int i=0;
    int word=0;
    while(i<pos)
    {
        while((str[i]==' '||str[i]=='\n')&&i<pos)
        {
            //printf("%d:%c ",i,str[i]);
            i++;
        }
        while(i<pos)
        {
            //printf("%d:%c ",i,str[i]);
            if(str[i]==' '||str[i]=='\n')
            {
                break;
            }
            i++;
        }
        word++;
    }
    return word;
}
int start_search(char input_str[],char file[],int mode,int at)
{
    int tah;
    int sar;
    int tedad=0;
    int i=0;
    if(input_str[0]=='\0')
    {
        if((tah=search(&input_str[1],&file[0],0))!=ERROR)
        {
            sar=1;
            tedad++;
            i=tah;
            if(different_modes(mode,sar,tedad,file,at)==ERROR)
                return OK;
        }
        for(;i<strlen(file);i++)
        {
            if(file[i]=='\n' || file[i]==' ')
            {
                if((tah=search(&input_str[1],&file[i+1],i+1))!=ERROR)
                {
                    sar=i+2;
                    tedad++;
                    i=tah;
                    if(different_modes(mode,sar,tedad,file,at)==ERROR)
                        return OK;
                }
            }
        }
        sar=-1;
        different_modes(mode,sar,tedad,file,at);
            return ERROR;
    }
    ////////
    int limit=strlen(file)-strlen(input_str)+1;
    for(;i<limit;i++)
    {
        if(strncmp(input_str,&file[i],strlen(input_str))==0)
        {
            //printf(" input:%s file:",input_str);
        //for(int j=0;j<strlen(input_str);j++)
            //printf("%c",file[i+j]);
            if((tah=search(&input_str[strlen(input_str)+1],&file[i+strlen(input_str)],i+1+strlen(input_str)))!=ERROR)
            {
                sar=i+1;
                tedad++;
                i=tah;
                //printf("|%d:%d:",sar,tah);
                //for(int j=sar-1;j<tah-1;j++)
                 //   printf("%c",file[j]);
                //printf("\n");
                //printf("%d %d %d %d ",mode,sar,tedad,at);
                if(different_modes(mode,sar,tedad,file,at)==ERROR)
                    return OK;
            }
        }
    }
    sar=-1;
    different_modes(mode,sar,tedad,file,at);
        return ERROR;
}
int different_modes(int mode,int sar,int tedad,char str[],int at)
{
    if(mode==0)
    {
        if(sar==-1)
        {
            printf("%d\n",tedad);
        }
        return OK;
    }
    if(mode==1)
    {
        if(sar!=-1)
        {
            if(tedad==1)
                printf("%d",sar);
            else
                printf(", %d",sar);
        }else if(sar==-1)
        {
            printf("\n");
        }
        return OK;
    }
    if(mode==2)
    {
        if(sar!=-1)
        {
            if(tedad==1)
                printf("%d",find_start_word(str,sar));
            else
                printf(", %d",find_start_word(str,sar));
        }else if(sar==-1)
        {
            printf("\n");
        }
        return OK;
    }
    if(mode==3)
    {
        if(tedad==at)
        {
            printf("%d\n",sar);
            return ERROR;
        }
        if(sar==-1)
            printf("-1\n");
        return OK;
    }
    if(mode==4)
    {
        if(tedad==at)
        {
            printf("%d\n",find_start_word(str,sar));
            return ERROR;
        }
        if(sar==-1)
            printf("-1\n");
        return OK;
    }
    if(mode==5)
    {
        if(sar!=-1)
        {
            printf("%d\n",find_start_word(str,sar));
            return ERROR;
        }else
        {
            printf("-1\n");
            return OK;
        }
    }
    if(mode==6)
    {
        if(sar!=-1)
        {
            printf("%d\n",sar);
            return ERROR;
        }else
        {
            printf("-1\n");
            return OK;
        }
    }else
    {
        if(sar!=-1)
            return ERROR;
        else
            return OK;
    }
}
int find()
{
    char flag[100];
    char path[100];
    char input_str[10000];
    char file[10001];
    int at=-10,count=0,byword=0,all=0;
    int str_check=0,file_check=0;
    for(int i=0;i<2;i++)
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
            if(get_str_for_find(input_str)==ERROR)
                return error(*invalid_input);
            continue;
        }
    }
    ////
    int mode;
    if(get_option(&at,&count,&byword,&all)==ERROR)
       return error(*invalid_input);
    if(count==1)
    {
        if(at==-10&&byword==0&&all==0)
        {
            mode=0;
        }else
            return error(*bad_flags);
    }else
    {
        if(all==1)
        {
            if(at==-10 && byword==0)
                mode=1;
            else if(at==-10 && byword==1)
                mode=2;
            else
                return error(*bad_flags);
        }
        else
        {
            if(at!=-10 && byword==0)
                mode=3;
            else if(at!=-10 && byword==1)
                mode=4;
            else if(at==-10 && byword==1)
                mode=5;
            else
                mode=6;
        }
    }
    FILE* fptr=fopen(path,"r");
    for(int i=0;fscanf(fptr,"%c",&file[i])!=-1;i++);
    file[strlen(file)]='\0';
    fclose(fptr);
    return start_search(input_str,file,mode,at);
}
//////////////////////////////////////////////////////////////REPLACE
int get_option_for_replace(int* at, int* all)
{
    char flag[100];
    char c;
    while(1)
    {
        scanf("%c",&c);
        if(c==' ')
            continue;
        if(c=='\n')
            return OK;
        if(c=='-')
        {
            scanf("%s",flag);
            if(strcmp(flag,"at")==0)
            {
                if(*at!=-10)
                    return ERROR;
                scanf("%d",at);
                continue;
            }
            if(strcmp(flag,"all")==0)
            {
                if(*all!=0)
                    return ERROR;
                (*all)++;
                continue;
            }
            return error(*invalid_input);
        }
    }
}
int asle_replace(char path[],int sar,int tah,char replace_str[])
{
    char end_str[10001],begining_str[10001];
    int size=tah-sar;
    int position=sar-1;
    get_begining_of_file(path,position,begining_str);
    get_end_of_file(path,position+size,end_str);
    rebuild(path,begining_str,replace_str,end_str);
    ///////
    return OK;
}
int different_modes_for_replace(int mode,int sar,char path[],int at,char replace_str[],int tedad,int tah)
{
    if(mode==0)
    {
        if(sar!=-1)
        {
            asle_replace(path,sar,tah,replace_str);
            printf("done\n");
            return ERROR;
        }else
        {
            printf("str1 not found!\n");
            return OK;
        }
    }
    if(mode==1)
    {
        if(sar!=-1)
        {
            if(tedad==at)
            {
                asle_replace(path,sar,tah,replace_str);
                printf("done\n");
                return ERROR;
            }
        }else if(sar==-1)
        {
            printf("str1 not found!\n");
        }
        return OK;
    }
    if(mode==2)
    {
        if(sar!=-1)
        {
            asle_replace(path,sar,tah,replace_str);
        }else if(tedad==0)
        {
            printf("str1 not found!\n");
        }else
            printf("done\n");
        return OK;
    }
}
int start_search_for_replace(char input_str[],char file[],int mode,int at,char replace_str[],char path[])
{
    int tah;
    int sar;
    int tedad=0;
    int i=0;
    if(input_str[0]=='\0')
    {
        if((tah=search(&input_str[1],&file[0],0))!=ERROR)
        {
            sar=1;
            tedad++;
            i=tah;
            if(different_modes_for_replace(mode,sar,path,at,replace_str,tedad,tah)==ERROR)
                return OK;
        }
        for(;i<strlen(file);i++)
        {
            if(file[i]=='\n' || file[i]==' ')
            {
                if((tah=search(&input_str[1],&file[i+1],i+1))!=ERROR)
                {
                    sar=i+2;
                    tedad++;
                    i=tah;
                    if(different_modes_for_replace(mode,sar,path,at,replace_str,tedad,tah)==ERROR)
                        return OK;
                }
            }
        }
        sar=-1;
        different_modes_for_replace(mode,sar,path,at,replace_str,tedad,tah);
            return OK;
    }
    ////////
    int limit=strlen(file)-strlen(input_str)+1;
    for(;i<limit;i++)
    {
        if(strncmp(input_str,&file[i],strlen(input_str))==0)
        {
            if((tah=search(&input_str[strlen(input_str)+1],&file[i+strlen(input_str)],i+1+strlen(input_str)))!=ERROR)
            {
                sar=i+1;
                tedad++;
                i=tah;
                if(different_modes_for_replace(mode,sar,path,at,replace_str,tedad,tah)==ERROR)
                    return OK;
            }
        }
    }
    sar=-1;
    different_modes_for_replace(mode,sar,path,at,replace_str,tedad,tah);
        return OK;
}
int replace()
{
    char flag[100];
    char path[100];
    char input_str[10000];
    char replac_str[10000];
    char file[10001];
    int at=-10,all=0;
    int str1_check=0,str2_check=0,file_check=0;
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
        if(strcmp(flag,"--str1")==0)
        {
            if(str1_check!=0)
                return error(*invalid_input);
            str1_check++;
            if(get_str_for_find(input_str)==ERROR)
                return error(*invalid_input);
            continue;
        }
        if(strcmp(flag,"--str2")==0)
        {
            if(str2_check!=0)
                return error(*invalid_input);
            str2_check++;
            if(get_str_for_find(replac_str)==ERROR)
                return error(*invalid_input);
            continue;
        }
    }
    ////////////
    int mode;
    if(get_option_for_replace(&at,&all)==ERROR)
       return error(*invalid_input);
    if(all==0&&at==-10)
    {
        mode=0;
    }else
    {
        if(all==0)
            mode=1;
        else if(at==-10)
            mode=2;
        else
            return error(*bad_flags);
    }
    FILE* fptr=fopen(path,"r");
    for(int i=0;fscanf(fptr,"%c",&file[i])!=-1;i++);
    file[strlen(file)]='\0';
    fclose(fptr);
    return start_search_for_replace(input_str,file,mode,at,replac_str,path);
}
///////////////////////////////////////////////////////////////////GREP
int get_file_for_grep(char str[])
{
    scanf("%c",&str[0]);
    if(str[0]=='"')
    {
        if(str_with_double_quotation(str)==ERROR)
        {
            return ERROR;
        }
    }else if(str[0]=='\n')
        return ERROR;
    else
    {
        scanf("%s",&str[1]);
        return OK;
    }
}
int file_input_for_grep(char str[])
{
    if(get_file_for_grep(str)==ERROR)
        return ERROR;
    if(str[0]=='/')
        strcpy(str,&str[1]);
    if(str[strlen(str)-1]=='/')
        str[strlen(str)-1]='\0';
    return OK;
}
int grep()
{
    char flag[100];
    char path[20][100];
    char input_str[10000];
    char file[10001];
    int l_option=0,c_option=0;
    int str_check=0,file_check=0;
    char c;
    int tedad_files=0;
    for(int i=0;i<4;i++)
    {
        while((flag[0]=getchar())==' ');
        if(flag[0]=='\n')
            break;
        scanf("%s",&flag[1]);
        //printf("|%c|",flag[0]);
        //printf("*");
        //printf("%s ",flag);
        if(strcmp(flag,"--files")==0)
        {
            //printf("#");
            if(file_check!=0)
                return error(*invalid_input);
            file_check++;
            for(int i=0;;i++)
            {
                //path[i][0]=c;
                c=getchar();
                //printf("$%c%d%d$",c,c,'\n');
                if(c=='\n')
                {
                    //printf("@");
                    tedad_files=i;
                    break;
                }
                if(file_input_for_grep(path[i])==ERROR)
                {
                    //printf("#");
                    if(path[i][0]=='\n')
                    {
                        //printf("#");
                        tedad_files=i;
                        break;
                    }else
                        return error(*invalid_input);
                }
                //printf("%s\n",path[i]);
                if(check_wrong_address(path[i])==ERROR)
                    return error(*invalid_address);
                if(check_existance_of_file(path[i])==ERROR)
                    return error(*no_such_file);
            }
            break;
        }
        if(strcmp(flag,"--str")==0)
        {
            if(str_check!=0)
                return error(*invalid_input);
            str_check++;
            if(get_str_for_find(input_str)==ERROR)
                return error(*invalid_input);
            continue;
        }
        if(strcmp(flag,"-l")==0)
        {
            if(l_option!=0)
                return error(*invalid_input);
            l_option++;
            continue;
        }
        if(strcmp(flag,"-c")==0)
        {
            if(c_option!=0)
                return error(*invalid_input);
            c_option++;
            continue;
        }
    }
    /////////////////////////
    int mode;
    if(l_option==0&&c_option==0)
        mode=7;
    else
    {
        if(l_option==0)
            mode=9;
        else if(c_option==0)
            mode=8;
        else
            return error(*bad_flags);
    }
    /////////////
    int at=-10;
    FILE* fptr;
    int tedad_lines=0;
    for(int i=0;i<tedad_files;i++)
    {
        fptr=fopen(path[i],"r");
        while(fgets(file,10000,fptr)!=NULL)
        {
            if(start_search(input_str,file,mode,at)==OK)
            {
                tedad_lines++;
                if(mode==7)
                {
                    printf("%s: %s",path[i],file);
                    if(file[strlen(file)-1]!='\n')
                    printf("\n");
                }else if(mode==8)
                {
                    printf("%s\n",path[i]);
                    break;
                }
            }
        }
        fclose(fptr);
    }
    if(tedad_lines==0)
    {
        printf("str not found!\n");
    }
    if(mode==9)
    {
        printf("%d\n",tedad_lines);
    }
    return OK;
}
////////////////////////////////////////////////////////////////////////CLOSING PAIRS
int asle_auto_indent(char file[],int sar,int tah,int indent)
{
    //printf("%d ",indent);
    char sar_file[10000],vasat_file[10000],tah_file[10000];
    if(sar==0)
        sar_file[0]='\0';
    else
        strncpy(sar_file,file,sar);
    strcpy(tah_file,&file[tah+1]);
    ///////////////
    int pos=0;
    if(!(sar==0||file[sar-1]==' '||file[sar-1]=='\n'))
    {
        vasat_file[pos]=' ';
        pos++;
    }
    vasat_file[pos]='{';
    vasat_file[pos+1]='\n';
    pos+=2;
    for(int i=sar+1;i<tah;i++)
    {
        if(indent>0)
        {
            for(int j=0;j<indent;j++)
            {
                vasat_file[pos]=' ';
                pos++;
            }
            for(;file[i]==' ';i++);
            if(i==tah)
            {
                pos-=4;
            }
        }
        while(i<tah)
        {
            vasat_file[pos]=file[i];
            pos++;
            if(file[i]=='\n')
            {
                break;
            }
            if(file[i]=='{')
            {
                indent-=100000;
            }
            if(file[i]=='}')
            {
                indent+=100000;
            }
            i++;
        }
    }
    if(vasat_file[pos-1]!='\n'&&vasat_file[pos-1]!=' ')
    {
        vasat_file[pos]='\n';
        pos++;
        for(int j=0;j<indent-4;j++)
        {
            vasat_file[pos]=' ';
            pos++;
        }
    }
    vasat_file[pos]='}';
    pos++;
    if(file[tah+1]!='\n'&&file[tah+1]!='\0')
    {
        vasat_file[pos]='\n';
        pos++;
    }
    vasat_file[pos]='\0';
    ////////////
    strcpy(file,sar_file);
    strcat(file,vasat_file);
    strcat(file,tah_file);
    //printf("%s\n///%c///\n",file,file[sar+strlen(vasat_file)-2]);
    return sar+strlen(vasat_file)-2;
}
int pair_up(char file[],int pos,int indent)
{
    //printf("%d ",indent);
    int last_n=pos;
    int new_indent=0;
    int sar=pos;
    for(int i=pos+1;i!=-1;i++)
    {
        //printf("#%c",file[i]);
        switch(file[i])
        {
            case '{':
                i=pair_up(file,i,indent+new_indent+4);
                break;
            case '}':
                return(i=asle_auto_indent(file,sar,i,indent+4));
            case '\0':
                return -2;
            case '\n':
                last_n=i;
                new_indent=0;
                break;
            case ' ':
                for(;file[i+1]==' ';i++);
                if(file[i+1]!='{')
                    new_indent=i-last_n;
                break;
        }
    }
}
int auto_indent()
{
    char path[100];
    char file[10000];
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
    ///////////////
    FILE*fptr=fopen(path,"r");
    int iiii=0;
    for(;fscanf(fptr,"%c",&file[iiii])!=-1;iiii++);
    file[iiii]='\0';
    fclose(fptr);
    /////////
    int last_n=0;
    int indent=0;
    for(int i=0;i!=-1;i++)
    {
        //printf("%d ",indent);
        switch(file[i])
        {
            case '\n':
                last_n=i;
                indent=0;
                break;
            case ' ':
                for(;file[i+1]==' ';i++);
                if(file[i+1]!='{')
                    indent=i-last_n;
                break;
            case '\0':
                i=-2;
                break;
            case '{':
                //printf("%d ",indent);
                i=pair_up(file,i,indent);
                break;
        }
    }
    //printf("%s",file);
    fptr=fopen(path,"w");
    fprintf(fptr,"%s",file);
    fclose(fptr);
    printf("done\n");
    return well_done();
}
/////////////////////////////////////////////////////////////////////TEXT COMPARATOR
int compare()
{
    char flag[100];
    char path[2][100];
    char line1[10000];
    char line2[10000];
    int file_check=0;
    char c;
    for(int i=0;i<2;i++)
    {
        c=getchar();
        if(c=='\n')
        {
            return error(*invalid_input);
        }
        if(file_input_for_grep(path[i])==ERROR)
        {
            return error(*invalid_input);
        }
        if(check_wrong_address(path[i])==ERROR)
            return error(*invalid_address);
        if(check_existance_of_file(path[i])==ERROR)
            return error(*no_such_file);
    }
    //////////////////////////////
    FILE*fptr1,*fptr2;
    fptr1=fopen(path[0],"r");
    fptr2=fopen(path[1],"r");
    int tafavot=0;
    for(int i=1;;i++)
    {
        if(fgets(line1,10000,fptr1)==NULL)
        {
            if(fgets(line2,10000,fptr2)!=NULL)
            {
                printf(">>>>>>>>>>>> #%d - file 2 >>>>>>>>>>>>\n",i);
                while(1)
                {
                    printf("%s",line2);
                    if(fgets(line2,10000,fptr2)==NULL)
                    {
                        break;
                    }
                }
                printf("\n");
            }
            fclose(fptr1);
            fclose(fptr2);
            if(tafavot==0)
                printf("are the same\n");
            return well_done();
        }else if(fgets(line2,10000,fptr2)==NULL)
        {
            if(fgets(line1,10000,fptr1)!=NULL)
            {
                printf(">>>>>>>>>>>> #%d - file 1 >>>>>>>>>>>>\n",i);
                while(1)
                {
                    printf("%s",line1);
                    if(fgets(line1,10000,fptr1)==NULL)
                    {
                        break;
                    }
                }
                printf("\n");
            }
            fclose(fptr1);
            fclose(fptr2);
            if(tafavot==0)
                printf("are the same\n");
            return well_done();
        }
        if(strcmp(line1,line2)!=0)
        {
            tafavot++;
            printf("============ #%d ============\n%s",i,line1);
            if(line1[strlen(line1)-1]!='\n')
                printf("\n");
            printf("%s",line2);
            if(line2[strlen(line2)-1]!='\n')
                printf("\n");
        }
    }
}
////////////////////////////////////////////////////////TREE
int asle_tree(char path[],int depth,int limit)
{
    struct dirent *files;
    DIR *dr = opendir(path);
    if (dr == NULL)
    {
        //printf("DALI");
        return ERROR;
    }
    while ((files = readdir(dr)) != NULL)
    {

        if(files->d_name[0]!='.')
        {
            for(int i=0;i<depth-1;i++)
                printf("   ");
            printf("\\___");
            printf("%s\n", files->d_name);
            if(depth+1<=limit)
            {
                char new_path[100];
                strcpy(new_path,path);
                strcat(new_path,"/");
                strcat(new_path,files->d_name);
                asle_tree(new_path,depth+1,limit);
            }
        }
    }
    closedir(dr);
    return OK;
}
int tree()
{
    int depth;
    scanf("%d",&depth);
    if(depth<-1)
        return error(*invalid_depth);
    char path[10000]={"root"};
    if(depth==-1)
        depth=10000;
    printf("root\n");
    ////////////////
    asle_tree(path,0,depth);
    return OK;
}
/////////////////////////////////////////////////////////////////

