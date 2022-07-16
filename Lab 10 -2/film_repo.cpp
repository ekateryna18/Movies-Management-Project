#include "film_repo.h"
#include <sstream>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stoi;

auto FilmRepo::find(int id) -> vector<Film>::iterator {
	auto f = std::find_if(allFilms.begin(), allFilms.end(),
		[=](const Film& film) {
			return film.getId() == id;
		});
	if (f != allFilms.end())
		return f;
	else {
		//daca nu exista arunca exceptie
		throw FilmRepoException("No movie existing with this id: " + to_string(id));
	}
}

bool FilmRepo::exist(const Film& f) {
	try {
		find(f.getId());
		return true;
	}
	catch (FilmRepoException&) {
		return false;
	}
}
void FilmRepo::add(const Film& f)
{
	if (exist(f)) {
		throw FilmRepoException("There is already a movie with this id: " + to_string(f.getId()));
	}
	allFilms.push_back(f);
}

void FilmRepo::modificare(const int id, Film f) {
	auto poz = find(id);
	(*poz).set_title(f.getTitle());
	(*poz).set_genre(f.getGenre());
	(*poz).set_year(f.getYear());
	(*poz).set_actor(f.getActor());
}

void FilmRepo::stergere(const int id) {
	auto poz = find(id);
	allFilms.erase(poz);
}

vector<Film> FilmRepo::get_all() {
	return allFilms;
}

auto FilmRepo::get_by_title(string title) -> vector<Film>::iterator {
	for (auto it = allFilms.begin(); it != allFilms.end(); it++) {
		if ((*it).getTitle() == title) {
			return it;
		}
	}
	throw FilmRepoException("No movie existing with this title!");
}

int FilmRepo::size() {
	return this->allFilms.size();
}

void FilmRepoFile::loadFromFile() {
	ifstream filmFile(this->filename);
	if (!filmFile.is_open()) {
		throw FilmRepoException("Cannot read from file: " + filename);
	}
	string line;
	while (getline(filmFile, line))
	{
		string titlu, gen, actor;
		int id, an;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) id = stoi(current_item);
			if (item_no == 1) titlu = current_item;
			if (item_no == 2) gen = current_item;
			if (item_no == 3) an = stoi(current_item);
			if (item_no == 4) actor = current_item;
			item_no++;
		}
		Film f{ id,titlu,gen,an,actor };
		FilmRepoFile::add(f);
	}
	filmFile.close();
}

void FilmRepoFile::saveToFile() {
	ofstream filmOutput(this->filename);
	if (!filmOutput.is_open())
		throw FilmRepoException("Cannot write to file " + filename);
	for (auto& film : get_all()) {
		filmOutput << film.getId() << "," << film.getTitle() << "," << film.getGenre() << "," << film.getYear() << "," << film.getActor() << endl;
	}
	filmOutput.close();
}

void FilmRepoFile::add(const Film& f) {
	FilmRepo::add(f);
	saveToFile();
}

void FilmRepoFile::stergere(int id) {
	FilmRepo::stergere(id);
	saveToFile();
}

void FilmRepoFile::modificare(const int id, Film f) {
	FilmRepo::modificare(id, f);
	saveToFile();
}

vector<Film> FilmRepoFile::get_all()
{
	return FilmRepo::get_all();
}

bool FilmRepoFile::exist(const Film& f)
{
	return FilmRepo::exist(f);
}

auto FilmRepoFile::get_by_title(string title)->vector<Film>::iterator {
	return FilmRepo::get_by_title(title);
}

int FilmRepoFile::size() {
	return FilmRepo::size();
}
/*
Cauta
arunca exceptie daca nu exista film
*/
auto FilmRepoFile::find(int id)->vector<Film>::iterator {
	return FilmRepo::find(id);
}