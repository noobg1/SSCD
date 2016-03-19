#include<stdio.h>
//#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct estab
{
	char csect[10];
	char sym_name[10];
	int add,length;
}table[10];

void main()
{
	char input[10],ch;
	int i,count=0,start,length,loc;
	FILE *fp1,*fp2,*fp;
	//fp=fopen("C:/Users/KARTHIK/Desktop/KARTHIK/6th Sem/sscd project/t1.txt","r");
	fp1=fopen("t1.txt","r");
	
	fp2=fopen("linkouttest.txt","w"); 
	
	/*while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);*/
	printf("\nEnter the location where the program has to be located: ");
	scanf("%x",&start);
	//printf("%x",start);
	fprintf(fp2,"CSect\tSym_Name\tAddress\t\tLength\n\n");
	rewind(fp1);
	while(!feof(fp1))
	{
	fscanf(fp1,"%s",input);
	if(strcmp(input,"H")==0)
	{
		fscanf(fp1,"%s",input);
		//printf("\n%s",input);
		strcpy(table[count].csect,input);
		strcpy(table[count].sym_name,"**");
		fscanf(fp1,"%s",input);
		table[count].add=atoi(input)+start;
		fscanf(fp1,"%x",&length);
		table[count++].length=length;
		printf("one %d",count);
		fscanf(fp1,"%s",input);
	}
	if(strcmp(input,"D")==0)
	{
	fscanf(fp1,"%s%x",input,&loc);
	while(strcmp(input,"R")!=0)
	{
		strcpy(table[count].csect,"**");
		strcpy(table[count].sym_name,input);
		table[count].add=loc+start;
		table[count++].length=0;
		printf("two %d",count);
		fscanf(fp1,"%s%x",input,&loc);
	}
	while(strcmp(input,"T")!=0)
		fscanf(fp1,"%s",input);
	}
	if(strcmp(input,"T")==0)
		while(strcmp(input,"E")!=0)
			fscanf(fp1,"%s",input);
	fscanf(fp1,"%s",input);
	start=start+length;
	}
	for(i=0;i<count;i++)
		fprintf(fp2,"%s\t%s\t\t%x\t\t%x\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
	fclose(fp1);
	fclose(fp2);
}
