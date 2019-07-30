#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ActorsData.h"

using namespace std;

enum balance_factor {
	left_higher,
	equal_height,
	right_higher
};

enum subtree {
	left_subtree,
	right_subtree,
	root
};

void read_file(int&);
void parse_line(string&);
void build_a_tree(string &, ActorsData &);
void show_inorder();
void show_preorder();
void show_postorder();
void show_bfs();
void find_record(string &);
void delete_record(string &);
void show_min_max();
void show_tree_heigh();
void find_multiple(const string &);
void print_in_range(const string &, const string &);
void get_rotations();
void show_node_height(subtree, int &);

void user_input_handler();
void user_input_find_data();
void user_input_new_data();
void user_input_delete_data();
void user_input_find_height();
void user_input_min_max_value();