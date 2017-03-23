#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <QThread>
#include <QDir>
#include <QSerialPort>

class Messages : public QThread{
	Q_OBJECT
public:
	Messages();
	void run();
	void writeMessage(const QByteArray&);
	void get_arduino_device(QString& device);
private:
	QSerialPort serial;
};

#endif
