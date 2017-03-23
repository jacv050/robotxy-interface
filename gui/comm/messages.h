#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <QThread>

class Messages : public QThread{
	Q_OBJECT
public:
	Messages();
	void run();
};

#endif
