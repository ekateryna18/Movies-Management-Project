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
#include <QPainter>
#include <cstdlib>

#include "cosfilm.h"
#include "observer.h"
//the UI made for cart using QListWidget
class CosGUIcuLista :public QWidget, public Observer {
private:
	CosFilm& cos;
	QListWidget* lst;
	QPushButton* btn;

	//add random
	QLabel* lblNr = new QLabel{ "Number/ID: " };
	QLabel* lblTitlu = new QLabel{ "Movie title: " };
	QLineEdit* editNr;
	QLineEdit* editTitlu;
	QPushButton* btnaddrandom;
	QPushButton* btndeletecositem;
	QPushButton* btnaddcart;

	void loadList(const std::vector<Film>& films) {
		this->lst->clear();

		for (auto& film : films) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(to_string(film.getId()) + "--" + film.getTitle() + "--" + film.getGenre() + "--" + to_string(film.getYear()) + "--" + film.getActor()));
			this->lst->addItem(item);
		}
	}
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
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

	}
public:
	CosGUIcuLista(CosFilm& cos) :cos{ cos } {
		initGUI();
		connectSignals();
		loadList(cos.lista());
	}

	void update() override {
		loadList(cos.lista());
	}
	~CosGUIcuLista() {
		cos.removeObserver(this);
	}
};

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
#include <QPainter>
#include <cstdlib>

#include "cosfilm.h"
#include "observer.h"

class CartDraw : public QWidget, public Observer {
private:
	CosFilm& cos;
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto film : cos.lista()) {
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("cat.jpg");

			p.drawImage(target, image, source);

			x += 40;
		}
	}

	void update() override {
		repaint();
	};

public:
	CartDraw(CosFilm& cos) :cos{ cos } {
		cos.addObserver(this);
	};

	~CartDraw() {
		cos.removeObserver(this);
	}
};