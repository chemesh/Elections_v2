#pragma once
#include <iostream>
#include "District.h"

namespace elc {
	class Citizen {
	private:
		char* name;
		int ID;
		int YOB;
		District dist;
		bool hasVoted;

	public:

		Citizen() : name(nullptr), ID(0), YOB(0), hasVoted(false) {}
		Citizen(char* name, int id, const District& _dist, int year)
			: ID(id), dist(_dist), YOB(year), hasVoted(false)
		{
			setName(name);
		}
		Citizen(const Citizen& other);

		~Citizen();

		const char* getName() const;
		int getID() const;
		const District& getDistrict() const;
		int getYOB() const;
		bool getVote() const { return hasVoted; }

		bool setName(const char* n);
		bool setID(int id);
		bool setDistrict(const District& _dist);
		bool setYOB(int year);
		bool setCitizen(const char* name, int id, const District& dist, int year);
		bool setVote(bool val) { hasVoted = val; return true; }

		friend std::ostream& operator<<(std::ostream& out, const Citizen& other)
		{
			std::cout
				<< "name: " << other.name << " , "
				<< "ID: " << other.ID << " , "
				<< "born in: " << other.YOB << " , "
				<< "district :" << other.dist.getDistName() << '\n';
			return out;
		}

		void operator=(const Citizen&);
	};



};

