/*
 * wmain.cpp
 *
 *  Created on: 25/01/2017
 *      Author: john
 */

#include "gui/pages/mainPage.h"

mainPage::mainPage(QWidget* parent) :
QWidget(parent),
messages(),
mUi(new Ui::mainPage){
	mUi->setupUi(this);
	connect(mUi->pb_move_steps, SIGNAL(clicked()), this, SLOT(clicked_pb_move_steps()));
	connect(mUi->pb_move_meters, SIGNAL(clicked()), this, SLOT(clicked_pb_move_meters()));
	connect(mUi->rb_up, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	connect(mUi->rb_down, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	connect(mUi->rb_left, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	connect(mUi->rb_right, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	messages.start();
}

void mainPage::get_arduino_device(std::string& device){
	QDir dir("/dev/");
	dir.setFilter(QDir::System);
	QStringList list = dir.entryList();
	QString ttyacm0 = list.filter(QString("ttyACM")).at(0);
	device = "/dev/";
	device.append(ttyacm0.toLocal8Bit().constData());
}

void mainPage::clicked_radio_button(){
	if(QObject::sender() == mUi->rb_up)
		m_move = 0;
	else if(QObject::sender() == mUi->rb_down)
		m_move = 1;
	else if(QObject::sender() == mUi->rb_left)
		m_move = 2;
	else if(QObject::sender() == mUi->rb_right)
		m_move = 3;

	mUi->rb_up->setChecked(false);
	mUi->rb_down->setChecked(false);
	mUi->rb_right->setChecked(false);
	mUi->rb_left->setChecked(false);
	((QRadioButton*)QObject::sender())->setChecked(true);
}

void mainPage::clicked_pb_move_steps(){
	uint8_t data[4];
	data[0] = m_move;
	data[1] = 4;//Tipo de movimiento m_type 4
	data[2] = (mUi->sb_steps->value()>>8);//Primera parte de m_steps
	data[3] = (mUi->sb_steps->value() & 0x00FF);//Segundoa parte de m_steps

	//Opcion qt
	QByteArray byteArray((char*)data, 4);
	messages.writeMessage(byteArray);

}

void mainPage::clicked_pb_move_meters(){
        uint8_t data[4];
	data[0] = m_move;
	data[1] = 5;//Tipo de movimiento centimetros 5
	data[2] = (mUi->sb_meters->value()>>8);
	data[3] = (mUi->sb_meters->value() & 0x00FF);

	//Opcion qt
	QByteArray byteArray((char*)data, 4);
	messages.writeMessage(byteArray);
}

mainPage::~mainPage(){
}
