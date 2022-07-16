#include "film.h"

bool cmpTitle(const Film& f1, const Film& f2) {
	return f1.getTitle() < f2.getTitle();
}

bool cmpActor(const Film& f1, const Film& f2) {
	return f1.getActor() < f2.getActor();
}

bool cmpAn(const Film& f1, const Film& f2) {
	return f1.getYear() < f2.getYear();
}

bool cmpGen(const Film& f1, const Film& f2) {
	return f1.getGenre() < f2.getGenre();
}