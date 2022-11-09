#include<stdio.h>
#include<conio.h>
#include<string.h>
void read(char ch,FILE *fp);
void expand(int);
int mntc=0,mdtc=0,flag=0;
char instr[50][50];
char buff[50];
FILE *fp,*fp1,*fp2;
int mdti,i;
char ch;
struct mnt
{
	char mnm[50];
	int index;
}mnt[2]={{"ABC",0},{"MNO",1}};

void main()
{
clrscr();
    fp=fopen("inter.dat","r");
    fp2=fopen("mdt.dat","r");
    fp1=fopen("expand.dat","w");
    printf("\n EXPANDED CODE");
    printf("\n ======================================");
    i=0;
     while(!feof(fp))
     {
	read(getc(fp),fp);
	{
		if(strcmp(buff,mnt[i].mnm)==0)
		{
			expand(mdti);
			i++;
		}
		else
		{
			fprintf(fp1,"\n%s",buff);
		}
	}
     }
     fclose(fp);
     fclose(fp1);
     fclose(fp2);
     fp1=fopen("expand.dat","r");
     while(!feof(fp1))
     {
	ch=fgetc(fp1);
	printf("%c",ch);
     }
     fclose(fp1);
     getch();
}

void expand(int mdti)
{
  int i;
  mdti++;
  read(getc(fp2),fp2);
  while(strcmp(buff,"MEND")!=0)
  {
    fprintf(fp1,"\n%s",buff);
    read(getc(fp2),fp2);
  };
}

void read(char ch,FILE *fp)
{
      int i=0;
      while(ch!='\n' && ch!=EOF)
      {
	   buff[i]=ch;
	   i++;
	   ch=getc(fp);
      }
	   buff[i]='\0';
}