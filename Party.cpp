
#include "Party.h"
#include <iostream>

namespace elc {

	int Party::numberOfParty = 0;

	int Elector::getDistrict() const { return districtId; }

	bool Elector::setdistrictId(int id)
	{
		this->districtId = id;
		return true;
	}

	char* Party::getPartyName() const { return partyName; }
	const Citizen& Party::getBossID() const { return boss; }
	int Party::getPartyNumber() const { return partyNumber; }

	bool Party::setPartyName(char* _n)
	{
		int len = strlen(_n);
		this->partyName = new char[len + 1];
		memcpy(this->partyName, _n, len + 1);
		return true;
	}
	bool Party::setBoss(const Citizen& boss)
	{
		this->boss = boss;
		return true;
	}
	bool Party::setElectors(Elector* e)
	{
		this->electors = e;
		return true;
	}

	//added
	bool Party::setElectorsSize(const int& _size)
	{
		Elector* temp = new Elector[_size];

		for (int i = 0; i < elec_size; i++)
			temp[i] = electors[i];
		this->elec_size = _size;
		delete[] electors;
		electors = temp;
		return true;
	}

	bool Party::setElectorsLength(const int& len)
	{
		int i;
		for (i = elec_length; i < len; i++)
		{
			this->electors[i].setdistrictId(i);
		}
		this->elec_length = len;
		return true;
	}
	///

	bool Party::setPartyNumber(int n)
	{
		this->partyNumber = n;
		return true;
	}

	//needed?
	bool Party::setParty(char* partyName, const Citizen& boss, int n, Elector* e, int size, int len)
	{
		return setPartyName(partyName) && setBoss(boss)
			&& setPartyNumber(n) && setElectors(e) &&
			setElectorsSize(size) && setElectorsLength(len);
	}

	bool Party::setParty(char* partyName, const Citizen& boss)
	{
		return setPartyName(partyName) && setBoss(boss);
	}
	bool Party::createElectorsList(int numOfDistricts)
	{

		this->electors = new Elector[numOfDistricts];
		for (int i = 0; i < numOfDistricts; i++)
		{
			this->electors[i].setdistrictId(i);
		}
		return true;
	}

	bool Party::addSenator(int numOfDistrict, const Citizen& rep)
	{

		this->electors[numOfDistrict].addSenator(rep);
		return true;
	}


	bool Elector::addSenator(const Citizen& rep)
	{
		Senator* temp = new Senator(rep);
		if (this->head == nullptr) //head is empty, handle first assignment
		{
			head = temp;
		}
		else
		{
			tail->setNext(temp);
		}
		tail = temp;
		this->numOfSenators++;
		return true;
	}

	Senator* Senator::getNext() const { return next; }

	bool Senator::setNext(Senator* next)
	{
		this->next = next;
		return true;
	}

	const Citizen& Senator::getId() const
	{
		return candidate;
	}

	bool Senator::setCandidate(const Citizen& _rep)
	{
		this->candidate = _rep;
		return true;
	}
	const Citizen& Senator::getCandidate() const
	{
		return candidate;
	}

	void Elector::makeEmpty(void)
	{
		Senator* temp;
		while (head != NULL)
		{
			temp = head;
			head = head->getNext();
			delete temp;
		}
	}

	//added
	//added
	const Senator& Elector::getSenator(int place)
	{
		int i;
		Senator* temp = head;
		for (i = 0; i < place; i++)
		{
			temp = temp->getNext();
		}
		return *temp;
	}

	///added
	int Party::getElectorsSize() const
	{
		return this->elec_size;
	}

	int Party::getElectorsLength() const
	{
		return this->elec_length;
	}

	const Senator* Party::getElectorListInDist(const int& distID)
	{
		return (&electors[distID].getSenator(0));
	}

	bool Party::AddNewDistElector(int distID)
	{
		if (isElectorsFull())
			setElectorsSize(elec_size * 2);
		electors[elec_length].setdistrictId(distID - 1); ///
		elec_length++;
		//electors[elec_length].setNumOfSenators(numOfReps);
		return true;
	}

	///

	const Senator& Party::getSenatorInDist(int distID, int place)
	{
		return electors[distID].getSenator(place);
	}


	void Party::operator=(const Party& o)
	{
		setParty(o.partyName, o.boss, o.partyNumber, o.electors, o.elec_size, o.elec_length);
	}

	void Party::save(ostream& out) const
	{
		int len = strlen(partyName);
		len++; //add ++ for '\0'
		out.write(rcastcc(&len), sizeof(len));	
		out.write(partyName, len);
		out.write(rcastcc(&numberOfParty), sizeof(numberOfParty));
		


	}

	void Party::load(istream& in)
	{
		int length;
		in.read(rcastc(&length), sizeof(length));
		this->partyName = new char[length + 1];
		in.read(rcastc(partyName), sizeof(length));
		in.read(rcastc(&numberOfParty), sizeof(numberOfParty));
	}
}