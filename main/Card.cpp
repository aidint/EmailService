#include "Card.h"

ostream& operator<<(ostream& out,const Card& _card)
{
  out<<_card.name<<endl
     <<_card.id<<endl
     <<_card.due_date;
  out<<_card.members.size()<<endl;
  for(int i=0;i<_card.members.size();i++)
    {
      out<<_card.members[i]<<endl;
    }
  out<<_card.description<<endl;
  out<<_card.comments.size()<<endl;
  for(int i=0;i<_card.comments.size();i++)
    {
      out<<*(_card.comments[i]);
    }
  return out;
}

void Card::add_user(string _user)
{
  for(int i=0;i<members.size();i++)
    if(members[i]==_user)
      {
	throw Bad_user_Existance();
	//cout<<"This user has already assigned to this card."<<endl;
	return ;
      }
  members.push_back(_user);
}


void Card::edit_description(string new_description)
{
  description=new_description;
}


void Card::rename(string new_name)
{
  name=new_name;
}


void Card::del_user(string _user)
{
  for(int i=0;i<members.size();i++)
    if(members[i]==_user)
      {
	swap(members[i],members[members.size()-1]);
	members.pop_back();
	return ;
      }
  throw Bad_user_Existance();
  //  cout<<"This user did not assigned to this card."<<endl;
}


void Card::edit_date(string new_date)
{
  due_date.edit(new_date);
}


void Card::add_comment(string com,string comer)
{
  comment *p;
  p=new comment(comer,com);
  comments.push_back(p);
}


string Card::show()
{
  string x;
  x+=name;
  x+='\n';
  x+=description;
  x+='\n';
  x+="members are :";
  x+='\n';
  //cout<<name<<endl
  //  <<description<<endl
  //  <<"members are :"<<endl;
  for(int i=0;i<members.size();i++)
    {
      x+=members[i];
      x+='\t';
    }
  x+='\n';
  x+="due date is: ";
  x+=due_date.print();
  x+='\n';
  for(int i=0;i<comments.size();i++)
    {
      x+=comments[i]->get_cmer();
      x+=" : ";
      x+=comments[i]->get_cm();
      x+='\n';
    }
  return x;
}

Card::Card(string _name) : due_date()
{
  extern int Card_ids;
  name=_name;
  id=Card_ids++;
  description="Nothing";
}

Card::~Card()
{
  for(int i=0;i<comments.size();i++)
    delete comments[i];
}

Card::Card(string _name,int _id,string des,vector <string> tmp_mem,int d,int m,int y,vector <comment *> cms) : due_date(d,m,y)
{
  name=_name;
  id=_id;
  description=des;
  members=tmp_mem;
  comments=cms;
}




bool Card::have_all(vector <string> _users)
{
  for(int i=0;i<_users.size();i++)
     if((find(members.begin(),members.end(),_users[i]))==(members.end()))
      return 0;
  return 1;
}
