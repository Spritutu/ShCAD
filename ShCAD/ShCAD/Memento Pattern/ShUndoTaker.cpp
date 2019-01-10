

#include "ShUndoTaker.h"
#include "Memento Pattern\ShMemento.h"
//delete 할때 전방선언 된 상태에서 지우니깐 클래스를 못찾아가는건가?

ShUndoTaker::ShUndoTaker() {

}

ShUndoTaker::~ShUndoTaker() {
	
	while (!this->IsEmpty())
		delete this->Pop();
	
}

void ShUndoTaker::Push(ShMemento *memento) {

	if (this->stack.size() > 30) {
		delete this->stack[0];
		this->stack.pop_front();
	}

	this->stack.push(memento);
}

ShMemento* ShUndoTaker::Pop() {

	if (this->stack.isEmpty()) {
		qDebug("Stack is empty");
		return 0;
	}

	return this->stack.pop();
}

bool ShUndoTaker::IsEmpty() {

	return this->stack.isEmpty();
}

void ShUndoTaker::DeleteAll() {

	while (!this->IsEmpty())
		delete this->Pop();

}