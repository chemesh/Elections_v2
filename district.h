#pragma once
#include <iostream>
#include "CitizenList.h"
#include "Representatives.h"

using namespace std;

namespace elc
{
	class District
	{
	private:
		char* name;
		int distID;
		int totalReps; //Total number of representatives in the district
		float voters_precentage;
		CitizensList citizens;
		Representatives* RepsList;
		int reps_size;
		int reps_lentgh;
		//need array hnadling
		//static int numberOfDistrict;


	public:

		District() : name(nullptr), distID(0), totalReps(0),
			citizens(), RepsList(nullptr), reps_size(1), reps_lentgh(0), voters_precentage(0)
		{
			RepsList = new Representatives[reps_size];
			RepsList[0].setPartyID(0);
			cout << "district ctor v1" << endl;
		};



		District(char* _name, int _numOfReps) : name(_name), distID(0), totalReps(_numOfReps),
			citizens(), RepsList(nullptr), reps_size(1), reps_lentgh(0), voters_precentage(0)
		{
			RepsList = new Representatives[reps_size];
			RepsList[0].setPartyID(0);
			cout << "district ctor v2";
			//numberOfDistrict++;
		};
		~District() { 
			if (RepsList != nullptr)
				delete[] RepsList; 
			if (name != nullptr)
				delete[] name; 
		}


		bool setDistName(const char*);
		bool setDistID(const int&);
		bool setDistCitizenInList(const Citizen& );
		bool setVoters(int& allCitizens);
		bool setCongressManInList(const Senator&);
		bool setDistReps(const int&);
		bool setVotersPersentage(const float&);
		bool setCitizenList(const CitizensList& citizens);
		bool setRepsList(Representatives* reps);
		bool setSenatorInDistReps(const Senator*, int partyID);

		bool setDistrict(const char*, int);
		bool setDistrict(const char* _name, int id, int numOfReps, float voterPer, const CitizensList& cList, Representatives* rList);

		bool setRepsSize(const int&);
		bool setRepsLength(const int&);

		int getRepsSize() const;
		int getRepsLength() const;

		const char* getDistName() const;
		const int& getDistID() const;
		const CitizensList& GetDistCitizens() const;
		const float& getVoters() const;
		const Representatives getRepsFromParty(const int partyID) const { return RepsList[partyID]; }
		//const Elector& getCongressMen() const;
		int getDistReps() const;

		

		bool isRepListFull(void) { return (reps_size == reps_lentgh); }
		bool addNewPartyReps(Party _newParty, int numOfReps);

		friend std::ostream& operator<<(std::ostream& out, const District& other)
		{
			std::cout
				<< "district number: " << other.distID << " , "
				<< "name: " << other.name << " , "
				<< "number of Representatives: " << other.totalReps << ".";
			return out;

		}

		void printNameAndId() //new function
		{
			cout << "(" << this->distID << " - " << this->name << ")";
		}

		void operator=(const District&);
	};
	
}