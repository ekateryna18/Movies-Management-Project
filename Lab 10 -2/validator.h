#pragma once
#include <sstream>
#include <string>
using std::ostream;
using std::string;

/*
* Used for signaling exceptional situations that can appear in the repository
*/
class FilmRepoException {
	string msg;
public:
	FilmRepoException(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const FilmRepoException& ex);
	string getErrorMessage() {
		return this->msg;
	}
};

ostream& operator<<(ostream& out, const FilmRepoException& ex);

/*
Folosit pentru a semnala situatii exceptionale ce pot aparea in consola
*/
class ConsoleException {
	string msg;
public:
	ConsoleException(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const ConsoleException& ex);
};

ostream& operator<<(ostream& out, const ConsoleException& ex);

/*
valideaza id-ul filmului
*/
int validare_nr(string id);
/*
valideaza titlul filmului
*/
void validare_titlu(string str);
/*
valideaza actorul filmului
*/
void validare_actor(string str);
/*
valideaza genul filmului
*/
void validare_gen(string gen);
/*
valideaza anul filmului
*/
int validare_an(string an);
/*
testeaza functiile de validare
*/
void test_validator();
