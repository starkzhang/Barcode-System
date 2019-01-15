
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#ifndef USER_H
#define USER_H
using namespace std;
class User {
 public:
    //Constructors
    User(int ID, string BCODE, string NAME, double PRICE, double SALE, int COUNT);
//    User();
    //Deconstructor
    //~User();
    //GET FUNCTIONS
    int getID();
    string getBCODE();
    string getName();
    double getPrice();
    double getSale();
    int getCount();
    
    //MODIFIED FUNCTIONS
    void increaseCount();
    void decreaseCount();
    void setCount(int num);
    double calSaleProfits();
 private:
    
    int id;
    string bcode;
    string name;
    double price;
    double sale;
    int count;
	int saleCounts;
};


#endif
