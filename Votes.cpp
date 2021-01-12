
#include"Votes.h"
#include <vector>



using namespace std;
namespace elc
{
	Votes::Votes(int _numOfParties, int _numOfDistricts) :
		numOfDistricts(_numOfDistricts), numOfParties(_numOfParties), after_calcs(false)
	{
		setVotes_table();
		setElectors_table();
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

	bool Votes::finishCalcs()
	{
		after_calcs = true;
		return true;
	}

	const bool Votes::isCalcsDone()
	{
		return after_calcs;
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

	const float& Votes::getPartyVotesPrecentageInDist(const int& PartyID, const int& distID) const
	{
		return ((100 * ((float)getPartyVotesInDist(PartyID, distID)) / getTotalVotesInDistrict(distID)));
	}

	const float& Votes::getTotalVotesPrecentage(const CitizensList& list)const
	{
		int i, citizens = list.getList().size();
		float totalVotes = 0;

		for (i = 0; i < numOfDistricts; i++)
		{
			totalVotes += getTotalVotesInDistrict(i);
		}

		return (100 * (totalVotes / citizens));

	}

	const float& Votes::getDistVotesPrecantage(const District& dist)const
	{
		int i, citizens = dist.GetDistCitizens().getList().size();
		float votes = getTotalVotesInDistrict(dist.getDistID());

		return (100 * (votes / citizens));
	}

	int** Votes::getPartiesWinningOrder()const
	{
		//double array keeping party id on 0, number of votes on 1, and number of electors in 2 
		int** order = new int*[numOfParties];
		int i, j, party_temp, votes_temp, electors_temp;

		//creating order array
		for (i = 0; i < numOfParties; i++)
			order[i] = new int[3];

		//initializing order array
		for (i = 0; i < numOfParties; i++)
		{
			order[i][0] = i;
			order[i][1] = getTotalPartyVotes(i);
			order[i][2] = getTotalPartyElectors(i);
		}

		//BubbleSort by electors
		for (i=0;i<numOfParties-1;i++)
			for (j = 0; j < numOfParties-i-1; j++)
			{
				if (order[j][2] > order[j+1][2])
				{
					//swap(i,j)
					party_temp = order[j][0];
					votes_temp = order[j][1];
					electors_temp = order[j][2];

					order[j][0] = order[j+1][0];
					order[j][1] = order[j+1][1];
					order[j][2] = order[j+1][2];

					order[j+1][0] = party_temp;
					order[j+1][1] = votes_temp;
					order[j+1][2] = electors_temp;
				}

			}
		return order;


	}

	void Votes::setElectorsInDist(PartyList& parties, District& dist)
	{
		int i, j, partyElectors, chosen_counter = 0, remaining;
		int totalVotes = getTotalVotesInDistrict(dist.getDistID());
		float partyPrecent, approxElectors, avg;
		const Senator* temp;

		for (i = 0; i < numOfParties; i++) //calculating rough estimate of electors for each party
		{
			partyPrecent = getPartyVotesPrecentageInDist(i, dist.getDistID());
			approxElectors = (partyPrecent / 100) * dist.getDistReps();
			partyElectors = (int)approxElectors;
			chosen_counter += partyElectors;

			electors[dist.getDistID()][i] = partyElectors;
		}

		remaining = dist.getDistReps() - chosen_counter;
		if (remaining > 0)
		{
			avg = static_cast<float>(remaining) / numOfParties;
			for (i = 0; i < numOfParties && remaining > 0; i++)
			{
				partyPrecent = getPartyVotesPrecentageInDist(i, dist.getDistID());
				approxElectors = (partyPrecent / 100) * dist.getDistReps();
				partyElectors = static_cast<int>(approxElectors);
				if (approxElectors - partyElectors >= avg)
				{
					partyElectors += 1;
					electors[dist.getDistID()][i]++;
					remaining--;
				}
			}

			for (i = 0; remaining > 0; i++)
			{
				electors[dist.getDistID()][i]++;
			}
		}

		for (i = 0; i < numOfParties; i++)
		{
			dist.setNumOfPartyReps(electors[dist.getDistID()][i], parties.getParty(i));
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

	const int Votes::getTotalPartyElectors(const int& partyID)const
	{
		int i, res=0;
		for (i = 0; i < numOfDistricts; i++)
		{
			res += electors[i][partyID];
		}
		return res;

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
	const int& Votes::getWinner(const DistrictsList& D_list) const
	{
		int i, j, max = 0, tempSum, winnerID = -1;
		int* counter = new int[numOfParties];
		const District* temp;

		for (i = 0; i < numOfParties; i++)
			counter[i] = 0; //intiating party-electors counter

		for (i = 0; i < numOfDistricts; i++)
		{
			temp = &D_list.getDistrict(i);
			if (typeid(*temp) == typeid(Divided)) //if distrcit is Divided
			{
				for (j = 0; j < numOfParties; j++) 
				{ //count for each party the number of electors they got
					counter[j] += electors[i][j];
				}
			}
			else //the district is not divided
			{
				//add all the electors is the district to the party that won in that district
				tempSum = 0;
				for (j = 0; j < numOfParties; j++)
					tempSum += electors[i][j];

				counter[getWinnerIDInDist(i)] += tempSum;
		
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
	/************************* Seralization *********************************/

	void Votes::save(ofstream& out) const
	{
		bool temp = false;
		out.write(rcastcc(&temp), sizeof(temp));
		out.write(rcastcc(&numOfParties), sizeof(numOfParties));
		out.write(rcastcc(&numOfDistricts), sizeof(numOfDistricts));
		int flag1,flag2; // 0 if electors && votetable are null ptr, else flag ==1

		if (electors == nullptr)
			flag1 = 0;
		else
			flag1 = 1;

		if (votes_table == nullptr)
			flag2 = 0;
		else
			flag2 = 1;

		out.write(rcastcc(&flag1), sizeof(flag1));
		out.write(rcastcc(&flag2), sizeof(flag2));

		if (flag1)
		{
			for (int i = 0; i < numOfDistricts; i++)
			{
				for (int j = 0; j < numOfParties; j++)
				{
					out.write(rcastcc(&electors[i][j]), sizeof(int));
				}
			}
		}

		if (flag2)
		{
			for (int i = 0; i < numOfDistricts; i++)
			{
				for (int j = 0; j < numOfParties; j++)
				{
					out.write(rcastcc(&votes_table[i][j]), sizeof(int));
				}
			}
		}
	}

	void Votes::load(ifstream& in)
	{
		int flag1, flag2; // 0 if electors && votetable are null ptr, else flag ==1
		
		in.read(rcastc(&after_calcs), sizeof(after_calcs));
		in.read(rcastc(&numOfParties), sizeof(numOfParties));
		in.read(rcastc(&numOfDistricts), sizeof(numOfDistricts));
		in.read(rcastc(&flag1), sizeof(flag1));
		in.read(rcastc(&flag2), sizeof(flag2));

		if (flag1 == 1)
		{
			electors = new int*[numOfDistricts];

			for (int i = 0; i < numOfDistricts; i++)
			{
				electors[i] = new int[numOfParties];
				for (int j = 0; j < numOfParties; j++)
				{
					in.read(rcastc(&electors[i][j]), sizeof(int));
				}
			}
		}

		if (flag2 ==1)
		{
			votes_table = new int* [numOfDistricts];
			for (int i = 0; i < numOfDistricts; i++)
			{
				votes_table[i] = new int[numOfParties];
				for (int j = 0; j < numOfParties; j++)
				{
					in.read(rcastc(&votes_table[i][j]), sizeof(int));
				}
			}
		}
	}

}