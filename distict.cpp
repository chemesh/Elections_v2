#pragma once
#include "district.h"

namespace elc
{
	//District::District(char* _name, int numOfReps) :
	//	distID(0), voters_precentage(0)
	//{
	//	District::setDistName(_name);
	//	District::setDistReps(numOfReps);
	//}
	//int District::numberOfDistrict = 0;


	bool District::setDistName(const char* _name)
	{
		int len = strlen(_name);
		this->name = new char[len + 1];
		memcpy(this->name, _name, len + 1);
		return true;
	}

	bool District::setDistID(const int& _id)
	{
		this->distID = _id;
		return true;
	}

	bool District::setDistCitizenInList(const Citizen& _citizen)
	{
		return citizens.setCitizen(_citizen);
		
	}
	
	bool District::setVoters(int& allCitizens)
	{
		voters_precentage = citizens.getLength() / float(allCitizens);
		return true;
	}

	//added
	bool District::setRepsSize(const int& _size)
	{
		Representatives* temp = new Representatives[_size];

		for (int i = 0; i < reps_size; i++)
			temp[i] = RepsList[i];
		this->reps_size = _size;
		delete[] RepsList;
		RepsList = temp;
		return true;
	}

	bool District::setRepsLength(const int& len)
	{
		int i;
		for (i = reps_lentgh; i < len; i++)
		{
			this->RepsList[i].setPartyID(i);
		}
		this->reps_lentgh = len;
		return true;
	}
	///

	bool District::setCongressManInList(const Senator& _senator)
	{
		RepsList->addSenator(_senator);
		return (true);
	}

	bool District::setDistReps(const int& _numOfReps)
	{
		totalReps = _numOfReps;
		return true;
	}

	const char* District::getDistName() const
	{
		return name;
	}

	const int& District::getDistID() const
	{
		return distID;
	}

	//const CitizensList& District::GetDistCitizens() const
	//{
	//	return citizens;
	//}

	const float& District::getVoters() const
	{
		return voters_precentage;
	}

	int District::getDistReps() const
	{
		return totalReps;
	}

	///added
	int District::getRepsSize() const
	{
		return this->reps_size;
	}

	int District::getRepsLength() const
	{
		return this->reps_lentgh;
	}
	///

	bool District::setVotersPersentage(const float& num)
	{
		this->voters_precentage = num;
		return true;
	}
	bool District::setRepsList(Representatives* reps)
	{
		this->RepsList = reps;
		return true;
	}

	bool District::setSenatorInDistReps(const Senator* newRep, int partyID)
	{
		RepsList[distID].addSenator(*newRep);
		return true;
	}
	bool District::setCitizenList(const CitizensList& list)
	{
		this->citizens = list;
		return true;
	}


	bool District::setDistrict(const char* _name, int id, int numOfReps, float voterPer,const CitizensList& cList, Representatives* rList)
	{
		return (setDistName(_name) && setDistID(id) && setDistReps(numOfReps) &&
			setVotersPersentage(voterPer) && setCitizenList(cList) && setRepsList(rList));
	}


	bool District::setDistrict(const char* _name, int numOfReps)
	{
		setDistName(_name);
		setDistReps(numOfReps);
		return true;
	}

	bool District::addNewPartyReps(Party _newParty, int numOfReps)
	{
		int i;
		if (isRepListFull())
		{
			setRepsSize(reps_size * 2);
		}

		for (i = 1; i <= numOfReps; i++)
		{
			RepsList[reps_lentgh].addSenator(_newParty.getSenatorInDist(distID,i));
		}
		reps_lentgh++;
		return true;
	}

	void District::operator=(const District& o)
	{
		setDistrict(o.name, o.distID, o.totalReps, o.voters_precentage, o.citizens, o.RepsList);
	}

	
}