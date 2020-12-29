#pragma once

#include <iostream>
#include "CitizenList.h"
#include "PartyList.h"
#include "DistrictsList.h"


using namespace std;
namespace elc
{
	class Votes
	{
	private:
		//holds in each cell the number of votes
		int** votes_table;

		//holds in each cell the number of electors from each party
		//in every district
		int** electors;

		int numOfParties;
		int numOfDistricts;

		//table[districts][parties]

	public:
		Votes() :votes_table(nullptr), electors(nullptr), numOfDistricts(0), numOfParties(0) {}
		Votes(int _numOfParties, int _numOfDistricts);
		~Votes();

		bool setnumOfParties(const int& num);
		bool setnumOfDistricts(const int& num);
		bool setVotes_table();
		bool setElectors_table();
		bool setVote(Citizen&, int PartyID);


		const int& getnumOfParties();
		const int& getnumOfDistricts();
		const int getTotalPartyVotes(const int& partyID)const;
		const int getTotalVotesInDistrict(const int& DistID)const;
		const int getPartyVotesInDist(const int& PartyID, const int& distID)const;
		const float getPartyVotesPrecentageInDist(const int& PartyID, const int& distID)const;

		//calculates the number of electors won for each Party in the district,
		//then adds the newly chosen senators under their party ID to the district representatives.
		void setElectorsInDist(PartyList& parties, District& dist);
		const int getElectorsforPartyInDist(const int& partyID, const int& distID) const;
		const int getWinnerIDInDist(const int& distID) const;
		const int getWinner() const;


	};






}