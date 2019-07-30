#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include "Node.h"

using namespace std;

class BST
{
protected:
	Node *root;
public:
	BST();
	~BST();
	
	// setters and getters
	Node *get_root() const { return root; };
	
	// util methods
	bool is_empty() const;
	// insert methods
	void insert(string &key, ActorsData &record);
	void search_and_insert(Node *& root, const string &key, const ActorsData &record);
	// searching methods
	void search_data(string &key);
	Node* search_tree(Node *&root, const string &key);
	// removals methods
	void remove(const string &key);
	void search_and_remove(Node *& root, const string &key);
	void remove_node(Node *& sub_root);
	// find min and max methods
	void find_min();
	void find_max();
	// find height;
	void height();
	int find_height(Node *&root);
	// find height of a given node index
	void get_node_height(subtree subtree, const int &index);

	// traversal methods
	void inorder();
	void inorder_recursive(Node *&root);
	void preorder();
	void preorder_recursive(Node *&root);
	void postorder();
	void postorder_recursive(Node *&root);
	void bfs();
	void bfs_travers(Node *&root);

	// search multiple data
	void searh_with_prefix(const string &key);
	Node *find_first(Node *&root, const string &key);
	void find_multiple_match(Node *&root, const string &key, int &count);
	// range query
	void find_in_range(const string &lower_bound, const string &upper_bound);
	void print_in_range(Node *&root, const string &low, const string &high);
};

