#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include <cstdlib>
#include <QFormLayout>
#include <QLineEdit>

#include "cosfilm.h"
#include "observer.h"
#include "MyTableModel.h"

class CosGUIcuListaModel :public QWidget, public Observer {
private:
	CosFilm& cos;
	MyTableModel* table;
	QTableView* tblV;
	QPushButton* btn;

	//add random
	QLabel* lblNr = new QLabel{ "Number/ID: " };
	QLabel* lblTitlu = new QLabel{ "Title movie: " };
	QLineEdit* editNr;
	QLineEdit* editTitlu;
	QPushButton* btnaddrandom;
	QPushButton* btndeletecositem;
	QPushButton* btnaddcart;

	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		setLayout(ly);

		tblV = new QTableView;
		ly->addWidget(tblV);

		btn = new QPushButton("Clear cos");
		ly->addWidget(btn);

		//add random
		QWidget* form = new QWidget;
		QFormLayout* lyform = new QFormLayout;
		form->setLayout(lyform);
		editNr = new QLineEdit;
		lyform->addRow(lblNr, editNr);

		editTitlu = new QLineEdit;
		lyform->addRow(lblTitlu, editTitlu);

		btnaddrandom = new QPushButton("Generate movies");
		lyform->addWidget(btnaddrandom);

		btnaddcart = new QPushButton("Add to cart by title");
		ly->addWidget(btnaddcart);

		btndeletecositem = new QPushButton("Delete from cart by id");
		ly->addWidget(btndeletecositem);

		ly->addWidget(form);
		setLayout(ly);
	}

	void loadList(const std::vector<Film>& films) {
		table->setFilms(films);
	}

	void connectSignals() {
		cos.addObserver(this);
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			cos.goleste();
			loadList(cos.lista());
			});

		QObject::connect(btnaddrandom, &QPushButton::clicked, [&]() {
			cos.goleste();
			int nr = editNr->text().toInt();
			editNr->clear();

			cos.umple(nr);
			loadList(cos.lista());
			});

		QObject::connect(btndeletecositem, &QPushButton::clicked, [&]() {
			int nr = editNr->text().toInt();
			editNr->clear();

			cos.sterge(nr);
			loadList(cos.lista());
			});

		QObject::connect(btnaddcart, &QPushButton::clicked, [&]() {
			string title = editTitlu->text().toStdString();
			editNr->clear();

			cos.addbyttl(title);
			loadList(cos.lista());
			});
		//selectia in tabel
		QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
			
			int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
			auto cel0Index = tblV->model()->index(selRow, 0);
			auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
			
			auto cel1Index = tblV->model()->index(selRow, 1);
			auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
			
			auto cel2Index = tblV->model()->index(selRow, 2);
			auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
			
			});
	}
public:
	CosGUIcuListaModel(CosFilm& cos) :cos{ cos } {
		initGUI();
		table = new MyTableModel{ cos.lista() };
		tblV->setModel(table);
		connectSignals();
		loadList(cos.lista());
	}

	void update() override {
		loadList(cos.lista());
	}
	~CosGUIcuListaModel() {
		cos.removeObserver(this);
	}
};