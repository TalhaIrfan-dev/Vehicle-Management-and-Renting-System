#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Structure to store vehicle details
struct Vehicle {
    int id;
    string model;
    string registrationNumber;
    string type;
    bool isAvailable;
};
// Structure to store customer details
struct Customer {
    string Name;
    string phno;
    string cnicNumber;
    string email;
    int rentedCarId; // Car Number customer has rented
};

// Constants
 int MAX_VEHICLES = 100;
 int MAX_CUSTOMERS = 100;

// Function
void add ( Vehicle *&vehicles, int&count);
void displayVehicles(Vehicle vehicles[],int &count);
void searchVehicle( Vehicle vehicles[], int count);
void editVehicle(Vehicle vehicles[], int count);
void deleteVehicle(Vehicle vehicles[], int& count);
void rentVehicle(Vehicle vehicles[],Customer *&customers, int& count, int& customercount);
void displaycustomer(Vehicle vehicles[],Customer customers[], int& count, int& customercount);

// main
int main(){
	
	int choice;
	int vehicleCount = 0;
	int customerCount = 0;

	
	
	
	// file to read vehicle data
	ifstream readvehicle("Vehicles Data.text");
	string data;
		    while(getline(readvehicle,data))
		    {
				vehicleCount++;
			}
	readvehicle.close();
	if (vehicleCount>=MAX_VEHICLES)
	{
		MAX_VEHICLES=vehicleCount*2;
	}
	Vehicle *vehicles = new Vehicle[MAX_VEHICLES];
	
	
	
	
	// file to read customer data
	ifstream readcustomer("Customer Data.text");
	string details;
			while(getline(readcustomer , details))
			{
				customerCount++;
			}
	readcustomer.close();
	if (customerCount>=MAX_CUSTOMERS)
	{
		MAX_CUSTOMERS=customerCount*2;
	}
	Customer *customers = new Customer[ MAX_CUSTOMERS];
	
	//menue
	do
	{
		cout<<setfill('=')<<setw(53)<<"="<<endl;
		cout<<"=====      WELCOME TO CAR RENTING FACILITY      =====\n";
		cout<<setfill('=')<<setw(53)<<"="<<endl;
		cout<<"1. Add New Vehicle to Facility.\n";
		cout<<"2. Display Vehicles of Facility.\n";
		cout<<"3. Search Vehicle in Facility.\n";
		cout<<"4. Edit Details of Vehicle\n";
		cout<<"5. Delete Vehicle From System\n";
		cout<<"6. Rent a Vehicle.\n";
		cout<<"7. Display Customers.\n";
	    cout<<"0. to Exit\n";
	    cout<<setfill('-')<<setw(43)<<"-"<<endl<<endl;
	    cout<<"Enter your Choice : ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				add(vehicles, vehicleCount);
			break;
			case 2:
				displayVehicles(vehicles, vehicleCount);
			break;
			case 3:
	            searchVehicle(vehicles, vehicleCount);
	        break;
	        case 4:
	            editVehicle(vehicles, vehicleCount);
	        break;
	        case 5:
	            deleteVehicle(vehicles, vehicleCount);
	        break;
	        case 6:
	            rentVehicle(vehicles, customers,vehicleCount , customerCount);
	        break;
	        case 7:
	            displaycustomer(vehicles, customers,vehicleCount , customerCount);
	        break;
	        case 0:
	            cout << "\nExiting the program. Goodbye!\n";
	        break;
	        default:
	            cout << "\nInvalid choice! Please try again.\n";
		}
		cout<<endl<<endl<<endl;
		system("Pause");
		system("cls");
		
	}while(choice!=0);
	cout<<"you are out of the menue\n";	
	
	return 0;
}

// Funtction to Add vehicle
void add ( Vehicle *&vehicles, int &count)
{
	string type;
	int check;
	
	// dynamically increase size of array
	if (count>=MAX_VEHICLES)                       // To check if maximum limit of cars is reached
	{
		Vehicle *temp = new Vehicle[MAX_VEHICLES];
		for(int i=0; i<MAX_VEHICLES; i++)
		{
			temp[i]=vehicles[i];
		}	
		delete[] vehicles;
		MAX_VEHICLES*=2;
		
		vehicles = new Vehicle[MAX_VEHICLES];
		
		for(int i=0; i<count; i++)
		{
			vehicles[i] = temp[i];
		}
		delete[] temp;	
		temp=NULL;
	}
	
	// filing :
	
	string data, strID;
	int ID, found;
	
		cout<<"\n\n";
		cout<<setfill('=')<<setw(53)<<"="<<endl;
		cout<<"=====               Add Vehicle                 =====\n";
		cout<<setfill('=')<<setw(53)<<"="<<endl;
	//	cout<<"\n\n-------Enter details of Vehicle-------\n";
		cout << "Enter Vehicle ID         : ";
	   do
	   {
		    cin >> vehicles[count].id;
		    check=0;
		    
		    
		    ifstream readvehicle("Vehicles Data.text");					// reading data from file of vehicle data
		    while(getline(readvehicle,data))
		    {
			    found = data.find(",");
			    if (found!= string::npos)
					{
						strID=data.substr(0,found);
						stringstream(strID) >> ID;
				    	if (vehicles[count].id == ID)
				    	{
				    		check++;
				    		cout<<"This Id is already registered make new Id : ";
				    		
						}
					}
			}
			readvehicle.close();
		}while(check!=0);
	    
	    cin.ignore();                                // To consume the newline character after the ID
	    cout << "Enter Vehicle Model      : ";
	    getline(cin, vehicles[count].model);
	    cout << "Enter Registration Number: ";
	    getline(cin, vehicles[count].registrationNumber);
	    cout << "Enter Vehicle Type (Car/Bike/Van) : ";
	    getline(cin, type);
	    
	    for(int i=0; i<type.length(); i++)
	    { type[i]=tolower(type[i]);     }
	    
	    vehicles[count].type = type;
		vehicles[count].isAvailable = true;
		
		//storing data in to vehicle data file
		ofstream vehicledata("Vehicles Data.text", ios::app); 
		
		vehicledata << vehicles[count].id<<","<<vehicles[count].model<<","<<vehicles[count].registrationNumber<<","<<vehicles[count].type<<","<<boolalpha<<vehicles[count].isAvailable<<".";
		
		
		
		count++;
		cout << "\nVehicle added successfully!!\n\n";
		vehicledata.close();
	
	
}

// Function to Display Vehicles
void displayVehicles(Vehicle vehicles[], int &count)
{
	int vc=0;
	string data;
	string ID, Model, RN, type, Avail;
	int find1,find2,find3,find4,find5;
	
	// opening file of vehicle data and storng data of vhicles in structure
	ifstream readvehicle("Vehicles Data.text");
	
	while(getline(readvehicle,data))
	{
		find1=data.find(",");
		if(find1!=string::npos)
		{
			ID=data.substr(0,find1);
		}
		
		find2=data.find("," , (find1+1));
		if(find2!=string::npos)
		{
			Model=data.substr((find1+1) , (find2-find1-1));
		}
		
		find3=data.find("," , (find2+1));
		if(find3!=string::npos)
		{
			RN=data.substr((find2+1) , (find3-find2-1));
		}
		
		find4=data.find("," , (find3+1));
		if(find4!=string::npos)
		{
			type=data.substr((find3+1) , (find4-find3-1));
			for(int i=0; i<type.length(); i++)
	    	{ type[i]=tolower(type[i]);     }
		}
		
		find5=data.find("." , (find4+1));
		if(find4!=string::npos)
		{
			Avail=data.substr((find4+1) , (find5-find4-1));
		}
		
		
		stringstream(ID)>>vehicles[vc].id;
		vehicles[vc].model=Model;
		vehicles[vc].registrationNumber=RN;
		vehicles[vc].type=type;
		if (Avail=="true")
		{
			vehicles[vc].isAvailable=true;
		}
		else if(Avail=="false")
		{
			vehicles[vc].isAvailable=false;
		}
		
		vc++;
	}
		
	// display vehicle
	int choose;
	cout<<"\n\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
	cout<<"=====             Display Vehicles              =====\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;	
	cout<<"1. Check available vehicles.\n";
	cout<<"2. Display all vehicles.\n";
	cout<<"\nEnter you Choice : ";
	cin>>choose;
	
	if (choose == 1)
	{
		cout << "\n--- Available Vehicle List ---\n";
		cout<<setfill('=')<<setw(75)<<"="<<endl;
		cout<<setfill(' ')<<setw(8)<<left<<"ID:"<<setw(16)<<"Model:"<<setw(27)<<"Registration Number:"<<setw(10)<<"Type:"<<"Availability:"<<endl;
		cout<<setfill('=')<<setw(75)<<"="<<endl;
	    for (int i = 0; i < count; i++) 
		{
			if (vehicles[i].isAvailable == true)
			{ 
			  cout<<setfill(' ')<<setw(8)<<left<<vehicles[i].id<<setw(18)<<vehicles[i].model<<setw(25)<<vehicles[i].registrationNumber<<setw(10)<<vehicles[i].type<<(vehicles[i].isAvailable ? "Yes" : "No")<<endl;
			}
		}
		cout<<setfill('=')<<setw(75)<<"="<<endl;	
	}
	else if (choose == 2)
	{
		cout << "\n--- Vehicle List ---\n";
		cout<<setfill('=')<<setw(75)<<"="<<endl;
		cout<<setfill(' ')<<setw(8)<<left<<"ID:"<<setw(16)<<"Model:"<<setw(27)<<"Registration Number:"<<setw(10)<<"Type:"<<"Availability:"<<endl;
		cout<<setfill('=')<<setw(75)<<"="<<endl;
	    for (int i = 0; i < count; i++) 
		{
			
			cout<<setfill(' ')<<setw(8)<<left<<vehicles[i].id<<setw(18)<<vehicles[i].model<<setw(25)<<vehicles[i].registrationNumber<<setw(10)<<vehicles[i].type<<(vehicles[i].isAvailable ? "Yes" : "No")<<endl;		
	    }
	    cout<<setfill('=')<<setw(75)<<"="<<endl;
	}
	
	readvehicle.close();
}

//Function to Search vehicle if it is Availabe
void searchVehicle(Vehicle vehicles[], int count) 
{
	int vc=0;
	string data;
	string ID, Model, RN, type, Avail;
	int find1,find2,find3,find4,find5;
	
	// again opening file to read data and store it in structure
	ifstream readvehicle("Vehicles Data.text");
	
	while(getline(readvehicle,data))
	{
		find1=data.find(",");
		if(find1!=string::npos)
		{
			ID=data.substr(0,find1);
		}
		
		find2=data.find("," , (find1+1));
		if(find2!=string::npos)
		{
			Model=data.substr((find1+1) , (find2-find1-1));
		}
		
		find3=data.find("," , (find2+1));
		if(find3!=string::npos)
		{
			RN=data.substr((find2+1) , (find3-find2-1));
		}
		
		find4=data.find("," , (find3+1));
		if(find4!=string::npos)
		{
			type=data.substr((find3+1) , (find4-find3-1));
			for(int i=0; i<type.length(); i++)
	    	{ type[i]=tolower(type[i]);     }
		}
		
		find5=data.find("." , (find4+1));
		if(find4!=string::npos)
		{
			Avail=data.substr((find4+1) , (find5-find4-1));
		}
		
		
		stringstream(ID) >> vehicles[vc].id;
		vehicles[vc].model=Model;
		vehicles[vc].registrationNumber=RN;
		vehicles[vc].type=type;
		if (Avail=="true")
		{
			vehicles[vc].isAvailable=true;
		}
		else if(Avail=="false")
		{
			vehicles[vc].isAvailable=false;
		}
		
		vc++;
	}
	readvehicle.close();
	
	
	// search vehicle
    int id, choice, check;
    string vehicleChoice;
    
    cout<<"\n\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
	cout<<"=====              Search Vehicle               =====\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
   
	cout<<"1. Search with ID \n2. Search with Type of Vehicle \n\nEnter your Choice: ";
	cin>>choice;
		
	switch(choice)
	{
		case 1 :
			cout << "\nEnter Vehicle ID to search: ";
		    cin >> id;
		
		    for (int i = 0; i < count; i++) {
		        if (vehicles[i].id == id) {
		            cout << "\n-----  Vehicle Details  -----\n";
		            cout<<setfill('-')<<setw(43)<<"-"<<endl;
		            cout << "ID                 : " << vehicles[i].id<<endl;
		            cout << "Model              : " << vehicles[i].model<<endl;
		            cout << "Registration Number: " << vehicles[i].registrationNumber<<endl;
		            cout << "Type               : " << vehicles[i].type<<endl;
		            cout << "Availability       : " << (vehicles[i].isAvailable ? "Yes" : "No") << "\n";
		            return;
		        }
		    }
		    cout << "Vehicle not found.\n";
		break;
		case 2 :
			cout<<"\nWhich type of vehicle do you want to search ( Car, Bike, Van) : ";
			cin>>vehicleChoice;
		 	for(int i=0; i<vehicleChoice.length(); i++)
			{ vehicleChoice[i]=tolower(vehicleChoice[i]);  }
		
			check=0;
				cout<<setfill('=')<<setw(75)<<"="<<endl;
				cout<<setfill(' ')<<setw(8)<<left<<"ID:"<<setw(16)<<"Model:"<<setw(27)<<"Registration Number:"<<setw(10)<<"Type:"<<"Availability:"<<endl;
				cout<<setfill('=')<<setw(75)<<"="<<endl;
			for (int i = 0; i < count; i++) {
	        	if ((vehicles[i].type) == vehicleChoice){
	            cout<<setfill(' ')<<setw(8)<<left<<vehicles[i].id<<setw(18)<<vehicles[i].model<<setw(25)<<vehicles[i].registrationNumber<<setw(10)<<vehicles[i].type<<(vehicles[i].isAvailable ? "Yes" : "No")<<endl;
			    check++;
	        	}
	    	}
	    	if (check==0)
	    	{
	    		cout << "Vehicle not found.\n";
	    		return;
			}
			cout<<setfill('=')<<setw(75)<<"="<<endl;
			 
		break;
		default :
			cout<<"Invalid Input.\n";
	}
 
}

//Function to Edit Vehicles Details
void editVehicle(Vehicle vehicles[], int count) {
	
	int vc=0;
	string data;
	string ID, Model, RN, type, Avail;
	int find1,find2,find3,find4,find5;
	
	// opening file to read and store data in to structure
	ifstream readvehicle("Vehicles Data.text");
	
	while(getline(readvehicle,data))
	{
		find1=data.find(",");
		if(find1!=string::npos)
		{
			ID=data.substr(0,find1);
		}
		
		find2=data.find("," , (find1+1));
		if(find2!=string::npos)
		{
			Model=data.substr((find1+1) , (find2-find1-1));
		}
		
		find3=data.find("," , (find2+1));
		if(find3!=string::npos)
		{
			RN=data.substr((find2+1) , (find3-find2-1));
		}
		
		find4=data.find("," , (find3+1));
		if(find4!=string::npos)
		{
			type=data.substr((find3+1) , (find4-find3-1));
			for(int i=0; i<type.length(); i++)
	    	{ type[i]=tolower(type[i]);     }
		}
		
		find5=data.find("." , (find4+1));
		if(find4!=string::npos)
		{
			Avail=data.substr((find4+1) , (find5-find4-1));
		}
		
		
		stringstream(ID) >> vehicles[vc].id;
		vehicles[vc].model=Model;
		vehicles[vc].registrationNumber=RN;
		vehicles[vc].type=type;
		if (Avail=="true")
		{
			vehicles[vc].isAvailable=true;
		}
		else if(Avail=="false")
		{
			vehicles[vc].isAvailable=false;
		}
		
		vc++;
	}
	readvehicle.close();
	
	
	
	// Edit vehicle details
    int id,choice;
    
    cout<<"\n\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
	cout<<"=====               Edit Vehicle               =====\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
 //   cout << "\n=====Edit Details of Vehicle=====";
    cout << "\nEnter Vehicle ID to edit : ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (vehicles[i].id == id) {
        	
        	cout<<"\n1. Edit Avalibility \n2. Edit whole details \nEnter your Choice : ";
        	cin>>choice;
        	switch(choice)
        	{
        		case 1:
        			cout << "\nOld availability ("<<(vehicles[i].isAvailable ? "Yes" : "No")<<")  New availability? (1 for Yes, 0 for No): ";
		            cin >> vehicles[i].isAvailable;
		            
		            cout << "\nVehicle details updated successfully!\n\n";
		            cout << "======== New Details of Vehicle ========\n";
		            cout << "New ID                 : " << vehicles[i].id<<endl;
		            cout << "New Model              : " << vehicles[i].model<<endl;
		            cout << "New Registration Number: " << vehicles[i].registrationNumber<<endl;
		            cout << "New Type               : " << vehicles[i].type<<endl;
		            cout << "Availability           : " << (vehicles[i].isAvailable ? "Yes" : "No") << "\n";
        			
        	
        		break;
				case 2:
					cout<<"\n\n-------Enter new details of Vehicle \""<<id<<"\"-------\n";
					cout<<setfill('-')<<setw(75)<<"-"<<endl;
					cout<<setfill(' ')<<setw(35)<<left<<"Lables"<<setw(25)<<"Old Details"<<setw(27)<<"New Details"<<endl;
				    cout<<setfill('-')<<setw(75)<<"-"<<endl;
				    
		            cin.ignore();                                    // To consume the newline character
		            cout<<setfill(' ')<<setw(35)<<left<<"Model"<<setw(25)<<vehicles[i].model;
		            getline(cin, vehicles[i].model);
		            cout<<setfill(' ')<<setw(35)<<left<<"Registration Number"<<setw(25)<<vehicles[i].registrationNumber;
		            getline(cin, vehicles[i].registrationNumber);
		            cout<<setfill(' ')<<setw(35)<<left<<"Type (Car/Bike/Van)"<<setw(25)<<vehicles[i].type;
		            getline(cin, vehicles[i].type);
		            cout<<setfill(' ')<<setw(35)<<left<<"Available (1 for Yes, 0 for No)"<<setw(25)<<(vehicles[i].isAvailable ? "Yes" : "No");
		            cin >> vehicles[i].isAvailable;
					cout<<setfill('-')<<setw(75)<<"-"<<endl;
		
		            cout << "\nVehicle details updated successfully!\n\n";
		            cout << "======== New Details of Vehicle ========\n";
		            cout << "New ID                 : " << vehicles[i].id<<endl;
		            cout << "New Model              : " << vehicles[i].model<<endl;
		            cout << "New Registration Number: " << vehicles[i].registrationNumber<<endl;
		            cout << "New Type               : " << vehicles[i].type<<endl;
		            cout << "Availability           : " << (vehicles[i].isAvailable ? "Yes" : "No") << "\n";
		             
		        break;
		        default :
		        	cout<<"Invalid Input.\n";
		        
	    	}
	    	// opening file and storing data in file with out append mode
	    	ofstream vehicledata("Vehicles Data.text"); 
			
			for(int i=0; i<count; i++)
			{
				vehicledata <<vehicles[i].id<<","<<vehicles[i].model<<","<<vehicles[i].registrationNumber<<","<<vehicles[i].type<<","<<boolalpha<<vehicles[i].isAvailable<<"."<<endl;
	    	}
	    	vehicledata.close();
	
	    	
			return;
		}
		
    }
    cout << "Vehicle not found.\n";
}

//Funtion to Delete Vehicle
void deleteVehicle(Vehicle vehicles[], int& count) 
{
    int id, choice;
    
    cout<<"\n\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
	cout<<"=====              Delete Vehicle              =====\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
   // cout<<"\n=====Delete Vehicle from menue=====\n";
    cout << "Enter Vehicle ID to delete: ";
    cin >> id;
	
	string data;
	string ID;
	int find1;
	int numid;
	bool check=false;

	// opening file of vehicle and checking id given 
	ifstream readvehicle("Vehicles Data.text");
	ofstream temp("temp.text");
	while(getline(readvehicle,data))
	{
		find1=data.find(",");
		if(find1!=string::npos)
		{
			ID=data.substr(0,find1);                 // extract id before comma in Id variable
			stringstream(ID) >> numid;				// storing string values of id into integer id variable
		}
			
		if (numid == id)                 // compairing if given id is equal to id entracted from file line by line
		{
        	cout<<"Do you really want to delete vehicle (1.Yes / 2.No) : ";
        	do
			{
				cin>>choice;
	        	if(choice==1)
	        	{   
		            count--;
		            cout << "Vehicle deleted successfully!\n";
		        
		    	}
		    	else if(choice == 2)
		    	{
		    		cout<<"Ok!";
		    		temp<<data<<endl;           // storing data in to temperory file
				}
				else
				{cout<<"Please enter correct input.\n";
				}
				
				
        	}while(choice<1 || choice>2);
        	check=true;
		}
		else
		{
			temp<<data<<endl;                                 // storing data in to temperory file
		}
	}
	readvehicle.close();                 // closing files
	temp.close();
	
	ifstream tempfile("temp.text");
	ofstream updatevehicle("Vehicles Data.text");       //opening file without append mode to update data
	string line;
	while(getline(tempfile , line))
	{
		updatevehicle<<line<<endl;              // copying data from temperory file to original file of vehicle data again 
	}

    updatevehicle.close();
	tempfile.close();
	
	if(check==false)
	{
    	cout << "Vehicle not found.\n";
	}
	
}

//Function to Rent car;
void rentVehicle(Vehicle vehicles[],Customer *&customers, int& count, int& customercount)
{
	
	// dynamically increase the size of customers array	
	if (customercount>= MAX_CUSTOMERS)                       // To check if maximum limit of cars is reached
	{
		//Vehicle *temp = new Vehicle[MAX_VEHICLES];
		Customer *temp = new Customer[ MAX_CUSTOMERS];
		for(int i=0; i<MAX_CUSTOMERS; i++)
		{
			temp[i]=customers[i];
		}	
		delete[] customers;
		MAX_CUSTOMERS*=2;
		
		customers = new Customer[MAX_VEHICLES];
		
		for(int i=0; i<count; i++)
		{
			customers[i] = temp[i];
		}
		delete[] temp;	
		temp=NULL;
	}
	
	
	// opening file and storing data of vehicle in to structure of vehicle
	int vc=0;
	string data;
	string ID, Model, RN, type, Avail;
	int find1,find2,find3,find4,find5;
	
	ifstream readvehicle("Vehicles Data.text");
	
	while(getline(readvehicle,data))
	{
		find1=data.find(",");
		if(find1!=string::npos)
		{
			ID=data.substr(0,find1);
		}
		
		find2=data.find("," , (find1+1));
		if(find2!=string::npos)
		{
			Model=data.substr((find1+1) , (find2-find1-1));
		}
		
		find3=data.find("," , (find2+1));
		if(find3!=string::npos)
		{
			RN=data.substr((find2+1) , (find3-find2-1));
		}
		
		find4=data.find("," , (find3+1));
		if(find4!=string::npos)
		{
			type=data.substr((find3+1) , (find4-find3-1));
			for(int i=0; i<type.length(); i++)
	    	{ type[i]=tolower(type[i]);     }
		}
		
		find5=data.find("." , (find4+1));
		if(find4!=string::npos)
		{
			Avail=data.substr((find4+1) , (find5-find4-1));
		}
		
		
		stringstream(ID) >> vehicles[vc].id;
		vehicles[vc].model=Model;
		vehicles[vc].registrationNumber=RN;
		vehicles[vc].type=type;
		if (Avail=="true")
		{
			vehicles[vc].isAvailable=true;
		}
		else if(Avail=="false")
		{
			vehicles[vc].isAvailable=false;
		}
		
		vc++;
	}
	readvehicle.close();
	
	
	// giving vehicle on rent
	int check=0, Id;
	double rent;
	string vehicleChoice;
	
	cout<<"\n\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
	cout<<"=====                Rent Vehicle               =====\n";
	cout<<setfill('=')<<setw(53)<<"="<<endl;
	
	cout<<"Which type of Vehicle do you want to rent ( Car. 5000rs ,  Bike. 2000rs , Van. 6000) : ";   // asking type of vehicle
	cin>>vehicleChoice;
	 for(int i=0; i<vehicleChoice.length(); i++)
		{ vehicleChoice[i]=tolower(vehicleChoice[i]);  }          // converting input into tolower form for easy readibility
	

	cout << "\n--- Available Vehicle List ---\n";
	for (int i = 0; i < count; i++) {                              // displaying available vehicles
        if (((vehicles[i].type) == vehicleChoice)&&(vehicles[i].isAvailable == true)){
            if(check == 0)
            {
            	cout<<setfill('=')<<setw(75)<<"="<<endl;
				cout<<setfill(' ')<<setw(8)<<left<<"ID:"<<setw(16)<<"Model:"<<setw(27)<<"Registration Number:"<<setw(10)<<"Type:"<<"Availability:"<<endl;
				cout<<setfill('=')<<setw(75)<<"="<<endl;
			}
            
            cout<<setfill(' ')<<setw(8)<<left<<vehicles[i].id<<setw(18)<<vehicles[i].model<<setw(25)<<vehicles[i].registrationNumber<<setw(10)<<vehicles[i].type<<(vehicles[i].isAvailable ? "Yes" : "No")<<endl;
		    check++;
        }
    }
    if (check==0)
    {cout << "Vehicle not Available.\n";}
    else
    {
    	cout<<setfill('=')<<setw(75)<<"="<<endl;
    	
    	// Collect customer details
    	cout<<"\n\n========== RENTERS DETAILS =============\n";
	    cout << "Enter Customer details For rent "<<vehicleChoice<<":\n";
	    cout << "Name : ";
	    cin.ignore();
	    getline(cin,customers[customercount].Name);
	    cout << "Phone Number : ";
	    getline(cin,customers[customercount].phno);
	    cout << "CNIC Number : ";
	    getline(cin,customers[customercount].cnicNumber);
	    cout << "Email : ";
	    getline(cin,customers[customercount].email);
	    cout<<"Enter the ID of "<<vehicleChoice<<" for Rent : ";
	    cin>>Id;
	    
	    if (vehicleChoice=="car")
	    { rent = 5000; }
	    else if(vehicleChoice=="bike")
	     { rent = 2000; }
	    else if(vehicleChoice=="van")
	     { rent = 6000; }
	    
	    for(int i=0; i<count; i++)
	    {
	    	if ((vehicles[i].id == Id) && (vehicles[i].type== vehicleChoice) && (vehicles[i].isAvailable == true))
	    	{ 	vehicles[i].isAvailable = false;
	    	
	    		customers[customercount].rentedCarId = vehicles[i].id;       
			
					// displaying vehicle renting recipt
			
				cout << "\n-------Recipt of Renting car----------\n";
			    cout << "Vehicle "<<vehicleChoice<<" is  : " <<vehicles[i].id<<endl;
			    cout << "Price    : $" << fixed << setprecision(2) << rent << endl;
			    cout << "Customer : " << customers[customercount].Name << endl;
			    cout << "PH.No    : "<< customers[customercount].phno << endl;
				cout << "CNIC Number: " << customers[customercount].cnicNumber << endl;
			    cout << "Email      : " << customers[customercount].email << endl;
			    cout << "\nFormalities are completed! Enjoy your trip!" << endl;
	
			    	
			    	// opening file and storing data of customer in file
			    	ofstream customerdata("Customer Data.text", ios::app);
			    	
						customerdata <<customers[customercount].Name<<","<<customers[customercount].phno<<","<<customers[customercount].cnicNumber<<","<<customers[customercount].email<<","<<customers[customercount].rentedCarId<<"."<<endl;
					
			    	customerdata.close();
			    
			    customercount++;
			    
			    
			    // opening file to update data in vehicle data file because after renting availability of vehicle is changed
	    			ofstream vehicledata("Vehicles Data.text"); 
					
					for(int i=0; i<count; i++)
					{
						vehicledata <<vehicles[i].id<<","<<vehicles[i].model<<","<<vehicles[i].registrationNumber<<","<<vehicles[i].type<<","<<boolalpha<<vehicles[i].isAvailable<<"."<<endl;
			    	}
			    	vehicledata.close();
	    		
			    return;
			}
		}
		cout<<"\nThis Vehicle Does not Exist in Facility.\n";
	    
	}
}

// Function to displaying customer details
void displaycustomer(Vehicle vehicles[],Customer customers[], int& count, int& customercount)
{
	int vc=0;
	string data;
	string ID, Model, RN, type, Avail;
	int find1,find2,find3,find4,find5;
	
	
	// opening file and storing data of vehicle in structure
	ifstream readvehicle("Vehicles Data.text");
	
	while(getline(readvehicle,data))
	{
		find1=data.find(",");
		if(find1!=string::npos)
		{
			ID=data.substr(0,find1);
		}
		
		find2=data.find("," , (find1+1));
		if(find2!=string::npos)
		{
			Model=data.substr((find1+1) , (find2-find1-1));
		}
		
		find3=data.find("," , (find2+1));
		if(find3!=string::npos)
		{
			RN=data.substr((find2+1) , (find3-find2-1));
		}
		
		find4=data.find("," , (find3+1));
		if(find4!=string::npos)
		{
			type=data.substr((find3+1) , (find4-find3-1));
			for(int i=0; i<type.length(); i++)
	    	{ type[i]=tolower(type[i]);     }
		}
		
		find5=data.find("." , (find4+1));
		if(find4!=string::npos)
		{
			Avail=data.substr((find4+1) , (find5-find4-1));
		}
		
		
		stringstream(ID) >> vehicles[vc].id;
		vehicles[vc].model=Model;
		vehicles[vc].registrationNumber=RN;
		vehicles[vc].type=type;
		if (Avail=="true")
		{
			vehicles[vc].isAvailable=true;
		}
		else if(Avail=="false")
		{
			vehicles[vc].isAvailable=false;
		}
		
		vc++;
	}
	readvehicle.close();
	
	
	// opening file and storing data of customers in structure
	
	int cuscount=0;
	string details;
	string name, phno, cnic, email, RentVehicleId;
	int search1,search2,search3,search4,search5;
	
	ifstream readcustomers("Customer Data.text");
	
	while(getline(readcustomers,details))
	{
		search1=details.find(",");
		if(search1!=string::npos)
		{
			name=details.substr(0,search1);
		}
		
		search2=details.find("," , (search1+1));
		if(search2!=string::npos)
		{
			phno=details.substr((search1+1) , (search2-search1-1));
		}
		
		search3=details.find("," , (search2+1));
		if(search3!=string::npos)
		{
			cnic=details.substr((search2+1) , (search3-search2-1));
		}
		
		search4=details.find("," , (search3+1));
		if(search4!=string::npos)
		{
			email=details.substr((search3+1) , (search4-search3-1));
			
		}
		
		search5=details.find("." , (search4+1));
		if(find4!=string::npos)
		{
			RentVehicleId=details.substr((search4+1) , (search5-search4-1));
		}
		
		customers[cuscount].Name=name;
		customers[cuscount].phno=phno;
		customers[cuscount].cnicNumber = cnic;
		customers[cuscount].email=email;
		stringstream(RentVehicleId) >> customers[cuscount].rentedCarId;
		cuscount++;
	}
	readcustomers.close();
	
	
	
	// displaying details of customers if vehicle is on rent
	if (customercount == 0) {
        cout << "\nNo Vehicle is on rent yet." << endl;
        return;
    }
    
    cout<<"\n\nTotal vehicles rented by customers are : "<<customercount<<endl;
	for(int i=0; i<customercount; i++)
	{
		cout<<"\n------------Customer Details---------------";
		cout<<"\nThe customer no : "<<i+1<<endl;
		cout<<"\nCustomer Name : " << customers[i].Name << endl;
		cout<<"PH.No         : "<< customers[i].phno << endl;
		cout<<"CNIC Number   : " << customers[i].cnicNumber << endl;
		cout<<"Email         : " << customers[i].email << endl;
		cout<<"\nThe Vehicel rented by customer is : \n";
		for(int j=0; j<count; j++)
	    {
			if (vehicles[j].id == customers[i].rentedCarId)
			{
				cout << "ID                 : " << vehicles[j].id<<endl;
	            cout << "Model              : " << vehicles[j].model<<endl;
	            cout << "Registration Number: " << vehicles[j].registrationNumber<<endl;
	            cout << "Type               : " << vehicles[j].type<<endl;	
			}
		}
	}
	
	
	
}


