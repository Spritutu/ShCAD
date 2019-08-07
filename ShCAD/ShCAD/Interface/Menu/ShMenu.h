
#ifndef _ShMENU_H
#define _ShMENU_H

#include <qmenu.h>
#include "Chain of Responsibility\ShChain.h"

class ShAbstractMenu : public QMenu, public ShChain {

public:
	ShAbstractMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	virtual ~ShAbstractMenu() = 0;

};

class ShEmptyDrawingFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;

public:
	ShEmptyDrawingFileMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShEmptyDrawingFileMenu();

	private slots:
	void newActionClicked();
};

class ShFileMenu : public ShAbstractMenu {

private:
	QAction *newAction;
	QAction *plotAction;
	QAction *previewAction;

public:
	ShFileMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShFileMenu();

	private slots:
	void newActionClicked();
};

class ShEditMenu : public ShAbstractMenu {

public:
	ShEditMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShEditMenu();

};

class ShDrawMenu : public ShAbstractMenu {

private:
	QAction *lineAction;

	QAction *polyLineAction;
	QAction *polygonAction;
	QAction *rectangleAction;

	QMenu *circleMenu;
	QAction *circleCenterRadiusAction;
	QAction *circleCenterDiameterAction;
	QAction *circleTwoPointAction;
	QAction *circleThreePointAction;

	QMenu *arcMenu;
	QAction *arcThreePointAction;
	QAction *arcStartCenterEndAction;
	QAction *arcStartCenterAngleAction;
	QAction *arcStartCenterLengthAction;
	QAction *arcStartEndAngleAction;
	QAction *arcStartEndDirectionAction;
	QAction *arcStartEndRadiusAction;
	QAction *arcCenterStartEndAction;
	QAction *arcCenterStartAngleAction;
	QAction *arcCenterStartLengthAction;

public:
	ShDrawMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShDrawMenu();

private:
	void createCircleMenu();
	void createArcMenu();
};

class ShModifyMenu : public ShAbstractMenu {

private:
	QAction *eraseAction;
	QAction *copyAction;
	QAction *mirrorAction;
	QAction *moveAction;
	QAction *rotateAction;
	QAction *scaleAction;
	QAction *stretchAction;
	QAction *trimAction;
	QAction *extendAction;

public:
	ShModifyMenu(const QString &title, ShChain *chain, QWidget *parent = nullptr);
	~ShModifyMenu();

};

#endif _MENU_H