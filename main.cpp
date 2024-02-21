#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

class contact{
private:
	char fName[50], lName[50], address[50], email[50];
	long long phNo;
		
public:
	void createContact() {
		cout<<"What is your first name: ";
		cin>>fName;
		cout<<"What is your last name: ";
		cin>>lName;
		cout<<"What is your phone number: ";
		cin>>phNo;
		cout<<"What is your address: ";
		cin>>address;
		cout<<"What is your email: ";
		cin>>email;	
	}
		
	void writeOnFile() {
		char ch;
		ofstream file;
		file.open("Contace_Management_System.dat", ios::binary | ios::app);

		do {
			createContact();
			file.write(reinterpret_cast<char*>(this),sizeof(*this));
			cout<<"Do you have next data?(y/n)";
			cin>>ch;
		}while(ch=='y');

		cout<<"Contact has been Sucessfully Created...";
		file.close();
	}

	void deleteFromFile() {
		long long num;
		int flag = 0;
		ofstream file;
		ifstream tempfile;

		file.open("Contace_Management_System.dat",ios::binary);
		tempfile.open("temp.dat",ios::binary);

		cout<<"which contact you want to delete: (Use the phone number to delete the contact)";
		cin>>num;

		while(!tempfile.eof()) {
			if(tempfile.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if(phNo!=num) {
					file.write(reinterpret_cast<char*>(this),sizeof(*this));
				}
				else 
					flag = 1;
			}
		}
		tempfile.close();
		file.close();
		remove("Contace_Management_System.dat");
		rename("temp.dat","Contace_Management_System.dat");

		flag==1?
		cout<<endl<<endl<<"\tContact Deleted...":
		cout<<endl<<endl<<"\tContact Not Found...";
	}
		
	void editContact() {
		long long num;
		fstream file;

		cout<<"Edit contact";
		cout<<"\n===============================\n\n";
		cout<<"Enter the phone number to be edit: ";
		cin>>num;

		file.open("Contace_Management_System.dat",ios::binary|ios::out|ios::in);

		while(!file.eof()) {
			if(file.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if (phNo==num) {
					cout<<"Enter new record\n";
					createContact();
                    cout << sizeof(*this);
					long long pos=-1*sizeof(*this);
					file.seekp(pos,ios::cur);
					file.write(reinterpret_cast<char*>(this),sizeof(*this));
					cout<<endl<<endl<<"\t Contact Successfully Updated...";
					return;
				}
			}
		}
		cout<<"\n\n No record not found";
		file.close(); 
	}

    void showContact() {
		cout<<"Name: "<<fName<<" "<<lName<<endl;
		cout<<"Phone: "<<phNo<<endl;
		cout<<"Address: "<<address<<endl;
		cout<<"Email: "<<email<<endl;	
	}
		
	void readFromFile() {
		ifstream file;
		file.open("Contace_Management_System.dat",ios::binary);

		cout<<"\n================================\n";
		cout<<"LIST OF CONTACTS";
		cout<<"\n================================\n";

		while(!file.eof()) {
			if(file.read(reinterpret_cast<char*>(this),sizeof(*this)))
			{
				showContact();
				cout<<"\n================================\n";
			}
		}
		file.close();
	}
		
	void searchOnFile() {
		ifstream file;
		long long phone;
		cout<<"Enter phone no.: ";
		cin>>phone;
		file.open("Contace_Management_System.dat",ios::binary);

		while(!file.eof()) {
			if(file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phone==phNo) {
					showContact();
					return;
				}
			}
		}
		cout<<"\n\n No record not found";
		file.close(); 
	}
};
		
int main() {
	system("cls");
	// system("Color 3F"); // "Color XY", X - backgroung color, Y - text color

	cout<<"\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
	getch();

	while(1) {
		contact c1;
		int choice;

		system("cls");

		cout<<"\nCONTACT MANAGEMENT SYSTEM";
        cout<<"\n\nMAIN MENU";
		cout<<"\n=====================\n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] List all Contacts\n";
        cout<<"[3] Search for contact\n";
        cout<<"[4] Delete a Contact\n";
        cout<<"[5] Edit a Contact\n";
        cout<<"[0] Exit";
		cout<<"\n=====================\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice) {
        	case 1:
        		system("cls");
        		c1.writeOnFile();
        		break;

        	case 2:
				system("cls");
        		c1.readFromFile();
        		break;

			case 3:
        		system("cls");
        		c1.searchOnFile();
        		break;

        	case 4:
				system("cls");
        		c1.deleteFromFile();
        		break;

        	case 5:
			    system("cls");
        		c1.editContact();
        		break;

        	case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank you for using CMS."<<endl<<endl;
        		exit(0);
        		break;

        	default:
				continue;	
		}

		int opt;
		cout<<"\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
		cin>>opt;

		switch (opt) {
			case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank you for using CMS."<<endl<<endl;
        		exit(0);
        		break;

			default:
				continue;
		}
	}

	return 0;
}