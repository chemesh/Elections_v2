
#include "Representatives.h"

namespace elc {


	void Representatives::makeEmpty(void)
	{
		Senator* temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->getNext();
			delete temp;
		}
	}

	bool Representatives::setPartyID(int id)
	{
		this->PartyID = id;
		return true;
	}

	bool Representatives::addSenator(const Citizen& rep)
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
		this->NumOfReps++;
		return true;
	}

	bool Representatives::addSenator(const Senator& _new)
	{
		return addSenator(_new.getId());

	}

	void Representatives::printsenatorsList(int num) const
	{
		Senator* temp = head;
		for (int i = 0; i < num; i++)
		{
			cout << temp->getCandidate().getName() << endl;
			temp = temp->getNext();
		}
	}

}