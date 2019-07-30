#include "AVL_node.h"


AVL_node::AVL_node()
{
	balance = equal_height;
}

AVL_node::AVL_node(const string& key, const ActorsData &record)
{
	this->key = key;
	this->record = record;
	balance = equal_height;
}

AVL_node::~AVL_node()
{
}
