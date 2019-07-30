#pragma once
#include <iostream>
#include <string>
#include "ActorsData.h"
#include "util.h"

using namespace std;

class Node
{
public:
	string key; // short_name
	ActorsData record;
	Node *left;
	Node *right;
public:
	Node();
	Node(const string &key, const ActorsData &record);
	~Node();
	virtual void set_balance(balance_factor b) {};
	virtual balance_factor get_balance() const { return equal_height; };
};

