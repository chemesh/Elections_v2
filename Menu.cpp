#include <iostream>
#include "Elections.h"

using namespace std;
using namespace elc;

#define MAX_SIZE 50


void mainMenu(Elections& e);

void inputScreenPage1();
void inputScreenPage2();

void save(Elections& e);

void addDistric(Elections& e);
void addCitizen(Elections& e);
void addParty(Elections& e);
void addPartyCandidates(Elections& e);

void results(Elections& e);
void openVotingMenu(Elections& e, bool& doneVoting);
bool handleErrors(int ctrl, Elections& e);

void inputScreenPage1()
{
	std::cout << "-----intput screen-----" << endl;
	std::cout
		<< " 1 - Create new election round. " << endl
		<< " 2 - Load Existing election round from file." << endl
		<< " 3 - Exit program." << endl
		<< "waiting for input..." << endl;
}
void inputScreenPage2()
{
	std::cout << "-----intput screen-----" << endl;
	std::cout << "what would you like to add? " << endl
		<< " 1 - Add District. " << endl
		<< " 2 - Add Citizen." << endl
		<< " 3 - Add Party." << endl
		<< " 4 - Add representitive for a party. " << endl
		<< " 5 - print ALL districts." << endl
		<< " 6 - print ALL citizens." << endl
		<< " 7 - print ALL parties." << endl
		<< " 8 - VOTE!! (inputs will no longer be avilable)" << endl
		<< " 9 - show results (not working)." << endl
		<< " 10 - exit this menu" << endl
		<< " 11 - Save Elections Round" << endl
		<< " 12 - Load Elections Round" << endl
		<< "waiting for input..." << endl;
}

void openingMenu(Elections& e)
{
	int ctrl;
	inputScreenPage1();
	cin >> ctrl;

	while (ctrl < 1 || ctrl>10) //handle inputs
	{
		std::cout << "wrong input!!" << endl;
		cin >> ctrl;
	}
	switch (ctrl)
	{
	case 1: { system("CLS");  mainMenu(e); break; }
	case 2: { std::cout << "loading file.." << endl; break; }
	case 3: { std::cout << "Exit menu was chosen, byebye!" << endl; break; }
	}
}


void mainMenu(Elections& e)
{
	int ctrl;
	bool doneVoting = false;
	bool done = false; //flag for while loop
	char* date = new char[MAX_SIZE];

	std::cout << " Welcome to Roy & Alon Election program!" << endl
		<< "please enter the date fot this run in 'DD/MM/YYYY' format:" << endl;
	cin.ignore();
	cin.getline(date, MAX_SIZE);

	e.setDate(date);
	delete[] date;

	//electoin type input

	while (!done)
	{
		inputScreenPage2();
		cin >> ctrl;
		while (ctrl < 1 || ctrl>12) //handle inputs
		{
			std::cout << "wrong input!!" << endl;
			cin >> ctrl;
		}
		while (handleErrors(ctrl, e)) //handle logical errors
		{
			cin >> ctrl;
		}

		system("CLS");
		switch (ctrl)
		{
		case 1: {if (!doneVoting) { addDistric(e); } break; }
		case 2: {if (!doneVoting) { addCitizen(e); }break; }
		case 3: {if (!doneVoting) { addParty(e); }break; }
		case 4: {if (!doneVoting) { addPartyCandidates(e); }break; }
		case 5: {e.printDistricts(); break; }
		case 6: {e.printCitizens(); break; }
		case 7: {e.printParties(); break; }
		case 8: {if (!doneVoting) openVotingMenu(e, doneVoting); break; }
		case 9: {if (doneVoting) { results(e); }; break; }
		case 10: { done = true; break; }
		case 11: { save(e); break; }
		case 12: { cout << "loading is complicated, not working yet..." << endl; break; }
		}
	}
	system("CLS");
	std::cout << "Exit menu was chosen, byebye!" << endl;
}


void save(Elections& e)
{
	char name[MAX_SIZE];
	std::cout << "enter name of file" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);

	ofstream outfile(name, ios::binary | ios::trunc);
	if (!outfile) {
		cout << "error opening file for write" << endl;
		exit(-1);
	}
	e.save(outfile);
	cout << "data was saved to file: " << name << endl;
	outfile.close();
}

void addDistric(Elections& e)
{
	char name[MAX_SIZE];
	int num;
	bool type = false;
	//need implementation of choosing between Divided or Complete district
	std::cout << "enter name of district:" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	std::cout << "enter number of representitves:" << endl; cin >> num;
	std::cout << "enter type of district: (0 - normal, 1 - diveded):" << endl; cin >> type;
	//============= for shemsh
	//Divided* newDist = new Divided(name, num);
	//e.addDistrict(newDist);
	//================
	if (type)
		e.addDistrict(name, num); // //e.addDistrict(newDist);
	else
		e.addDistrict(name, num);

	if (!e.isPartiesEmpty())
	{
		e.AddNewDistToParties(e.getDistrictsLength());
	}
	std::cout << "all good, passed input" << endl;
}

void addCitizen(Elections& e)
{
	char name[MAX_SIZE];
	int id, yob, distID;
	std::cout << "enter name" << endl;
	cin.ignore(); cin.getline(name, MAX_SIZE);

	std::cout << "enter id" << endl; cin >> id;
	std::cout << "enter year of birth" << endl; cin >> yob;
	std::cout << "enter district from avilable: ";
	e.printDistrictsNameAndID(); std::cout << endl;
	cin >> distID;
	e.addCitizen(name, id, e.getDistrict(distID), yob);
	std::cout << "all good, passed input" << endl;
}

void addParty(Elections& e)
{
	char name[MAX_SIZE];
	int id;
	const Citizen* temp;
	std::cout << "enter name of the party:" << endl;
	cin.ignore(); cin.getline(name, MAX_SIZE);
	//extra, check if party name doesnt exist yet.
	std::cout << "enter id of president" << endl; cin >> id;
	temp = e.findCitizen(id);
	while (temp == nullptr)
	{
		std::cout << "id did not match to an existing citizen." << endl
			<< "please enter a valid id: " << endl;
		cin >> id;
		temp = e.findCitizen(id);
	}
	e.addParty(name, *temp);
	std::cout << "all good, passed input" << endl;
}

void addPartyCandidates(Elections& e)
{
	int id, partyID, distID;
	const Citizen* temp;
	std::cout << "please enter the ID of the Candidate" << endl;
	cin >> id;
	temp = e.findCitizen(id);
	while (temp == nullptr)
	{
		std::cout << "id did not match to an existing citizen." << endl
			<< "please enter a valid id: " << endl;
		cin >> id;
		temp = e.findCitizen(id);
	}
	std::cout << "enter Party from avilable: ";
	e.printPartiesNameAndID(); std::cout << endl;
	cin >> partyID;
	std::cout << "enter District from avilable: ";
	e.printDistrictsNameAndID(); std::cout << endl;
	cin >> distID;
	e.addPartyCandidate(*temp, partyID, distID);
	std::cout << "all good, passed input" << endl;
}

void openVotingMenu(Elections& e, bool& doneVoting)
{
	char ctl = '0';
	int id, partyID;
	Citizen* temp;
	e.StartVotingProccess();
	system("CLS");

	while (ctl != 'q' && ctl != 'Q')
	{

		std::cout << "Welcome to voting proccess!" << endl
			<< "Please enter ID to vote." << endl;
		cin >> id;
		temp = e.findCitizen(id);
		while (temp == nullptr)
		{
			system("CLS");
			std::cout << "ID was not found, please enter Valid ID" << endl;
			cin >> id;
			temp = e.findCitizen(id);
		}
		if (temp->getVote())
		{
			std::cout << "why like this... you already Voted!" << endl;
		}
		else
		{
			system("CLS");
			std::cout << "plese enter the number of the party you would like to vote for. " << endl;
			std::cout << "enter Party from avilable: " << endl;
			e.printPartiesNameAndID(); std::cout << endl;
			cin >> partyID;
			e.setVote(*temp, partyID);
			std::cout << "Thank You very much for participating int the Voting Proccess!" << endl;
		}
		std::cout << "please press any key other then 'Q'and then 'Enter' to finish, and clear your place for the next Voter," << endl
			<< "Or press 'Q' then 'Enter' to terminate voting proccess (once the program terminates, no more votes will be acceptable)" << endl;
		cin.ignore();
		cin >> ctl;
		system("CLS");
	}
	doneVoting = true;
	return;
}

void results(Elections& e)
{
	int winnerIdDist, winner;
	int numOfDistricts = e.getDistrictsLength(), numOfParties = e.getPartiesLength();
	int numOfReps;
	const char* distName, * partyName;

	e.setResults();
	winner = e.getVotes().getWinner();
	std::cout << "The new prime minister for elections " << e.getDate() << endl
		<< "is: " << e.getParty(winner).getBossID().getName() << endl
		<< "from party: " << e.getParty(winner).getPartyName() << endl << endl;

	std::cout << "The elctions result are as follows: " << endl << endl;

	for (int i = 0; i < numOfDistricts; i++)
	{
		distName = e.getDistrict(i).getDistName();
		winnerIdDist = e.getVotes().getWinnerIDInDist(i);
		partyName = e.getParty(winnerIdDist).getPartyName();
		numOfReps = e.getDistrict(i).getDistReps();
		std::cout << "For district " << distName << ", " << endl
			<< "number of representative in the district: " << numOfReps << endl
			<< "The district gives all of its representatives to: " << partyName << endl << endl;
		for (int j = 0; j < numOfParties; j++)
		{
			numOfReps = e.getVotes().getElectorsforPartyInDist(j, i);
			partyName = e.getParty(j).getPartyName();
			std::cout << "Party " << partyName << ": " << endl
				<< "with " << e.getVotes().getPartyVotesInDist(j, i) << " votes, and " << e.getVotes().getPartyVotesPrecentageInDist(j, i) << "% votes precentage, " << endl;
			if (numOfReps == 0)
			{
				cout << "there are 0 representatives from the party for this district" << endl;
			}
			else
			{
				cout << "the representatives from the party are: " << endl;
				e.getDistrict(i).getRepsFromParty(j).printsenatorsList(numOfReps);
				cout << endl;

			}

		}

	}
	return;
}

bool handleErrors(int ctrl, Elections& e)
{
	if (ctrl == 2 && e.getDistrictsLength() == 0)
	{
		std::cout << "no districts avilable" << endl;
		return true;
	}

	if (ctrl == 3 && e.getCitizensLength() == 0)
	{
		std::cout << "no citizens avilable" << endl;
		return true;
	}

	if (ctrl == 4 && e.getPartiesLength() == 0)
	{
		std::cout << "no parties avilable" << endl;
		return true;
	}

	if (ctrl == 4 && e.getCitizensLength() == 0)
	{
		std::cout << "no citizens avilable" << endl;
		return true;
	}

	//if (ctrl == 8)
	//{
	//	system("CLS");
	//	int i, j;
	//	for (i = 0; i < e.getDistrictsLength(); i++)
	//	{
	//		for (j = 0; j < e.getPartiesLength(); j++)
	//		{
	//			if (!e.isEnoughRepsInDist(i, j))
	//			{
	//				std::cout << "there are " << e.getParty(j).getElectorInDist(i).getNumOfSenators() << " candidates in Party number "
	//				<< j << ", while the minimum candidates in district " << i << " is " << e.getDistrict(i).getDistReps() << endl
	//				<< "please enter more candidates for the party " << e.getParty(j).getPartyName() << endl;
	//				return true;
	//			}
	//		}
	//	}
	//}

	return false;
}


