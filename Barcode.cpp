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
#include <algorithm>
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
double totalPrice (vector<User> v);
int totalCount (vector<User> v);
double getProfitsForTotalProducts (vector<User> v);
double getPersentageForTotalProducts (vector<User> v);
void writeProducts(const char* filename, vector<User> v);
void writeOtherData(const char* filename, vector<User> v);
string replaceWhiteSpace (string text);
int main(int argc, char* argv[]) {
	string skipNewItem;
	string barCode;
	double pPrice;
    double sPrice;
	string productName;
	string ioChoice;
    string newChoice;
    int pCount = 0;
    int pID = -1;
    string didNotMatch;
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
    while(ioChoice.compare("1")== 0 || ioChoice.compare("2")== 0){
        if (ioChoice.compare("1")== 0) {
            cout << "Enter 1 for a new products" << endl;
            cout << "Enter 2 for increase count of exsit product"<<endl;
            cout << "Enter any keys to exit the program"<<endl;
            cin>>newChoice;
            if(newChoice.compare("-1") == 0){
                break;
            }
            if(newChoice.compare("1")==0){
                do{
                    cout << "Please enter the new items start with barcode" << endl;
                   
                    cout << "Please enter BarCode" << endl;
                    cin >> barCode;
                    cout << "Please enter name of the Product" << endl;
                    cin.ignore(); 
                    getline(cin, productName);
                    cout << productName<<endl;
                    replaceWhiteSpace(productName);
                    cout << productName<<endl;
                    cout << "Please enter the price of the Product" << endl;
                    cin >> pPrice;
                    cout << "Please enter the sales price of the Product" << endl;
                    cin >> sPrice;
                    cout << "Do you know how many products you have? (if you do not know enter 0)"<<endl;
                    cin >> pCount;
                    
                    productsList.push_back(User(pID, barCode, productName, pPrice,sPrice, pCount,0));
                    cout << "Continuing entering new products?(enter 1 to continue, enter 2 to increase count of exsit product)" << endl;
                    cin >> newChoice;
                    if(newChoice.compare("1")!=0 && newChoice.compare("2")!=0){
                    	
                    	do{
                    		cout<<"Wrong input!"<<endl;
                    		cout<<"Please enter 1 to continue, enter 2 to increase count of exsit product, enter -1 to end program"<<endl;
                    		cin >> newChoice;
                    	}while(newChoice.compare("1")!=0 && newChoice.compare("2")!=0 && newChoice.compare("-1")!=0);
                    }
                }while(newChoice.compare("1")==0);

            }

            if(newChoice.compare("2")==0){
				do{
					cout << "Please enter the barcode (Enter 'q' back to the main manu)" << endl;
					cin>>barCode;
                    if(!isdigit(barCode[0])){
                        break;
                    }
					indexOfList = barCodeMatch(barCode,productsList);
					if(indexOfList==-1){
						cout<<"Did not match the barcode in the system, do you want to add a new item?(Please enter 0 for add a new item, other key for continue scanning)"<<endl;
						cin >> didNotMatch;
						if(didNotMatch.compare("0") == 0){
							break;
						}
					}
					else{
						productsList[indexOfList].increaseCount();
					}
				}while(didNotMatch.compare("0") != 0);
            }
            
        }
		else if(ioChoice.compare("2")== 0){
			do{
                printUser(productsList);
				cout << "Please enter a barcode to decrease a product in the system(Enter 'q' back to the main manu)"<<endl;
				cin >> barCode;
                if(!isdigit(barCode[0])){
                    break;
                }
				indexOfList = barCodeMatch(barCode,productsList);

				if(indexOfList == -1){
					cout<<"Did not match the barcode in the system, do you want to add a new item?(Please enter 0 for add a new item, other key for continue scanning)"<<endl;
					cin >> didNotMatch;
					if(didNotMatch.compare("0") == 0){
						break;
					}
                    else {
                        continue;
                    }
				}
				else{
                    
						if(productsList[indexOfList].getCount() <= 0){
							cout<<"You do not have any products left in your stock"<<endl;
                            productsList[indexOfList].setCount(0);
							break;
						}
						productsList[indexOfList].decreaseCount();
					}
			}while(didNotMatch.compare("0") != 0);
		}
		cout << "Please choice the floowing options" << endl;
		cout << "Enter 1 for input products" << endl;
		cout << "Enter 2 for output products" << endl;
    	cout << "Enter any other keys to exist the program" << endl;
		cin >> ioChoice;
    }
	cout<<"Write the products infomation out to test.txt"<<endl;
	writeProducts("test.txt", productsList);
    
    cout<<"Do you want to write the profits to profits.txt? (yes or no)"<<endl;
    cin>>ioChoice;
    transform(ioChoice.begin(), ioChoice.end(), ioChoice.begin(), ::tolower);
    
    do{
        if(ioChoice.compare("yes") == 0){
            writeOtherData("Profits.txt", productsList);
        }
        else if(ioChoice.compare("no") == 0){
            cout << "No data writing into profits.txt"<<endl;
        }
        else{
            cout << "Please enter yes for write the profits to text file, otherwise enter no (enter any other keys to end program)"<<endl;
            cin>>ioChoice;
            transform(ioChoice.begin(), ioChoice.end(), ioChoice.begin(), ::tolower); 
        }
    }while(ioChoice.compare("yes") != 0 && ioChoice.compare("no") != 0 );
    
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
    int saleCounts;
    vector<User> listOfProducts;
    inFile>>numUsers;
    cout<<numUsers<<endl;
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
            
            inFile>>saleCounts;

            
            listOfProducts.push_back(User(productID,bCode,productName,productPrice,salesPrice,productCount,saleCounts));
            hardCount++;
        }
        
       
        //EOF check
    }while(!inFile.fail());
    inFile.close();
    return listOfProducts;
}
void writeProducts(const char* filename, vector<User> v){
	ofstream outFile(filename);
    outFile << (signed)v.size() <<endl;
    for(int i = 0 ; i < (signed)v.size(); i ++){
        
        outFile << v[i].getID() << " " << setw(14) << left << v[i].getBCODE() << setw(20) << left << v[i].getName()
                << setw(5) << left << v[i].getPrice() << setw(5) << left << v[i].getSale() << setw(5) << left << v[i].getCount()<< setw(5) << left << v[i].getSaleCounts() << endl;
    }
    
    outFile.close();
}
void writeOtherData(const char* filename, vector<User> v){
    ofstream outFile(filename);
    double totalProfits = getProfitsForTotalProducts (v);
    double totalPersentage = getPersentageForTotalProducts (v);
    
    for(int i = 0 ; i < (signed)v.size(); i ++){
        outFile << v[i].getID() << " " << setw(14) << left << v[i].getBCODE() << setw(20) << left << v[i].getName()
                << setw(5) << left << v[i].getPrice() << setw(5) << left << v[i].getSale() << setw(5) << left << v[i].getCount()
                << setw(8) << left << v[i].getProfits() << setw(8) << left << v[i].getPersentage() << endl;
    }
    outFile << "Total Profits: " <<totalProfits<<endl;
    outFile << "Total Persentage: " <<totalPersentage<<endl;
}
void printUser(vector<User> v){
    for(int i = 0 ; i < (signed)v.size();i++){
        cout<<"ID: "<<v[i].getID()<<" BarCode: "<<v[i].getBCODE()<<" Name: "<<v[i].getName()<<" Price: "<<v[i].getPrice()<<" Sale: " <<v[i].getSale()<<" Count: "<<v[i].getCount()
        <<" Profits: "<<v[i].getProfits()<<" Persentage: "<<v[i].getPersentage()<<endl;
    }
}
//return index found -1 not found.
int barCodeMatch(string b, vector<User> v){

    for(int i = 0 ; i < (signed)v.size();i++){
        
        
        
        if(b.compare(v[i].getBCODE())==0){

            return i;
        }
        
    }
    return -1;
}

double getProfitsForTotalProducts (vector<User> v){
    double sum = 0.0;
    for(int i = 0 ; i < (signed)v.size() ; i++){
        v[i].setProfits(v[i].calSaleProfits());
        sum += v[i].calSaleProfits();
        cout<<"1"<<endl;
        printUser(v);
    }
    return sum;
}

double getPersentageForTotalProducts (vector<User> v){
    double persen = 0.0;
    
    for(int i = 0 ; i < (signed)v.size() ; i++){
        v[i].setPersentage(v[i].calSaleProfitsPersentage());
        cout<<"2"<<endl;
        printUser(v);
    }
    persen = getProfitsForTotalProducts (v) * totalCount(v) /  totalPrice(v) * 100;
    return persen;
}

//Helper Functions
int totalCount (vector<User> v){
    int sumCount = 0;
    for(int i = 0 ; i < (signed)v.size() ; i++){
        
        sumCount += v[i].getCount();
    }
    return sumCount;
}
double totalPrice (vector<User> v){
    double totalP = 0.0;
    for(int i = 0 ; i < (signed)v.size() ; i++){
        totalP += v[i].getPrice();
    }
    return totalP;
}
string replaceWhiteSpace (string text){
    for(int i = 0; i < (signed)text.length(); i++)
    {
        if( isspace(text[i]) )
           text[i] = '_';
    }
    return text;
}
