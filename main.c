#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>

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
int start_search(char*input_str,char*file,int mod,int*sar, int*tah);
/////////////////////////////////////////MAIN
int main()
{
    clipboard[0]='\0';
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
    //copy();
    //paste();
    //cat();
    //printf("%s",clipboard);
    find();
    //printf("%d",find_start_word("hello\nhello salam",13));
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
                    return pos+i+1;
            }
            return pos+strlen(str2);
        }
        return pos+1;
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
int start_search(char*input_str,char*file,int mode,int*sar, int*tah)
{
    int tedad=0;
    if(input_str[0]=='\0')
    {
        if((*tah=search(&input_str[1],&file[0],0))!=ERROR)
        {
            *sar=1;
            tedad++;
        }
        for(int i=0;i<strlen(file);i++)
        {
            if(file[i]=='\n' || file[i]==' ')
            {
                if((*tah=search(&input_str[1],&file[i+1],i+1))!=ERROR)
                {
                    *sar=i+2;
                    tedad++;
                }
            }
        }
        *sar=-1;
        //return;
    }
    ////////
    int limit=strlen(file)-strlen(input_str)+1;
    for(int i=0;i<limit;i++)
    {
        if(strncmp(input_str,&file[i],strlen(input_str))==0)
        {
            if((*tah=search(&input_str[strlen(input_str)+1],&file[i+strlen(input_str)],i+strlen(input_str)))!=ERROR)
            {
                *sar=i+1;
                tedad++;
            }
        }
    }
    *sar=-1;
    //return;
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
            return error(*invalid_input);
    }else
    {
        if(all==1)
        {
            if(at==-10 && byword==0)
                mode=1;
            else if(at==0 && byword==1)
                mode=2;
            else
                return error(*invalid_input);
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
    //printf("mode:%d ",mode);
    ////////
    FILE* fptr=fopen(path,"r");
    for(int i=0;fscanf(fptr,"%c",&file[i])!=-1;i++);
    file[strlen(file)]='\0';
    /////////////////
    /*for(int i=0;i<20;i++)
    {
        if(input_str[i]=='\0')
            printf("-");
        else
            printf("%c",input_str[i]);
    }*/
    int tah;
    int sar;
    int tedad=0;
    if(input_str[0]=='\0')
    {
        if((tah=search(&input_str[1],&file[0],0))!=ERROR)
        {
            sar=1;
            tedad++;
            if(different_modes(mode,sar,tedad,file,at)==ERROR)
                return OK;
        }
        for(int i=0;i<strlen(file);i++)
        {
            if(file[i]=='\n' || file[i]==' ')
            {
                if((tah=search(&input_str[1],&file[i+1],i+1))!=ERROR)
                {
                    sar=i+2;
                    tedad++;
                    if(different_modes(mode,sar,tedad,file,at)==ERROR)
                        return OK;
                }
            }
        }
        sar=-1;
        different_modes(mode,sar,tedad,file,at);
            return OK;
    }
    ////////
    int limit=strlen(file)-strlen(input_str)+1;
    for(int i=0;i<limit;i++)
    {
        if(strncmp(input_str,&file[i],strlen(input_str))==0)
        {
            if((tah=search(&input_str[strlen(input_str)+1],&file[i+strlen(input_str)],i+strlen(input_str)))!=ERROR)
            {
                sar=i+1;
                tedad++;
                //printf("%d %d %d %d ",mode,sar,tedad,at);
                if(different_modes(mode,sar,tedad,file,at)==ERROR)
                    return OK;
            }
        }
    }
    sar=-1;
    different_modes(mode,sar,tedad,file,at);
        return OK;
}
