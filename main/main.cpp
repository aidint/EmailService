#include "System.h"


int Board_ids;
int List_ids;
int Card_ids;


vector <user*> users;
vector <string> user_names;




int main(int argc, char *argv[])
{


  reading_from_database();




  //tamame chiz haye mojud ro tuye file hashun zakhire konim baz
  //inja ba hamun formate tozih dade shode tamame etefaqate oftade ro mirizim tuye databasemun.


  process(argc,argv);

  //  cerr<<"I am here"<<endl;

  writing_to_database();


  return 0;
}
