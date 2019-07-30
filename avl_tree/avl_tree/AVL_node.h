#pragma once
#include <iostream>
#include <string>
#include "Node.h"
#include "util.h"

class AVL_node : public Node
{
public:
	balance_factor balance;
public: 
	AVL_node();
	AVL_node(const string &key, const ActorsData &record);
	~AVL_node();
	// overridden virtual functions
	void set_balance(balance_factor b) { balance = b; };
	balance_factor get_balance() const { return balance; };
};

