
#include "Citizen.h"
#include "district.h"
#include "DistrictsList.h"



namespace elc {

	//removed because string hanndles dtor
//	Citizen::~Citizen()
//	{ 
//		if (this->name != nullptr)
//			delete[] this->name; 
//	}

	Citizen::Citizen(const Citizen& other)
	{
		setCitizen(other.name, other.ID, *other.dist, other.YOB);
	}

	std::string Citizen::getName() const { return name; }
	int Citizen::getID() const { return ID; }

	const District& Citizen::getDistrict() const { return *dist; }
	int Citizen::getYOB() const { return YOB; }

	/*bool Citizen::setName(const char* _n)
	{
		if (_n == nullptr) 
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
	}*/

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
	bool Citizen::setCitizen(const std::string name, int id, const District& dist, int year)
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
	 
	/**************************serialiazion***************************/
	 void Citizen::save(std::ofstream& out) const
	 {
		 int distID = dist->getDistID();
		 int len = name.size();
		 out.write(rcastcc(&len), sizeof(len));									 // name length
		 out.write(rcastcc(name.c_str()), len);												// len+1 for the '\0'
		 out.write(rcastcc(&ID), sizeof(ID));									 // int ID
		 out.write(rcastcc(&YOB), sizeof(YOB));									 // int - yob
		 out.write(rcastcc(&hasVoted), sizeof(hasVoted));	
		 out.write(rcastcc(&distID), sizeof(distID));

	 }
	 void Citizen::load(std::ifstream& in, const DistrictsList& _list) //districts
	 {
		 int len, distID;
		 in.read(rcastc(&len), sizeof(len));
		 char* _name = new char[len + 1];
		 in.read(_name, len);
		 _name[len] = '\0';  //notice, we assign string to char*
		 name = _name;		 //then, assign it to the string name
		 delete[] _name; 	 //at last, delete the temporary char* 
		 in.read(rcastc(&ID), sizeof(ID));
		 in.read(rcastc(&YOB), sizeof(YOB));
		 in.read(rcastc(&hasVoted), sizeof(hasVoted));
		 in.read(rcastc(&distID), sizeof(distID));

		 dist = &(_list.getDistrict(distID));
	 }
}	



