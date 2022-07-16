#include "cosGUI.h"
#include <fstream>
using std::ofstream;

void CartGUI::initializeGUIComponents() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	QWidget* form = new QWidget;
	QFormLayout* lyform = new QFormLayout;
	form->setLayout(lyform);

	//add to cart
	editTitlu = new QLineEdit;
	lyform->addRow(lblTitlu, editTitlu);
	btnaddtocart = new QPushButton("Adauga in cos dupa titlu");
	lyform->addWidget(btnaddtocart);

	//add random
	editNr = new QLineEdit;
	lyform->addRow(lblNr, editNr);
	btnaddrandom = new QPushButton("Genereaza filme");
	lyform->addWidget(btnaddrandom);

	//export cart
	editExport = new QLineEdit;
	lyform->addRow(lblExport, editExport);
	btnexport = new QPushButton("Export");
	lyform->addWidget(btnexport);

	lyLeft->addWidget(form);

	//buton pentru stergere cos
	btnemptycart = new QPushButton("Goleste cos");
	lyLeft->addWidget(btnemptycart);

	//tabel cos cu filme
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 5;
	this->tableFilms = new QTableWidget(noLines, noColumns);

	//header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Id" << "Titlu" << "Gen" << "An" << "Actor";
	this->tableFilms->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableFilms->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	lyRight->addWidget(tableFilms);

	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void CartGUI::ReloadFilmList(vector<Film> films) {
	this->tableFilms->clearContents();
	this->tableFilms->setRowCount(films.size());

	int lineNumber = 0;
	for (auto& film : films) {
		this->tableFilms->setItem(lineNumber, 0, new QTableWidgetItem(QString::number(film.getId())));
		this->tableFilms->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.getTitle())));
		this->tableFilms->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(film.getGenre())));
		this->tableFilms->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(film.getYear())));
		this->tableFilms->setItem(lineNumber, 4, new QTableWidgetItem(QString::fromStdString(film.getActor())));
		lineNumber++;
	}
}

void CartGUI::connectSignalsSlots() {
	//adauga filme
	QObject::connect(btnaddtocart, &QPushButton::clicked, this, &CartGUI::addToCart);

	//generate cart
	QObject::connect(btnaddrandom, &QPushButton::clicked, this, &CartGUI::generateCart);

	//empty cart
	QObject::connect(btnemptycart, &QPushButton::clicked, this, &CartGUI::emptyCart);

	//export
	QObject::connect(btnexport, &QPushButton::clicked, this, &CartGUI::exportCart);
}

void CartGUI::addToCart() {
	try {
		//preluare info din QLineEdit-uri
		string titlu = editTitlu->text().toStdString();

		editTitlu->clear();

		this->srv.addToCart(titlu);
		this->ReloadFilmList(this->srv.getCartFilms());

		QMessageBox::information(this, "INFO", QString::fromStdString("Film adaugat cu succes!"));
	}
	catch (FilmRepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void CartGUI::generateCart() {
	//preluare info din QLineEdit-uri
	int nr = editNr->text().toInt();

	editNr->clear();

	this->srv.addRandomToCart(nr);
	this->ReloadFilmList(this->srv.getCartFilms());

	QMessageBox::information(this, "INFO", QString::fromStdString("Filme generate cu succes!"));
}

void CartGUI::emptyCart() {
	this->srv.emptycart();
	this->ReloadFilmList(this->srv.getCartFilms());

	QMessageBox::information(this, "INFO", QString::fromStdString("Cos golit cu succes!"));
}

void CartGUI::exportCart() {
	string file = editExport->text().toStdString();
	editExport->clear();

	std::ofstream filename(file);
	filename << "<!DOCTYPE html>";
	filename << "<html>";
	filename << "<body style=\"background-color:#FCD6FF;\">";
	filename << "<h1 style = \"color:purple;\"> " << "Cos inchirieri filme" << "</h1>";
	for (auto& film : srv.getCartFilms())
	{

		filename << "<h2 style = \"color:purple;\"> " << ">>>" << film.getId() << " " << film.getTitle() << " " << film.getGenre() << " " << film.getYear() << " " << film.getActor() << "</h2>" << "<br>";

	}
	filename << "</body>";
	filename << "</html>";
	filename.close();
	QMessageBox::information(this, "INFO", QString::fromStdString("Export realizat cu succes!"));
}