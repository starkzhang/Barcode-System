
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
    User(int ID, string BCODE, string NAME, double PRICE, double SALE, int COUNT, int SALECOUNTS, double PROFITS, double PERSENTAGE);
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
    int getSaleCounts();
    double getProfits();
    double getPersentage();
    
    //MODIFIED FUNCTIONS
    void increaseCount();
    void decreaseCount();
    void setCount(int num);
    void setProfits(double p);
    void setPersentage(double p);
    double calSaleProfits();
    double calSaleProfitsPersentage();
 private:
    
    int id;
    string bcode;
    string name;
    double price;
    double sale;
    int count;
	int saleCounts;
    double profits;
    double persentage;
};


#endif
