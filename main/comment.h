#ifndef __MMZ_17__CM
#define __MMZ_17__CM


#include <string>
#include "Exceptions.h"

using namespace std;


class comment{

public:	
	comment(string _cmer,string _cm) : cmer(_cmer) , cm(_cm) {}
	string get_cmer() { return cmer; }
	string get_cm() { return cm; }
	friend ostream& operator<<(ostream& out,const comment& _cm)
	{out<<_cm.cmer<<endl<<_cm.cm<<endl; return out; }

private:
	string cmer;
	string cm;

};


#endif
