#pragma once
#include <fstream>
#include "CitizenList.h"
#include "PartyList.h"
#include "DistrictsList.h"
#include "Votes.h"

using namespace std;



namespace elc {

	class Elections
	{
	private:
		int roundType; // 0 = normal, 1 = simple
		char* date;
		PartyList parties;
		CitizensList citizens;
		DistrictsList districts;
		Votes voting;
	public:

		Elections() : date(nullptr), roundType(0) {};
		~Elections() { cout << "elec dtor" << endl; if (date != nullptr) delete[] date; };



		int getPartiesLength() const { return parties.getLength(); }
		int getCitizensLength() const { return citizens.getLength(); }
		int getDistrictsLength() const { return districts.getLength(); }


		const char* getDate() const { return date; }
		const int& getRoundType() const { return roundType;  }

		const Party& getParty(const int& partyID) const { return parties.getParty(partyID); }
		const District& getDistrict(const int& distID) { return districts.getDistrict(distID); }
		District& getDistrict(int distID, bool flag) { return districts.getDistrict(distID, flag); }

		const DistrictsList& getDistList() const { return districts; }
    
		bool setDate(char* date);
		bool setRoundType(int _type);


		void addCitizen(const char* name, int id, const District& dist, int yob);
		void addParty(char* name, const Citizen& boss);
		void addDistrict(char* name, int num, bool div);
		void addPartyCandidate(int id, int partyID, int distID);
		void addPartyCandidate(const Citizen& rep, int partyID, int distID);

		//versions for simple round
		//void addCitizen(const char* name, int id, int yob);

		void AddNewDistToParties(int);
		Citizen* findCitizen(int id);
		bool isPartiesEmpty() { return parties.isEmpty(); }
		
		void printCitizens();
		void printParties();
		void printDistricts();
		void printDistrictsNameAndID(); 
		void printPartiesNameAndID();


		/*********************** voting proccess *******************************/

		bool isEnoughRepsInDist(const int& distID, const int& partyID);

		void StartVotingProccess();
		bool setVote(Citizen& voter, const int& partyID) { return voting.setVote(voter, partyID); }
		const Votes& getVotes() { return voting; }

		void setResults();

		/**************************serialiazion***************************/
		void save(ostream& out) const;

	};



}