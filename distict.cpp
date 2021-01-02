#pragma once
#include "district.h"

namespace elc
{
	District::District(const District& o)
	{
		*this = o;
	}

	bool District::setDistName(const char* _name)
	{
		int len = strlen(_name);
		this->name = new char[len + 1];
		memcpy(this->name, _name, len + 1);
		name[len] = '\0';
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

	const CitizensList& District::GetDistCitizens() const
	{
		return citizens;
	}

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

	bool District::initRepsList(const int& size, Party* list)
	{
		Representatives* temp = new Representatives[size+1];

		for (int i = 0; i < size; i++)
		{
			temp[i].setPartyID(list[i].getPartyNumber());
		}
		reps_size = size+1;
		reps_lentgh = size;
		delete[] RepsList;
		RepsList = temp;
		return true;
	}

	bool District::setNumOfPartyReps(const int& num, const Party& _party)
	{
		RepsList[_party.getPartyNumber()].setNumOfReps(num);
		return true;
	}

	bool District::setSenatorInDistReps(const Senator* newRep, int partyID)
	{
		//RepsList[distID].addSenator(*newRep);
		RepsList[partyID].addSenator(*newRep);
		return true;
	}
	bool District::setCitizenList(const CitizensList& list)
	{
		this->citizens = list;
		return true;
	}


	bool District::setDistrict(const char* _name, int id, int numOfReps, float voterPer, const CitizensList& cList, Representatives* rList)
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
			RepsList[reps_lentgh].addSenator(_newParty.getSenatorInDist(distID, i));
		}
		reps_lentgh++;
		return true;
	}

	void District::operator=(const District& o)
	{
		setDistrict(o.name, o.distID, o.totalReps, o.voters_precentage, o.citizens, o.RepsList);
	}

	std::ostream& operator<<(std::ostream& out, const District& other)
	{

		std::cout
			<< "district number: " << other.distID << " , "
			<< "name: " << other.name << " , "
			<< "number of Representatives: " << other.totalReps;
		if (typeid(other) == typeid(Divided))
			std::cout << " , type: Divided.";
		else
			std::cout << " , type: Unified.";
		return out;
	}

	bool District::isDivided()
	{
		if (typeid(*this) == typeid(Divided))
			return true;
		else
			return false;
	}

	void District::save(ofstream& out) const 
	{
		int len = strlen(name);
		out.write(rcastcc(&len), sizeof(len));									 // name length
		out.write(name, len);												// len+1 for the '\0'
		out.write(rcastcc(&distID), sizeof(distID));							 // int distID
		out.write(rcastcc(&totalReps), sizeof(totalReps));						 // int - total reps
		out.write(rcastcc(&voters_precentage), sizeof(voters_precentage));       // float - votes percentag
		//citizen list will be updated later on load, no need to keep them here	 //

		out.write(rcastcc(&reps_lentgh), sizeof(reps_lentgh));					 //int repsList length
		//reps conected list will be added later
		//for (int i = 0; i < reps_lentgh; i++)									 //for each reps, save
		//	RepsList[i].save(out);
	}

	void District::load(ifstream& in)
	{
		int len;
		in.read(rcastc(&len), sizeof(len));
		name = new char[len + 1];
		in.read(name, len);
		name[len] = '\0';
		in.read(rcastc(&distID), sizeof(distID));
		in.read(rcastc(&totalReps), sizeof(totalReps));
		in.read(rcastc(&voters_precentage), sizeof(voters_precentage));
		//citizenlist...
		in.read(rcastc(&reps_lentgh), sizeof(reps_lentgh));
		RepsList = new Representatives[reps_lentgh];
		//for (int i = 0; i < reps_lentgh; i++)									 
		//	RepsList[i].load(in);
	}
}