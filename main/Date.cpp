#include "Date.h"


int strtoi(string x)
{
  int sol=0;
  for(int i=0;i<x.size();i++)
    {
      sol*=10;
      sol+=x[i]-'0';
    }
  return sol;
}

bool is_leap_year(int y) {
  int r = y % 33;
  return r==1 || r==5 || r==9 || r==13 || r==17 || r==22 || r==26 || r==30;
}

int days_of_month(int m, int y) {
  if (m < 7)
    return 31;
  else if (m < 12)
    return 30;
  else if (m == 12)
    return is_leap_year(y) ? 30 : 29;
}


void Date::edit(int d,int m,int y)
{
  if (y < 0 || m < 1 || m > 12 || d < 1 || d > days_of_month(m, y)) {
    throw Bad_Date_Exception();
  }
  day = d;
  month = m;
  year = y;
}


void Date::edit(string new_date)
{
  int day=0,year=0,month=0;
  if(new_date.size()!=10)
    throw Bad_Date_Exception();
  for(int i=0;i<new_date.size();i++)
    {
      //cerr<<"here"<<endl;
      if((i==4 || i==7))
	{
	  if(new_date[i]!='-')	
	    throw Bad_Date_Exception();
	}
      else
	{
	  //cerr<<"haha"<<endl;
	  if(new_date[i]<'0' || new_date[i]>'9')
	    throw Bad_Date_Exception();
	}
    }
  year=strtoi(new_date.substr(0,4));
  month=strtoi(new_date.substr(5,2));
  day=strtoi(new_date.substr(8,2));
  
  //cerr<<"       "<<day<<" "<<month<<" "<<year<<endl;
  edit(day,month,year);


}



string Date::print()
{
  string x;
  x+=(day/10)+'0';
  x+=(day%10)+'0';
  x+='/';
  x+=(month/10)+'0';
  x+=(month%10)+'0';
  x+='/';
  x+=(year/1000)+'0';
  x+=(year%1000)/100 +'0';
  x+=(year%100)/10 + '0';
  x+=(year%10)+'0';
  return x;
}
