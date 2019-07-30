#include "util.h"
#include "BST.h"
#include "AVL_tree.h"

#define FILE_PATH "C:\\Users\\zvone\\Desktop\\actors100K.txt"
#define NUMBER_OF_ATTRIBUTES 3
#define ID_INDEX 0
#define SHORT_NAME_INDEX 1
#define LONG_NAME_INDEX 2

const char *show_actions_message = "1) Tree traversals\n2) Searching tree \n3) Add new data\n"\
"4) Delete data \n5) Find height\n6) Find min and max value\n0) Exit\n";
const char *traversals = "1) Inorder\n2) Postorder\n3) Preorder\n4) Level order traversal (cik-cak)\n";
const char *search_actions = "1) Search for data (short name or prefix)\n2) Print in range (low-high)\n";

// global instance of AVL tree
AVL_tree avl;

void read_file(int& in_read_count) {
	ifstream file;
	string line;
	int i = 0;

	file.open(FILE_PATH);

	if (file.is_open()) {
		while ((i < in_read_count) && getline(file, line)) { // todo: read until EOF
			parse_line(line);
			++i;
		}
		file.close();
	}
	else {
		cerr << "Unable to open: " << FILE_PATH << " file!" << endl;
	}
}

void parse_line(string &line) {
	string delimiter = "\t";
	size_t pos = 0;
	string token;
	vector<string> parsed(NUMBER_OF_ATTRIBUTES);
	int index = 0;
	ActorsData actor;

	while ((pos = line.find(delimiter)) != string::npos) {
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		parsed[index++] = token;
	}
	parsed[index] = line;

	actor = ActorsData(stoi(parsed[ID_INDEX]), parsed[SHORT_NAME_INDEX], parsed[LONG_NAME_INDEX]);
	build_a_tree(parsed[SHORT_NAME_INDEX], actor);
	parsed.clear();
}

void build_a_tree(string &key, ActorsData &record) {
	avl.insert(key, record);
}

void show_inorder() {
	avl.inorder();
}

void show_postorder() {
	avl.postorder();
}

void show_preorder() {
	avl.preorder();
}

void find_record(string &key) {
	avl.search_data(key);
}

void delete_record(string &key) {
	avl.remove(key);
}

void show_min_max() {
	avl.find_min();
	avl.find_max();
}

void show_tree_heigh() {
	avl.height();
}

void show_bfs() {
	avl.bfs();
}

void find_multiple(const string &key) {
	avl.searh_with_prefix(key);
}

void print_in_range(const string &low, const string &high) {
	avl.find_in_range(low, high);
}

void get_rotations() {
	int left = avl.get_left_rotations();
	int right = avl.get_right_rotations();
	
	cout << "Left rotations: " << left << endl;
	cout << "Right rotations: " << right << endl;
}

void show_node_height(subtree subtree, int &index) {
	avl.get_node_height(subtree, index);
}

void user_input_handler() {
	int input;
	bool flag = true;
	while (flag) {
		cout << show_actions_message;
		cout << "User input: ";
		cin >> input;
		cin.ignore();
		switch (input){
		case 1:
			cout << traversals;
			cin >> input;
			if (input == 1) {
				show_inorder();
			}
			else if (input == 2) {
				show_postorder();
			}
			else if (input == 3) {
				show_preorder();
			}
			else {
				show_bfs();
			}
			cout << endl;
			break;
		case 2:
			user_input_find_data();
			cout << endl;
			break;
		case 3:
			user_input_new_data();
			show_inorder();
			get_rotations();
			cout << endl;
			break;
		case  4:
			user_input_delete_data();
			cout << endl;
			break;
		case 5:
			user_input_find_height();
			cout << endl;
			break;
		case 6:
			user_input_min_max_value();
			cout << endl;
			break;
		default:
			flag = false;
			break;
		}
	}
}

void user_input_find_data() {
	cout << search_actions;
	int input;
	cin >> input;
	cin.ignore();
	if (input == 1) {
		cout << "Enter actor: ";
		string short_name;
		getline(cin, short_name);
		find_multiple(short_name);
	}
	else {
		string low, high;
		cout << "Enter low bound: ";
		getline(cin, low);
		cout << "Enter high bound: ";
		getline(cin, high);
		print_in_range(low, high);
	}
}

void user_input_new_data() {
	ActorsData new_data;
	int id;
	string short_name, long_name;

	cout << "ID: ";
	cin >> id;
	cin.ignore();
	cout << "Short name: ";
	getline(cin, short_name);
	cout << "Long name: ";
	getline(cin, long_name);
	new_data = ActorsData(id, short_name, long_name);
	avl.reset_rotations(); // reset previous rotations
	avl.insert(new_data.get_short_name(), new_data);
}

void user_input_delete_data() {
	string short_name;
	cout << "Enter short name: ";
	getline(cin, short_name);
	cout << "Deleting " << short_name << endl;
	delete_record(short_name);
	show_inorder();
}

void user_input_find_height() {
	int input;
	cout << "1) Tree height or 2) Find node height\n";
	cin >> input;
	cin.ignore();
	if (input == 1) {
		show_tree_heigh();
	}
	else {
		int index;
		subtree sub;
		cout << "Enter node index: ";
		cin >> index;
		cout << "Enter subtree (0 - left, 1 - right, 2 - root): ";
		cin >> input;
		if (input == 0) {
			sub = left_subtree;
		}
		else if (input == 1) {
			sub = right_subtree;
		}
		else {
			sub = root;
		}
		show_node_height(sub, index);
	}
}

void user_input_min_max_value() {
	show_min_max();
}