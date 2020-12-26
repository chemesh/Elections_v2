#pragma once
#include <iostream>
#include "Citizen.h"


using namespace std;

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
		CitizensList(int _size = 1) : length(0) , size(_size) { list = new Citizen[_size]; }
		~CitizensList() { delete[] list; }

		bool setSize(const int&);
		bool setLength(const int&);
		bool setCitizen(const Citizen&);
		bool setCitizen(char* name, int id, int yob, int district);
		

		int getSize() const;
		int getLength() const;

		Citizen* const getCitizen(int id);
		int getCitizenIndex(int id);
		const Citizen* const getList();

		bool removeCitizen(const Citizen&);
		bool isFull();

		void CitizenSort() { mergeSort(list, 0, length); }

		
		//void printList()
		//{
		//	for (int i = 0; i < length; i++)
		//	{
		//		cout << list[i] << '\n';
		//	}
		//}

		friend std::ostream& operator<<(std::ostream& out, const CitizensList& other)
		{
			for (int i = 0; i < other.length; i++)
			{
				cout << other.list[i] << '\n';
			}
			return out;
		}
		
	};
}