#include "Board.h"

ostream& operator<<(ostream& out,const Board& _board)
{
  out<<_board.name<<endl<<_board.id<<endl<<_board.board_manager<<endl;
  out<<_board.members.size()<<endl;
  for(int i=0;i<_board.members.size();i++)
    {
      out<<_board.members[i]<<endl;
    }
  out<<_board.board_lists.size()<<endl;
  for(int i=0;i<_board.board_lists.size();i++)
    {
      out<<*(_board.board_lists[i]);
    }
  return out;
}

bool Board::is_member(string x)
{
  return (find(members.begin(),members.end(),x)!=members.end());
}

bool Board::have_list(int list_id)
{
  for(int i=0;i<board_lists.size();i++)
    if(board_lists[i]->get_id()==list_id)
      return 1;
  return 0;
}

bool Board::have_card(int card_id)
{
  for(int i=0;i<board_lists.size();i++)
    if(board_lists[i]->have_card(card_id))
      return 1;
  return 0;
}

void Board::move_card(int card_id,int list_id)
{
  if(!have_card(card_id))
    {
      throw Bad_card_Existance();
      //      cout<<"This card does not exist int this board."<<endl;
      return ;
    }
  if(!have_list(list_id))
    {
      throw Bad_list_Existance();
      //cout<<"This List does not exist int this board."<<endl;
      return ;
    }
  Card* pc;
  for(int i=0;i<board_lists.size();i++)
    if(board_lists[i]->have_card(card_id))
      {
	pc=board_lists[i]->get_p_card(card_id);
	board_lists[i]->pop(card_id);
      }
  for(int i=0;i<board_lists.size();i++)
    if(board_lists[i]->get_id()==list_id)
      board_lists[i]->push(pc);
}


string Board::show_lists()
{
  string x;
  for(int i=0;i<board_lists.size();i++)
    {
      x+=board_lists[i]->get_id()+'0';
      x+="\t";
      x+=board_lists[i]->get_name();
      x+='\n';
    }
  if(board_lists.size()==0)
    {
      x+="There is not any lists in this board.\n";
    }
  return x;
}


Board::~Board()
{
  for(int i=0;i<board_lists.size();i++)
    delete board_lists[i];
}


void Board::add_list(string name)
{
  List* p;
  p=new List(name);
  board_lists.push_back(p);
}


Board::Board(string _name,string manager)
{
  extern int Board_ids;
  name=_name;
  board_manager=manager;
  members.push_back(manager);
  id=Board_ids++;
}


Board::Board(string _name,string manager,vector<string> _members,int _id,vector <List *> lists)
{
  name=_name;
  board_manager=manager;
  id=_id;
  members=_members;
  board_lists=lists;
}



void Board::add_user(string name)
{
  for(int i=0;i<members.size();i++)
    {
      if(members[i]==name)
	{
	  throw Bad_user_Existance();
	  //	  cout<<"This user already exist in this Board"<<endl;
	  return ;
	}
    }
  
  bool exist=0;
  extern vector <string> user_names;
  for(int i=0;i<user_names.size();i++)
    {
      if(user_names[i]==name)
	exist = 1;
    }

  if(exist)
    members.push_back(name);
  else
    throw Bad_user_Existance();
    //cout<<"This username doesn't exist"<<endl;
}



void Board::remove_user(string name)
{
  if(name==board_manager)
    throw Bad_Access();
  vector<string>::iterator it;
  it=find(members.begin(),members.end(),name);
  if(it==members.end())
    throw Bad_user_Existance();
  else
    members.erase(it);
}


void Board::remove_list(int list_id)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->get_id()==list_id)
	{
	  List* tmp=board_lists[i];
	  board_lists[i]=board_lists[board_lists.size()-1];
	  board_lists[board_lists.size()-1]=tmp;
	  delete tmp;
	  board_lists.pop_back();
	  return ;
	}
    }
  throw Bad_list_Existance();
  //cout<<"There wasn't this id number in this board"<<endl;
}



string Board::show_cards(int list_id)
{
  string x;
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->get_id()==list_id)
	{
	  x+=board_lists[i]->show_cards();
	  return x;
	}
    }
  throw Bad_list_Existance();
  //cout<<"There wasn't this id number in this board"<<endl;
}



void Board::commenting(string _user_name,int card_id,string cm)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->commenting(_user_name,card_id,cm);
	  return ;
	}
    }
  throw Bad_card_Existance();
  //cout<<"This card doesn't exist in this board."<<endl;
}



string Board::show_card(int card_id)
{
  string x;
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  x+=board_lists[i]->show_card(card_id);
	  return x;
	}
    }
  throw Bad_card_Existance();
  //cout<<"this card doesn'e exist in this board."<<endl;
}


void Board::add_card(string _name,int list_id)
{
  if(!have_list(list_id))
    {
      throw Bad_list_Existance();
      //      cout<<"This list id doesn't exist in this board."<<endl;
      return ;
    }
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->get_id()==list_id)
	{
	  board_lists[i]->add_card(_name);
	  return ;
	}
    }
}



void Board::remove_card(int card_id)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->remove_card(card_id);
	  return ;
	}
    }
  throw Bad_card_Existance();
  // cout<<"This card does not exist in this board."<<endl;
}




void Board::rename_card(int card_id,string card_name)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->rename_card(card_id,card_name);
	  return ;
	}
    }
  throw Bad_card_Existance();
  //cout<<"This card does not exist in this board."<<endl;
}





void Board::edit_card_des(int card_id,string card_des)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->edit_card_des(card_id,card_des);
	  return ;
	}
    }
  throw Bad_card_Existance();
  //  cout<<"This card does not exist in this board."<<endl;
}



void Board::edit_card_date(int card_id,string card_date)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->edit_card_date(card_id,card_date);
	  return ;
	}
    }
  throw Bad_card_Existance();
  //cout<<"This card does not exist in this board."<<endl;
}

void Board::assign(int card_id,string _user)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->assign(card_id,_user);
	  return ;
	}
    }
  throw Bad_card_Existance();
  //cout<<"This card does not exist in this board."<<endl;
}



void Board::remove_user_from_card(int card_id,string _user)
{
  for(int i=0;i<board_lists.size();i++)
    {
      if(board_lists[i]->have_card(card_id))
	{
	  board_lists[i]->remove_user_from_card(card_id,_user);
	  return ;
	}
    }
  throw Bad_card_Existance();
  //cout<<"This card does not exist in this board."<<endl;
}



string Board::filter(vector<string> _users)
{
  string x;
  for(int i=0;i<board_lists.size();i++)
    {
      x+=board_lists[i]->filter(_users);
    }
  return x;
}
