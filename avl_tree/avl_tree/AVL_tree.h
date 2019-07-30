#pragma once
#include <string>
#include "BST.h"
#include "AVL_node.h"

class AVL_tree : public BST
{
protected:
	int left_rotations;
	int right_rotations;
public:
	// insert methods
	void insert(const string &key, const ActorsData &record);
	void avl_insert(Node *&root, const string &key, 
		            const ActorsData &record, bool &taller);

	// remove methods
	void remove(const string &key);
	void remove_avl_node(Node *&root, bool &shorter);
	void avl_search_and_delete(Node *&root, const string &key, bool &shorter);
	void restore_balance(Node *&root, Node *&sub_root, bool &shorter);

	// rotation methods
	void rotate_left(Node *&root);
	void right_balance(Node *&root);
	void rotate_right(Node *&root);
	void left_balance(Node *&root);

	// get number of left and right rotations
	int get_left_rotations() const { return left_rotations; }
	int get_right_rotations() const { return right_rotations; }
	void reset_rotations() { left_rotations = right_rotations = 0; }

	AVL_tree();
	~AVL_tree();
};

