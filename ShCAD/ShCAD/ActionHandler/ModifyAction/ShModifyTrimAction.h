

#ifndef _SHMODIFYTRIMACTION_H
#define _SHMODIFYTRIMACTION_H

#include "ShModifyAction.h"

class ShTrimEntityTransaction;

class ShModifyTrimAction : public ShModifyAction {

private:
	ShTrimEntityTransaction *transaction;

public:
	ShModifyTrimAction(ShCADWidget *widget);
	~ShModifyTrimAction();

	virtual void mouseLeftPressEvent(ShActionData &data);
	virtual void mouseRightPressEvent(ShActionData &data);
	virtual void mouseMoveEvent(ShActionData &data);

	virtual ActionType getType();
	virtual QString getHeadTitle();


	virtual void invalidate(ShPoint3d &point);

	virtual void finishSelectingEntities();

protected:
	virtual void trigger(const ShPoint3d &point);

private:
	void trim(ShEntity *original, const QLinkedList<ShEntity*> &trimedEntities);

};

#endif //_SHMODIFYTRIMACTION_H