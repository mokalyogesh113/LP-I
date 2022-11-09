
//   Macro Pass I Program

#include<stdio.h>
#include<conio.h>
#include<string.h>
struct mnt
{
	char mnm[50];
	int index;
}mnt[50];
FILE *fp,*fp1,*fp2,*fp3;
void read(char ch,FILE *fp);
void callmac() ;
     int mntc=0,mdtc=0,flag=0;
     char instr[50][50];
     char buff[50];

void main()
{
     int i,j;
     char ch;
     clrscr();
     fp=fopen("in.txt","r");
     fp1=fopen("inter.dat","w");
     fp2=fopen("mdt.dat","w");
     fp3=fopen("mnt.dat","w");
     printf("\n\n Input File\n");
      printf("\n ======================================\n");
     while(!feof(fp))
     {
	ch=fgetc(fp);
	printf("%c",ch);
     }
     rewind(fp);
     do
     {
	read(getc(fp),fp);
	if(strcmp(buff,"MACRO")!=0)
	{
	    fprintf(fp1,"\n%s",buff);
	}
	else
	{
	     callmac();
	}
     }while(strcmp(buff,"END")!=0);
     printf("\n\n MNT TABLE");
      printf("\n ======================================");
     printf("\nMacro Name\tStarting index");
     for(i=0;i<mntc;i++)
     {
	printf("\n %s  \t \t%d",mnt[i].mnm,mnt[i].index);
     }
     printf("\n\n MDT TABLE");
      printf("\n ======================================");
     printf("\nopcode\t\tIndex\n");
     for(i=0;i<mdtc;i++)
     {
	printf("\n %s\t\t%d ",instr[i],i);
     }
     fclose(fp);
     fclose(fp1);
     fclose(fp2);
     fclose(fp3);
     fp1=fopen("inter.dat","r");
     printf("\n \nIntermidete code");
      printf("\n ======================================");
      while(!feof(fp))
     {
	ch=fgetc(fp1);
	printf("%c",ch);
     }
     fclose(fp1);
     printf("\n");
getch();
}
void read(char ch,FILE *fp)
{
      int i=0;
      while(ch!='\n' && ch!=EOF)
      {
	   buff[i++]=ch;
	   ch=getc(fp);
      }
	   buff[i]='\0';
}
void callmac()
{
     read(getc(fp),fp) ;
     strcpy(mnt[mntc].mnm,buff);
     fprintf(fp3,"\n%s",buff);
     mnt[mntc].index=mdtc;
     mntc++;
     strcpy(instr[mdtc],buff);
     mdtc++;
     do
     {
	   read(getc(fp),fp) ;
	   strcpy(instr[mdtc],buff);
	   fprintf(fp2,"\n%s",buff);
	   mdtc++;
     }while(strcmp(buff,"MEND")!=0);
}

//----------------------------------------------------------------------------------
//		OUTPUT
 Input File
 ======================================
START 101
ABC
MNO
COMP CREG,N
MACRO
ABC
MOVEM AREG,A
MEND
MACRO
MNO
ADD AREG,A
MEND
END 

 MNT TABLE
 ======================================
Macro Name      Starting index
 ABC            0
 MNO            3

 MDT TABLE
 ======================================
opcode          Index
 ABC          	     0
 MOVEM AREG,A    1
 MEND           	     2
 MNO        	     3
 ADD AREG,A          4
 MEND         	    5

Intermediate code
 ======================================
START 101
ABC
MNO
COMP CREG,N
END 

