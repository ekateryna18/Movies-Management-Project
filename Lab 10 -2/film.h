#pragma once
#include<string>
#include<iostream>

using std::string;
//film class
class Film
{
public:
	//constructor film by id, title, genre, year, actor
	Film() = default;
	Film(int i, string t, string g, int y, string a) :id{ i }, title{ t }, genre{ g }, year{ y }, actor{ a }{}

	Film(const Film& ot) :id{ ot.id }, title{ ot.title }, genre{ ot.genre }, year{ ot.year }, actor{ ot.actor }{}


	//getters
	int getId() const noexcept {
		return id;
	}

	string getTitle() const {
		return title;
	}

	string getGenre() const {
		return genre;
	}

	int getYear() const noexcept {
		return year;
	}

	string getActor() const {
		return actor;
	}

	//setters
	void set_title(string nou) {
		title = nou;
	}

	void set_genre(string nou) {
		genre = nou;
	}

	void set_year(int nou) noexcept {
		year = nou;
	}

	void set_actor(string nou) {
		actor = nou;
	}

private:
	int id = -1;
	string title;
	string genre;
	int year = -1;
	string actor;
};

//comparing functions for the sort function
bool cmpTitle(const Film& f1, const Film& f2);

bool cmpActor(const Film& f1, const Film& f2);

bool cmpAn(const Film& f1, const Film& f2);

bool cmpGen(const Film& f1, const Film& f2);