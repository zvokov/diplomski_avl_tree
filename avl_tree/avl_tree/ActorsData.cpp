#include "ActorsData.h"


ActorsData::ActorsData()
{
}

ActorsData::ActorsData(const int &id, const string &short_name, 
					   const string &long_name)
{
	this->id = id;
	this->short_name = short_name;
	this->long_name = long_name;
}


ActorsData::~ActorsData()
{
}

void ActorsData::print_actors_data()
{
	cout << "ID = " << this->get_id() << " Short name = " \
		 << this->get_short_name() << " Long name = " << this->get_long_name() \
		 << endl;
}