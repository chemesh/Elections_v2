#pragma once
#include <iostream>
#include "Party.h"

using namespace std;
namespace elc {

	class Representatives
	{
	private:
		int PartyID;
		Senator* head;
		Senator* tail;
		int NumOfReps;

	public:

		Representatives() :PartyID(0), head(nullptr),
			tail(nullptr), NumOfReps(0) {}
		~Representatives()
		{
			cout << "reps dtor" << endl;
			makeEmpty();
		}

		void makeEmpty(void);
		int getPartyID() const;
		bool setPartyID(int dist);
		bool setNumOfReps(const int& num) { NumOfReps = num; return true; }
		const Senator& getSenator(int id);

		bool addSenator(const Citizen& rep);
		bool addSenator(const Senator&);

		void printsenatorsList(int num) const
		{
			Senator* temp = head;
			for (int i = 0; i < num; i++)
			{
				cout << temp->getCandidate().getName() << endl;
				temp = temp->getNext();
			}
		}




	};




}