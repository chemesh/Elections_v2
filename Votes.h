#pragma once

#include <iostream>
#include <typeinfo>
#include "CitizenList.h"
#include "PartyList.h"
#include "DistrictsList.h"



using namespace std;
namespace elc
{
	class Votes
	{
	private:
		bool after_calcs;
		//holds in each cell the number of votes
		int** votes_table;

		//holds in each cell the number of electors from each party
		//in every district
		int** electors;

		int numOfParties;
		int numOfDistricts;

		//table[districts][parties]

	public:
		Votes() :votes_table(nullptr), electors(nullptr), numOfDistricts(0), numOfParties(0),after_calcs(false) {}
		Votes(int _numOfParties, int _numOfDistricts);
		~Votes();

		bool setnumOfParties(const int& num);
		bool setnumOfDistricts(const int& num);
		bool setVotes_table();
		bool setElectors_table();
		bool setVote(Citizen&, int PartyID);
		bool finishCalcs();

		const bool isCalcsDone();
		const int& getnumOfParties();
		const int& getnumOfDistricts();
		const int getTotalPartyVotes(const int& partyID)const;
		const int getTotalVotesInDistrict(const int& DistID)const;
		const int getPartyVotesInDist(const int& PartyID, const int& distID)const;
		const float& getPartyVotesPrecentageInDist(const int& PartyID, const int& distID)const;
		const float& getTotalVotesPrecentage(const CitizensList& list)const;
		const float& getDistVotesPrecantage(const District& dist)const;
		int** getPartiesWinningOrder()const;

		//calculates the number of electors won for each Party in the district,
		//then adds the newly chosen senators under their party ID to the district representatives.
		void setElectorsInDist(PartyList& parties, District& dist);
		const int getElectorsforPartyInDist(const int& partyID, const int& distID) const;
		const int getTotalPartyElectors(const int& partyID)const;
		const int getWinnerIDInDist(const int& distID) const;
		const int getWinnerIDInDist(District* const dist) const;
		const int getWinner() const;
		const int& getWinner(const DistrictsList& D_list) const;

		void save(ofstream& out) const;
		void load(ifstream& in);

	};






}