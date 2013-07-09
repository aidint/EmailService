#include "User.h"

ostream& operator<<(ostream& out,const user& _user)
{
  out<<_user.name<<endl<<_user.user_name<<endl<<_user.pass<<endl;
  out<<_user.my_boards.size()<<endl;
  for(int i=0;i<_user.my_boards.size();i++)
    out<<*(_user.my_boards[i]);
  return out;
}

user::user(string _name,string _user,string _pass)
{
  name=_name;
  user_name=_user;
  pass=_pass;
  current_board=NULL;
}


user::user(string _name,string _user,string _pass,vector <Board *> b_vec)
{
  name=_name;
  user_name=_user;
  pass=_pass;
  current_board=NULL;
  my_boards=b_vec;
}



void user::enter_board(int board_id)
{
  extern vector<user *> users;
  for(int i=0;i<users.size();i++)
    {
      if((users[i]->get_p_board(board_id))!=NULL)
	{
	  if(users[i]->get_p_board(board_id)->is_member(user_name))
	    current_board=users[i]->get_p_board(board_id);
	  else
	    throw Bad_Access();
	    //cout<<"You are not member of this board."<<endl;
	  return ;
	}
    }
  throw Bad_board_Existance();
  //cout<<"This board doesn't exist"<<endl;
}


Board* user::get_p_board(int board_id)
{
  for(int i=0;i<my_boards.size();i++)
    {
      if(my_boards[i]->get_id()==board_id)
	{
	  return my_boards[i];
	}
    }
  return NULL;
} 



string user::show_boards()
{
  string x;
  extern vector<user *> users;
  for(int i=0;i<users.size();i++)
    x+=users[i]->show_boards_member(user_name);
  return x;
}


string user::show_boards_member(string _user)
{
  string x;
  for(int i=0;i<my_boards.size();i++)
    {
      if(my_boards[i]->is_member(_user))
	{
	  x+=my_boards[i]->get_id()+'0';
	  x+="\t";
	  x+=my_boards[i]->get_name();
	  x+="\t";
	  if(_user==user_name)
	    x+="Admin";
	  else
	    x+="member";
	  x+='\n';
	}
    }
  return x;
}


void user::create_board(string _name)
{
  Board* pb;
  pb=new Board(_name,user_name);
  my_boards.push_back(pb);
}


void user::remove_board(int board_id)
{
  if(current_board!= NULL && current_board->get_id()==board_id)
    {
      delete current_board;
      current_board=NULL;
      return ;
    }
  for(int i=0;i<my_boards.size();i++)
    {
      if(my_boards[i]->get_id()==board_id)
	{
	  Board* tmp_board;
	  tmp_board=my_boards[i];
	  my_boards[i]=my_boards[my_boards.size()-1];
	  delete tmp_board;
	  my_boards.pop_back();
	  return ;
	}
    }
  throw Bad_board_Existance();
  //cout<<"You do not have a board with this id"<<endl;
}


void user::add_user_to_board(string _user)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in any board"<<endl;
      return ;
    }
  if(current_board->get_manager()!=user_name)
    {
      throw Bad_Access();
      //cout<<"you are not the manager of this board"<<endl;
      return ;
    }
  current_board->add_user(_user);
}



void user::del_user_from_board(string _user)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in any board"<<endl;
      return ;
    }
  if(current_board->get_manager()!=user_name)
    {
      throw Bad_Access();
      //cout<<"you are not the manager of this board"<<endl;
      return ;
    }
  current_board->remove_user(_user);
}



void user::commenting(int card_id,string cm)
{
  current_board->commenting(user_name,card_id,cm);
}



string  user::show_lists()
{
  string x;
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      // return ;
    }
  x=current_board->show_lists();
  return x;
}



string user::show_cards(int list_number)
{
  string x;
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      //return ;
    }
  x=current_board->show_cards(list_number);
  return x;
}


void user::add_list(string name)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->add_list(name);
}



void user::remove_list(int list_id)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      // cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->remove_list(list_id);
}


string user::show_card(int card_id)
{
  string x;
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      // return ;
    }
  x=current_board->show_card(card_id);
  return x;
}



void user::remove_card(int card_id)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->remove_card(card_id);
}


void user::add_card(string _name,int list_id)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->add_card(_name,list_id);
}



void user::move_card(int card_id,int list_id)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      // cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->move_card(card_id,list_id);
}


void user::rename_card(int card_id,string card_name)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->rename_card(card_id,card_name);
}


void user::edit_card_des(int card_id,string card_des)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->edit_card_des(card_id,card_des);
}


void user::edit_card_date(int card_id,string card_date)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->edit_card_date(card_id,card_date);
}



void user::assign(int card_id,string _user)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->assign(card_id,_user);
}


void user::remove_user_from_card(int card_id,string _user)
{
  if(current_board==NULL)
    {
      throw Bad_Access();
      //cout<<"You are not in a board."<<endl;
      return ;
    }
  current_board->remove_user_from_card(card_id,_user);
}


string user::filter(vector<string> _users)
{
  string x;
  if(current_board==NULL)
    {
      throw Bad_Access();
      // cout<<"You are not in a board."<<endl;
      //return ;
    }
  x=current_board->filter(_users);
  return x;
}

