#pragma once
#include <fstream>


#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elc {

	class District;
	class DistrictsList;


	class Citizen {
	private:
		std::string name;
		int ID;
		int YOB;
		const District* dist;
		bool hasVoted;

	public:

		Citizen() :  ID(0), YOB(0), hasVoted(false), dist(nullptr) {}
		Citizen(std::string name, int id, const District& _dist, int year)
			: ID(id), dist(&_dist), YOB(year), hasVoted(false)
		{
			setName(name);
		}
		Citizen(const Citizen& other);

		~Citizen() {};

		std::string getName() const;
		int getID() const;
		int getYOB() const;
		const District& getDistrict()const;
		bool getVote() const { return hasVoted; }
		//bool setName(const char* n);
		bool setName(const std::string n) { name = n; return true; };
		bool setID(int id);
		bool setDistrict(const District& _dist);
		bool setYOB(int year);
		bool setCitizen(const std::string name, int id, const District& dist, int year);
		bool setVote(bool val) { hasVoted = val; return true; }

		friend std::ostream& operator<<(std::ostream& out, const Citizen& other);

		void operator=(const Citizen&);

		void save(std::ofstream& out) const;
		void load(std::ifstream& in, const DistrictsList& _list);
	};
};

