#pragma once
#include "film.h"
#include "film_repo.h"

//undo class using polymorphism
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};
//undo class for adding a movie using the undo class
class UndoAdauga : public ActiuneUndo {
	Film filmadaugat;
	FilmRepo& repo;
public:
	UndoAdauga(FilmRepo& repo, const Film& f) : repo{ repo }, filmadaugat{ f } {}
	void doUndo() override {
		repo.stergere(filmadaugat.getId());
	}
};

//undo class for deleting a movie using the undo class
class UndoStergere : public ActiuneUndo {
	Film film_sters;
	FilmRepo& repo;
public:
	UndoStergere(FilmRepo& repo, const Film& film_sters) : repo{ repo }, film_sters{ film_sters } {}
	void doUndo() override {
		repo.add(film_sters);
	}
};
//undo class for changing a movie using the undo class
class UndoModificare : public ActiuneUndo {
	Film film_modificat;
	FilmRepo& repo;
public:
	UndoModificare(FilmRepo& repo, const Film& f) : repo{ repo }, film_modificat{ f } {}
	void doUndo() override {
		repo.modificare(film_modificat.getId(), film_modificat);
	}
};