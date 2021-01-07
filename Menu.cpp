#include <iostream>
#include "Elections.h"

using namespace std;
using namespace elc;

#define MAX_SIZE 50


void mainMenu(Elections& e, bool& doneVoting);
void inputDateAndElectionRound(Elections& e);
void inputScreenPage1();
void inputScreenPage2(Elections& e);

void save(Elections& e,bool& doneVoting);
void load(Elections* e,bool& doneVoting);

void addDistric(Elections& e);
void addCitizen(Elections& e);
void addParty(Elections& e);
void addPartyCandidates(Elections& e);

void results(Elections& e);
void simpleResults(Elections& e);
void openVotingMenu(Elections& e, bool& doneVoting);
bool handleErrors(int ctrl, Elections& e);

void inputScreenPage1()
{
	std::cout << "--------intput screen--------" << endl;
	std::cout
		<< " 1 - Create new election round. " << endl
		<< " 2 - Load Existing election round from file." << endl
		<< " 3 - Exit program." << endl
		<< "waiting for input..." << endl;
}
void inputScreenPage2(Elections& e)
{
	
	std::cout << endl << "--------intput screen--------" << endl;
	(e.getRoundType()) ? cout << "   Simple Election Round" << endl : cout << "   Normal Election Round" << endl;
	std::cout << "   Election Date:" << e.getDate() << endl;
	std::cout << "--------intput screen--------" << endl << endl;
	std::cout << "what would you like to add? " << endl
		<< " 1 - Add District. " << endl
		<< " 2 - Add Citizen." << endl
		<< " 3 - Add Party." << endl
		<< " 4 - Add representitive for a party. " << endl
		<< " 5 - print ALL districts." << endl
		<< " 6 - print ALL citizens." << endl
		<< " 7 - print ALL parties." << endl
		<< " 8 - VOTE!! (inputs will no longer be avilable)" << endl
		<< " 9 - show results." << endl
		<< " 10 - exit this menu." << endl
		<< " 11 - Save Elections Round." << endl
		<< " 12 - Load Elections Round." << endl
		<< "waiting for input..." << endl;
}

void openingMenu(Elections& e)
{
	int ctrl;
	bool doneVoting = false;
	inputScreenPage1();
	cin >> ctrl;

	while (ctrl < 1 || ctrl>4) //handle inputs
	{
		std::cout << "wrong input!!" << endl;
		cin >> ctrl;
	}
	switch (ctrl)
	{
	case 1: { system("CLS"); inputDateAndElectionRound(e); mainMenu(e,doneVoting); break; }
	case 2: { load(&e, doneVoting) ; break; }
	case 3: { std::cout << "Exit menu was chosen, byebye!" << endl; break; }
	}
}

void inputDateAndElectionRound(Elections& e)
{
	char* date = new char[MAX_SIZE];
	int type = 0, reps = 0;
	char distName[20] = "system-District";

	std::cout << " Welcome to Roy & Alon Election program!" << endl
		<< "please enter the date fot this run in 'DD/MM/YYYY' format: " << endl;
	cin.ignore();
	cin.getline(date, MAX_SIZE);
	e.setDate(date);
	delete[] date;

	std::cout << "choose Election round type (0 - normal) , (1 - simple) : "; cin >> type;
	if (type)
	{
		e.setRoundType(type);
		std::cout << "Enter number of Representitives: "; cin >> reps;
		e.handleSimpleRound(distName, reps);
	}
}

void mainMenu(Elections& e, bool& doneVoting)
{
	int ctrl;
	bool done = false; //flag for while loop
	char* date = new char[MAX_SIZE];
	

	system("CLS");
	while (!done)
	{
		inputScreenPage2(e);
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
		case 1: {
			if (!doneVoting && !e.getRoundType()) //check the round type
				addDistric(e); 
			else
				std::cout << "function not avilable in a Simple Election round" << endl;break; }
		case 2: {if (!doneVoting) { addCitizen(e); }break; }
		case 3: {if (!doneVoting) { addParty(e); }break; }
		case 4: {if (!doneVoting) { addPartyCandidates(e); }break; }
		case 5: {e.printDistricts(); break; }
		case 6: {e.printCitizens(); break; }
		case 7: {e.printParties(); break; }
		case 8: {if (!doneVoting) openVotingMenu(e, doneVoting); break; }
		case 9: {if (doneVoting) { results(e); }; break; }
		case 10: { done = true; break; }
		case 11: { save(e, doneVoting); break; }
		case 12: { load(&e, doneVoting) ; break; }
		}
	}
	system("CLS");
	std::cout << "Exit menu was chosen, byebye!" << endl;
}


void save(Elections& e, bool& doneVoting)
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
	outfile.write(rcastcc(&doneVoting), sizeof(doneVoting));
	e.save(outfile);
	cout << "data was saved to file: " << name << endl;
	outfile.close();
}


void load(Elections* e, bool& doneVoting )
{
	char name[MAX_SIZE];
	std::cout << "enter name of file" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);

	ifstream infile(name, ios::binary);
		if (!infile)
		{
			cout << "error opening file for read" << endl;
			exit(-1);
		}
		infile.read(rcastc(&doneVoting), sizeof(doneVoting));
		e = new Elections(infile);
		mainMenu(*e, doneVoting);
		infile.close();
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
		e.addDistrict(name, num, type); // //e.addDistrict(newDist);

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
	//Handle simple round
	if (!e.getRoundType())
	{
		std::cout << "enter district from avilable: ";
		e.printDistrictsNameAndID(); std::cout << endl;
		cin >> distID;
		e.addCitizen(name, id, e.getDistrict(distID), yob);
	}
	else // if simple, we want to pass add citizen function without district
	{
		 e.addCitizen(name, id,e.getDistrict(0),yob); //in simple round, 0 is default id
	}
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
	if (e.getRoundType())
		distID = 0;
	else
	{
		std::cout << "enter District from avilable: ";
		e.printDistrictsNameAndID(); std::cout << endl;
		cin >> distID;
	}
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
	e.setResults();

	if (e.getRoundType())
	{
		simpleResults(e);
		return;
	}


	int winnerIdDist, winner;
	int party_id, numOfReps;
	int numOfDistricts = e.getDistrictsLength(), numOfParties = e.getPartiesLength();
	int** party_order = e.getVotes().getPartiesWinningOrder();
	string partyName;
	const District* dist;




	winner = e.getVotes().getWinner(e.getDistList());

	cout << "for Elections " << e.getDate() << ", The elections results are as follow: " << endl << endl;

	for (int i = 0; i < numOfDistricts; i++)
	{
		dist = &e.getDistrict(i);
		winnerIdDist = e.getVotes().getWinnerIDInDist(i);
		partyName = e.getParty(winnerIdDist).getPartyName();
		numOfReps = e.getDistrict(i).getDistReps();
		std::cout << " --- In District " << dist->getDistName() << " --- " << endl
			<< "number of representative in the district: " << numOfReps << endl;
		if (typeid(*dist) == typeid(Divided))
		{
			cout << "District "<< dist->getDistName() << " is a divided district" << endl << endl;
			for (int j = numOfParties-1; j >= 0; j--)
			{
				party_id = party_order[j][0];
				partyName = e.getParty(party_id).getPartyName();
				numOfReps = e.getVotes().getElectorsforPartyInDist(party_id, i);

				if (numOfReps > 0)
				{
					cout << numOfReps << " Electors from the district choose " << e.getParty(j).getBossID().getName()
						<< ", of party " << partyName << endl;
				}
				else
				{
					cout << "party " << partyName << " has no representatives" << endl;
				}
			}
			cout << endl;
		}
		else
			cout << "The district gives all of its representatives to: " << partyName << endl << endl
			<< "voting precantage in the District: " << e.getVotes().getDistVotesPrecantage(*dist) <<"%"<< endl << endl;

		for (int j = numOfParties-1; j >= 0; j--)
		{
			party_id = party_order[j][0];
			partyName = e.getParty(party_id).getPartyName();
			numOfReps = e.getVotes().getElectorsforPartyInDist(party_id, i);

			cout << "  - For party " << partyName << " -" << endl
				<< "number of votes won in the district: " << e.getVotes().getPartyVotesInDist(party_id, i) << endl
				<< "precentage of votes: " << e.getVotes().getPartyVotesPrecentageInDist(party_id, i) << "%" << endl
				<< "number of representatives won: " << numOfReps << endl;
			if (numOfReps > 0)
			{
				cout << "party representatives: " << endl;
				e.getDistrict(i).getRepsFromParty(party_id).printsenatorsList(numOfReps);
			}
			cout << endl << endl;
		}

	}

	cout << " -- Election results for each party --  " << endl << endl;
	for (int i = numOfParties - 1; i >= 0; i--)
	{
		party_id = party_order[i][0];
		partyName = e.getParty(party_id).getPartyName();

		cout << "  - For party " << partyName << " - " << endl
			<< "Party candidate for prime minister: " << e.getParty(party_id).getBossID().getName() << endl
			<< "Total party electors won: " << party_order[i][2] << endl
			<< "Total party votes: " << party_order[i][1] << endl << endl;
	}
	return;

}

void simpleResults(Elections& e)
{
	const CitizensList& citizens = e.getCitizensList();
	int i, numOfReps, party_id, numOfParties = e.getPartiesLength();
	int** party_order = e.getVotes().getPartiesWinningOrder();
	string partyName;

	cout << "for Elections " << e.getDate() << ", The elections results are as follow: " << endl << endl
		<< "With a total of " << e.getVotes().getTotalVotesPrecentage(citizens) << "% votes precentage:" << endl;
	
	for (i = numOfParties-1; i >= 0; i--)
	{
		party_id = party_order[i][0];
		partyName = e.getParty(party_id).getPartyName();
		numOfReps = e.getVotes().getElectorsforPartyInDist(party_id, 0);
		cout << "  - For party " << partyName << "-" << endl
			<< "party candidate for prime minister: " << e.getParty(party_id).getBossID().getName() << endl
			<< "number of votes won: " << party_order[i][1] << endl
			<< "precentage of votes: " << e.getVotes().getPartyVotesPrecentageInDist(party_id, 0) << "%" << endl
			<< "number of representatives won: " << numOfReps << endl;
			if (numOfReps > 0)
			{
				cout << "party representatives: " << endl;
				e.getDistrict(0).getRepsFromParty(party_id).printsenatorsList(numOfReps);
			}
		cout << endl << endl;

	}
	cout << endl;
		


	for (i = 0; i < numOfParties; i++)
		delete[] party_order[i];
	delete[] party_order;
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

	return false;
}


