#include "AVL_tree.h"

AVL_tree::AVL_tree()
{
}


AVL_tree::~AVL_tree()
{
}

void AVL_tree::insert(const string &key, const ActorsData &record)
{
	bool taller;
	return avl_insert(root, key, record, taller);
}

void AVL_tree::avl_insert(Node *&root, const string &key, 
						  const ActorsData &record, bool &taller)
{
	if (root == NULL) {
		root = new AVL_node(key, record);
		taller = true;
	}
	else if (key.compare(root->key) == 0) {
		taller = false;
		std::cout << "Duplicates not allowed!" << std::endl;
	}
	else if (key.compare(root->key) < 0) {
		avl_insert(root->left, key, record, taller);
		if (taller == true) {
			switch (root->get_balance()) {
			case left_higher:
				left_balance(root);
				taller = false;
				break;
			case equal_height:
				root->set_balance(left_higher);
				break;
			case right_higher:
				root->set_balance(equal_height);
				taller = false;
				break;
			default:
				break;
			}
		}
	}
	else {
		avl_insert(root->right, key, record, taller);
		if (taller == true) {
			switch (root->get_balance()) {
			case left_higher:
				root->set_balance(equal_height);
				taller = false;
				break;
			case equal_height:
				root->set_balance(right_higher);
				break;
			case right_higher:
			    right_balance(root);
				taller = false;
				break;
			default:
				break;
			}
		}
	}
}

void AVL_tree::right_balance(Node *&root)
{
	Node * &right_tree = root->right;
	switch (right_tree->get_balance()) {
	case right_higher:
		root->set_balance(equal_height);
		right_tree->set_balance(equal_height);
		rotate_left(root);
		break;
	case equal_height:
		std::cout << "Error while doing right balance!" << std::endl;
		break;
	case left_higher: {
		Node * left_sub_tree = right_tree->left;
		switch (left_sub_tree->get_balance()) {
		case equal_height:
			root->set_balance(equal_height);
			right_tree->set_balance(equal_height);
			break;
		case left_higher:
			root->set_balance(equal_height);
			right_tree->set_balance(right_higher);
			break;
		case right_higher:
			root->set_balance(left_higher);
			right_tree->set_balance(equal_height);
			break;
		}
		left_sub_tree->set_balance(equal_height);
		rotate_right(right_tree);
		rotate_left(root);
		break;
	}
	default:
		break;
	}
}

void AVL_tree::left_balance(Node *&root)
{
	Node *&left_tree = root->left;
	switch (left_tree->get_balance()) {
	case left_higher:
		root->set_balance(equal_height);
		left_tree->set_balance(equal_height);
		rotate_right(root);
		break;
	case equal_height:
		std::cout << "Error while doing left balance!" << std::endl;
		break;
	case right_higher: {
		Node * right_sub_tree = left_tree->right;
		switch (right_sub_tree->get_balance()) {
		case equal_height:
			root->set_balance(equal_height);
			left_tree->set_balance(equal_height);
			break;
		case right_higher:
			root->set_balance(equal_height);
			left_tree->set_balance(left_higher);
			break;
		case left_higher:
			root->set_balance(right_higher);
			left_tree->set_balance(equal_height);
			break;
		}
		right_sub_tree->set_balance(equal_height);
		rotate_left(left_tree);
		rotate_right(root);
		break;
	}
	default:
		break;
	}
}

void AVL_tree::rotate_left(Node *&root)
{
	if (root == NULL || root->right == NULL) {
		std::cout << "Error while rotating left!" << std::endl;
	}
	else {
		Node *right_tree = root->right;
		root->right = right_tree->left;
		right_tree->left = root;
		root = right_tree;
		left_rotations++;
	}
}

void AVL_tree::rotate_right(Node *&root)
{
	if (root == NULL || root->left == NULL) {
		std::cout << "Error while rotating right!" << std::endl;
	}
	else {
		Node *left_tree = root->left;
		root->left = left_tree->right;
		left_tree->right = root;
		root = left_tree;
		right_rotations++;
	}
}

void AVL_tree::remove(const string &key)
{
	bool shorter = true;
	avl_search_and_delete(root, key, shorter);
}

void AVL_tree::avl_search_and_delete(Node *&root, const string &key, bool &shorter)
{
	if (root == NULL || (root->key.compare(key) == 0)) {
		remove_avl_node(root, shorter);
	}
	else if (key.compare(root->key) < 0) {
		avl_search_and_delete(root->left, key, shorter);
		if (shorter == true) {
			switch (root->get_balance()) {
			case equal_height:
				root->set_balance(right_higher);
				shorter = false;
				break;
			case left_higher:
				root->set_balance(equal_height);
				break;
			case right_higher:
				restore_balance(root, root->right, shorter);
				break;
			}
		}
	}
	else {
		avl_search_and_delete(root->right, key, shorter);
		if (shorter == true) {
			switch (root->get_balance()) {
			case equal_height:
				root->set_balance(left_higher);
				shorter = false;
				break;
			case left_higher:
				restore_balance(root, root->left, shorter);
				break;
			case right_higher:
				root->set_balance(equal_height);
				break;
			}
		}
	}
}

void AVL_tree::restore_balance(Node *&root, Node *&sub_root, bool &shorter)
{
	if (root == NULL || sub_root == NULL) {
		std::cout << "Something went wrong while restoring balance!" << std::endl;
		shorter = false;
		return;
	}

	if (sub_root->get_balance() == root->get_balance()) { // expecting righ or left higher
		switch (root->get_balance()) {
		case right_higher:
			root->set_balance(equal_height);
			sub_root->set_balance(equal_height);
			rotate_left(root);
			break;
		case left_higher:
			root->set_balance(equal_height);
			sub_root->set_balance(equal_height);
			rotate_right(root);
			break;
		}
	}
	else if (sub_root->get_balance() == equal_height) { // sub_root is equal and root is either left or right higher
		switch (root->get_balance()) {
		case right_higher:
			sub_root->set_balance(left_higher);
			rotate_left(root);
			break;
		case left_higher:
			sub_root->set_balance(right_higher);
			rotate_right(root);
			break;
		}
		shorter = false;
	}
	else { // The balance factor of root and sub_root are opposite
		if (sub_root->get_balance() == left_higher) {
			Node * left_sub_tree = sub_root->left;
			switch (left_sub_tree->get_balance()) {
			case equal_height:
				root->set_balance(equal_height);
				sub_root->set_balance(equal_height);
				break;
			case left_higher:
				root->set_balance(equal_height);
				sub_root->set_balance(right_higher);
				break;
			case right_higher:
				root->set_balance(left_higher);
				sub_root->set_balance(equal_height);
				break;
			}
			left_sub_tree->set_balance(equal_height);
			rotate_right(sub_root);
			rotate_left(root);
		}
		else {
			Node * right_sub_tree = sub_root->right;
			switch (right_sub_tree->get_balance()) {
			case equal_height:
				root->set_balance(equal_height);
				sub_root->set_balance(equal_height);
				break;
			case right_higher:
				root->set_balance(equal_height);
				sub_root->set_balance(left_higher);
				break;
			case left_higher:
				root->set_balance(right_higher);
				sub_root->set_balance(equal_height);
				break;
			}
			right_sub_tree->set_balance(equal_height);
			rotate_left(sub_root);
			rotate_right(root);
		}
	}
}

void AVL_tree::remove_avl_node(Node *&sub_root, bool &shorter)
{
	if (sub_root == NULL) {
		std::cout << "Data not presented in dataset!" << std::endl;
		shorter = false;
		return;
	}

	Node *node_to_delete = sub_root;

	if (sub_root->right == NULL) {
		sub_root = sub_root->left;
	}
	else if (sub_root->left == NULL) {
		sub_root = sub_root->right;
	}
	else {
		Node *parent = sub_root;
		node_to_delete = sub_root->left;
		while (node_to_delete->right != NULL) {
			parent = node_to_delete;
			node_to_delete = node_to_delete->right;
		}
		sub_root->key = node_to_delete->key;
		sub_root->record = node_to_delete->record;
		if (parent == sub_root) {
			sub_root->left = node_to_delete->left;
		}
		else {
			parent->right = node_to_delete->left;
		}
	}

	delete node_to_delete;
}