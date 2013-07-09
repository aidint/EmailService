#ifndef __MMZ_17__LIST
#define __MMZ_17__LIST

#include <vector>
#include <string>
#include "Card.h"
#include "Exceptions.h"

class List{
public:
	//constructor
	List(string _name);
	List(string _name,int _id,vector <Card *> cards);
	~List();
	void remove_user_from_card(int card_id,string _user);
	void assign(int card_id,string _user);
	void edit_card_date(int card_id,string card_date);
	void edit_card_des(int card_id,string card_des);
	void rename_card(int card_id,string card_name);
	bool have_card(int card_id);
	void commenting(string _user_name,int card_id,string cm);
	string show_cards();
	string show_card(int card_id);
	void add_card(string name);
	void remove_card(int card_id);
	void pop(int card_id);
	void push(Card* ptoc);
	string filter(vector<string> _users);
	//getters
	string get_name() { return name; }
	int get_id() { return id; }
	Card* get_p_card(int card_id);

	friend ostream& operator<<(ostream& out,const List& _list);

private:
	string name;
	int id;
	vector <Card *> list_cards;



};


#endif
