#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<vector>
using namespace std;

//#include<conio.h>

#include<stdlib.h>
struct estab
{
	char csect[6];
	//char symbol[12][6];
	int start_add,length;
	std::vector<string> def_sym(5);// def_sym[5][6];
	int def_add[5];
	int define_index;
	int ref_index;
	std::vector<string> ref_sym(12);//char ref_sym[12][6];
}table[10];

int main()
{
	//char input[10],ch;
	//int i,count=0,start,length,loc;
	//FILE *fp1,*fp2,*fp;
	//fp=fopen("C:/Users/KARTHIK/Desktop/KARTHIK/6th Sem/sscd project/t1.txt","r");
	//fp1=fopen("t1.txt","r");
	ifstream infile ("linkin.txt");
	
	ofstream outfile ("linkouttest.txt");
	
	/*while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);*/
	printf("\nEnter the location where the program has to be located: ");
	//scanf("%x",&start);
	int start, count = 0;
	cin>>start;
	int CSADDR = start,n,m;
	//printf("%x",start);
	//fprintf(fp2,"CSect\tSym_Name\tAddress\t\tLength\n\n");
	outfile << "CSect\tSym_Name\tAddress\t\tLength\n\n";
	//rewind(fp1);
	string line;
	while(getline (infile,line))
	{
	//fscanf(fp1,"%s",input);
		char record;
		record = line[0];
		switch(record){
			case 'H' : //strcpy(table[count].csect,line.substr(1,6));
						table[count].csect.assign(line.substr(1,6));
						table[count].start_add = std::stoi(line.substr(7,12)) + CSADDR;
						table[count].length = std::stoi(line.substr(13,19));
						break;
			case 'D' : n = line.length();
						 table[count].define_index = 0;
					for(int i = 1;i < n; i = i + 12){
						//strcpy(table[count].def_sym[table[count].define_index],line.substr(i,i+5));
						table[count].def_sym[table[count].define_index].assign(line.substr(i,i+5));
						table[count].def_add[table[count].define_index] = CSADDR + std::stoi(line.substr(i+6,i+12));
						table[count].define_index++;
					}
					break;
			case 'R' :  m = line.length();
						 table[count].ref_index = 0;
					for(int i = 1;i < m; i = i + 6){
						//strcpy(table[count].ref_sym[table[count].ref_index],line.substr(i,i+5));
						table[count].ref_sym[table[count].ref_index].assign(line.substr(i,i+5));
						table[count].ref_index++;
					}
					break;
			case 'E' : count++;
						CSADDR += table[count].length;
						break;
			default : break;			
		}


	}
		
		
	
	for(int i=0;i<count;i++)
	{  
		outfile << table[i].csect << "\t\t\t\t" << table[i].start_add << " \t" << table[i].length <<endl<<endl;
		for(int j = 0; j < table[i].define_index ; i++)
		{
		//fprintf(fp2,"%s\t%s\t\t%x\t\t%x\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
		outfile << "\t\t\t\t" << table[i].def_sym[j] << "\t" <<table[i].def_add[j]<< endl;
		}
	}
	
	return 0;
}
