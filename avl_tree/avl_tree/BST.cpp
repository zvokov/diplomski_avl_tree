#include "BST.h"

BST::BST()
{
	this->root = NULL;
}

BST::~BST()
{
}

bool BST::is_empty() const
{
	return (this->root == NULL);
}

void BST::inorder()
{
	inorder_recursive(root);
}

void BST::inorder_recursive(Node *&root)
{
	if (root != NULL) {
		this->inorder_recursive(root->left);
		std::cout << root->key << std::endl;
		this->inorder_recursive(root->right);
	}
}

void BST::preorder()
{
	preorder_recursive(root);
}

void BST::preorder_recursive(Node *&root)
{
	if (root != NULL) {
		std::cout << root->key << std::endl;
		this->preorder_recursive(root->left);
		this->preorder_recursive(root->right);
	}
}

void BST::postorder()
{
	postorder_recursive(root);
}

void BST::postorder_recursive(Node *&root)
{
	if (root != NULL) {
		this->postorder_recursive(root->left);
		this->postorder_recursive(root->right);
		std::cout << root->key << std::endl;
	}
}

void BST::insert(string &key, ActorsData &record)
{
	search_and_insert(this->root, key, record);
}

void BST::search_and_insert(Node *& root, const string &key, const ActorsData &record)
{
	if (root == NULL) {
		root = new Node(key, record);
	}
	else if ((key.compare(root->key)) < 0) {
		search_and_insert(root->left, key, record);
	}
	else if ((key.compare(root->key)) > 0) {
		search_and_insert(root->right, key, record);
	}
	else {
		std::cout << "Duplicates not allowed" << std::endl;
	}
}

void BST::search_data(string &key)
{
	Node* target_node = search_tree(root, key);
	if (target_node != NULL) {
		std::cout << "Found = " << target_node->key << std::endl;
	}
	else {
		std::cout << "Not found = " << key << std::endl;
	}
}

Node* BST::search_tree(Node *&root, const string &key)
{
	if (root == NULL || (root->key.compare(key) == 0)) {
		return root;
	}
	else if (key.compare(root->key) < 0) {
		return search_tree(root->left, key);
	}
	else {
		return search_tree(root->right, key);
	}
}

void BST::remove(const string &key)
{
	search_and_remove(root, key);
}

void BST::search_and_remove(Node *&root, const string &key)
{
	if (root == NULL || (root->key.compare(key) == 0)) {
		remove_node(root);
	}
	else if (key.compare(root->key) < 0) {
		search_and_remove(root->left, key);
	}
	else {
		search_and_remove(root->right, key);
	}
}

void BST::remove_node(Node *& sub_root)
{
	if (sub_root == NULL) {
		std::cout << "Data not presented in dataset!" << std::endl;
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

void BST::find_min() {
	Node* temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	std::cout << "Min element is = " << temp->key << std::endl;
	temp->record.print_actors_data();
}

void BST::find_max()
{
	Node* temp = root;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	std::cout << "Max element is = " << temp->key << std::endl;
	temp->record.print_actors_data();
}

void BST::height() {
	int height = find_height(root);
	cout << "Height = " << height << endl;
}

int BST::find_height(Node *&root)
{
	if (root == NULL) {
		return -1;
	}
	return std::max(find_height(root->left), find_height(root->right)) + 1;
}

void BST::bfs()
{
	bfs_travers(root);
}


static void add_to_queue(std::queue<Node*> &queue, Node *&node)
{
	if (node != NULL) {
		queue.push(node);
	}
}

void BST::bfs_travers(Node *&root)
{
	if (root == NULL) {
		return;
	}

	std::queue<Node*> q;
	int level_count = 1;

	q.push(root);
	q.push(NULL); // delimiter
	while (!q.empty()) {
		Node* current = q.front();
		q.pop();
		if (current != NULL) {
			std::cout << current->key << " ";
			if (level_count % 2 == 0) {
				// left to right
				add_to_queue(q, current->left);
				add_to_queue(q, current->right);
			}
			else {
				// right to left
				add_to_queue(q, current->right);
				add_to_queue(q, current->left);
			}
		}
		else {
			if (!q.empty()) {
				std::cout << std::endl;
				q.push(NULL);
			}
		}
		level_count++;
	}
	std::cout << std::endl;
}


void BST::searh_with_prefix(const string &key)
{
	Node *first_found = find_first(root, key);
	int count = 0;
	if (first_found != NULL) {
		// find all entries matching given prefix 
		find_multiple_match(first_found, key, count);
		std::cout << "Entries found = " << count << std::endl;
	}
	else {
		std::cout << "No entries found with given key = " << key << std::endl;
	}
}

void BST::find_multiple_match(Node *&root, const string &key, int &count)
{
	if (root != NULL &&
		(key.compare(0, key.size(), root->key, 0, key.size())) == 0) {
		find_multiple_match(root->left, key, count);
		root->record.print_actors_data();
		count++;
		find_multiple_match(root->right, key, count);
	}
}

Node* BST::find_first(Node *&root, const string &key)
{
	if (root == NULL || (key.compare(0, key.size(), root->key, 0, key.size())) == 0) {
		return root;
	}
	else if ((key.compare(0, key.size(), root->key, 0, key.size())) < 0) {
		return find_first(root->left, key);
	}
	else {
		return find_first(root->right, key);
	}

}

void BST::find_in_range(const string &lower_bound, const string &upper_bound)
{
	print_in_range(root, lower_bound, upper_bound);
}

void BST::print_in_range(Node *& root, const string &low, const string &high)
{
	if (root == NULL) {
		return;
	}

	if (low.compare(0, low.size(), root->key, 0, low.size()) < 0) {
		print_in_range(root->left, low, high);
	}
	if ((low.compare(0, low.size(), root->key, 0, low.size()) <= 0) &&
		(high.compare(0, high.size(), root->key, 0, high.size()) >= 0)) {
		root->record.print_actors_data();
	}
	if (high.compare(0, high.size(), root->key, 0, high.size()) > 0) {
		print_in_range(root->right, low, high);
	}
}


void BST::get_node_height(subtree subtree, const int &index)
{
	int level_count = 0;
	if (root != NULL) {
		Node *temp = root;
		switch (subtree) {
		case left_subtree:
			while (temp->left && level_count < index) {
				temp = temp->left;
				level_count++;
			}
			break;
		case right_subtree:
			while (temp->right && level_count < index) {
				temp = temp->right;
				level_count++;
			}
			break;
		default:
			BST::height(); // find root height
			return;
		}

		if (level_count == index) {
			cout << "Height of a given node is " << BST::find_height(temp) << std::endl;
		}
	}
}