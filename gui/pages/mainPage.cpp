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

	std::string prueba;
	get_arduino_device(prueba);
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
	std::string device="";
	get_arduino_device(device);

	uint8_t data[4];
	data[0] = m_move;
	data[1] = 4;//Tipo de movimiento m_type 4
	data[2] = (mUi->sb_steps->value()>>8);//Primera parte de m_steps
	data[3] = (mUi->sb_steps->value() & 0x00FF);//Segundoa parte de m_steps

	//Opcion qt
	QByteArray byteArray((char*)data, 4);
	QSerialPort serial;
	serial.setPortName(QString(device.c_str()));
	serial.setBaudRate(QSerialPort::Baud9600);
	serial.setDataBits(QSerialPort::Data8);
	serial.setParity(QSerialPort::NoParity);
	serial.setStopBits(QSerialPort::OneStop);
	serial.setFlowControl(QSerialPort::NoFlowControl);
	
	if(serial.open(QIODevice::ReadWrite)){
		if(serial.isWritable()){
	        	serial.waitForBytesWritten(-1);
	        	serial.write(byteArray);
	        	serial.flush(); // Port Error 12 (timed out???)
	        	serial.close();
		}
	}

	//Opcion a bajo nivel - Funcional
	//int desc = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	//write(desc, data, 4);
	//close(desc);

}

void mainPage::clicked_pb_move_meters(){
        uint8_t data[4];
        std::string message;
	//m_type 5
        message.append("echo '");
        message.append((char*)data, 4);
        message.append("'");
        message.append(" >> /dev/ttyACM0");
        system(message.c_str());

}

mainPage::~mainPage(){
}
