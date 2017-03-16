#include <iostream>
#include "gui/gui.h"
#include <qapplication.h>

int main(int argc, char* argv[]){

	QApplication app(argc, argv);
	//Main interface
	gui::initClass();

	//Add pages
	mainPage *mMainPage = new mainPage();

	gui::addPage(mMainPage);

	gui::show();
	int output = app.exec();
	gui::destroyClass();//The pages will be destroyed too
	return output;
}

