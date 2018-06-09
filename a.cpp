#include<iostream>
#include<string.h>
#include<fstream>
#include <conio.h>
using namespace std;
char encryptpasswd[62][4];
int count=1;
class encryption
{
public:
string checkencrypt(char *a)
{
	int k;
	int len = strlen(a);
	string pass;
	for(int i=0;i<len;i++)
	{
		if(a[i]>='0' && a[i]<='9')
		{
			k=a[i];
			k-=48;
		}
		else if(a[i]>='a' && a[i]<='z')
		{
			k=a[i];
			k-=97;
			k+=9;
		}
		else if(a[i]>='A' && a[i]<='Z')
		{
			k=a[i];
			k-=65;
			k+=35;
		}
		for(int j=0;j<4;j++)
		{
			pass += encryptpasswd[k][j];

		}
	}
	return pass;
}
void encrypt()
{
	for(int i=0;i<62;i++)
	{
		encryptpasswd[i][0]=i+41;
		encryptpasswd[i][1]=i+31;
		encryptpasswd[i][2]=i+65;
		encryptpasswd[i][3]=i-97;
	}
}


int checkfunc(string check)
{
	count=1;
	int flag=0;
	ifstream infile;
	infile.open("Username.txt");
	infile.clear();
	infile.seekg(0, infile.end);
	int length=infile.tellg();
	infile.seekg(0,infile.beg);
	string output;

	while(!infile.eof())
	{
		getline(infile,output);
		if(output==check)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
		}
		count++;
	}
	if(flag)
		return 1;
	else
		return 0;
}


int checkpasswd(string check)
{
	int flag=0;
	ifstream infile;
	infile.open("Username.txt");
	infile.seekg(0,infile.beg);
	string output;
	for(int i=0;i<=count;i++)
	{
		getline(infile,output);
	}
	if(output==check)
		return 1;
	else
		return 0;
}

char* inputpassword(){
	char *passwd = new char [15];
	cout<<"Enter password"<<endl;
	cin.ignore();
	cin.getline(passwd,15);	
	return passwd;
}




void inputdata()
{
	// std::vector<char> password;
	char name[50],passwd[15];
	int len;
	ofstream outfile;

	outfile.open("Username.txt", ios::app);
	outfile.seekp(outfile.end);
	do{
		cout<<"Enter Username"<<endl;
		//checkfunc();
		cin.ignore();
		cin.getline(name,50);
		if(checkfunc(name))
		{
			cout<<"Username Already exists!"<<endl;
			continue;
		}
		else
		{
			break;
		}
	}while(1);
	getpassword:
	{
		cout<<"Enter password"<<endl;
		// cin.ignore();
		cin.getline(passwd,15);
	
		len=strlen(passwd);
		for(int i=0;i<len;i++)
		{
			if((passwd[i]>='a' && passwd[i]<='z') || (passwd[i]>='0' && passwd[i]<='9') || (passwd[i]>='A' && passwd[i]<='Z'))
			{
			}
			else
			{
				goto getpassword;
			}
		}	
	}
	string pass;
	outfile<<name<<"\n";
	int k;
	for(int i=0;i<len;i++)
	{
		if(passwd[i]>='0' && passwd[i]<='9')
		{
			k=passwd[i];
			k-=48;
		}
		else if(passwd[i]>='a' && passwd[i]<='z')
		{
			k=passwd[i];
			k-=97;
			k+=9;
		}
		else if(passwd[i]>='A' && passwd[i]<='Z')
		{
			k=passwd[i];
			k-=65;
			k+=35;
		}
		for(int j=0;j<4;j++)
		{
			outfile<<encryptpasswd[k][j];
			pass += encryptpasswd[k][j];

		}
		outfile<<"";
	}
	outfile<<"\n";
	outfile.close();
}
};
main()
{
	int hello=0;
	encryption en;
	en.encrypt();
	int num	,k;
	cout<<"Enter 1 for login, 2 for signup, 3 for exit"<<endl;
	cin>>num;
	while(num==1 || num==2)
	{
	if(num==1)
	{
		string user;
		char * newpasswd = new char [15];
		cout<<"Enter Username"<<endl;
		cin>>user;
		if(en.checkfunc(user))
		{
			newpasswd = en.inputpassword();
			string newencrypt = en.checkencrypt(newpasswd);
			if(en.checkpasswd(newencrypt))
			{
				cout<<"You are Logged in!"<<endl;
				hello=1;
				break;
			}
			else
			{
				cout<<"Incorrect username/password!"<<endl;
			}


		}
		
	}
	else if(num==2)
	{
		cout<<"Username Must not contain Spaces!"<<endl;
		en.inputdata();
	}
	else
	{
		cout<<"Wrong input"<<endl<<"Try again"<<endl;
	}
	cout<<"Enter 1 for login, 2 for signup, 3 for exit"<<endl;
	cin>>num;
	}
	if(hello)
	{
		cout<<"If you want to logout enter 1 else you can stay here and have fun :)!"<<endl;
		int number;
		cin>>number;
		if(number==1)
			return 0;

	}
	//encrypt();
	getch();

}