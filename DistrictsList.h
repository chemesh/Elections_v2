#pragma once
#include <iostream>
#include "district.h"

using namespace std;

namespace  elc {

	class DistrictsList
	{
	private:
		District** list;
		int length;
		int size;

	public:
		DistrictsList(int _size = 1) : length(0), size(_size) { list = new District*[_size]; }
		~DistrictsList() { cout << "distlist dtor" << endl; delete[] list; }

		bool setSize(const int&);
		bool setLength(const int&);
		bool setDistrict(char* _DistrictName, int numOfReps, bool div);
		
		bool setDistrict(const District& _dist);

		bool setCitizenInDist(const Citizen&, const District& dist);

		int getSize() const;
		int getLength() const;
		District** const getList() const { return list; }
		const District& getDistrict(const int& distID) const { return *(list[distID]); }
		District& getDistrict(int distID, bool flag) const { return *(list[distID]); }
		const int& getTotalRepsInDist(const int& distID) const { return list[distID]->getDistReps(); }

		bool isFull();

		void operator=(const DistrictsList& o);

		void PrintNameAndId() //new function
		{
			for (int i = 0; i < length; i++)
				list[i]->printNameAndId();
		}

		friend std::ostream& operator<<(std::ostream& out, const DistrictsList& other)
		{
			for (int i = 0; i < other.length; i++)
			{
				cout << *other.list[i] << '\n';
			}
			return out;
		}

		bool isDivided(int i);

		void save(ofstream& out) const;
		void load(ifstream& in);

	};



}