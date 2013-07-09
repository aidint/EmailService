#ifndef __MMZ_17__BOARD
#define __MMZ_17__BOARD

#include <vector>
#include "List.h"
#include <string>
#include <algorithm>
//#include "User.h"
#include "Exceptions.h"


using namespace std;




class Board{
public:
	//constructor
	Board(string _name,string manager) ;
	Board(string _name,string manager,vector<string> _members,int _id,vector <List *> lists);
	~Board();



	//not done
	string filter(vector<string> _users);

	void move_card(int card_id,int list_id);
	void commenting(string _user_name,int car_id,string cm);
	void assign(int card_id,string _user);
	void remove_user_from_card(int card_id,string _user);
	void add_list(string name);
	void remove_list(int list_id);
	void add_card(string _name,int list_id);
	void remove_card(int car_id);
	string show_lists();
	string show_cards(int list_id);
	string show_card(int card_id);
	void rename_card(int card_id,string card_name);
	void edit_card_des(int card_id,string card_des);
	void edit_card_date(int card_id,string card_date);
	
	void add_user(string name);
	void remove_user(string name);

	//methods
	bool is_member(string x);
	bool have_list(int list_id);
	bool have_card(int card_id);

	friend ostream& operator<<(ostream& out,const Board& _board);

	//getters
	string get_name() { return name; }
	int get_id() { return id; }
	string get_manager() { return board_manager; }
	

private:
	string name;
	int id;
	string board_manager;	
	vector <string> members;
	vector <List *> board_lists;
	


};


#endif
