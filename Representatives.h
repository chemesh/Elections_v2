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

		Representatives() : Representatives(0){}
		Representatives(const int& num) : PartyID(0), head(nullptr), tail(nullptr), NumOfReps(num) {}
		~Representatives()	{ makeEmpty(); 	}

		void makeEmpty(void);
		int getPartyID() const   {return PartyID; };
		bool setPartyID(int dist);
		bool setNumOfReps(const int& num) { NumOfReps = num; return true; }

		bool addSenator(const Citizen& rep);
		bool addSenator(const Senator&);

		void printsenatorsList(int num) const;


	};



	
}