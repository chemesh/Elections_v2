#include "PartyList.h"

namespace elc
{
	bool PartyList::setSize(const int& _size)
	{
		Party* temp = new Party[_size];

		for (int i = 0; i < size; i++)
			temp[i] = list[i];
		this->size = _size;
	//	delete[] list; // major bug
		list = temp;
		return true;
	}

	bool PartyList::setLength(const int& len)
	{
		this->length = len;
		return true;
	}

	bool PartyList::setParty(char* _partyName, const Citizen& boss, int numOfDistricts)
	{
		if (isFull())
		{
			setSize(size * 2);
		}
		list[length].setParty(_partyName,boss);
		list[length].setElectorsSize(numOfDistricts+1);
		list[length].setElectorsLength(numOfDistricts);
		list[length].setPartyNumber(length);
		setLength(length + 1);
		return true;
	}

	bool PartyList::addRepInParty(const Citizen& rep , int partyID, int distID)
	{
		list[partyID].addSenator(distID, rep);
		return true;
	}
	
	int PartyList::getSize() const
	{
		return this->size;
	}

	int PartyList::getLength() const
	{
		return this->length;
	}

	Party& PartyList::getParty(const int& partyID) const
	{
		return list[partyID];
	}

	bool PartyList::AddNewDistToParties(int distID)
	{
		//int temp;
		for (int i = 0; i < length; i++)
		{
			list[i].AddNewDistElector(distID);
		}
		return true;

	}

	const int& PartyList::getPartyElectorsLength(const int& partyID) const
	{
		 return list[partyID].getElectorsLength(); 
	}

	const char* const PartyList::getPartyName(const int& partyID) const
	{
		return list[partyID].getPartyName();
	}

	bool PartyList::isFull()
	{
		if (length == size)
			return true;
		return false;
	}

}