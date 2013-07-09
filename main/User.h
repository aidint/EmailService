#ifndef __USER__MMZ17
#define __USER__MMZ17


#include <vector>
#include <string>
#include "Board.h"
#include "Exceptions.h"

using namespace std;



class user{
	public:
	//constructor
	user(string _name,string _user,string _pass);
	user(string _name,string _user,string _pass,vector<Board *> b_vec);
	


	//getters
	string get_name() { return name; }
	string get_user_name() { return user_name; }
	string get_pass() { return pass; }
	


	//not done
	



	string show_card(int card_id);
	void add_list(string name);
	void remove_list(int list_id);
	void commenting(int card_id,string cm);
	string show_lists();
	string show_cards(int list_number);
	void del_user_from_board(string _user);
	void add_user_to_board(string _user);
	void create_board(string _name);
	void remove_board(int board_id);
	string show_boards();
	void enter_board(int board_id);
	Board* get_p_board(int board_id);
	string show_boards_member(string _user);

	void remove_card(int card_id);
	void add_card(string _name,int list_id);
	void move_card(int card_id,int list_id);

	void rename_card(int card_id,string card_name);
	void edit_card_des(int card_id,string card_des);
	void edit_card_date(int card_id,string card_date);

	void assign(int card_id,string _user);
	void remove_user_from_card(int card_id,string _user);
	string filter(vector<string> _users);


	friend ostream& operator<<(ostream& out,const user& _user);


	private:
	Board* current_board;
	vector <Board *> my_boards;
	string name;
	string pass;
	string user_name;

};



#endif
