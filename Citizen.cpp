/*

citizen - name, id, DOB, living district
- add a citizien.

party - candidate, list of representives,
- add citizen as representitive (CIN of id, num of party, name of district)

district - name, id, list of aproved voters (list of citizen id), 
		   percent of voters, won(data stucr that containes lists of representiteves),

electionRound
- date (day, month, year)
- list of voters (each item is a citizen)
- list of parties (each item is a party)
- list of districts (each item is a district)
-
*/

#include "Citizen.h"
#include <iostream>

namespace elc {  

	Citizen::~Citizen() 
	{ //major bug, for now row 12 of districtlist.cpp is hiden...
		std::cout << "citizen dtor:" << std::endl;
		if (this->name != nullptr)
			delete[] this->name; ///ERROR????
	}

	char* Citizen::getName() const { return name; }
	int Citizen::getID() const { return ID;  }
	int Citizen::getDistrict() const { return districtId;  }
	int Citizen::getYOB() const { return YOB; }

	bool Citizen::setName(char* _n)
	{
		int len = strlen(_n);
		this->name = new char[len+1];
		memcpy(this->name,_n,len+1);
		return true;
	}
	bool Citizen::setID(int id)
	{
		this->ID = id;
		return true;
	}
	bool Citizen::setDistrict(int  dist)
	{
		this->districtId = dist;
		return true;
	}
	bool Citizen::setYOB(int year)
	{
		this->YOB = year;
		return true;
	}
	bool Citizen::setCitizen(char* name, int id, int dist, int year)
	{
		return setName(name) && setID(id) && 
			setDistrict(dist) && setYOB(year);
	}

	void Citizen::operator=(const Citizen& o)
	{
		setCitizen(o.name, o.ID, o.districtId, o.YOB);
	}
}


 
