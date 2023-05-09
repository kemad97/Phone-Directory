#ifndef PHONEDIRECTORY_H
#define PHONEDIRECTORY_H

#include <string>
#include "BinarySearchTree.h"

using namespace std;

struct Node{
	// ..
	string data;
	Node* parent;
	Node* left;
	Node* right;
	Node* associated_node;
};
/*
 * Assume a Balanced BST (BBST): 
 * insert/remove/search complexity: O(Log N)
 */
class PhoneDirectory{
public:
	// void or bool
	void insert(string name, string phone_num);

	void remove(string name);
	// List of Positions to Name nodes starting with or matching string name.
	PositionList search_by_name(string name);
	// List of Positions to Phone number nodes starting with or matching string phone_num.
	PositionList search_by_phone_num(string phone_num);
	
	PositionList get_contact_list();
	
	void delete_all();
	
	unsigned int get_count();
private:
	// Copy Constructor / Destructor / Copy Assignment (Not Implemented)
	BinarySearchTree name_bst;
	BinarySearchTree phone_bst;
};

/*
Name // lower case letters w/ spaces
PhoneNumber // only numeric digits
*/
#endif // PHONEDIRECTORY_H