#include "positionlistutils.h"

void PositionListUtils::display_list(PositionList& pl, bool is_name_list)
{
	if(!pl.size())
	  {cout << "not found" << endl; return;}

	printf("found %d matches\n", (int)pl.size());
	for (PositionList::iterator i = pl.begin(); i!=pl.end(); i++)
	{
	  // Name list
	  if (is_name_list)
	    cout << (**i).data <<": " << (**i).associated_node->data << endl;
	  // Phone list: print name first
	  else
   		cout << (**i).associated_node->data << ": " << (**i).data << endl;
	}
}

void PositionListUtils::sort_list(PositionList& pl, bool is_name_list)
{
	for (PositionList::iterator i = pl.begin(); i!=pl.end(); i++)
	{
	  PositionList::iterator j = i;
	  while(++j!=pl.end())
	  {
	    // Always sort by name
	    if((is_name_list && (**i).data > (**j).data) ||
	       (!is_name_list && (**i).associated_node->data > (**j).associated_node->data))
	    {
	      Position temp_p = *i;
	      *i = *j;
	      *j = temp_p;
	    }
	  }
	}
}