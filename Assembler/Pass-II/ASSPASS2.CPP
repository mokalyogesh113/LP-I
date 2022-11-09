/*Name: Chhajed Sneha S.
   Roll No. : 14
   Program Defination: Assembler pass 2 */ 

#include<stdio.h>
#include<conio.h>
#include<string.h>
struct sym
{
  int no;
  char name[20];
  int  add;
};
struct sym s[3]= {{1,"sai",116},{2,"om",119},{3,"li",120}};
struct lit
{
   int no;
   char name[10];
   int add;
};

struct lit l[3]={{1,"='2'",121},{2,"='1'",122},{3,"='4'",122}};

void main()
{
int i,no;
char ch;
FILE *fr,*fw;
char buff[10];
clrscr();

fr=fopen("inter.dat","r");
if(fr<0)
{
	printf("\n error...............");
}
fw=fopen("machine.dat","w");
if(fw<0)
{
	printf("\n error...............");
}
printf("\nsymbol table");
for(i=0;i<3;i++)
	{
	   printf("\n\t %d \t\t %s \t\t %d",s[i].no,s[i].name,s[i].add);
	}
printf("\nliteral table");
for(i=0;i<3;i++)
	{
	   printf("\n\t %d \t\t %s \t\t %d",l[i].no,l[i].name,l[i].add);
	}
 fscanf(fr,"%s",buff);
if(strcmp(buff,"(ad,01)")==0)
 fscanf(fr,"%s",buff);
readinst:
 fscanf(fr,"%s",buff);
if(strcmp(buff,"(is,")==0)
{
fscanf(fr,"%d",&no);
fprintf(fw,"\n%d",no);

fscanf(fr,"%s",buff);

fscanf(fr,"%d",&no);
fprintf(fw,"\t%d",no);

fscanf(fr,"%s",buff);
 if(strcmp(buff,"(c,")==0)
 {
 fscanf(fr,"%d",&no);
 fprintf(fw,"\t%d",no);
 fscanf(fr,"%c",&ch);
 }
 if(strcmp(buff,"(s,")==0)
 {
 fscanf(fr,"%d",&no);

 fprintf(fw,"\t%d",s[no-1].add);
 fscanf(fr,"%c",&ch);
 }
 if(strcmp(buff,"(l,")==0)
 {
 fscanf(fr,"%d",&no);
 fprintf(fw,"\t%d",l[no-1].add);
 fscanf(fr,"%c",&ch);
 }

}
fscanf(fr,"%s",buff);
if(strcmp(buff,"(ad,02)")==0)
goto end;
goto readinst;

end:
	getch();
}
/* OUTPUT:

symbol table
         1               sai             116
         2               om            119
         3               li               120
literal table
         1               ='2'            121
         2               ='1'            122
         3               ='4'            122
*/
