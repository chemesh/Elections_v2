#include <iostream>
#include "Elections.h"
#define MAX_SIZE 50

using namespace std;
using namespace elc;

//cin dont know to get space, 
void inputScreenPage()
{
	cout << "-----intput screen-----" << endl;
	cout << "what would you like to add? " << endl
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
		<< "waiting for input..." << endl;
}
void addDistric(Elections& e)
{
	char name[MAX_SIZE];
	int num;
	cout << "enter name of district" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "enter number of representitves" << endl; cin >> num;
	e.addDistrict(name, num);
	if (!e.isPartiesEmpty())
	{
		e.AddNewDistToParties(e.getDistrictsLength());
	}
	cout << "all good, passed input" << endl;
}
void addCitizen(Elections& e)
{
	char name[MAX_SIZE];
	int id, yob, distID;
	cout << "enter name" << endl;
	cin.ignore(); cin.getline(name, MAX_SIZE);

	cout << "enter id" << endl; cin >> id;
	cout << "enter year of birth" << endl; cin >> yob;
	cout << "enter district from avilable: ";
	e.printDistrictsNameAndID(); cout << endl;
	cin >> distID;
	e.addCitizen(name, id, e.getDistrict(distID), yob);
	cout << "all good, passed input" << endl;
}


void addParty(Elections& e)
{
	char name[MAX_SIZE];
	int id;
	const Citizen* temp;
	cout << "enter name of the party:" << endl;
	cin.ignore(); cin.getline(name, MAX_SIZE);
	//extra, check if party name doesnt exist yet.
	cout << "enter id of president" << endl; cin >> id;
	temp = e.findCitizen(id);
	while (temp == nullptr)
	{
		cout << "id did not match to an existing citizen." << endl
			<< "please enter a valid id: " << endl;
		cin >> id;
		temp = e.findCitizen(id);
	}
	e.addParty(name, *temp);
	cout << "all good, passed input" << endl;
}

void addPartyCandidates(Elections& e)
{
	int id, partyID, distID;
	const Citizen* temp;
	cout << "please enter the ID of the Candidate" << endl;
	cin >> id;
	temp = e.findCitizen(id);
	while (temp == nullptr)
	{
		cout << "id did not match to an existing citizen." << endl
			<< "please enter a valid id: " << endl;
		cin >> id;
		temp = e.findCitizen(id);
	}
	cout << "enter Party from avilable: ";
	e.printPartiesNameAndID(); cout << endl;
	cin >> partyID;
	cout << "enter District from avilable: ";
	e.printDistrictsNameAndID(); cout << endl;
	cin >> distID;
	e.addPartyCandidate(*temp, partyID, distID);
	cout << "all good, passed input" << endl;
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

		cout << "Welcome to voting proccess!" << endl
			<< "Please enter ID to vote." << endl;
		cin >> id;
		temp = e.findCitizen(id);
		while (temp == nullptr)
		{
			system("CLS");
			cout << "ID was not found, please enter Valid ID" << endl;
			cin >> id;
			temp = e.findCitizen(id);
		}
		if (temp->getVote())
		{
			cout << "why like this... you already Voted!" << endl;
		}
		else
		{
			system("CLS");
			cout << "plese enter the number of the party you would like to vote for. " << endl;
			cout << "enter Party from avilable: " << endl;
			e.printPartiesNameAndID(); cout << endl;
			cin >> partyID;
			e.setVote(*temp, partyID);
			cout << "Thank You very much for participating int the Voting Proccess!" << endl;
		}
		cout << "please press any key other then 'Q'and then 'Enter' to finish, and clear your place for the next Voter," << endl
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
	cout << "The new prime minister for elections " << e.getDate() << endl
		<< "is: " << e.getParty(winner).getBossID().getName() << endl
		<< "from party: " << e.getParty(winner).getPartyName() << endl << endl;

	cout << "The elctions result are as follows: " << endl << endl;

	for (int i = 0; i < numOfDistricts; i++)
	{
		distName = e.getDistrict(i).getDistName();
		partyName = e.getParty(winnerIdDist).getPartyName();
		winnerIdDist = e.getVotes().getWinnerIDInDist(i);
		numOfReps = e.getDistrict(i).getDistReps();
		cout << "For district " << distName << ", " << endl
			<< "number of representative in the district: " << numOfReps << endl
			<< "The district gives all of its representatives to: " << partyName << endl << endl;
		for (int j = 0; j < numOfParties; j++)
		{
			numOfReps = e.getVotes().getElectorsforPartyInDist(j, i);
			partyName = e.getParty(j).getPartyName();
			cout << "For Party " << partyName << ": " << endl
				<< "with " << e.getVotes().getPartyVotesInDist(j, i) << " votes, and " << e.getVotes().getPartyVotesPrecentageInDist(j, i) << " votes precentage, " << endl
				<< "the representatives from the party are: " << endl;
			e.getDistrict(i).getRepsFromParty(j).printsenatorsList(numOfReps);

		}

	}
	return;

}


bool handleErrors(int ctrl, Elections& e)
{
	if (ctrl == 2 && e.getDistrictsLength() == 0)
	{
		cout << "no districts avilable" << endl;
		return true;
	}

	if (ctrl == 3 && e.getCitizensLength() == 0)
	{
		cout << "no citizens avilable" << endl;
		return true;
	}

	if (ctrl == 4 && e.getPartiesLength() == 0)
	{
		cout << "no parties avilable" << endl;
		return true;
	}

	if (ctrl == 4 && e.getCitizensLength() == 0)
	{
		cout << "no citizens avilable" << endl;
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
	//				cout << "there are " << e.getParty(j).getElectorInDist(i).getNumOfSenators() << " candidates in Party number "
	//				<< j << ", while the minimum candidates in district " << i << " is " << e.getDistrict(i).getDistReps() << endl
	//				<< "please enter more candidates for the party " << e.getParty(j).getPartyName() << endl;
	//				return true;
	//			}
	//		}
	//	}
	//}

	return false;
}

void mainMenu(Elections& e)
{
	int ctrl;
	bool doneVoting = false;
	char* date = new char[MAX_SIZE];

	cout << " Welcome to a new Election run!" << endl
		<< "please enter the date fot this run in 'DD/MM/YYYY' format:" << endl;
	cin.ignore();
	cin.getline(date, MAX_SIZE);

	e.setDate(date);
	delete[] date;





	while (true)
	{
		inputScreenPage();
		cin >> ctrl;
		while (ctrl < 1 || ctrl>10) //handle inputs
		{
			cout << "wrong input!!" << endl;
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
		case 10: goto exit_loop; break;
		}
	}
	system("CLS");
exit_loop:;
	//run elections
	cout << "bye bye" << endl;
}


int main()
{
	Elections e;
	mainMenu(e);
}
