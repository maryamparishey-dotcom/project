#include <iostream>
#include <string>
#include <fstream>  
using namespace std;
struct bankaccount {
	int accountnumber ;
	string accountname;
	double balanceamount ;                                                                                      
	
	};
	void createaccount( bankaccount account[], int &count ){
		cout <<" Enter your account name : ";
		cin>>account[count] .accountname;
	
		cout <<"Enter account number: ";
		cin>>account[count].accountnumber ;
		cout<<"Enter your balance amount : ";
		cin>>account[count].balanceamount ;
		count ++;
		cout <<"Account created successfully!";
		
		
	}
	void displayaccount(bankaccount account[],int count ){
	if(count == 0) {
        cout <<"No accounts available.\n";
        return;
    }
     cout <<"\n--- All Accounts ---\n";

	for(int i = 0; i < count; i++){
    cout <<"\n--- Account Info ---\n";
    cout <<"Account Holder Name: " << account[i].accountname << endl;
    cout <<"Account Number: " << account[i].accountnumber << endl;
    cout <<"Balance Amount: " << account[i].balanceamount << endl;
}
}

	void depositamount (bankaccount account[],int count ){
		int amount,accountno;
		bool found =false ;
		cout<<"Enter your account number "; 
		cin >>accountno;
 int index=0;
		for(int i = 0; i < count; i++){
			
		 if(account[i].accountnumber == accountno){ //searching
		  found =true ;
		 	index =i;
		 	break;
			}
		}
			if (found){
		 cout <<"Enter deposit amount";
		cin >>amount ; //search ur account
		account[index].balanceamount=account[index].balanceamount+amount ;
		cout <<"Your balance after depositing is : "<<account[index].balanceamount;
	}
	else {
		cout <<"Your account dont exist";
	}
	
	}
	
	void withdraw (bankaccount account[], int count ){
		int amount,accountno,index=0,i;
			bool found =false ;
		cout<<"Enter your account number: "; 
		cin >>accountno;
			for( i = 0; i < count; i++){
				 if(account[i].accountnumber == accountno){ // Searching account
				 	found =true ;
					index=i;
				 	break;
				 }
			}
		if (found )	{		 
				cout <<"Enter amount u want to withdraw: ";
	        	cin >>amount ;
		  if(amount <= account[index].balanceamount){
	
		account[index].balanceamount=account[index].balanceamount-amount ;
		cout<<"You have withdraw ur amount and now ur balance is : "<<account[i].balanceamount;
}
	else { 
	cout <<"Insufficient balance ";
	}  	
    }
    else 
    {
    	cout << "Your account dont exist";
	}
    }
	void modifyaccountinfo (bankaccount account[],int count ){
		int accountno,i,index=0;
		bool found =false;
		cout<<"Enter your account number "; 
		cin >>accountno;
		for( i = 0; i < count; i++){   
				 if(account[i].accountnumber == accountno){ // Searching account
				 	found =true ;
				 	index=i;
				 	break;
				 }
			}
				 	if (found )	{
		cout <<"Update your data in below fields "<<endl;
		cout <<" Enter  your new account name ";
		cin>>account [index].accountname;
		cout <<"Enter your new account number ";
		cin>>account[index].accountnumber ;
		cout<<"Enter your new  balance amount ";
		cin>>account[index].balanceamount ;
		cout <<"Your data has been succesfully updated!";
		 //displayaccount(account);
	}
else {
	cout << "Your account dont exist";
}
}	
void deleteaccount(bankaccount account[], int &count) {
    int accountno;
    cout << "Enter your account number to delete: ";
    cin >> accountno;

    bool found = false;
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (account[i].accountnumber == accountno) {   // Search for deleting account
            found = true;
            index = i;
            break;
        }
    }

    if (found) {
        for (int i = index; i < count - 1; i++) {
            account[i] = account[i + 1]; 
        }
        count--;
        cout << "Account deleted successfully.\n";
    } else {
        cout << "Account not found \n";
    }
}

void saveToFile(bankaccount account[], int count) {
    ofstream fout("accounts.txt");
    for (int i = 0; i < count; i++) {
        fout << account[i].accountnumber << " "
             << account[i].accountname << " "
             << account[i].balanceamount << endl;
    }
    fout.close();
}

// Load accounts from file
void loadFromFile(bankaccount account[], int &count) {
    ifstream fin("accounts.txt");
    count = 0;
    while (fin >> account[count].accountnumber 
               >> account[count].accountname 
               >> account[count].balanceamount) {
        count++;
    }
    fin.close();
}


int main (){  
 bankaccount account[50];  // array to store up to 50 accounts
    int count = 0; 
	char choice;
	// Load accounts at start
    loadFromFile(account, count);


do {
	
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Modify Account information \n";
        cout << "6. Delete Account\n";  
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice ){
        	case '1' :
			createaccount( account,count );
			saveToFile(account, count);
			break;
			case '2' :
			displayaccount( account,count );
			saveToFile(account, count);
			break;
			case '3' :
			depositamount(account,count );
			saveToFile(account, count);
			break;
			case '4':
         	withdraw (account,count );
         	saveToFile(account, count);
         	break;
         	case '5' :
         	modifyaccountinfo (account,count);
         	saveToFile(account, count);
         	break;
            case '6':
        	deleteaccount(account, count);
        	saveToFile(account, count);
			break;
			case '7':
         	exit (0);
         	break;
         	default :
         		cout << "Invalid input ";
         		break;
		} 

}while (choice!='7');
return 0;
}
