/*
 * wmain.h
 *
 *  Created on: 25/01/2017
 *      Author: john
 */

#ifndef WMAIN_H_
#define WMAIN_H_

#include <QtWidgets>
#include <QSerialPort>
#include <QDir>
#include <iostream>
#include "ui_mainPage.h"
#include "gui/gui.h"
#include "../comm/messages.h"
#include <unistd.h>
#include <fcntl.h>
//#include "stdio.h"
//#include "stdlib.h"

/**
 * Page to select the tool
 */
class mainPage : public QWidget {
	Q_OBJECT
public:
	mainPage(QWidget* parent = 0);
	virtual ~mainPage();

private:
	Ui::mainPage *mUi;
	uint8_t m_move;
	void get_arduino_device(std::string& device);

private slots:
	void clicked_pb_move_steps();
	void clicked_pb_move_meters();
	void clicked_radio_button();
};

#endif /* WMAIN_H_ */
