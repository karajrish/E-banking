//***************************************************************
//                   HEADER FILES
//****************************************************************


#include<fstream>
#include<iostream>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<process.h>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();   //function to modify account data from user
	void dep(float);	//function to accept amount and add/DEPOSIT to balance amount
	float draw(float);	//function to accept amount and subtract/WITHDRAW from balance amount
	void report();	//function to show data in tabular format
	int retacno();	//function to return account number
	int retdeposit();	//function to return balance amount
	char rettype();	//function to return type of account
};         //class ends here

void account::create_account()//Function to create account using specific details
{
	accreate:
	cout<<"\n\n MAIN MENU->1.NEW ACCOUNT-->REGISTRATION\n\n";
	cout<<"\n WARNING: ANY ERROR WHILE REGISTERING, OR ENTERING ANY FORM OF DATA \n THAT IS NOT RECOGNISED BY THE RESPECTIVE FIELDS WILL RESTART THE REGISTRATION\n PROCESS. USERS ARE ADVISED TO BE CAREFUL WHILE REGISTERING. ";
	cout<<"\n\n\nEnter The account No.(>100) :";
	cin>>acno;

	if (acno<100)
	{
	  cout<<"\a\n\n Enter account number correctly.";getch();
	  goto accreate;
	}

   ifstream file;
   file.open("account.dat",ios::binary);
   account a1;
   while(file)
   {
   	file.read((char*)&a1,sizeof(a1));
      if(a1.retacno()==acno)
      {
      	cout<<"\a\n\n Account number already exists.";
   	   goto accreate;
      }
   }

	cout<<"\n\nEnter The Name of The account Holder : "; gets(name);

	cout<<"\nEnter Type of The account (C/S) : "; cin>>type;
	type=toupper(type);//converting to uppercase character

	cout<<"\n\n Your account type choice:"<<type;
	if(type!='C'&&type!='S')
  {
	 cout<<"\a\n\n Incorrect Account type. Choose from C or S. ";
	 goto accreate;
  }
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;

	if((type=='S')&&(deposit<500))
	{
	  cout<<"\n For Savings Account, enter an initial amount greater than or equal to 500.";
	  goto accreate;
	}
	else if ((type=='C')&&(deposit<1000))
	{ cout<<"\n For Current Account, enter an initial amount greater than or equal to 1000.";
	  goto accreate;
	}
	else

	cout<<"\n\n\nAccount Created Successfully. Press any key to return to MAIN MENU.";
}

void account::show_account()//Function to show account details
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : "<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()//Function to modify existing account
{
	cout<<"\nAccount Number: "<<acno;
	cout<<"\n\nEnter Name of Account Holder : ";
	gets(name);

	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);

	cout<<"\nEnter The amount : ";
	cin>>deposit;
}



void account::dep(float x)//Function to ADD/DEPOSIT money in account
{
	deposit+=x;
}

float account::draw(float x)//Function to SUBTRACTD/WITHDRAW money in account
{
	deposit-=x;
	return(deposit);
}

void account::report()//Function to PRINT tabulated report
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno()//Function to return account number
{
	return acno;
}

int account::retdeposit()//Function to return deposit
{
	return deposit;
}

char account::rettype()//Function to return accoutn type
{
	return type;
}
//END OF CLASS ASSOCIATED FUCNTIONS

//***************************************************************
//    	FUNCTION PROTOTYPES
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to DEPOSIT AND WITHDRAW amount for given account
void moneyac_transfer();//function to transfer money between two specific accounts
void intro();	//introductory screen function
void box();
//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	int ch;
	int num;
	intro();//Fucntion to display introductory screen
	do
	{  mainmenu:


		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\n\t=========";
	   cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. ACCOUNT CREDIT";
		cout<<"\n\n\t03. ACCOUNT DEBIT";
		cout<<"\n\n\t04. ACCOUNT INFORMATION ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY ACCOUNT ";
		cout<<"\n\n\t08. MONEY TRANSFER BETWEEN TWO ACCOUNTS";
		cout<<"\n\n\t09. EXIT";
		cout<<"\n\n\tSelect Your Option (1-9): ";
		cin>>ch;

		if(ch>9)
		{cout<<"\nEnter a choice less than 10. Redirecting......\n\n";
		 goto mainmenu;
		}


		switch(ch)
		{
		case 1://NEW ACCOUNT
			write_account();
			break;
		case 2://DEPOSIT AMOUNT: n=1->DEPOSIT
			cout<<"\n\n MAIN MENU->2.ACCOUNT CREDIT";
			cout<<"\n\n\n\n\tEnter The account No. : "; cin>>num;
			if(num<100)
			{
			  cout<<"\a\n  WRONG ACCOUNT NUMBER. Going back to  main menu...";
			  goto mainmenu;
			  long wait=-9999;
			  while(++wait<10000);

			}
			deposit_withdraw(num, 1);
			break;
		case 3://WITHDRAW AMOUNT: n=2->WITHDRAW
			cout<<"\n\n MAIN MENU->3.ACCOUNT DEBIT";
			cout<<"\n\n\n\n\tEnter The account No. : "; cin>>num;
			if(num<100)
			{
			  cout<<"\a\n  WRONG ACCOUNT NUMBER. Going back to  main menu...";
			  long wait=-9999;
			  while(++wait<10000);
			  goto mainmenu;
			}
			deposit_withdraw(num, 2);
			break;
		case 4://BALANCE ENQUIRY
			cout<<"\n\n MAIN MENU->4.ACCOUNT INFORMATION ENQUIRY";
			cout<<"\n\n\n\n\tEnter The account No. : "; cin>>num;if(num<100)
			{
			  cout<<"\n  WRONG ACCOUNT NUMBER. Going back to  main menu...";
			  long wait=-9999;
			  while(++wait<10000);
			  goto mainmenu;
			}
			display_sp(num);
			break;
		case 5://DISPLAY REPORT
			cout<<"\n\n MAIN MENU->5.ALL ACCOUNT HOLDER LIST\n\n\n";
			display_all();
			break;
		case 6://CLOSE ACCOUNT
			cout<<"\n\n MAIN MENU->6.CLOSE ACCOUNT ";
			cout<<"\n\n\n\n\tEnter The account No. : "; cin>>num;
			if(num<100)
			{
			  cout<<"\n  WRONG ACCOUNT NUMBER. Going back to  main menu...";
			  long wait=-9999;
			  while(++wait<10000);
			  goto mainmenu;
			}
			delete_account(num);
			break;
		 case 7://MODIFY ACCOUNT
			cout<<"\n\n MAIN MENU->7.MODIFY ACCOUNT ";
			cout<<"\n\n\n\n\tEnter The account No. : "; cin>>num;
			if(num<100)
			{
			  cout<<"\n  WRONG ACCOUNT NUMBER. Going back to  main menu...";
			  long wait=-9999;
			  while(++wait<10000);
			  goto mainmenu;
			}
			modify_account(num);
			break;
		 case 8://MONEY TRANSFER BETWEEN TWO ACCOUNTS
			cout<<"\n\n MAIN MENU->8.MONEY TRANSFER BETWEEN TWO ACCOUNTS ";
			moneyac_transfer();
			break;

		 case 9://EXIT
			cout<<"\n\t  Thank you for using the Electronic Bank Management System\n\n\n\n\n\n";
			box();

			}//end of switch case
			getch();

  }while(ch!=9);
  return 0;

}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;// Class:account Class Object:ac
	ofstream outFile;  //ofstream mode:to write data to file
	outFile.open("account.dat",ios::binary|ios::app); //binary file for data writing, append mode : to continue writing after the last record
	ac.create_account();//Member function of class to initialize values
	outFile.write((char *) &ac, sizeof(account));//Writing enterted details to record
	outFile.close();//Closing file
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)//Function to display specific account details(given by user)
{
	account ac;// Class:account Class Object:ac
	int flag=0;
	ifstream inFile;//ifstream mode:to read data from file
	 inFile.open("account.dat",ios::binary);//binary file for data reading

	//Error Checking for error during file opening
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	//Error Checking for error during file opening

	cout<<"\nBALANCE DETAILS\n";
	 while(inFile.read((char *) &ac, sizeof(account)))//Reading the file "InFile"
	{
		if(ac.retacno()==n)//Checking if saved account number = enyered account number
		{
			ac.show_account();//Funciton to show account
			flag=1;
		}
	}
	 inFile.close();//Closing File
	if(flag==0)
		cout<<"\a\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	 File.open("account.dat",ios::binary|ios::in|ios::out);//Opening File in both modes

	//Error Checking for error during file opening
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	//Error Checking for error during file opening

	 while(File.read((char *) &ac, sizeof(account)) && found==0)//Reading the file "File"
	{
		if(ac.retacno()==n)//Checking if saved account number = entered account number
		{
			ac.show_account(); //Function to show account
			cout<<"\n\nEnter The New Details of account"<<endl;

			ac.modify();//Function to modify account

			int pos=(-1)*sizeof(account); //position for entry into binary data file

			File.seekp(pos,ios::cur);//positioning the pointer for data entry
			 File.write((char *) &ac, sizeof(account)); //writing data to file

			 cout<<"\n\n\t Record Updated";
			 found=1;
		  }
	}
	File.close();//closing file
	if(found==0)
		cout<<"\a\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{


	account ac;
	ifstream inFile;//to read data from file
	ofstream outFile;//to write dat to file
	inFile.open("account.dat",ios::binary);

	//Error Checking for error during file opening
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	//Error Checking for error during file opening

	outFile.open("Temp.dat",ios::binary);

	inFile.seekg(0,ios::beg);//Placing pointer at the beginning of the file
	while(inFile.read((char *) &ac, sizeof(account)))//Reading records from file
	{
		if(ac.retacno()!=n)//chekcing: if saved account number = entered account number
		{
			outFile.write((char *) &ac, sizeof(account));//writing records to file
		}
	}
	 inFile.close(); //Closing file
	 outFile.close();//Closing file

	remove("account.dat"); //Deleting Binary file
	rename("Temp.dat","account.dat"); //renaming Binary File
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile; //to read data from file
	inFile.open("account.dat",ios::binary); //opening binary file to read data

	//Error Checking for error during file opening
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	//Error Checking for error during file opening

	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";

	while(inFile.read((char *) &ac, sizeof(account)))//Reading file records
	{
		ac.report(); //Calling function to print in tabulated form
	}
	inFile.close();//Closing file
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;//TO read data from file and write data to file
	 File.open("account.dat", ios::binary|ios::in|ios::out);

	//Error Checking for error during file opening
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	//Error Checking for error during file opening

	 while(File.read((char *) &ac, sizeof(account)) && found==0) //'account' is the class. 'ac' is the class object.
	{
		if(ac.retacno()==n)//Checking: if saved account number = entered account number
		{
			ac.show_account(); //SHOWING ACCOUNT DETAILS AND CURRENT STATUS

			if(option==1)//1->DEPOSIT
			{
				rp1:
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;

				//Checking for negative amount
				if(amt<0)
				{
				  cout<<"\a\n\n ERROR: Negative amount. Please re-enter.";
				  goto rp1;
				}
				else
				ac.dep(amt);//'amt' is passed to member function: dep
			}
			 if(option==2)//2->WITHDRAW
			{
				rp2:
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;

				if(amt<0)
				{
				  cout<<"\a\n\n ERROR: Negative amount. Please re-enter.";
				  goto rp2;
				}
				else
			  {
				int bal=ac.retdeposit()-amt;

				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance";
				else
					ac.draw(amt);//'amt' is passed to member function: draw
				}

			}
			int pos=(-1)* sizeof(ac);//position of record
			File.seekp(pos,ios::cur);//Plaicing pointer at the current position
			File.write((char *) &ac, sizeof(account));//WRitign data to file
			cout<<"\n\n\t Record Updated";
			found=1;
			 }
	 }
	 File.close();//CLosign the file
	if(found==0)
		cout<<"\a\n\n Record Not Found ";
}

//***************************************************************
//    	FUNCTION TO TRANSFER MONEY BETWEEN TWO ACCOUNTS
//****************************************************************

void moneyac_transfer()
{ account ac;
  int ac1,ac2,tf=0,pos1=0,pos2=0;
  float acmt;
  rp3:
  cout<<"\n Enter account number FROM which money is to TRANSFERRED:";
  cin>>ac1;

  cout<<"\n Enter account number TO which money is to be DEPOSITED:";
  cin>>ac2;


	 fstream File;//TO read data from file and write data to file
	 File.open("account.dat", ios::binary|ios::in);

	//Error Checking for error during file opening
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File)
	{
		pos1=File.tellg();
		File.read((char*)&ac,sizeof(ac));

		cout<<"\n Verifying account number...";
		long wait=-99999;
		while(++wait<10000);

		if(ac.retacno()==ac1)//Checking: if saved account number1 = entered ac1
		{
		  cout<<"\n Ac1 Matches.";
		  cout<<"\n Saved account number"<<ac.retacno();
		  cout<<"\n Entered account number1:"<<ac1;
		  tf=1;
		  break;
		}
	}
	File.close();
	if(tf==0)
	{
	  cout<<"\n Account number 1 doesn't match. Retry.";
	  goto rp3;
	}
	else
	{  tf=0;
		File.open("account.dat", ios::binary|ios::in);
		while(File)
		 {//start of while loop
			pos2=File.tellg();
			File.read((char*)&ac,sizeof(ac));
			if(ac.retacno()==ac2)//Checking: if saved account number1 = entered ac1
			{ cout<<"\n Account number 2 checking...";
			  cout<<"\n Ac2 Matches.";
			  cout<<"\n Saved account number"<<ac.retacno();
				cout<<"\n Entered account number2:"<<ac2;
				tf=1;
				break;
			}//end of if
		 }//end of while
		File.close();
		if(tf==0)
		{
			cout<<"\n Account number 2 doesn't match. Retry.";
			goto rp3;
		}
		else
		{//start of else

			cout<<"\nEnter the amount to be transferred:";
			cin>>acmt;

		//deducting money from account 1..
			File.open("account.dat", ios::binary|ios::in|ios::out);
			File.seekg(pos1);
			File.read((char*)&ac,sizeof(ac));
			if(ac.draw(acmt)<0)
				cout<<"\n\nTRANSFER NOT POSSIBLE DUE TO INSUFFICIENT BALANCE"<<endl;
			else
				{//start of else
				 File.seekp(pos1);
				 File.write((char*)&ac,sizeof(ac));
				 File.close();
				 cout<<"\n Rupees "<<acmt<<" is transferred from account: "<<ac1;

				 //depositing money to account 2..
				 File.open("account.dat", ios::binary|ios::in|ios::out);
				 File.seekg(pos2);
				 File.read((char*)&ac,sizeof(ac));
				 ac.dep(acmt);
				 File.seekp(pos2);
				 File.write((char*)&ac,sizeof(ac));
				 File.close();
				 cout<<"\n Rupees "<<acmt<<" is transferred to account: "<<ac2;
				}//end of else
		 }//end fo else
	}//end of else
}//end of moneyac_transfer fucntion

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout<<"\n\n\n\t\t\t  BANK MANAGEMENT SOFTWARE\n";
	cout<<"\t\t  ========================================";
	cout<<"\n\n\n\n MADE BY : Rishabh Karajgi\n";
	cout<<"\n\n\n Welcome to the Bank Management Software.\n Let's get started. Press any key to proceed. ";

	getch();
}

void box()
{
int i,j;
for( j=0;j<29;++j)//loop controlling horizontal alignment
cout<<" ";
for (i=0; i<10; i++)
cout<<'*'<<" "; //prints the first row
i=1;
while (i<4)
{
cout<<"\n";
for(int j=0;j<29;++j)
cout<<" ";
cout<<'*';
if(i==1)
{cout<<" Done By:-";cout<<setw(8)<<'*';}
else if(i==2)
{cout<<" Rishabh Karajgi";cout<<setw(2)<<'*';}
i++;
}
cout<<"\n";
for(j=0;j<29;++j)//loop controlling horizontal alignment
cout<<" ";
for (i=0;i<10; i++)
cout<<'*'<<" "; // prints the last row
cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
