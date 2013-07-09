#ifndef __MMZ17__DATE
#define __MMZ17__DATE

#include <iostream>
#include <string>
#include "Exceptions.h"


using namespace std;




class Date{
public:
	Date() : day(1) , month(1) , year(1) {}
	Date(int d,int m,int y) : day(d) , month(m) , year(y) {}
	void edit(int d,int m,int y);
	void edit(string new_date);



	string print();
	friend ostream& operator<<(ostream& out,const Date& _d) {out<<_d.day<<" "<<_d.month<<" "<<_d.year<<endl; return out; }

private:
	int day;
	int month;
	int year;
};


#endif
