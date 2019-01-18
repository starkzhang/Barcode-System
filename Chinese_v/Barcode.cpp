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
int totalSold (vector<User> v);
double getProfitsForTotalProducts (vector<User> v);
double getPersentageForTotalProducts (vector<User> v, double tProducts);
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
    string barCodeIdentify;
    int pCount = 0;
    double pProfits = 0.0;
    double pPersentage = 0.0;
    int pID = -1;
    string didNotMatch;
    int indexOfList;
    int soldItems;
	vector<string> barVector;
	vector<User> productsList = readProducts("test.txt");
    if(productsList.empty()){
        pID = 0;
    }
    else{
        pID = productsList.size();
    }
	//MAIN MANUE
    
	cout << "欢迎使用本软件" << endl;
	cout << "入库：请输入 1 " << endl;
	cout << "出库：请输入 2" << endl;
    cout << "输入其他任意键结束程序" << endl;
	cin >> ioChoice;
    while(ioChoice.compare("1")== 0 || ioChoice.compare("2")== 0){
        if (ioChoice.compare("1")== 0) {
            barCodeIdentify.clear();
            
            cout << "入库新产品：请输入 1 " << endl;
            cout << "增加现有产品库存： 请输入 2 "<<endl;
            cout << "输入其他任意键结束程序"<<endl;
            cin>>newChoice;
            if(newChoice.compare("-1") == 0){
                break;
            }
            if(newChoice.compare("1")==0){
                do{
                    cout << "~请开始添加新产品~" << endl;
                   //BarCode
                    cout << "请用扫码枪输入产品编号" << endl;
                    cin >> barCode;
                    
                    cout << "您扫入的编号为： " << barCode<<endl;
                    cout << "确认请输入 1,重新输入请输入 2.";
                    cin >> barCodeIdentify;
                    if(barCodeIdentify.compare("2") == 0){
                        cout << "请用扫码枪输入产品编号" << endl;
                        cin >> barCode;
                    }
                    while(barCodeIdentify.compare("1") != 0 && barCodeIdentify.compare("2") != 0){
                        cout << "输入错误\n"<<"确认条码编号请输入 1,重新输入请输入 2， 结束程序请输入 q"<<endl;
                        cin >> barCodeIdentify;
                        if(barCodeIdentify.compare("1") == 0){
                            break;
                        }
                        else if(barCodeIdentify.compare("2") == 0){
                            cin >> barCode;
                            break;
                        }
                        else if(barCodeIdentify.compare("q") == 0){
                            return 0;
                        }
                    }
                    //Product Name
                    cout << "请输入新产品名称" << endl;
                    cin.ignore(); 
                    getline(cin, productName);
                    
                    cout << "您扫入的新产品名称： " << productName<<endl;
                    cout << "确认请输入 1,重新输入请输入 2.";
                    cin >> barCodeIdentify;
                    if(barCodeIdentify.compare("2") == 0){
                        cout << "请输入新产品名称" << endl;
                        cin >> productName;
                    }
                    while(barCodeIdentify.compare("1") != 0 && barCodeIdentify.compare("2") != 0){
                        cout << "输入错误\n"<<"确认新产品名称请输入 1,重新输入请输入 2， 结束程序请输入 q"<<endl;
                        cin >> barCodeIdentify;
                        if(barCodeIdentify.compare("1") == 0){
                            break;
                        }
                        else if(barCodeIdentify.compare("2") == 0){
                            cin >> productName;
                            break;
                        }
                        else if(barCodeIdentify.compare("q") == 0){
                            return 0;
                        }
                    }
                    
                    replaceWhiteSpace(productName);
                    
                    //Price
                    cout << "请输入新产品成本价" << endl;
                    cin >> pPrice;
                    
                    //selling price
                    cout << "请输入新产品售价" << endl;
                    cin >> sPrice;
                    //counts
                    cout << "请输入新产品数量（输入 0 如果不知道）"<<endl;
                    cin >> pCount;
                    
                    pProfits = sPrice - pPrice;
                    pPersentage = pProfits / pPrice * 100;
                    
                    productsList.push_back(User(pID, barCode, productName, pPrice,sPrice, pCount, 0, pProfits, pPersentage));
                    pID ++;
                    cout << "继续添加新产品请输入 1， 增加现有产品数量请输入 2， 返回主菜单请输入 q" << endl;
                    cin >> newChoice;
                    if(newChoice.compare("q")==0)
                        break;
                    if(newChoice.compare("1")!=0 && newChoice.compare("2")!=0){
                    	
                    	do{
                    		cout<<"输入错误！"<<endl;
                    		cout<<"继续添加新产品请输入 1， 增加现有产品数量请输入 2， 返回主菜单请输入 q"<<endl;
                    		cin >> newChoice;
                    	}while(newChoice.compare("1")!=0 && newChoice.compare("2")!=0 && newChoice.compare("q")!=0);
                    }
                }while(newChoice.compare("1")==0);

            }

            if(newChoice.compare("2")==0){
				do{
					cout << "请用扫码枪输入产品编号" << endl;
                    cin >> barCode;
                    
                    cout << "您扫入的编号为： " << barCode<<endl;
                    cout << "确认请输入 1,重新输入请输入 2.";
                    cin >> barCodeIdentify;
                    if(barCodeIdentify.compare("2") == 0){
                        cout << "请用扫码枪输入产品编号" << endl;
                        cin >> barCode;
                    }
                    while(barCodeIdentify.compare("1") != 0 && barCodeIdentify.compare("2") != 0){
                        cout << "输入错误\n"<<"确认条码编号请输入 1,重新输入请输入 2， 结束程序请输入 q"<<endl;
                        cin >> barCodeIdentify;
                        if(barCodeIdentify.compare("1") == 0){
                            break;
                        }
                        else if(barCodeIdentify.compare("2") == 0){
                            cin >> barCode;
                            break;
                        }
                        else if(barCodeIdentify.compare("q") == 0){
                            return 0;
                        }
                    }
                    
                    if(!isdigit(barCode[0])){
                        break;
                    }
                    
                    
					indexOfList = barCodeMatch(barCode,productsList);
					if(indexOfList==-1){
						cout<<"系统中没有匹配的产品， 结束程序请输入0， 继续输入请输入任意键 "<<endl;
						cin >> didNotMatch;
						if(didNotMatch.compare("0") == 0){
							break;
						}
					}
					else{
						productsList[indexOfList].increaseCount();
					}
                    cout<<"结束程序请输入0， 继续输入请输入任意键 "<<endl;
                    cin >> didNotMatch;
				}while(didNotMatch.compare("0") != 0);
            }
            cout<<"---现有产品数据---\n"<<endl;
            printUser(productsList);
            cout<<endl;
        }
		else if(ioChoice.compare("2")== 0){
			do{
                cout<<"---现有产品数据---\n"<<endl;
                printUser(productsList);
                cout<<endl;
                cout << "~请开始录入出库产品~" << endl;
                
                
				cout << "请用扫码枪输入产品编号" << endl;
                    cin >> barCode;
                    
                    cout << "您扫入的编号为： " << barCode<<endl;
                    cout << "确认请输入 1,重新输入请输入 2.";
                    cin >> barCodeIdentify;
                    if(barCodeIdentify.compare("2") == 0){
                        cout << "请用扫码枪输入产品编号" << endl;
                        cin >> barCode;
                    }
                    while(barCodeIdentify.compare("1") != 0 && barCodeIdentify.compare("2") != 0){
                        cout << "输入错误\n"<<"确认条码编号请输入 1,重新输入请输入 2， 结束程序请输入 q"<<endl;
                        cin >> barCodeIdentify;
                        if(barCodeIdentify.compare("1") == 0){
                            break;
                        }
                        else if(barCodeIdentify.compare("2") == 0){
                            cin >> barCode;
                            break;
                        }
                        else if(barCodeIdentify.compare("q") == 0){
                            return 0;
                        }
                    }
                    
                if(!isdigit(barCode[0])){
                    break;
                }
				indexOfList = barCodeMatch(barCode,productsList);

				if(indexOfList == -1){
					cout<<"系统中没有匹配的产品， 结束程序请输入0， 继续输入请输入任意键"<<endl;
					cin >> didNotMatch;
					if(didNotMatch.compare("0") == 0){
						break;
					}
                    else {
                        continue;
                    }
				}
				else{
                        soldItems = 1;
						if(productsList[indexOfList].getCount() <= 0){  
							
                            cout<<productsList[indexOfList].getName()<<"： 数量： "<<
                            productsList[indexOfList].getCount()<<"\n库存已没有产品 "<<endl;
                            productsList[indexOfList].setCount(0);
							break;
						}
                        cout << "如知道出库数量请输入，单件出库请输入 -1 " <<endl;
                        
                        cin >> soldItems;
                        if(soldItems == -1)
                            soldItems = 1;
                        for(int k = 0; k < soldItems; k ++){
                            productsList[indexOfList].decreaseCount();
                        }
					}
			}while(didNotMatch.compare("0") != 0);
		}
		cout << "请选择下列输入： " << endl;
        cout << "入库：请输入 1 " << endl;
        cout << "出库：请输入 2" << endl;
        cout << "输入其他任意键结束程序" << endl;
		cin >> ioChoice;
    }
	
	writeProducts("test.txt", productsList);
    
    cout<<"写入现有数据到 profits.txt? (输入yes 或 no)"<<endl;
    cout<<"!!输入no,您的数据将不会得到保存!!"<<endl;
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
    
    cout<<"谢谢使用本软件"<<endl;
    
    cout<<"任何疑问请致电张先生： 9493971862， 微信：stark_zhang"<<endl;
    cout<<"再见"<<endl;
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
    double profits;
    double persentage;
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
            
            inFile>>profits;
            inFile>>persentage;

            
            listOfProducts.push_back(User(productID,bCode,productName,productPrice,salesPrice,productCount,saleCounts,profits,persentage));
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
                << setw(5) << left << v[i].getPrice() << setw(5) << left << v[i].getSale() << setw(5) << left << v[i].getCount()
                << setw(5) << left << v[i].getSaleCounts() << setw(5) << left<<v[i].getProfits()<< setw(7) << left << v[i].getPersentage()<<endl;
    }
    
    outFile.close();
}
void writeOtherData(const char* filename, vector<User> v){
    ofstream outFile(filename);
    double totalProfits = getProfitsForTotalProducts (v);
    double totalPersentage = getPersentageForTotalProducts (v,totalProfits);
    
    for(int i = 0 ; i < (signed)v.size(); i ++){
        outFile <<"ID: "<< v[i].getID() << " "  <<"条码号: "<< setw(20) << left << v[i].getBCODE() << " 产品名称: " << setw(22) << left << v[i].getName()
                << " 成本价: "<< setw(13) << left << v[i].getPrice()  <<" 售价: " << setw(13) << left<< v[i].getSale()  <<" 仓储数量: " << setw(8) << left << v[i].getCount()
                 <<" 售出数量: "<< setw(13) << left << v[i].getSaleCounts() <<" 单品利润: " << setw(13) << left<< v[i].getProfits()  <<" 单品利润率: "<< v[i].getPersentage() <<"%"<< endl;
    }
    outFile << "Total Profits: " <<totalProfits<<endl;
    //outFile << "Total Persentage: " <<totalPersentage<<"%"<<endl;
}
void printUser(vector<User> v){
    for(int i = 0 ; i < (signed)v.size();i++){
        cout<<"ID: "<< v[i].getID() << " "  <<"条码号: "<< setw(20) << left << v[i].getBCODE() << " 产品名称: " << setw(22) << left << v[i].getName()
                << " 成本价: "<< setw(13) << left << v[i].getPrice()  <<" 售价: " << setw(13) << left<< v[i].getSale()  <<" 仓储数量: " << setw(8) << left << v[i].getCount()
                 <<" 售出数量: "<< setw(13) << left << v[i].getSaleCounts() <<" 单品利润: " << setw(13) << left<< v[i].getProfits()  <<" 单品利润率: "<< v[i].getPersentage() <<"%"<< endl;
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
       v[i].calSaleProfits();
        sum += v[i].calSaleProfits();
    }
    return sum;
}

double getPersentageForTotalProducts (vector<User> v, double tProducts){
    double persen = 0.0;
    
    for(int i = 0 ; i < (signed)v.size() ; i++){
        v[i].calSaleProfitsPersentage();
    }
    persen = tProducts * totalSold(v) /  totalPrice(v) * 100;
    return persen;
}

//Helper Functions
int totalSold (vector<User> v){
    int sumCount = 0;
    for(int i = 0 ; i < (signed)v.size() ; i++){
        
        sumCount += v[i].getSaleCounts();
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

