#pragma once
#include <iostream>
#include <string>

using namespace std;

class ActorsData
{
private:
	int id;
	string short_name;
	string long_name;
public:
	ActorsData();
	ActorsData(const int&, const string&, const string&);
	~ActorsData();
	// setters
	void set_id(int _id) { id = _id; };
	void set_short_name(string _short) { short_name = _short; };
	void set_long_name(string _long) { long_name = _long; };
	// getters
	int get_id() const { return id; };
	string get_short_name() const { return short_name; };
	string get_long_name() const { return long_name; };

	void print_actors_data();
};

