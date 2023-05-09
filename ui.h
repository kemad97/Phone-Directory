#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "phonedirectory.h"
#include "positionlistutils.h"

using namespace std;

// const string insert_help = "i[nsert] <name>,<number> \tinserts a new entry";
// const string delete_help = "d[elete] <name> \tdeletes the given name";
// const string search_help = "s[earch] name/num[ber],<name/number> \tsearches with the given prefix";
// const string clear_help = "c[lear] \tclears the whole directory";

class UI
{
public:
  enum CmdName {INSERT, SEARCH_BY_NAME, SEARCH_BY_NUMBER,
            DELETE, CLEAR, INVALID_CMD}; 
  struct Cmd{
    CmdName cmd_name;
    string name;
    string num;
    Cmd();
    Cmd(CmdName p_cmd_name, string p_name, string p_num);
  };

  // UI methods
  void run(PhoneDirectory* dir);
  Cmd parse_string(string s);
};

typedef UI::Cmd Cmd;
typedef UI::CmdName CmdName;

#endif