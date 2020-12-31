#pragma once
#include <iostream>

namespace elc {

	class District;


	class Citizen {
	private:
		char* name;
		int ID;
		int YOB;
		const District* dist;
		bool hasVoted;

	public:

		Citizen() : name(nullptr), ID(0), YOB(0), hasVoted(false), dist(nullptr) {}
		Citizen(char* name, int id, const District& _dist, int year)
			: ID(id), dist(&_dist), YOB(year), hasVoted(false)
		{
			setName(name);
		}
		Citizen(const Citizen& other);

		~Citizen();

		const char* getName() const;
		int getID() const;
		int getYOB() const;
		const District& getDistrict()const;
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
				<< "district :" << (other.dist) << ".";
			//bug related to foward decleration, 
			//cant ask district to use getter because he dosn"T reconize them
			return out;
		}

		void operator=(const Citizen&);
	};



};

