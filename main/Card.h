#ifndef __CARD__MMZ17
#define __CARD__MMZ17



#include <vector>
#include <string>
#include <algorithm>
#include "Date.h"
#include "comment.h"
#include <iostream>
#include "Exceptions.h"


using namespace std;



class Card{
	public:

	//constructor
	Card(string _name) ;
	Card(string _name,int _id,string des,vector <string> tmp_mem,int d,int m,int y,vector <comment *> cms) ;
	~Card();


	void add_user(string _user);
	void del_user(string _user);
	void edit_description(string new_description);
	void rename(string new_name);


	void edit_date(string date);
	void add_comment(string com,string comer);
	string show();
	bool have_all(vector<string> _users);

	//getters
	string get_name() { return name; }
	int get_id() { return id; }
	string get_description() { return description; }

	friend ostream& operator<<(ostream& out,const Card& _card);

	private:

	string name;
	int id;
	string description;
	vector <string> members;
	Date due_date;
	vector <comment *> comments;


};



#endif
