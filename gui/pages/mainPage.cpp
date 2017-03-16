/*
 * wmain.cpp
 *
 *  Created on: 25/01/2017
 *      Author: john
 */

#include "gui/pages/mainPage.h"

mainPage::mainPage(QWidget* parent) :
QWidget(parent),
mUi(new Ui::mainPage){
	mUi->setupUi(this);
	connect(mUi->pb_move_steps, SIGNAL(clicked()), this, SLOT(clicked_pb_move_steps()));
	connect(mUi->pb_move_meters, SIGNAL(clicked()), this, SLOT(clicked_pb_move_meters()));
	connect(mUi->rb_up, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	connect(mUi->rb_down, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	connect(mUi->rb_left, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
	connect(mUi->rb_right, SIGNAL(clicked()), this, SLOT(clicked_radio_button()));
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
	data[1] = 4;//Tipo de movimiento m_type
	data[2] = (mUi->sb_steps->value()>>8);//Primera parte de m_steps
	data[3] = (mUi->sb_steps->value() & 0x00FF);//Segundoa parte de m_steps

	std::string message;
	
	message.append("echo '");
	message.append((char*)data, 4);
	message.append("'");
	message.append(" >> /dev/ttyACM0");
	system(message.c_str());
}

void mainPage::clicked_pb_move_meters(){
        uint8_t data[4];
        std::string message;

        message.append("echo '");
        message.append((char*)data, 4);
        message.append("'");
        message.append(" >> /dev/ttyACM0");
        system(message.c_str());

}

mainPage::~mainPage(){
}
