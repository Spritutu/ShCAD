
#include "ShDecoratorActionFactory.h"
#include "ActionHandler\DecoratorAction\ShDecoratorDefaultAction.h"
#include "ActionHandler\DecoratorAction\ShOrthogonalAction.h"
#include "Data\ShDraftData.h"
#include "ActionHandler\DecoratorAction\ShDisposableSnapAction.h"
#include "ActionHandler\DrawAction\ShDrawLineAction.h"
#include <qdebug.h>

ShDecoratorActionFactory::ShDecoratorActionFactory() {

}

ShDecoratorActionFactory::~ShDecoratorActionFactory() {

}

ShDecoratorAction* ShDecoratorActionFactory::create(ShCADWidget *widget, ShActionHandler *actionHandler, const ShDraftData &draftData) {

	ShDecoratorAction *decoratorAction = new ShDecoratorDefaultAction(widget, actionHandler);

	if (draftData.getOrthMode() == true)
		decoratorAction = new ShOrthogonalAction(widget, actionHandler, decoratorAction);


	if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapNothing) {

	}

	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapEndPoint)
		decoratorAction = new ShDisposableSnapAction_End(widget, actionHandler, decoratorAction);
	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapMidPoint)
		decoratorAction = new ShDisposableSnapAction_Mid(widget, actionHandler, decoratorAction);
	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapCenter)
		decoratorAction = new ShDisposableSnapAction_Center(widget, actionHandler, decoratorAction);
	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapQuadrant)
		decoratorAction = new ShDisposableSnapAction_Quadrant(widget, actionHandler, decoratorAction);

	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapPerpendicular) {

		if (dynamic_cast<ShDrawLineAction*>(actionHandler)) {

			decoratorAction = ShDecoratorActionFactory::createLineActionPerpendicular(widget, actionHandler, decoratorAction);
		}
		else {

			decoratorAction = new ShDisposableSnapAction_Perpendicular(widget, actionHandler, decoratorAction);
		}
	}
	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapIntersection)
		decoratorAction = new ShDisposableSnapAction__Intersection(widget, actionHandler, decoratorAction);
	else if (draftData.getDisposableSnap() == ObjectSnap::ObjectSnapAppraentIntersection)
		decoratorAction = new ShDisposableSnapAction_ApparentIntersection(widget, actionHandler, decoratorAction);


	return decoratorAction;
}


ShDecoratorAction* ShDecoratorActionFactory::createLineActionPerpendicular(ShCADWidget *widget, ShActionHandler *actionHandler, ShDecoratorAction *child) {

	ShDecoratorAction *decoratorAction;

	ShDrawLineAction *drawLineAction = dynamic_cast<ShDrawLineAction*>(actionHandler);
	ShDrawLineAction::Status status = drawLineAction->getStatus();
	ShDrawLineAction::SubAction subAction = drawLineAction->getSubAction();

	if (status == ShDrawLineAction::Status::PickedStart &&
		subAction == ShDrawLineAction::SubAction::Default) {
	
		decoratorAction = new ShDisposableSnapAction_Perpendicular(widget, actionHandler, child);
	}
	else if (status == ShDrawLineAction::Status::PickedNothing &&
		subAction == ShDrawLineAction::SubAction::Default) {
	
		decoratorAction = new ShDisposableSnapAction_Perpendicular_DrawLineActionPickNothing(widget, actionHandler, child);
	}
	else if (status == ShDrawLineAction::Status::PickedStart &&
		subAction == ShDrawLineAction::SubAction::Perpendicular) {
	
		decoratorAction = new ShDisposableSnapAction_DrawLineActionPerPer(widget, actionHandler, child);
	}
	else {
	
		Q_ASSERT("ShDecoratorActionFactory::createLineActionPerpendicular() this can't be happend.");
	}
	
	return decoratorAction;
}