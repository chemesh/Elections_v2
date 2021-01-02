#include "Elections.h"
#include <iostream>

using namespace std;
namespace elc {

	bool Elections::setDate(char* _date)
	{
		int size = strlen(_date);
		if (date != nullptr)
			delete[] date;

		date = new char[size + 1];
		memcpy(date, _date, sizeof(char) * size);
		date[size] = '\0';
		return true;
	}

	bool Elections::setRoundType(int _type) { return this->roundType = _type; }

	void Elections::addCitizen(const char* name, int id, const District& dist, int yob)
	{
		citizens.setCitizen(name, id, yob, dist);
		districts.setCitizenInDist(*citizens.getCitizen(id), dist);
	}
	void Elections::addParty(char* name, const Citizen& boss)
	{
		parties.setParty(name, boss, districts.getLength());
	}
	void Elections::addDistrict(char* name, int num)
	{
		districts.setDistrict(name, num);
	}

	void Elections::addPartyCandidate(int id, int partyID, int distID)
	{
		Citizen* temp = citizens.getCitizen(id);
		parties.addRepInParty(*temp, partyID, distID);
	}
	void Elections::addPartyCandidate(const Citizen& rep, int partyID, int distID)
	{
		parties.addRepInParty(rep, partyID, distID);
	}

	void Elections::AddNewDistToParties(int distID)
	{
		parties.AddNewDistToParties(distID);
	}

	Citizen* Elections::findCitizen(int id)
	{
		citizens.CitizenSort();
		return (citizens.getCitizen(id));
		//if ID doesn't exist in the database,
		//the return value will be nullptr
	}


	void Elections::printCitizens() { cout << citizens; }
	void Elections::printParties() { cout << parties; }
	void Elections::printDistricts() { cout << districts; }
	void Elections::printPartiesNameAndID()
	{
		parties.PrintNameAndId();
	}
	void Elections::printDistrictsNameAndID() 
	{
		districts.PrintNameAndId();//need to pass to .cpp
	}

	/*********************** voting proccess *******************************/

	bool Elections::isEnoughRepsInDist(const int& distID, const int& partyID)
	{
		return (parties.getParty(partyID).getElectorInDist(distID).getNumOfSenators() > districts.getTotalRepsInDist(distID));
	}

	void Elections::StartVotingProccess()
	{
		voting.setnumOfDistricts(districts.getLength());
		voting.setnumOfParties(parties.getLength());

		voting.setVotes_table();
		voting.setElectors_table();
	}

	void Elections::setResults()
	{
		bool flag = true;
		for (int i = 0; i < getDistrictsLength(); i++)
		{
			districts.getDistrict(i, flag).initRepsList(parties.getLength(), parties.getPartyList());
			voting.setElectorsInDist(parties, getDistrict(i, flag));
		}
}

	/**************************serialiazion***************************/
		void Elections::save(ostream& out) const
		{
			int len = strlen(date);
			out.write(rcastcc(&len), sizeof(len));
			out.write(rcastc(date), sizeof(len));
			parties.save(out);
		}
	}