#include "Node.h"

Node::Node()
{
}

Node::Node(const string &key, const ActorsData &record)
{
	this->key = key;
	this->record = record;
	this->left = NULL;
	this->right = NULL;
}

Node::~Node()
{
}
