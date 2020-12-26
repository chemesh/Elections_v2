#pragma once
#include <iostream>

namespace elc {
	class Citizen {
	private:
		char *name;
		int ID;
		int YOB;
		int districtId;
		bool hasVoted;

	public:
		
		Citizen() : name(nullptr), ID(0), districtId(0), YOB(0), hasVoted(false){}
		Citizen(char* name, int id, int dist, int year)
			: ID(id), districtId(dist), YOB(year), hasVoted(false)
		{
			setName(name);
		}

		~Citizen();
				
		char* getName() const;
		int getID() const;
		int getDistrict() const;
		int getYOB() const;
		bool getVote() const { return hasVoted; }

		bool setName(char* n);
		bool setID(int id);
		bool setDistrict(int dist);
		bool setYOB(int year);
		bool setCitizen(char* name, int id, int dist, int year);
		bool setVote(bool val) { hasVoted = val; return true; }

		friend std::ostream& operator<<(std::ostream& out, const Citizen& other)
		{
			std::cout
				<< "name: " << other.name 	<< " , " 
				<< "ID: " << other.ID		<< " , " 
				<< "born in: " << other.YOB << " , " 
				<< "district :" << other.districtId << '\n';
			return out;
		}

		void operator=(const Citizen&);
	};



};

