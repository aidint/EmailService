//#include "comment.h"
#include "Date.h"
#include "User.h"
#include "List.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Card.h"
#include "Exceptions.h"


//for socket

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


using namespace std;





extern int Board_ids;
extern int List_ids;
extern int Card_ids;


extern vector <user*> users;
extern vector <string> user_names;
