/*


#pragma once
#include <iostream>
#include "Party.h"
#include "Citizen.h"


using namespace std;
namespace elc {

	class CitizensList; //foward declaration
	class Citizen;

	class Senator {
	private:
		Senator* next = nullptr;
	public:
		Citizen candidate;
		Senator() : next(nullptr) {}
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
		void load(ifstream& in, const elc::CitizensList& _list);

	};

}

*/
