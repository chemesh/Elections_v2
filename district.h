#pragma once
#include <iostream>
#include "CitizenList.h"
#include "Representatives.h"



using namespace std;

namespace elc
{
	class District
	{
	protected:
		string name;
		int distID;
		int totalReps; //Total number of representatives in the district
		float voters_precentage;
		CitizensList citizens;
		Representatives* RepsList;
		int reps_size;
		int reps_lentgh;


	public:

		District() : distID(0), totalReps(0),
			citizens(), RepsList(nullptr), reps_size(1), reps_lentgh(0), voters_precentage(0)
		{
			RepsList = new Representatives[reps_size];
			RepsList[0].setPartyID(0);
		};

		District(string _name, int _numOfReps) : distID(0), totalReps(_numOfReps),
			citizens(), RepsList(nullptr), reps_size(1), reps_lentgh(0), voters_precentage(0)
		{
			setDistName(_name);
			RepsList = new Representatives[reps_size];
			RepsList[0].setPartyID(0);
		};

		District(const District&);

		virtual ~District() {
			if (RepsList != nullptr)
				delete[] RepsList;
		}

		bool  setDistName(const string _n) { name = _n; return true; };
		bool setDistID(const int&);
		bool setDistCitizenInList(const Citizen&);
		bool setVoters(int& allCitizens);
		bool setCongressManInList(const Senator&);
		bool setDistReps(const int&);
		bool setVotersPersentage(const float&);
		bool setCitizenList(const CitizensList& citizens);
		bool setRepsList(Representatives* reps);
		bool initRepsList(const int& size, Party* list);
		bool setNumOfPartyReps(const int& num, const Party& _party);
		bool setSenatorInDistReps(const Senator*, int partyID);

		bool setDistrict(const std::string, int);
		bool setDistrict(const std::string _name, int id, int numOfReps, float voterPer, const CitizensList& cList, Representatives* rList);

		bool setRepsSize(const int&);
		bool setRepsLength(const int&);

		int getRepsSize() const;
		int getRepsLength() const;

		const string getDistName() const;
		const int& getDistID() const;
		const CitizensList& GetDistCitizens() const;
		const float& getVoters() const;
		const Representatives& getRepsFromParty(const int partyID) const { return RepsList[partyID]; }

		int getDistReps() const;

		bool isRepListFull(void) { return (reps_size == reps_lentgh); }
		bool addNewPartyReps(Party _newParty, int numOfReps);

		friend std::ostream& operator<<(std::ostream& out, const District& other);


		void printNameAndId() //new function
		{
			cout << "(" << this->distID << " - " << this->name << ")";
		}

		void operator=(const District&);
		bool isDivided();

		void save(ofstream& out) const;
		void load(ifstream& in);
	};



	class Divided : public District
	{
	private:

	public:
		Divided() : District() {}
		Divided(string _name, int _numOfReps) : District(_name, _numOfReps) {}
		Divided(const Divided& o) : District(o){}
		virtual ~Divided() {};

		const Divided& operator=(const Divided& o)
		{
			District::operator=(o);
			return *this;
		}

	};
}