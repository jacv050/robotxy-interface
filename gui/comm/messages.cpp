#include "gui/comm/messages.h"

Messages::Messages(){
	QString device;
	get_arduino_device(device);
	serial.setPortName(device);
	serial.setBaudRate(QSerialPort::Baud9600);
	serial.setDataBits(QSerialPort::Data8);
	serial.setParity(QSerialPort::NoParity);
	serial.setStopBits(QSerialPort::OneStop);
	serial.setFlowControl(QSerialPort::NoFlowControl);
}

void Messages::run(){
	while(true){
		if(serial.canReadLine()){
			
		}
	}
}

void Messages::writeMessage(const QByteArray& byteArray){
	if(serial.open(QIODevice::ReadWrite)){
		if(serial.isWritable()){
	        	serial.waitForBytesWritten(-1);
	        	serial.write(byteArray);
	        	serial.flush(); // Port Error 12 (timed out???)
	        	serial.close();
		}
	}
}


void Messages::get_arduino_device(QString& device){
	QDir dir("/dev/");
	dir.setFilter(QDir::System);
	QStringList list = dir.entryList();
	QString ttyacm0 = list.filter(QString("ttyACM")).at(0);
	device = "/dev/";
	device.append(ttyacm0);
}
