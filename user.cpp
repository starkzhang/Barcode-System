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
    return sale;
}

//MODIFIED GUNCTIONS
void User::increaseCount(){
    count++;
}
void User::decreaseCount(){
    count--;
	saleCounts++;
}
void User::setCount(int num){
    count = num;
}
double User::calSaleProfits(){
	return (sale - price) * saleCounts;
}