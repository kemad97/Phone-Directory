#include <iostream>
#include <fstream>
#include "phonedirectory.h"
#include "ui.h"
using namespace std;

/*
  Test1: search_by_name(name)
  Test2: search_by_phone_num(phone_num)
  Test3: delete (given_name)
  Test4: remove_all()
  Test5: search_by_name(name_prefix), 
         search_by_phone_num(phone_num_prefix)
*/

/*
 const string insert_help = "i[nsert] <name>,<number> \tinserts a new entry";
 const string delete_help = "d[elete] <name> \tdeletes the given name";
 const string search_help = "s[earch] name/num[ber],<name/number> \tsearches with the given prefix";
 const string clear_help = "c[lear] \tclears the whole directory";
*/

int main(int arc, char** argv) {
  PhoneDirectory dir;
  UI pd_ui;
  pd_ui.run(&dir);
  return 0;
}
