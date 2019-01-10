

#ifndef _SHUNDOTAKER_H
#define _SHUNDOTAKER_H

#include <qstack.h>
class ShMemento;
class ShUndoTaker {

private:
	QStack<ShMemento*> stack;

public:
	ShUndoTaker();
	~ShUndoTaker();

	void Push(ShMemento *);
	ShMemento* Pop();
	bool IsEmpty();

	/* deallocate all items and set empty */
	void DeleteAll();
};

#endif //_SHUNDOTAKER_H