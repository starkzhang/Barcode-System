#include "user.h"

//Constructor
User::User(int ID, string BCODE, string NAME, double PRICE, double SALE, int COUNT)
{
    id = ID;
    bcode = BCODE;
    name = NAME;
    price = PRICE;
    sale = SALE;
    count = COUNT;
	saleCounts = 0;
    profits = 0.0;
    persentage = 0.0;
}

//GET FUNCTIONS
// User::~User()
// {
// }
int User::getID(){
    return id;
}
string User::getBCODE(){
    return bcode;
}
string User::getName(){
    return name;
}
double User::getPrice(){
    return price;
}
double User::getSale(){
    return sale;
}
int User::getCount(){
    return count;
}
double User::getProfits(){
    return profits;
}

double User::getPersentage(){
    return persentage;
}

//MODIFIED GUNCTIONS
void User::increaseCount(){
    count++;
}
void User::decreaseCount(){
    count--;
    cout<<count<<endl;
	saleCounts++;
}
void User::setCount(int num){
    count = num;
}
void User::setProfits(double p){
    profits = p;
}
void User::setPersentage(double p){
    persentage = p;
}
double User::calSaleProfits(){
	return (sale - price) * saleCounts;
}
double User::calSaleProfitsPersentage(){
    return ((sale - price) * saleCounts) / price * 100;
}