#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "service.h"


class CartGUI : public QWidget {
	
private:
	FilmService& srv;
	//add to cart
	QLabel* lblTitlu = new QLabel{ "Titlu film: " };
	QLineEdit* editTitlu;
	QPushButton* btnaddtocart;

	//add random
	QLabel* lblNr= new QLabel{ "Numar filme: " };
	QLineEdit* editNr;
	QPushButton* btnaddrandom;

	//export in html
	QLabel* lblExport = new QLabel{ "Nume fisier(.html): " };
	QLineEdit* editExport;
	QPushButton* btnexport;

	QPushButton* btnemptycart;

	QTableWidget* tableFilms;

	void initializeGUIComponents();
	void connectSignalsSlots();
	void ReloadFilmList(vector<Film> films);

public:
	CartGUI(FilmService& filmsrv) : srv{filmsrv} {
		initializeGUIComponents();
		connectSignalsSlots();
		ReloadFilmList(srv.getCartFilms());
	}

	void addToCart();
	void generateCart();
	void emptyCart();
	void exportCart();
};