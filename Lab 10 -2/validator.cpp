#include "validator.h"
#include <string>

using std::stoi;

ostream& operator<<(ostream& out, const FilmRepoException& ex) {
	out << ex.msg;
	return out;
}

ostream& operator<<(ostream& out, const ConsoleException& ex) {
	out << ex.msg;
	return out;
}

int validare_nr(string id) {
	for (int i = 0;i < id.size();i++)
		if (!isdigit(id[i])) {
			throw ConsoleException(id + "  nu este numar!");
		}
	int id_nr = stoi(id);
	return id_nr;
}

void validare_titlu(string str) {
	if (str.size() < 5)
		throw ConsoleException("Introduceti un titlu complet!");
}

void validare_actor(string str) {
	if (str.size() < 5)
		throw ConsoleException("Introduceti un nume de actor complet!");
}

int validare_an(string an) {
	for (int i = 0;i < an.size();i++)
		if (!isdigit(an[i])) {
			throw ConsoleException(an + "  nu este numar!");
		}
	int an_nr = stoi(an);
	if (an_nr < 1800 || an_nr>2021)
		throw ConsoleException("Anul trebuie sa fie intre 1800-2021!");
	return an_nr;
}

void validare_gen(string gen) {
	if ((gen != "actiune") and (gen != "comedie") and (gen != "horror") and (gen != "musical") and (gen != "thriller") and (gen != "drama"))
		throw ConsoleException("Genul nu face parte din lista de genuri acceptata!\n(actiune, comedie, horror, musical, thriller, drama)\n");
}