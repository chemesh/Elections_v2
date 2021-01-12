#include "CitizenList.h"

namespace elc
{

	bool CitizensList::setCitizen(const string name, int id, int yob, const District& district)
	{
		setCitizen(Citizen(name, id, district, yob));
		return true;
	}

	bool CitizensList::setCitizen(const Citizen& citizen)
	{
		list.push_back(citizen);
		return true;
	}


	Citizen* const CitizensList::getCitizen(int id) const
	{

		//using find_if std fuction, because we need to find the citizen obj maching ID
		//using lambda fuction as learn on stack-overflow
		//https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute

		auto it = find_if(list.begin(), list.end(), [&id](const Citizen& obj) {return obj.getID() == id; });

		if (it != list.end())
		{
			return it._Ptr; //return the pointer of the element in terator?
		}

		return nullptr; //if citizen not found then,
	}

	const vector<Citizen>  CitizensList::getList()const
	{
		return list;
	}

	bool CitizensList::removeCitizen(const Citizen& _citizen)
	{
		for (vector<Citizen>::iterator itr = list.begin();
			itr != list.end(); itr++)
		{
			if (itr->getID() == _citizen.getID())
			{
				list.erase(itr);
				return true;
			}
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& out, const CitizensList& other)
	{
		for (int i = 0; i < other.list.size(); i++)
		{
			cout << other.list[i] << '\n';
		}
		return out;
	}
	/**************************serialiazion***************************/
	void CitizensList::save(ofstream& out) const
	{
		int size = list.size();
		int capacity = list.capacity();

		out.write(rcastcc(&capacity), sizeof(capacity));
		out.write(rcastcc(&size), sizeof(size));
		for (int i = 0; i < size; ++i)
		{
			list[i].save(out);
		}
	}

	void CitizensList::load(ifstream& in, const DistrictsList& _list)
	{
		int size;
		int capacity;
		in.read(rcastc(&capacity), sizeof(capacity));
		in.read(rcastc(&size), sizeof(size));

		list =  vector<Citizen>(capacity);
		for (int i = 0; i < size; i++)
		{
			list[i].load(in, _list);
		}
	}
}