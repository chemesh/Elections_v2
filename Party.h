#pragma once

#include <iostream>
#include "Citizen.h"

using namespace std;
namespace elc {

	class CitizensList; //foward declaration

	class Senator {
	private:
		Senator* next = nullptr;
	public:
		Citizen candidate;
		Senator(): next(nullptr){}
		Senator(const Citizen& _rep) :candidate(_rep), next(nullptr) {};
		~Senator() {};

		const Citizen& getId() const;
		Senator* getNext() const;
		bool setCandidate(const Citizen&);
		const Citizen& getCandidate() const;
		bool setNext(Senator* next);
	};


	//========================================================================================================
	//========================================================================================================
	//each class of elector, represent the list of representives of the party, for the district.
	class Elector { 

	private:
		int districtId;
		Senator* head;
		Senator* tail;
		int numOfSenators; //every time a senator is added, increase by 1;

	public:

		Elector() : districtId(NULL), head(nullptr), tail(nullptr), numOfSenators(0) {};

		void makeEmpty(void);
		int getDistrict() const;
		bool setdistrictId(int dist);
		int getNumOfSenators() const { return numOfSenators; }

		bool addSenator(const Citizen& rep); //addTotail
		const Senator& getSenator(int place);

		void printElector();

		friend std::ostream& operator<<(std::ostream& out, Elector& other);

		void save(ofstream& out) const;
		void load(ifstream& in, const CitizensList& _list);

	};


	//========================================================================================================
	//========================================================================================================
	class Party {
	private:
		int partyNumber;
		string partyName;
		Citizen boss; //citizen&
		Elector* electors; //each node of the arrays represents one district, with a list of the party electors
		int elec_size;
		int elec_length; //logi
		static int numberOfParty;

	public:

		Party() : Party("", 0) {}
		Party(string _partyName, int numOfDistricts = 0) :
			partyName(_partyName), elec_size(numOfDistricts + 1), elec_length(numOfDistricts), partyNumber(numberOfParty)
		{
			createElectorsList(elec_size);
			numberOfParty++;
		}
		Party(string _partyName, const Citizen& _boss, int numOfDistricts = 0)
			: partyName(_partyName), elec_size(numOfDistricts + 1), elec_length(numOfDistricts), partyNumber(numberOfParty), boss(_boss)
		{
			createElectorsList(elec_size);
			numberOfParty++;
		}

		~Party()
		{
			if (electors != nullptr)
				delete[] electors;
		}

		string getPartyName() const;
		const Citizen& getBossID() const;
		int getPartyNumber() const;
		const Senator& getSenatorInDist(int distID, int place);

		bool setPartyName(string _n) { partyName = _n; return true; };
		bool setBoss(const Citizen& boss);
		bool setPartyNumber(int n);
		
		bool setElectors(Elector* e);
		
		bool setParty(string partyName, const Citizen& boss, int n, Elector* e, int el_size, int el_len);

		bool setParty(string partyName, const Citizen& boss);
		bool createElectorsList(int numOfDistricts);
		bool addSenator(int numOfDistrict, const Citizen& rep);

		bool setElectorsSize(const int&);
		bool setElectorsLength(const int&);

		int getElectorsSize() const;
		int getElectorsLength() const;
		const Elector& getElectorInDist(const int& distID) const { return electors[distID]; }
		const Senator* getElectorListInDist(const int& distID);

		bool isElectorsFull(void) { return (elec_size == elec_length); }
		bool AddNewDistElector(int distID);

		void printElectors();

		friend std::ostream& operator<<(std::ostream& out, Party& other);

		void printNameAndId() const;

		void operator=(const Party&);

		void save(ofstream& out) const;
		void load(ifstream& in, const CitizensList& _list);

	};

};

