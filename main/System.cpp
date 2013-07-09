#include "System.h"

int stoint(string x)
{
  int n=0;
  for(int i=0;i<x.size();i++)
    {
      if(x[i]>'9' || x[i]<'0')
	return -1;
      n*=10;
      n+=x[i]-'0';
    }
  return n;
}



vector <string> parse(string x)
{
  string tmp;
  int flag=0;
  vector <string> myvec;
  while(flag<x.size())
    {
      while(x[flag]!=' ' && x[flag]!='\t' && x[flag]!='\n' && flag<x.size())
	{
	  tmp+=x[flag];
	  flag++;
	}
      myvec.push_back(tmp);
      tmp.resize(0);
      flag++;
    }
  return myvec;
}

string signup(user*& p,vector <string> myvec)
{
  // string y;
  // getline(cin,y);

  if(p!=NULL)
    return "You are signed in with another account.\n";
  string name;
  string user_name;
  string pass;
  pass=myvec.back();
  myvec.pop_back();
  user_name=myvec.back();
  myvec.pop_back();
  for(int i=1;i<myvec.size();i++)
    {
      name+=myvec[i];
      if(i!=myvec.size()) name+=' ';
    }
  user *up=new user(name,user_name,pass);
  users.push_back(up);
  user_names.push_back(user_name);
  return "Signing up completed.\n";
}


string signin(user*& p,vector <string> myvec)
{
  if(myvec.size()!=3)
    return "invalid input.\n";
  if(p!=NULL)
    return "You are signed in with another account.\n";
  string x,y;
  x=myvec[1];
  y=myvec[2];
  for(int i=0;i<users.size();i++)
    {
      if(users[i]->get_user_name()==x)
	{
	  if(users[i]->get_pass()==y)
	    {
	      p=users[i];
	      return "Signing in completed.\n";
	      //  return users[i];
	    }
	  else
	    {
	      p=NULL;
	      return "PASSWORD is wrong.\n";
	    }
	}
    }
  p=NULL;
  return "This user name doesn't exist.\n";
}

string show_boards(user* up)
{
  if(up==NULL)
    return "You are not signed in.\n";
  return up->show_boards()+"\n";
}

string enter_board(user* up,vector <string> myvec)
{
  if(up==NULL)
    return "You are not signed in.\n";
  if(myvec.size()!=2)
    return "Invalid input.\n";
  int number;
  //cin>>number;
  number=stoint(myvec[1]);
  try
    {
      up->enter_board(number);
      return "You have entered the board.\n";
    }
  catch(Bad_board_Existance ex)
    {
      return "this board does not exist.\n";
    }
  catch(Bad_Access ex2)
    {
      return "You are not a member of this board.\n";
    }
}

string add_user(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  string user_name=myvec[1];
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->add_user_to_board(user_name);
      return "Done.\n";
    }
  catch(Bad_user_Existance ex)
    {
      return "This user does not exist.\n";
    }
  catch(Bad_Access ex2)
    {
      return "You are not the manger or not in a board.\n";
    }
}



string remove_user_from_board(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input\n";
  string y;
  y=myvec[1];
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->del_user_from_board(y);
      return "Done.\n";
    }
  catch(Bad_user_Existance ex)
    {
      return "Wrong username.Try again.\n";
    }
  catch(Bad_Access ex2)
    {
      return "You are not the manger or not in a board.maybe you want to remove yourself.\n";
    }
}
string show_lists(user* up)
{
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      return up->show_lists();
    }
  catch(Bad_Access ex)
    {
      return "You are not in a board.\n";
    }
}


string show_cards(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  int list_number=stoint(myvec[1]);
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      return up->show_cards(list_number)+'\n';
    }
  catch(Bad_Access ex)
    {
      return "You are not in a board."+'\n';
    }
  catch(Bad_list_Existance ex2)
    {
      return "This list does not exist."+'\n';
    }
}



string show_card(user* up,vector<string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  int card_number=stoint(myvec[1]);
  if(up==NULL)
    return "You are not signed in."+'\n';
  try
    {
      return up->show_card(card_number)+'\n';
    }
  catch(Bad_Access ex)
    {
      return "You are not in a board."+'\n';
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist."+'\n';
    }
}

string create_board(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  string board_name=myvec[1];
  if(up==NULL)
    return "You are not signed in.\n";
  up->create_board(board_name);
  return "Done.\n";
}

string remove_board(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  int board_id=stoint(myvec[1]);
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->remove_board(board_id);
      return "Done.\n";
    }
  catch(Bad_board_Existance ex)
    {
      return "This board does not exist.\n";
    }
}

string add_list(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  string list_name=myvec[1];
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->add_list(list_name);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "You are not in a board.\n";
    }
}



string remove_list(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  int list_id=stoint(myvec[1]);
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->remove_list(list_id);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "You are not in a board.\n";
    }
  catch(Bad_list_Existance ex2)
    {
      return "This list does not exist.\n";
    }
}


string remove_card(user* up,vector <string> myvec)
{
  if(myvec.size()!=2)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->remove_card(card_id);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "You are not in a board.\n";
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist.\n";
    }
}


string add_card(user* up,vector<string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  string card_name=myvec[1];
  int list_id=stoint(myvec[2]);
  if(up==NULL)
      return "You are not signed in.\n";
  try
    {
      up->add_card(card_name,list_id);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "You are not  in a board.\n";
    }
  catch(Bad_list_Existance ex2)
    {
      return "This list does not exist.\n";
    }
}



string move_card(user* up,vector <string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  int list_id=stoint(myvec[2]);;
  if(up==NULL)
    return "You are not signed in.\n";
try
  {
    up->move_card(card_id,list_id);
    return "Done.\n";
  }
 catch(Bad_Access ex)
   {
     return "Tou are not in  aboard.\n";
   }
 catch(Bad_card_Existance ex2)
   {
     return "this card does not exist.\n";
   }
 catch(Bad_list_Existance ex3)
   {
     return "This list does not exist.\n";
   }
}







string rename_card(user* up,vector <string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  string card_name=myvec[2];
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->rename_card(card_id,card_name);
      return "Done.\n"; 
    }
  catch(Bad_Access ex)
    {
      return "you are not in  aboard.\n";
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist in this board.\n";
    }
}


string edit_card_des(user* up,vector<string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  string card_des=myvec[2];
  if(up==NULL)
    return "You are not signed in.\n";
  try
    {
      up->edit_card_des(card_id,card_des);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "you are not in  aboard.\n";
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist in this board.\n";
    }
}


string edit_card_date(user* up,vector <string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  string card_date=myvec[2];
  if(up==NULL)
    return "You are not signed in.\n";
  try{
    up->edit_card_date(card_id,card_date);
    return "Done.\n";
  }
 catch(Bad_Access ex)
    {
      return "you are not in  aboard.\n";
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist in this board.\n";
    }
  catch(Bad_Date_Exception ex3)
    {
      return "date is wrong\n";
    }
}


string assign(user* up,vector<string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  string username=myvec[2];
  if(!have_member(username))
    return "this user does not exist\n";
  if(up==NULL)
    return "You are not signed in.\n";
try
  {
    up->assign(card_id,username);
    return "Done.\n";
  }
 catch(Bad_Access ex)
   {
     return "you are not in  aboard.\n";
   }
 catch(Bad_card_Existance ex2)
   {
     return "This card does not exist in this board.\n";
   }
}




string commenting(user* up,vector <string> myvec)
{
  if(myvec.size()<3)
     return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  string cm;
  for(int i=2;i<myvec.size();i++)
    {
      cm+=myvec[i];
      if(i!=myvec.size())
	cm+=' ';
    }
  if(up==NULL)
      return "You are not signed in.\n";
  try
    {
      up->commenting(card_id,cm);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "you are not in  aboard.\n";
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist in this board.\n";
    }
}



string filter(user* up,vector<string> myvec)
{
  string names;
  //getline(cin,names);
  vector<string> user_names;
  for(int i=1;i<myvec.size();i++)
    user_names.push_back(myvec[i]);
  for(int i=0;i<user_names.size();i++)
    if(!have_member(user_names[i]))
      return "this user does not exist : "+user_names[i]+'\n';
  if(up==NULL)
      return "You are not signed in.\n";
  return up->filter(user_names)+'\n';
}

string remove_user_from_card(user* up,vector <string> myvec)
{
  if(myvec.size()!=3)
    return "Invalid input.\n";
  int card_id=stoint(myvec[1]);
  string username=myvec[2];
  if(!have_member(username))
    return "this user does not exist\n";
  if(up==NULL)
      return "You are not signed in.\n";
  try
    {
      up->remove_user_from_card(card_id,username);
      return "Done.\n";
    }
  catch(Bad_Access ex)
    {
      return "you are not in  aboard.\n";
    }
  catch(Bad_card_Existance ex2)
    {
      return "This card does not exist in this board.\n";
    }
}


string solve(string command,user*& cur_user)
{
  vector <string> commands;
  string x;

  string sol;
  commands=parse(command);
  x=commands[0];
  if(x=="exit" || x=="disconnect")
    return x;
  if(x=="signup")
    sol=signup(cur_user,commands);
  if(x=="signin")
    sol=signin(cur_user,commands);
  if(x=="signout" && commands.size()==1)
    {
      cur_user=NULL;
      return "signing out completed.\n";
    }
  if(x=="show_boards")
    sol=show_boards(cur_user);
  if(x=="enter_board")
    sol=enter_board(cur_user,commands);
  if(x=="add_user")
    sol=add_user(cur_user,commands);
  if(x=="remove_user_from_board")
    sol=remove_user_from_board(cur_user,commands);
  if(x=="show_lists" && commands.size()==1)
    sol=show_lists(cur_user);
  if(x=="show_cards")
    sol=show_cards(cur_user,commands);
  if(x=="show_card")
    sol=show_card(cur_user,commands);
  if(x=="create_board")
    sol=create_board(cur_user,commands);
  if(x=="remove_board")
    sol=remove_board(cur_user,commands);
  if(x=="add_list")
    sol=add_list(cur_user,commands);
  if(x=="remove_list")
    sol=remove_list(cur_user,commands);
  if(x=="add_card")
    sol=add_card(cur_user,commands);
  if(x=="remove_card")
    sol=remove_card(cur_user,commands);
  if(x=="move_card")
    sol=move_card(cur_user,commands);
  if(x=="rename_card")
    sol=rename_card(cur_user,commands);
  if(x=="edit_card_description")
    sol=edit_card_des(cur_user,commands);
  if(x=="edit_card_due_date")
    sol=edit_card_date(cur_user,commands);
  if(x=="assign_user")
    sol=assign(cur_user,commands);
  if(x=="remove_user")
    sol=remove_user_from_card(cur_user,commands);
  if(x=="comment")
    sol=commenting(cur_user,commands);
  if(x=="filter")
    sol=filter(cur_user,commands);
  if(sol.size()==0)
    sol="Invalid command.\n";
  return sol;
     
}




/**************************main function************************/


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

string chartos(char *sth)
{
  string x;
  int i=0;
  while(sth[i]!='\0')
    {
      x+=sth[i++];
    }
  return x;
}



bool tasavi(string x,string y)
{
  if(x.size()<y.size())
    return 0;
  for(int i=0;i<y.size();i++)
    if(x[i]!=y[i])
      return 0;
  return 1;
}


void process(int argc, char *argv[])
{


  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[1024];
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  cout<<"Binding....."<<endl;
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
	   sizeof(serv_addr)) < 0) 
    error("ERROR on binding");
  while(1)
    {
      bool exiting =0;
      cout<<"Listening......."<<endl;
      listen(sockfd,2);
      clilen = sizeof(cli_addr);
      newsockfd = accept(sockfd, 
			 (struct sockaddr *) &cli_addr, 
			 &clilen);
      if (newsockfd < 0) 
	error("ERROR on accept");
      cout<<"connected...."<<endl;
      
      user* cur_user=NULL;
      string command;
      while(1){
	// cerr<<"      command migiram"<<endl;
	bzero(buffer,1024);
	n = read(newsockfd,buffer,1023);
	if (n < 0) error("ERROR reading from socket");
	
	command=chartos(buffer);
	cout<<"Client command is :"<<endl<<command<<endl;
	//cerr<<command<<endl;
	if(tasavi(command,"exit"))
	  {
	    //	cerr<<"here"<<endl;
	    n = write(newsockfd,"exit",5);
	    exiting=1;
	    //cerr<<"na injam"<<endl;
	    if (n < 0) error("ERROR writing to socket");
	    break;
	  }
	if(tasavi(command,"disconnect"))
	  {
	    n = write(newsockfd,"disconnect",12);
	    if (n < 0) error("ERROR writing to socket");
	    break;
	  }
	string x=solve(command,cur_user);
	char outbuf[1024];
	bzero(outbuf,1024);
	for(int i=0;i<x.size();i++)
	  outbuf[i]=x[i];
	outbuf[x.size()]='\0';
	n = write(newsockfd,outbuf,x.size());
	if (n < 0) error("ERROR writing to socket");
      }
      //cerr<<"here"<<endl;     
      
      if(exiting)
	{
	  // cerr<<"moein"<<endl;
	  close(newsockfd);
	  close(sockfd);
	  break;
	}
      // cerr<<"inja"<<endl;
    }
 
}

















bool have_member(string name)
{
  extern vector <string> user_names;
  for(int i=0;i<user_names.size();i++)
    if(user_names[i]==name)
      return 1;
  return 0;
}







void writing_to_database()
{
  ofstream fout("database.in");
  int n;
  fout<<Board_ids<<endl
      <<List_ids<<endl
      <<Card_ids<<endl;
  fout<<users.size()<<endl;
  for(int i=0;i<users.size();i++)
    {
      fout<<*users[i];
    }
}

void reading_from_database()
{
  ifstream fin("database.in");
  int n;
  if(!(fin>>n))
    {
      Board_ids=1;
      List_ids=1;
      Card_ids=1;
      return ;
    }
  Board_ids=n;
  fin>>List_ids>>Card_ids;
  int number_of_users;
  fin>>number_of_users;
  for(int i=0;i<number_of_users;i++)
    {
      string name;
      string user_name;
      string pass;
      getline(fin,name);
      getline(fin,name);
      fin>>user_name>>pass;
      int number_of_boards;
      fin>>number_of_boards;
      vector <Board *> boards;
      for(int j=0;j<number_of_boards;j++)
	{
	  string name;
	  fin>>name;
	  int id;
	  fin>>id;
	  string manager;
	  fin>>manager;
	  vector <string> members;
	  int number_of_members;
	  fin>>number_of_members;
	  string member;
	  getline(fin,member);
	  for(int k=0;k<number_of_members;k++)
	    {
	      getline(fin,member);
	      members.push_back(member);
	    }
	  int number_of_lists;
	  fin>>number_of_lists;
	  vector<List *> lists;
	  for(int k=0;k<number_of_lists;k++)
	    {
	      string name;
	      fin>>name;
	      int id;
	      fin>>id;
	      int number_of_cards;
	      fin>>number_of_cards;
	      vector <Card *> cards;
	      for(int l=0;l<number_of_cards;l++)
		{
		  string name;
		  fin>>name;
		  int id;
		  fin>>id;
		  int day,month,year;
		  fin>>day>>month>>year;
		  int members_num;
		  fin>>members_num;
		  string mems;
		  vector<string> member;
		  getline(fin,mems);
		  for(int m=0;m<members_num;m++)
		    {
		      getline(fin,mems);
		      member.push_back(mems);
		    }
		  string des;
		  getline(fin,des);
		  vector <comment *> cms;
		  int cm_number;
		  fin>>cm_number;
		  for(int m=0;m<cm_number;m++)
		    {
		      string cmer;
		      fin>>cmer;
		      string cm;
		      getline(fin,cm);
		      getline(fin,cm);
		      comment* cmp=new comment(cmer,cm);
		      cms.push_back(cmp);
		    }
		  Card* cp=new Card(name,id,des,member,day,month,year,cms);
		  cards.push_back(cp);
		}
	      List* lp=new List(name,id,cards);
	      lists.push_back(lp);
	    }
	  Board *bp=new Board(name,manager,members,id,lists);
	  boards.push_back(bp);
	}
      user* up=new user(name,user_name,pass,boards);
      users.push_back(up);
      user_names.push_back(up->get_user_name());

    }
}


