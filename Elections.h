#pragma once
#include "CitizenList.h"
#include "PartyList.h"
#include "DistrictsList.h"
#include "Votes.h"

using namespace std;


namespace elc {

	class Elections
	{
	private:
		char* date;
		PartyList parties;
		CitizensList citizens;
		DistrictsList districts;
		Votes voting;
	public:

		Elections() : date(nullptr) {};
		~Elections() { if (date != nullptr) delete[] date; };

		bool setDate(char* date);
		int getPartiesLength() const;
		int getCitizensLength() const;
		int getDistrictsLength() const;
		const char* getDate() { return date; }

		void printCitizens();
		void printParties();
		void printDistricts();

		void addCitizen(char *name, int id, int dist, int yob);
		void addParty(char *name, const Citizen& boss);
		void addDistrict(char* name, int num);

		const Party& getParty(const int& partyID) const { return parties.getParty(partyID); }
		const District& getDistrict(const int& distID) const { return districts.getDistrict(distID); }
		District& getDistrict(int distID, bool flag) { return districts.getDistrict(distID, flag); }
		void printDistrictsNameAndID() //new function
		{
			districts.PrintNameAndId();//need to pass to .cpp
		}
		void printPartiesNameAndID();

		/*********************************************/
		void addPartyCandidate(int id, int partyID, int distID);
		void addPartyCandidate(const Citizen& rep, int partyID, int distID);

		Citizen* findCitizen(int id);

		bool isPartiesEmpty() { return parties.isEmpty(); }

		void AddNewDistToParties(int);
		
		/*********************** voting proccess *******************************/

		bool isEnoughRepsInDist(const int& distID, const int& partyID);
	
		void StartVotingProccess();
		bool setVote(Citizen& voter, const int& partyID) { return voting.setVote(voter, partyID); }
		const Votes& getVotes() { return voting; }

		void setResults();
	};



}