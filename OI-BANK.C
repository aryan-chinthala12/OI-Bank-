#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#define SPACE(k) for(j=1;j<=k;j++) fprintf(stdout," ");
#define LINE for(j=1;j<=80;j++)  fprintf(stdout,"-");
struct customer
{
   int accno;
   char name[20];
   float balance;

};
void create();
void view();
void delet();
void edit();
int main()
{
  int i,j,k;
  int x;
  clrscr();
  SPACE(32);
  printf(" OI bank\n");
  LINE;
  SPACE(12)
  printf("\n---Welcome---\n");
  printf("\nWhat do u wanna do: \n1]Create a file and enter new accounts.");
  printf("\n2]Display the accounts [customer report].");
  printf("\n3]Delete any account in the file");
  printf("\n4]Edit the file [withdrawal or deposit done by customer]");
  printf("\nEnter the choice what to do: ");
  scanf("%d",&x);
  fflush(stdin);

  switch(x)
  {
     case 1:
     create();
     break;

     case 2:
     view();
     break;

     case 3:
     delet();
     break;

     case 4:
     edit();
     break;

     default:
     printf("\nWrong choice , choose again ");
     main();

  }
  getch();
  return 0;
}


void create()
{
  struct customer oi;
  FILE *fp;
  int j,k;
  char fname[50];
  clrscr();
  SPACE(37);
  printf("OI-Bank\n");
  LINE;
  printf("\nEnter any file to store these with ending with .dat : ");
  gets(fname);
  fp=fopen(fname,"wb");
  printf("\n...Welcome to OI Bank...");
  printf("\nPress 0 at account no. to stop.\n");

  for(; ;)
  {
     printf("\nEnter your Account No.: ");
     scanf("%d",&oi.accno);
     if(oi.accno==NULL)
	break;
     fflush(stdin);
     printf("\n\tEnter your name : ");
     gets(oi.name);
     printf("\nEnter your balance amount : ");
     scanf("%f",&oi.balance);
     fwrite(&oi,sizeof(oi),1,fp);

  }
  printf("\nOI Bank.dat file is succesfully created...!");
  fclose(fp);

}


void view()
{
  struct customer oi;
  int i=1,j,k;
  char fname[30];
  FILE *fp;
  clrscr();
  printf("\nEnter your file name : ");
  gets(fname);
  fp=fopen(fname,"rb");
  if(fp==NULL)
  {
    printf("\nFile not found ...");
    getch();
    return;
  }
  clrscr();
  SPACE(22);
  fprintf(stdout,"\nOI Bank Customer Report\n");
  LINE;
  fprintf(stdout,"\n%10s","S.no");
  fprintf(stdout,"%25s","Account no");
  fprintf(stdout,"%25s","Name");
  fprintf(stdout,"%12s","Balance");
  fprintf(stdout,"\n");
  LINE;
  fread(&oi,sizeof(oi),1,fp);
  while(!feof(fp))
  {
    fprintf(stdout,"\n%10d",i);
    fprintf(stdout,"%25d",oi.accno);
    fprintf(stdout,"%25s",oi.name);
    fprintf(stdout,"%12.2f",oi.balance);

    fread(&oi,sizeof(oi),1,fp);
  }
  fprintf(stdout,"\n");
  LINE;
  fclose(fp);

}


void delet()
{
 struct customer oi;
 FILE *fp,*fp1;
 int tempno,j,k;
 char pfile[20],nfile[20];
 clrscr();
 SPACE(37);
 printf("OI-Bank\n");
 LINE;
 printf("\nEnter the file name which has the accounts. ");
 scanf("%s",&pfile);
 printf("\nEnter the new file name . ");
 scanf("%s",&nfile);
 fp=fopen(pfile,"rb");
 fp1=fopen(nfile,"wb");
 printf("\nEnter the account no to be deleted? ");
 scanf("%d",&tempno);
 fread(&oi,sizeof(oi),1,fp);
 while(!feof(fp))
 {
    if(tempno!=oi.accno)
       fwrite(&oi,sizeof(oi),1,fp1);
    fread(&oi,sizeof(oi),1,fp);

 }
 fclose(fp);
 fclose(fp1);
 remove(pfile);
 rename(nfile,pfile);
 printf("\nOne record deleted succesfully....");

}


void edit()
{
    struct customer oi;
  FILE *fp;
  int tempno,recsize,j,k;
  char choice,fname[30];
  float amount=0;
  clrscr();
  SPACE(37);
  printf("OI-Bank\n");
  LINE;
  printf("\nENter the file name where u stored accounts: ");
  scanf("%s",&fname);
  fp=fopen(fname,"r+b");
 // fflush(stdin);
  printf("\nEnter account no: ");
  scanf("%d",&tempno);
  fread(&oi,sizeof(oi),1,fp);
  while(!feof(fp))
  {
     if(tempno==oi.accno)
     {
	printf("\nEnter W for withdrawal \nD for deposit : ");
	fflush(stdin);
	scanf("%c",&choice);
	if(toupper(choice)=='D')
	{
	   printf("\nENter amount to deposit? ");
	   scanf("%f",&amount);
	   oi.balance+=amount;
	}
	else if(toupper(choice)=='W')
	{
	   printf("\nENter amount to withdraw? ");
	   scanf("%f",&amount);
	   oi.balance-=amount;
	}
	else
	{
	   printf("\nINvalid choice...");
	}
	recsize=sizeof(oi);
	fseek(fp,-recsize,SEEK_CUR);
      fwrite(&oi,sizeof(oi),1,fp);
      fclose(fp);
      exit(0);
     }
     fread(&oi,sizeof(oi),1,fp);
  }
  printf("\nDone the file changed...");

}