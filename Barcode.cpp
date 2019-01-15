// ConsoleApplication14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include "user.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

// compile: g++ {user,network,test_shortest_path}.cpp -o test_shortest_path
// bool is_number(const string& s)
// {
	// return !s.empty() && find_if(s.begin(), 
		// s.end(), [](char c) { return !isdigit(c); }) == s.end();
// }
vector<User> readProducts(const char* filename);
void printUser(vector<User> v);
int barCodeMatch(string b, vector<User> v);
void writeProducts(const char* filename, vector<User> v);
int main(int argc, char* argv[]) {
	string skipNewItem;
	string barCode;
	double pPrice;
    double sPrice;
	string productName;
	int ioChoice;
    int newChoice;
    int pCount = 0;
    int pID = -1;
    int didNotMatch;
    int indexOfList;
	vector<string> barVector;
	vector<User> productsList = readProducts("test.txt");
    if(productsList.empty()){
        pID = 0;
    }
    else{
        pID = productsList.size();
    }
	//MAIN MANUE
    
	cout << "Please choice the floowing options" << endl;
	cout << "Enter 1 for input products" << endl;
	cout << "Enter 2 for output products" << endl;
    cout << "Enter any other key to exist the program" << endl;
	cin >> ioChoice;
    while(ioChoice != -1){
        if (ioChoice == 1) {
            cout << "Enter 1 for a new products" << endl;
            cout << "Enter 2 for increase count of exsit product"<<endl;
            cout << "Enter -1 to exit the program"<<endl;
            cin>>newChoice;
            if(newChoice == -1){
                break;
            }
            if(newChoice == 1){
                do{
                    cout << "Please enter the new items start with barcode" << endl;
                   
                    cout << "Please enter BarCode" << endl;
                    cin >> barCode;
                    cout << "Please enter name of the Product" << endl;
                    cin >> productName;
                    cout << "Please enter the price of the Product" << endl;
                    cin >> pPrice;
                    cout << "Please enter the sales price of the Product" << endl;
                    cin >> sPrice;
                    cout << "Do you know how many products you have? (if you do not know enter 0)"<<endl;
                    cin >> pCount;
                    
                    productsList.push_back(User(pID, barCode, productName, pPrice,sPrice, pCount));
                    cout << "Continuing entering new products?(enter 1 to continue, enter 2 to increase count of exsit product)" << endl;
                    cin >> newChoice;
                    if(newChoice != 1 && newChoice != 2){
                    	
                    	do{
                    		cout<<"Wrong input!"<<endl;
                    		cout<<"Please enter 1 to continue, enter 2 to increase count of exsit product, enter -1 to end program"<<endl;
                    		cin >> newChoice;
                    	}while(newChoice != 1 || newChoice != 2 || newChoice != -1);
                    }
                }while(newChoice == 1);
                cout << newChoice<<endl;
            }

            if(newChoice == 2){
				do{
					cout << "Please enter the barcode (Enter -1 to exit)" << endl;
					cin>>barCode;
					indexOfList = barCodeMatch(barCode,productsList);
					if(indexOfList==-1){
						cout<<"Did not match the barcode in the system, do you want to add a new item?(Please enter 0 for add a new item, other key for continue scanning)"<<endl;
						cin >> didNotMatch;
						if(didNotMatch == 0){
							break;
						}
					}
					else{
						productsList[indexOfList].increaseCount();
					}
				}while(didNotMatch != 0 || barCode.compare("-1"));
            }
            // printUser(productsList);
        }
		else if(ioChoice == 2){
			do{
				cout << "Please enter a barcode to decrease a product in the system"<<endl;
				cin >> barCode;
				indexOfList = barCodeMatch(barCode,productsList);
				if(indexOfList == -1){
					cout<<"Did not match the barcode in the system, do you want to add a new item?(Please enter 0 for add a new item, other key for continue scanning)"<<endl;
					cin >> didNotMatch;
					if(didNotMatch == 0){
						break;
					}
				}
				else{
						if(productsList[indexOfList].getCount() < 0){
							cout<<"You do not have any products left in your stock"<<endl;
							break;
						}
						productsList[indexOfList].decreaseCount();
					}
			}while(didNotMatch != 0 || barCode.compare("-1"));
		}
		cout << "Please choice the floowing options" << endl;
		cout << "Enter 1 for input products" << endl;
		cout << "Enter 2 for output products" << endl;
    	cout << "Enter -1 to exist the program" << endl;
		cin >> ioChoice;
    }
	cout<<"Write the products out to test.txt"<<endl;
	writeProducts("test.txt", productsList);
    cout<<"Thank you for using the program"<<endl;
    cout<<"Bye-bye"<<endl;
    cout<<"Stark"<<endl;

	return 0;
}
//

vector<User> readProducts(const char* filename){
    ifstream inFile;
    inFile.open(filename);
    int numUsers = 0;
    int productID;
    string productName;
    double productPrice;
    double salesPrice;
    string bCode;
    int productCount;
    vector<User> listOfProducts;
    inFile>>numUsers;
    int hardCount = 0;
    //Until the EOF, read through the input file
    do{
        //Special case when no friends in the file
        if(hardCount == numUsers){
            break;
        }
        
        if (numUsers == 0) {
            break;
        }
        for (int j = 0; j < numUsers; j++) {
            //Read UserID
            inFile>>productID;
            inFile>>bCode;
            //Read User name
            inFile>>productName;
            //Read User product Price
            inFile>>productPrice;
            
            //Read User sales Price
            inFile>>salesPrice;
            //Read user's friends
            inFile>>productCount;
            
            listOfProducts.push_back(User(productID,bCode,productName,productPrice,salesPrice,productCount));
        }
        hardCount++;
        //EOF check
    }while(!inFile.fail());
    inFile.close();
    return listOfProducts;
}
void writeProducts(const char* filename, vector<User> v){
	ofstream outFile(filename);
    for(int i = 0 ; i < (signed)v.size(); i ++){
        outFile << v[i].getID() << ": " << setw(14) << left << v[i].getBCODE() << setw(20) << left << v[i].getName()
                << v[i].getPrice() << " " << v[i].getSale() << " " << v[i].getCount() << endl;
    }
    
    outFile.close();
}
void printUser(vector<User> v){
    for(int i = 0 ; i < (signed)v.size();i++){
        cout<<"ID: "<<v[i].getID()<<" BarCode: "<<v[i].getBCODE()<<" Name: "<<v[i].getName()<<" Price: "<<v[i].getPrice()<<" Sale: " <<v[i].getSale()<<" Count: "<<v[i].getCount()<<endl;
    }
}
//return index found -1 not found.
int barCodeMatch(string b, vector<User> v){
    for(int i = 0 ; i < (signed)v.size();i++){
        if(b.compare(v[i].getName())==0){
            return i;
        }
    }
    return 0;
}