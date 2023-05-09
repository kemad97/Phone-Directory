#ifndef POSITIONLISTUTILS_H
#define POSITIONLISTUTILS_H
#include <iostream>
#include "phonedirectory.h"

using namespace std;

class PositionListUtils
{
public:
  static void display_list(PositionList& pl, bool is_name_list);
  static void sort_list(PositionList& pl, bool is_name_list);
};

#endif