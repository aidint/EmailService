#include "List.h"

ostream& operator<<(ostream& out,const List& _list)
{
  out<<_list.name<<endl<<_list.id<<endl<<_list.list_cards.size()<<endl;
  for(int i=0;i<_list.list_cards.size();i++)
    {
      out<<*(_list.list_cards[i]);
    }
  return out;
}

void List::add_card(string name)
{
  Card *p;
  p=new Card(name);
  list_cards.push_back(p);
}



string List::show_cards()
{
  string x;
  for(int i=0;i<list_cards.size();i++)
    {
      x+=list_cards[i]->get_id()+'0';
      x+="\t";
      x+=list_cards[i]->get_name();
      x+='\n';
    }
  return x;
}

string List::show_card(int card_id)
{
  string x;
  for(int i=0;i<list_cards.size();i++)
    {
      if(list_cards[i]->get_id()==card_id)
	x+=list_cards[i]->show();
    }
  return x;
}



List::~List()
{
  for(int i=0;i<list_cards.size();i++)
    delete list_cards[i];
}


List::List(string _name)
{
extern int List_ids;
  name=_name;
  id=List_ids++;
}


List::List(string _name,int _id,vector <Card *> cards)
{
  name=_name;
  id=_id;
  list_cards=cards;
}



void List::remove_card(int card_id)
{
  for(int i=0;i<list_cards.size();i++)
    {
      if(list_cards[i]->get_id()==card_id)
	{
	  Card* tmp_card=list_cards[i];
	  list_cards[i]=list_cards[list_cards.size()-1];
	  list_cards[list_cards.size()-1]=tmp_card;
	  delete tmp_card;
	  list_cards.pop_back();
	  return ;
	}
    }
  throw Bad_card_Existance();
  //  cout<<"This card was not in this list"<<endl;
}


bool List::have_card(int card_id)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      return 1;
  return 0;
}

void List::commenting(string _user_name,int card_id,string cm)
{
  for(int i=0;i<list_cards.size();i++)
    {
      if(list_cards[i]->get_id()==card_id)
	{
	  list_cards[i]->add_comment(cm,_user_name);
	  return ;
	}
    }
}


void List::pop(int card_id)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      {
	list_cards[i]=list_cards[list_cards.size()-1];
	list_cards.pop_back();
      }
}


void List::push(Card* ptoc)
{
  list_cards.push_back(ptoc);
}


Card* List::get_p_card(int card_id)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      return list_cards[i];
}



void List::rename_card(int card_id,string card_name)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      {
	list_cards[i]->rename(card_name);
	return ;
      }
}

void List::edit_card_des(int card_id,string card_des)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      {
	list_cards[i]->edit_description(card_des);
	return ;
      }
}


void List::edit_card_date(int card_id,string card_date)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      {
	list_cards[i]->edit_date(card_date);
	return ;
      }
}



void List::assign(int card_id,string _user)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      {
	list_cards[i]->add_user(_user);
	return ;
      }
}



void List::remove_user_from_card(int card_id,string _user)
{
  for(int i=0;i<list_cards.size();i++)
    if(list_cards[i]->get_id()==card_id)
      {
	list_cards[i]->del_user(_user);
	return ;
      }
}


string inttos(int number)
{
  string x;
  while(number>0)
    {
      x+=(number%10)+'0';
      number/=10;
    }
  string y=x;
  for(int i=0;i<y.size();i++)
    x[i]=y[y.size()-i-1];
  return x;
}


string  List::filter(vector<string> _users)
{
  string x;
  for(int i=0;i<list_cards.size();i++)
    {
      if(list_cards[i]->have_all(_users))
	{
	  int tmp=list_cards[i]->get_id();
	  x+=inttos(tmp);
	  x+='\t';
	  x+=list_cards[i]->get_name();
	  x+='\n';
	}
    }
  return x;
}
