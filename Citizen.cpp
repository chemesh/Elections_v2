
#include "Citizen.h"
#include "district.h"
#include <iostream>

namespace elc {

	Citizen::~Citizen()
	{ //major bug, for now row 12 of districtlist.cpp is hiden...
		std::cout << "citizen dtor:" << std::endl;
		if (this->name != nullptr)
			delete[] this->name; ///ERROR????
	}

	Citizen::Citizen(const Citizen& other)
	{
		setCitizen(other.name, other.ID, *other.dist, other.YOB);
	}

	const char* Citizen::getName() const { return name; }
	int Citizen::getID() const { return ID; }

	const District& Citizen::getDistrict() const { return *dist; }
	int Citizen::getYOB() const { return YOB; }

	bool Citizen::setName(const char* _n)
	{
		if (_n == nullptr) 
		//some bug when adding districts without citizens. this should prevent
		{
			name = nullptr;
			return true;
		}

		if (name != nullptr)
			delete[] name;

		int len = strlen(_n);
		this->name = new char[len + 1];
		memcpy(this->name, _n, len + 1);
		return true;
	}
	bool Citizen::setID(int id)
	{
		this->ID = id;
		return true;
	}
	bool Citizen::setDistrict(const District& _dist)
	{
		this->dist = &_dist;
		return true;
	}
	bool Citizen::setYOB(int year)
	{
		this->YOB = year;
		return true;
	}
	bool Citizen::setCitizen(const char* name, int id, const District& dist, int year)
	{
		return setName(name) && setID(id) &&
			setDistrict(dist) && setYOB(year);
	}

	void Citizen::operator=(const Citizen& o)
	{
		setCitizen(o.name, o.ID, *o.dist, o.YOB);

	}

	 std::ostream& operator<<(std::ostream& out, const Citizen& other)
	{
		std::cout
			<< "name: " << other.name << " , "
			<< "ID: " << other.ID << " , "
			<< "born in: " << other.YOB << " , "
			<< "district: " << other.dist->getDistName() << ".";
		return out;
	}
}



