#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<utility>

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
	vector<string> ref_sym;
	vector<string> textrecord;
	int textrecord_index;
	pair<float,int> textp;
	vector<pair<float,int>> textv;//char ref_sym[12][6];
};

int check_table_def(string str,estab table[10], int count){
	for(int i = 0; i < table[count].define_index; i++){
		if( str.compare(table[count].def_sym[i]) == 0){
			cout<<"**** Define Record :: "<<table[count].def_sym[i]<<" occurs more than once**** "<<endl;
						exit(0);
		}
	}
	return 1;
}

int check_table_csect(string str,estab table[10], int count){
	for(int i = 0; i < count; i++){
		if( str.compare(table[i].csect) == 0 ){
			cout<<"**** Control Section name :: "<<table[i].csect<<" occurs more than once**** "<<endl;
						exit(0);
		}
	}
	return 1;
}
int mod_sym_search(string s,estab table[10],int count){
for(int i=0;i<count;i++)
	{  
		
		for(int j = 0; j < table[i].define_index ; j++)
		{
		//fprintf(fp2,"%s\t%s\t\t%x\t\t%x\n",table[i].csect,table[i].sym_name,table[i].add,table[i].length);
		if(s.compare(table[i].def_sym[j]) == 0){
			return table[i].def_add[j];
		}
		//cout<<s<<" : "<<table[i].def_sym[j]<<endl;
		
		}
	}
	return -1;
}

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
	ofstream pass2text("pass2text.txt");
	
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
	{//cout<<line<<endl;
	//fscanf(fp1,"%s",input);
		char record;
		int check ;
		
		record = line[0];string str;
		switch(record){
			case 'H' : //strcpy(table[count].csect,line.substr(1,6));
						//cout<<line.length();
						if(line.length() != 20){
							cout<<"*****Header Definition Invalid*****";
							exit(0);
						}
						str = line.substr(1,6);
						check_table_csect(str,table,count);
						table[count].csect.assign(str);
						str = line.substr(7,6);
						table[count].start_add = stoi(str) + CSADDR;
						//table[count].start_add += CSADDR;
						str = line.substr(13,18);
						table[count].length = stoi(str);
						break;
			case 'D' : n = line.length();
						if(n > 74){
							cout<<"*****Defintion Record Definition Invalid*****";
							exit(0);
						}

						  ind = table[count].define_index = 0;
						  //cout<<n;
						  m = n /12;
						for(int i = 1;i < n -1; i = i + 12){
						//strcpy(table[count].def_sym[table[count].define_index],line.substr(i,i+5));
						//if(flag == 0)
						
						str = line.substr(i,6);
						check_table_def(str,table,count);
						
						
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
						if(m > 74){
							cout<<"*****Reference Record Definition Invalid*****";
							exit(0);
						}
						  imd = table[count].ref_index = 0;
						  //string k;
					for(int i = 1;i < m; i = i + 6){
						//strcpy(table[count].ref_sym[table[count].ref_index],line.substr(i,i+5));
						str = line.substr(i,6);
						table[count].ref_sym.push_back(str);
						table[count].ref_index++;
					}
					break;
			case 'T' :{

						if(line.length() > 70){
							cout<<"*****Text Record Exceeds absolute length*****";
							exit(0);
						}
						table[count].textrecord_index = 0;
						str = line.substr(1,6);
						int text_start = stoul(str,NULL,16) + CSADDR;
						int text_len = stoul(line.substr(7,2),NULL,16);
						//cout<<text_len<<" "<<line.substr(7,2);
						pair<float,int> aux;
						for(int i = 9; i < text_len *2 + 9; i++){
							//if(i % 2 == 0)
							{
								//cout<<text_start + i/2<<"\t"<<line[i]<<endl;
								aux.first = (text_start * 2 + i -9)/2;
								aux.second = stoul(line.substr(i,1),NULL,16);
								table[count].textv.push_back(aux);
								
							}
							//else cout<<"\t"
						}
						table[count].textrecord_index++;
						break;
					}
			
			case 'E' : 
						CSADDR += table[count].length;
						count++;
						//cout<<count;
						break;
			default : 
					//cout<<"default";
						break;			
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
	
	pair<int,int> aux;
	for(int i = 0; i <count ;i++){
		for(vector<pair<float,int> >::iterator it2 = table[i].textv.begin(); it2 != table[i].textv.end(); ++it2){
			aux = *it2;
			pass2text << (float)aux.first <<" : "<<aux.second <<endl;
		}
	}

//pass 2
	infile.clear();
	infile.seekg(0);

	while(getline(infile,line)){
		//cout<<line;
		if(line[0] == 'M'){
			if(line.length() > 17)
				{
					cout<<"*****MOdification record Invalid*****";
					exit(0);
				}

						
						int mod_add = stoul(line.substr(1,6),NULL,16);
						int mod_len = stoul(line.substr(7,2),NULL,16);
						string mod_sign = line.substr(9,1);
						string mod_sym = line.substr(10,6);
						int mod_val = mod_sym_search(mod_sym,table,count);
						if(mod_sym.compare(table[1].def_sym[0]) == 0){
								cout<<table[1].def_sym[0]<<" " <<mod_sym<<endl;
							}
							cout<<table[1].def_sym[0]<<mod_sym<<":"<<endl;
						if(mod_val == -1)
						{
						cout<<"*****symbol not defined*****\n";
											//exit(0);
						}
						//cout<<mod_sym<<"\t"<<mod_val<<endl;
		}
	}

	outfile.close();
	infile.close();
	//delete[] table;
	//cout<<endl<<table[0].def_sym[0]<<" "<<table[0].def_add[0]<<endl;
	
	return 0;
}
