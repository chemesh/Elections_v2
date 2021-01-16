/*


#include "Elector.h"
#include <iostream>
#include "CitizenList.h" 

namespace elc {

	class CitizensList; 


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

	void Elector::printElector()
	{
		Senator* temp = head;
		while (temp != nullptr)
		{
			cout << temp->getCandidate() << endl;
			temp = temp->getNext();
		}
	}

	std::ostream& operator<<(std::ostream& out, Elector& other)
	{
		cout
			<< "Electors from district ID: " << other.districtId << ":" << endl;
		other.printElector();
		return out;
	}

	void Elector::save(ofstream& out) const
	{
		out.write(rcastcc(&numOfSenators), sizeof(numOfSenators));
		Senator* temp = head;
		int citzId;
		while (temp)
		{
			citzId = temp->candidate.getID();
			out.write(rcastcc(&citzId), sizeof(citzId));
			temp = temp->getNext();
		}
	}
	void Elector::load(ifstream& in, const elc::CitizensList& _list)
	{
		Citizen* temp;
		int citzId;
		in.read(rcastc(&numOfSenators), sizeof(numOfSenators));
		for (int i = 0; i < numOfSenators; i++)
		{
			in.read(rcastc(&citzId), sizeof(citzId));
			temp = (_list.getCitizen(citzId));
			Elector::addSenator(*temp);
			numOfSenators--; //NOTICE! addSenator() increases numOfSenators, not needed while loading form file.
		}

	}
}

*/