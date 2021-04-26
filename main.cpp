#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

char  s[10000];         //输入程序代码
int mistake[100];       //记录出错信息
int i=0,t=0,u=0;
char lists[20][20];     //储存对照表

int translate()
{
    if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
    {
        char sample[20];
        int n=0;
        sample[n++] = s[i++];
        while((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
		{
			sample[n++]=s[i++];
		}
		sample[n]='\0';
		i--;
		for(int x=0;x<20;x++)           //检验是否为保留字
        {
            if(strcmp(sample,lists[x])==0)
            {
                printf("<%d,->,",x);
                return 1;
            }
        }
        printf("<1,%s>, ",sample);
        return 1;
    }
    else if(s[i]>='0'&&s[i]<='9')   //检验是否为常量
    {
        char sample_1[100];
        int m=i+1,n=0;
        while((s[m]>='a'&&s[m]<='z')||(s[m]>='A'&&s[m]<='Z'))
        {
            m++;
            if(s[m]=='\n'||s[m]==' ')
            {
                i=m;
                printf("LexicalError,");
                mistake[u]=t+1;
                u++;
                return 1;
            }
        }
        while(s[i]>='0'&&s[i]<='9')
        {
            sample_1[n++]=s[i++];
        }
        sample_1[n]='\0';
        i--;
        printf("<2,%s>,",sample_1);
        return 1;
    }
    else
    {
        switch(s[i])
        {
            case '#':return 0;
            case ' ':return 1;
            case '\n':return 2;
            case '=':i++;
                    if(s[i]=='=')
                    {
                        printf("<23,->,");
                        return 1;
                    }
                    else
                    {
                        printf("<27,->,");
                        i--;
                        return 1;
                    }
            case '>':i++;
                    if (s[i] == '=')
                    {
                        printf("<22,->,");
                        return 1;
                    }
                    else
                    {
                        printf("<21,->,");
                        i--;
                        return 1;
                    }
            case '<':i++;
                    if(s[i]=='=')
                    {
                        printf("<20,->,");
                        return 1;
                    }
                    else
                    {
                        printf("<19,->,");
                        i--;
                        return 1;
                    }
            case '+':printf("<14,->,");return 1;
            case '-':printf("<15,->,");return 1;
            case '*':printf("<16,->,");return 1;
            case '/':
                    i++;
                    if(s[i]=='/')
                    {
                        while(1)                    //检验注释（一行）
                        {
                            if(s[i++]=='\n')
                            {
                                i--;
                                return 2;
                            }
                        }
                    }
                    if(s[i]=='*')               // 检验多行注释
                    {
                        while(s[i]!='/')
                        {i++;}
                        return 2;
                    }
                    printf("<17,->,");          //除号
                    return 0;
			case '%': printf("<18,->,"); return 1;
            case '!': printf("<24,->,"); return 1;
            case '&': printf("<25,->,"); return 1;
		    case '|': i++;
				      printf("<26,->,"); return 1;
		    case '(': printf("<28,->,"); return 1;
		    case ')': printf("<29,->,"); return 1;
		    case '[': printf("<30,->,"); return 1;
            case ']': printf("<31,->,"); return 1;
		    case '{': printf("<32,->,"); return 1;
            case '}': printf("<33,->,"); return 1;
		    case ';': printf("<34,->,"); return 1;
		    case ',': printf("<35,->,"); return 1;
        }
    }
}

void assigned()         //为对照表赋值
{
    strcpy(lists[3],"void");
    strcpy(lists[4],"int");
    strcpy(lists[5],"float");
    strcpy(lists[6],"char");
    strcpy(lists[7],"if");
    strcpy(lists[8],"else");
    strcpy(lists[9],"while");
    strcpy(lists[10],"do");
    strcpy(lists[11],"for");
    strcpy(lists[12],"return");
    strcpy(lists[13],"main");
}

int main()
{
    int a=0;
    int flag=5;
    int g=0;
    assigned();
    scanf("%c",&s[a]);
    while(s[a]!='#')            //录入程序代码
    {
        a++;
        scanf("%c",&s[a]);
    }
    while(flag!=0)
	{
		flag=translate();
		switch(flag)
		{
		case 2:
			i++;
			if(g==0)
			{
				printf("\n");
				t++;
				g++;
			}
			break;
		case 1:
			i++;
			if(g==1)
				g--;
			break;
		case 0:
			i++;
			if(g==1)
				g--;
			break;
		}
	}
	u=0;
	while(mistake[u]!=0)            //输出错误行数
	{
		if(u==0)
			printf("LexicalError(s) on line(s) %d,",mistake[u]);
		else
			printf("%d,",mistake[u]);
		u++;
	}

    return 0;
}
