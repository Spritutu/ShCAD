
#ifndef _SHLAYERTRANSACTION_H
#define _SHLAYERTRANSACTION_H

#include "ShTransaction.h"
#include "Data\ShPropertyData.h"

class ShCADWidget;
class ShLayer;

class ShChangeCurrentLayerTransaction : public ShTransaction {

private:
	ShCADWidget *widget;
	ShLayer *prev;
	ShLayer *current;

public:
	ShChangeCurrentLayerTransaction(ShCADWidget *widget, ShLayer *prev, ShLayer *current);

	virtual void redo();
	virtual void undo();

protected:
	~ShChangeCurrentLayerTransaction();

};

/////////////////////////////////////////////

class ShChangeLayerDataTransaction : public ShTransaction {

public:
	enum ChangedType {
		Color,
		LineStyle,
	};

private:
	ShCADWidget *widget;
	ShLayer *layer;
	ShPropertyData prev;
	ShPropertyData current;
	ChangedType changedType;

public:
	ShChangeLayerDataTransaction(ShCADWidget *widget, ShLayer *layer, const ShPropertyData &prev, const ShPropertyData &current, ChangedType changedType);
	
	virtual void redo();
	virtual void undo();

protected:
	~ShChangeLayerDataTransaction();

private:
	void changeLayerColor(const ShPropertyData &aboutToChange);
	void changeLayerLineStyle(const ShPropertyData &aboutToChange);
};

#endif //_SHLAYERTRANSACTION_H