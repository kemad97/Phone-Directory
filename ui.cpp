#include "ui.h"

Cmd::Cmd():cmd_name(INVALID_CMD) {}
UI::Cmd::Cmd(CmdName p_cmd_name, string p_name, string p_num):
cmd_name(p_cmd_name), name(p_name), num(p_num) {}

void UI::run(PhoneDirectory* dir)
{
	string s;
	while(getline(cin, s))
	{
	  Cmd cmd =parse_string(s);
	  PositionList name_list;
	  PositionList num_list;

	  // cout << s <<": " << cmd.cmd_name << '-' 
	  //      << cmd.name << '-' << cmd.num << endl;
	  switch(cmd.cmd_name)
	  {
	    case INSERT:
	      dir->insert(cmd.name, cmd.num);
	    break;
	    case SEARCH_BY_NAME:
	      name_list = dir->search_by_name(cmd.name);
	      PositionListUtils::sort_list(name_list, true);
	      PositionListUtils::display_list(name_list, true);
	    break;
	    case SEARCH_BY_NUMBER:
	      num_list = dir->search_by_phone_num(cmd.num);
	      PositionListUtils::sort_list(num_list, false);
	      PositionListUtils::display_list(num_list, false);
	    break;
	    case DELETE:
	      dir->remove(cmd.name);
	    break;
	    case CLEAR:
	      dir->delete_all();
	    break;
	    case INVALID_CMD:
	      cout << "Invalid command" << endl;
	    break;
	  } // end of switch
	} // end of while
}

UI::Cmd UI::parse_string(string s)
{
	// split string
	// command structure: cmd arg1,arg2
	string s_cmd = s.substr(0, s.find(' '));
	string arg1;
	string arg2;
	// space exists (at least 1-arg cmd)
	if(s.find(' ')!=string::npos) 
	{
	  // cmd arg1,arg2
	  int arg1_len =s.find(',')-s.find(' ')-1;
	  arg1 = s.substr(s.find(' ') + 1, arg1_len);
	}
	// comma exists (2-arg cmd)
	if(s.find(',')!=string::npos)
	  arg2 = s.substr(s.find(',') + 1);
	// cout << s_cmd << '-' << arg1 << '-' << arg2 << endl;

	// req. name & num: arg1 & arg2
	if(s_cmd == "i" || s_cmd == "insert") 
	  return {INSERT, arg1, arg2};
	// req. name: arg2
	else if((s_cmd == "s" || s_cmd == "search") && arg1 == "name")
	  return {SEARCH_BY_NAME, arg2, ""};
	// req. num: arg2
	else if((s_cmd == "s" || s_cmd == "search") && (arg1 == "num" || arg1 == "number")) 
	  return {SEARCH_BY_NUMBER, "", arg2};
	// req. name: arg1
	else if(s_cmd == "d" || s_cmd == "delete") 
	  return {DELETE, arg1, ""};
	// req. no-arg
	else if(s_cmd == "c" || s_cmd == "clear") 
	  return {CLEAR, "", ""};
	else
	return Cmd(); 
}

