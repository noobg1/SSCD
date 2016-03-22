#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<vector>
using namespace std;

//#include<conio.h>

#include<stdlib.h>
class estab
{
	public:
	string csect;
	//char symbol[12][6];
	int start_add,length;
	vector<string> def_sym;// def_sym[5][6];
	int def_add[5];
	int define_index;
	int ref_index;
	vector<string> ref_sym;//char ref_sym[12][6];
};

int main()
{
	//char input[10],ch;
	//int i,count=0,start,length,loc;
	//FILE *fp1,*fp2,*fp;
	//fp=fopen("C:/Users/KARTHIK/Desktop/KARTHIK/6th Sem/sscd project/t1.txt","r");
	//fp1=fopen("t1.txt","r");
	estab table[10];
	ifstream infile ("linkin.txt");
	
	ofstream outfile ("linkouttest1.txt");
	
	/*while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);*/
	printf("\nEnter the location where the program has to be located: ");
	//scanf("%x",&start);
	int start, count = 0;
	cin>>start;
	int CSADDR = start,n,m,ind,imd,flag = 0;
	//printf("%x",start);
	//fprintf(fp2,"CSect\tSym_Name\tAddress\t\tLength\n\n");
	outfile << "CSect\tSym_Name\tAddress\t\tLength\n\n";
	//rewind(fp1);
	string line;int lnum = 0;
	while(getline (infile,line))
	{
	//fscanf(fp1,"%s",input);
		char record;
		cout<<line<<endl;
		record = line[0];string str;
		switch(record){
			case 'H' : //strcpy(table[count].csect,line.substr(1,6));
						str = line.substr(1,6);
						table[count].csect.assign(str);
						str = line.substr(7,6);
						table[count].start_add = stoi(str) + CSADDR;
						//table[count].start_add += CSADDR;
						str = line.substr(13,18);
						table[count].length = stoi(str);
						break;
			case 'D' : n = line.length();
						  ind = table[count].define_index = 0;
						  //cout<<n;
						  m = n /12;
						for(int i = 1;i < n -1; i = i + 12){
						//strcpy(table[count].def_sym[table[count].define_index],line.substr(i,i+5));
						//if(flag == 0)
						
						str = line.substr(i,6);
						
						table[count].def_sym.push_back(str);
						str = line.substr(i+6,6);
						table[count].def_add[table[count].define_index] =  stoi(str) + CSADDR;
						
						flag = 1;
						
						/*else {
						str = line.substr(i,i+5);
						table[count].def_sym.push_back(str);
						str = line.substr(i+6,i+11);	
						table[count].def_add[table[count].define_index] =  stoi(str) + CSADDR;
						flag = 0;
						}*/
						//table[count].def_add[ind] += CSADDR;
						//cout<<i<<endl;
						//cout<<
						table[count].define_index++;
					}
					//table[count].define_index /= 2;
					break;
			case 'R' :  m = line.length();
						  imd = table[count].ref_index = 0;
						  //string k;
					for(int i = 1;i < m; i = i + 6){
						//strcpy(table[count].ref_sym[table[count].ref_index],line.substr(i,i+5));
						str = line.substr(i,i+5);
						table[count].ref_sym.push_back(str);
						table[count].ref_index++;
					}
					break;
			case 'E' : 
						CSADDR += table[count].length;
						count++;
						//cout<<count;
						//break;
			default : 
					cout<<"default";break;			
		}
		continue;

	}
		
		
	
	for(int i=0;i<count;i++)
	{  
		outfile << table[i].csect << "\t\t\t\t" << table[i].start_add << " \t\t\t" << table[i].length <<endl<<endl;
		for(int j = 0; j < table[i].define_index ; j++)
		{
		//fprintf(fp2,"%s\t%s\t\t%x\t\t%x\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
		outfile << "\t\t" << table[i].def_sym[j] << "\t\t" <<table[i].def_add[j]<< endl;
		
		}
	}
	outfile.close();
	infile.close();
	//delete[] table;
	//cout<<endl<<table[0].def_sym[0]<<" "<<table[0].def_add[0]<<endl;
	
	return 0;
}
