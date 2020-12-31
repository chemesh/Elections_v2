
#include"Votes.h"

using namespace std;
namespace elc
{
	Votes::Votes(int _numOfParties, int _numOfDistricts) :
		numOfDistricts(_numOfDistricts), numOfParties(_numOfParties)
	{
		setVotes_table();
		setElectors_table();
		setElectors_table();
		setVotes_table();
	}

	Votes::~Votes()
	{
		int i;

		if (votes_table != nullptr)
		{
			for (i = 0; i < numOfDistricts; i++)
			{
				delete[] votes_table[i];
			}
			delete[] votes_table;
		}
		if (electors != nullptr)
		{
			for (i = 0; i < numOfDistricts; i++)
			{
				delete[] electors[i];
			}
			delete[] electors;
		}

	}

	bool Votes::setnumOfParties(const int& num)
	{
		this->numOfParties = num;
		return true;
	}

	bool Votes::setnumOfDistricts(const int& num)
	{
		this->numOfDistricts = num;
		return true;
	}

	bool Votes::setVotes_table()
	{
		int i, j;

		votes_table = new int* [numOfDistricts];
		for (i = 0; i < numOfDistricts; i++)
		{
			votes_table[i] = new int[numOfParties];

			for (j = 0; j < numOfParties; j++)
			{
				votes_table[i][j] = 0;
			}
		}
		return true;
	}

	bool Votes::setElectors_table()
	{
		int i, j;

		electors = new int* [numOfDistricts];
		for (i = 0; i < numOfDistricts; i++)
		{
			electors[i] = new int[numOfParties];

			for (j = 0; j < numOfParties; j++)
			{
				electors[i][j] = 0;
			}
		}
		return true;
	}

	bool Votes::setVote(Citizen& voter, int PartyID)
	{
		votes_table[voter.getDistrict().getDistID()][PartyID]++;
		voter.setVote(true);
		return true;
	}

	const int& Votes::getnumOfParties()
	{
		return numOfParties;
	}

	const int& Votes::getnumOfDistricts()
	{
		return numOfDistricts;
	}

	const int Votes::getTotalPartyVotes(const int& partyID) const
	{
		int i, sum = 0;

		for (i = 0; i < numOfDistricts; i++)
		{
			sum += votes_table[i][partyID];
		}
		return sum;
	}

	const int Votes::getTotalVotesInDistrict(const int& DistID) const
	{
		int i, sum = 0;

		for (i = 0; i < numOfParties; i++)
		{
			//check if += or =+
			sum += votes_table[DistID][i];
		}
		return sum;
	}

	const int Votes::getPartyVotesInDist(const int& PartyID, const int& distID) const
	{
		return votes_table[distID][PartyID];
	}

	const float Votes::getPartyVotesPrecentageInDist(const int& PartyID, const int& distID) const
	{
		return ((100 * ((float)getPartyVotesInDist(PartyID, distID)) / getTotalVotesInDistrict(distID)));
	}

	void Votes::setElectorsInDist(PartyList& parties, District& dist)
	{
		int i, j, partyElectors, totalVotes = getTotalVotesInDistrict(dist.getDistID());
		float partyPrecent, approxElectors, avg = (float)dist.getDistReps() / numOfParties;
		const Senator* temp;

		for (i = 0; i < numOfParties; i++)
		{
			partyPrecent = getPartyVotesPrecentageInDist(i, dist.getDistID());
			approxElectors = (partyPrecent / 100) * dist.getDistReps();
			partyElectors = (int)approxElectors;
			if (approxElectors - partyElectors >= avg)
				partyElectors += 1;

			electors[dist.getDistID()][i] = partyElectors;
		}

		for (i = 0; i < numOfParties; i++)
		{
			temp = parties.getParty(i).getElectorListInDist(dist.getDistID());
			for (j = 0; j < electors[dist.getDistID()][i]; j++)
			{

				dist.setSenatorInDistReps(temp, parties.getParty(i).getPartyNumber());
				temp = temp->getNext();
			}
		}

	}

	const int Votes::getElectorsforPartyInDist(const int& partyID, const int& distID) const
	{
		return electors[distID][partyID];
	}

	const int Votes::getWinnerIDInDist(const int& distID) const
	{
		//-1 is for sanity check
		int i, max = 0, winningPartyID = -1;

		for (i = 0; i < numOfParties; i++)
		{
			if (votes_table[distID][i] > max)
			{
				winningPartyID = i;
				max = votes_table[distID][i];
			}
		}
		return winningPartyID;
	}

	/************************* added *********************************/
	const int Votes::getWinnerIDInDist(District* const dist) const
	{
		District* temp = dist;
		int i, max = 0, winningPartyID = -1;

		if (typeid(dist) == typeid(Divided))
		{
			for (i = 0; i < numOfParties; i++)
			{
				if (max < electors[temp->getDistID()][i])
				{
					winningPartyID = i;
					max = electors[temp->getDistID()][i];
				}
			}
		}

		else
		{
			for (i = 0; i < numOfParties; i++)
			{
				if (votes_table[dist->getDistID()][i] > max)
				{
					winningPartyID = i;
					max = votes_table[dist->getDistID()][i];
				}
			}
		}
		return winningPartyID;

	}
	/************************* added *********************************/

	const int Votes::getWinner() const
	{
		int i, j, max = 0, tempSum, winnerID = -1;
		int* counter = new int[numOfParties];
		for (i = 0; i < numOfParties; i++)
			counter[i] = 0;

		//calclulates the number of electors the winning party get in each district
		for (i = 0; i < numOfDistricts; i++)
		{
			tempSum = 0;
			for (j = 0; j < numOfParties; j++)
				tempSum += electors[i][j];

			counter[getWinnerIDInDist(i)] += tempSum;
		}

		//checks which party has the most electors
		for (i = 0; i < numOfParties; i++)
		{
			if (counter[i] > max)
			{
				max = counter[i];
				winnerID = i;
			}
		}
		delete[] counter;
		return winnerID;

	}


	/************************* added *********************************/
	const int Votes::getWinner(const DistrictsList& D_list) const
	{
		int i, j, max = 0, tempSum, winnerID = -1;
		int* counter = new int[numOfParties];
		const District* temp;

		for (i = 0; i < numOfParties; i++)
			counter[i] = 0; //intiating party-electors counter

		for (i = 0; i < numOfDistricts; i++)
		{
			temp = &D_list.getDistrict(i);
			if (typeid(temp) == typeid(Divided)) //if distrcit is Divided
			{
				for (j = 0; j < numOfParties; j++) 
				{ //count for each party the number of electors they got
					counter[j] += electors[i][j];
				}
			}
			else //the district is not divided
			{
				for (i = 0; i < numOfDistricts; i++)
				{ //add all the electors is the district to the party that won in that district
					tempSum = 0;
					for (j = 0; j < numOfParties; j++)
						tempSum += electors[i][j];

					counter[getWinnerIDInDist(i)] += tempSum;
				}
			}
		}
		//checks which party has the most electors
		for (i = 0; i < numOfParties; i++)
		{
			if (counter[i] > max)
			{
				max = counter[i];
				winnerID = i;
			}
		}
		delete[] counter;
		return winnerID;

	}
	/************************* added *********************************/










}