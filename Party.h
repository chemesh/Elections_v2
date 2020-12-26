#pragma once

#include <iostream>
#include "Citizen.h"

//party - candidate, list of electors,
//-add citizen as representitive(CIN of id, num of party, name of district)
using namespace std;
namespace elc {

class Senator {
	private:
		Citizen candidate;
		Senator* next;
	public:
		Senator(const Citizen& _rep) :candidate(_rep), next(nullptr) {};
		~Senator() {};

		const Citizen& getId() const;
		Senator* getNext() const;
		bool setCandidate(const Citizen&);
		const Citizen& getCandidate() const;
		bool setNext(Senator* next);
};

	//each class of elector, represent the list of representives of the party, for the district.
	class Elector { 

	private:
		int districtId;
		Senator* head;
		Senator* tail;
		int numOfSenators; //every time a senator is added, increase by 1;

	public:

		Elector() : districtId(NULL), head(nullptr), tail(nullptr), numOfSenators(0) {};
		//~Elector() 
		//{
		//	makeEmpty();
		//};

		void makeEmpty(void);
		int getDistrict() const;
		bool setdistrictId(int dist);
		//bool setNumOfSenators(int num);
		int getNumOfSenators() const { return numOfSenators; }

		bool addSenator(const Citizen& rep); //addTotail
		const Senator& getSenator(int place);
		
		void printElector()
		{
			Senator* temp = head;
			while (temp != nullptr)
			{
				cout << temp->getCandidate();
				temp = temp->getNext();
			}
		}

		friend std::ostream& operator<<(std::ostream& out, Elector& other)
		{
			cout
				<< "Electors from district ID: " << other.districtId << ":" << endl;
			other.printElector();
			return out;
		}
	};

	class Party {
	private:
		int partyNumber;
		char* partyName;
		Citizen boss; //citizen&
		Elector* electors; //each node of the arrays represents one district, with a list of the party electors
		int elec_size; 
		int elec_length; //logi
		static int numberOfParty;

	public:
		
		Party() : Party(nullptr,0){}
		Party(char* _partyName, int numOfDistricts = 0) :
			partyName(_partyName), elec_size(numOfDistricts + 1), elec_length(numOfDistricts), partyNumber(numberOfParty)
		{
			createElectorsList(elec_size);
			numberOfParty++;
		}
		Party(char* _partyName, const Citizen& _boss, int numOfDistricts=0)
			: partyName(_partyName), elec_size(numOfDistricts + 1), elec_length(numOfDistricts), partyNumber(numberOfParty), boss(_boss)
		{
			createElectorsList(elec_size);
			numberOfParty++;
		}

		~Party()
		{
			if(electors != nullptr)
				delete[] electors;
			if (partyName != nullptr)
				delete[] partyName;
		}

		char* getPartyName() const;
		const Citizen& getBossID() const;
		int getPartyNumber() const;
		const Senator& getSenatorInDist(int distID, int place);

		bool setPartyName(char* _n);
		bool setBoss(const Citizen& boss);
		bool setPartyNumber(int n);
		//why?
		bool setElectors(Elector* e);
		//
		bool setParty(char *partyName, const Citizen& boss, int n, Elector* e, int el_size, int el_len);
		bool setParty(char* partyName, const Citizen& boss, int numOfDistricts);
		bool setParty(char *partyName, const Citizen& boss);
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

		 void printElectors()
		{
			for (int i = 0; i < elec_length; i++)
				cout << electors[i];
		}
		friend std::ostream& operator<<(std::ostream& out, Party& other)
		{
			cout
				<< "Party name: " << other.partyName << " | "
				<< "party number: " << other.partyNumber << " | "
				<< "Party boss-> " << other.boss;
			other.printElectors();
			return out;
		}

		void printNameAndId() const //new function
		{
			std::cout << "(" << this->partyNumber << " - " << this->partyName << ")";
		}

		void operator=(const Party&);
	};

};

