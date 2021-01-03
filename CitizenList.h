#pragma once
#include <iostream>
#include "Citizen.h"


using namespace std;
class DistrictsList;

namespace elc {

	class CitizensList
	{
	private:
		Citizen* list;
		int length; //log
		int size;  //phisical size of array

		void mergeSort(Citizen* arr, int l, int r);
		void merge(Citizen*, int l, int m, int r);

	public:
		CitizensList(int _size = 1) : length(0), size(_size) { list = new Citizen[_size]; }
		~CitizensList() { cout << "citizenlist dtor" << endl; delete[] list; }

		bool setSize(const int&);
		bool setLength(const int&);
		bool setCitizen(const Citizen&);
		bool setCitizen(const char* name, int id, int yob, const District& district);


		int getSize() const;
		int getLength() const;

		Citizen* const getCitizen(int id) const;
		int getCitizenIndex(int id) const;
		const Citizen* const getList()const;

		bool removeCitizen(const Citizen&);
		bool isFull();

		void CitizenSort() { mergeSort(list, 0, length); }

		void operator=(const CitizensList&);

		friend std::ostream& operator<<(std::ostream& out, const CitizensList& other)
		{
			for (int i = 0; i < other.length; i++)
			{
				cout << other.list[i] << '\n';
			}
			return out;
		}

		/**************************serialiazion***************************/
		void save(ofstream& out) const;
		void load(ifstream& in, const DistrictsList& _list);
	};
}