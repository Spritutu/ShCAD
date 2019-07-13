
#include "ShCADWidgetDrawStrategy.h"
#include "ShCADWidgetDrawStrategyFactory.h"
#include "Interface\ShCADWidget.h"
#include <qpainter.h>
#include <qdebug.h>
ShCADWidgetDrawStrategy::ShCADWidgetDrawStrategy(ShCADWidget *widget, QPainter *painter)
	:widget(widget), painter(painter), strategy(nullptr) {

}

ShCADWidgetDrawStrategy::ShCADWidgetDrawStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	: widget(widget), painter(painter) {

	qDebug() << "yyyy" << drawType;
	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);

}


ShCADWidgetDrawStrategy::~ShCADWidgetDrawStrategy() {

	if (this->strategy != nullptr)
		delete this->strategy;
}

void ShCADWidgetDrawStrategy::draw() {

	qDebug() << "vvvvvvv";

	

	if (this->strategy != nullptr)
		this->strategy->draw();
}


ShDrawAllStrategy::ShDrawAllStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter) {

	qDebug() << "hhhh";
	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawAllStrategy::~ShDrawAllStrategy() {

}

void ShDrawAllStrategy::draw() {

	/*
	ShDrawer drawer(this->view, DrawType::DrawAll);

	this->view->axis.Draw(this->painter, this->view);

	QLinkedList<ShEntity*>::iterator itr;
	for (itr = this->view->entityTable.TurnOnLayerBegin(); itr != this->view->entityTable.TurnOnLayerEnd(); ++itr)
	(*itr)->Accept(&drawer);
	*/
	qDebug() << "asdsadasdasdsadasdasdasddas";

	this->widget->getAxis().draw(this->painter, this->widget);

	if (this->strategy != nullptr)
		this->strategy->draw();
}


//////////////////////////////////////////////////////////////


ShDrawCaptureImageStrategy::ShDrawCaptureImageStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawCaptureImageStrategy::	~ShDrawCaptureImageStrategy() {

}

void ShDrawCaptureImageStrategy::draw() {

	if (this->painter->isActive() == false)
		this->painter->begin(this->widget);

	this->painter->drawImage(0, 0, this->widget->getCaptureImage(), 0, 0, 0, 0);
	this->painter->end();

	if (this->strategy != nullptr)
		this->strategy->draw();
}



///////////////////////////////////////////////////////////////




ShDrawPreviewEntitiesStrategy::ShDrawPreviewEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType)
	:ShCADWidgetDrawStrategy(widget, painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawPreviewEntitiesStrategy::	~ShDrawPreviewEntitiesStrategy() {

}

void ShDrawPreviewEntitiesStrategy::draw() {

	/*
	ShDrawer drawer(this->view, DrawType::DrawPreviewEntities);

	if (this->view->rubberBand != NULL) {
	this->view->rubberBand->Accept(&drawer);
	}

	QLinkedList<ShEntity*>::iterator itr;



	for (itr = this->view->preview.Begin(); itr != this->view->preview.End(); ++itr)
	(*itr)->Accept(&drawer);

	*/


	if (this->strategy != nullptr)
		this->strategy->draw();
}



//////////////////////////////////////////////////////////////



ShDrawAddedEntitiesStrategy::ShDrawAddedEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType) 
	:ShCADWidgetDrawStrategy(widget, painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawAddedEntitiesStrategy::	~ShDrawAddedEntitiesStrategy() {

}

void ShDrawAddedEntitiesStrategy::draw() {

	/*
	ShDrawer drawer(this->view, DrawType::DrawAddedEntities);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->view->entityTable.JustAddedEntitiesBegin();
	itr != this->view->entityTable.JustAddedEntitiesEnd();
	++itr) {

	if ((*itr)->GetLayer()->IsTurnOn() == true)
	(*itr)->Accept(&drawer);
	}
	*/

	if (this->strategy != nullptr)
		this->strategy->draw();
}



//////////////////////////////////////////////////////////////



ShDrawSelectedEntitiesStrategy::ShDrawSelectedEntitiesStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType) 
	:ShCADWidgetDrawStrategy(widget, painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawSelectedEntitiesStrategy::~ShDrawSelectedEntitiesStrategy() {

}

void ShDrawSelectedEntitiesStrategy::draw() {

	/*
	ShDrawer drawer(this->view, DrawType::DrawSelectedEntities);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->view->selectedEntityManager.GetJustSelectedBegin();
	itr != this->view->selectedEntityManager.GetJustSelectedEnd();
	++itr) {

	(*itr)->Accept(&drawer);
	}

	*/

	if (this->strategy != nullptr)
		this->strategy->draw();
}



//////////////////////////////////////////////////////////////



ShDrawJustTurnOnLayerStrategy::ShDrawJustTurnOnLayerStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType) 
	:ShCADWidgetDrawStrategy(widget, painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawJustTurnOnLayerStrategy::	~ShDrawJustTurnOnLayerStrategy() {

}

void ShDrawJustTurnOnLayerStrategy::draw() {

	/*
	ShDrawer drawer(this->view, DrawType::DrawJustTurnOnLayer);

	QLinkedList<ShEntity*>::iterator itr;

	for (itr = this->view->entityTable.GetLayerTable()->GetJustTurnOnLayer()->Begin();
	itr != this->view->entityTable.GetLayerTable()->GetJustTurnOnLayer()->End();
	++itr) {

	(*itr)->Accept(&drawer);

	}
	*/
	if (this->strategy != nullptr)
		this->strategy->draw();
}



///////////////////////////////////////////////////////////////


ShDrawActionHandlerStrategy::ShDrawActionHandlerStrategy(ShCADWidget *widget, QPainter *painter, DrawType drawType) 
	:ShCADWidgetDrawStrategy(widget, painter) {

	this->strategy = ShCADWidgetDrawStrategyFactory::create(this->widget, this->painter, drawType);
}

ShDrawActionHandlerStrategy::~ShDrawActionHandlerStrategy() {

}

void ShDrawActionHandlerStrategy::draw() {

}

	