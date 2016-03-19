#include <stdio.h>
#include <stdlib.h>
 
int main()
{
   char ch, file_name[25];
   FILE *fp;
 
   //printf("Enter the name of file you wish to see\n");
   //gets(file_name);
 
   fp = fopen("C:/Users/KARTHIK/Desktop/KARTHIK/6th Sem/sscd project/linkout.txt","r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   printf("The contents of file are :\n");
 
   while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);
 
   fclose(fp);
   return 0;
}
