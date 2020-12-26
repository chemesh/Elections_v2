#pragma once
#include <iostream>
#include "Party.h"

using namespace std;

namespace  elc {

	class PartyList
	{
	private:
		Party* list;
		int length;
		int size;

	public:
		PartyList(int _size = 1) : length(0), size(_size) { list = new Party[_size]; }
		~PartyList() { delete[] list; }

		bool setSize(const int&);
		bool setLength(const int&);
		bool setParty(char* _partyName, const Citizen& boss, int numOfDistricts);
		bool addRepInParty(const Citizen&, int partyID, int distID);

		int getSize() const;
		int getLength() const;
		const char* const getPartyName(const int& partyID) const;
		Party& getParty(const int& partyID)const ;
		const int& getPartyElectorsLength(const int& partyID) const;

		bool AddNewDistToParties(int);

		bool isEmpty() { return (length == 0); }
		bool isFull();

		void PrintNameAndId()
		{
			for (int i = 0; i < length; i++)
				list[i].printNameAndId();
		}


		friend std::ostream& operator<<(std::ostream& out, const PartyList& other)
		{
			for (int i = 0; i < other.length; i++)
			{
				cout << other.list[i] << '\n';
			}
			return out;
		}
	};
}