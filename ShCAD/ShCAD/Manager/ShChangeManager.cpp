
#include "ShChangeManager.h"
#include "Interface/StatusBar/ShStatusBar.h"
#include "Interface/Dock/ShCommandDock.h"

ShChangeManager ShChangeManager::instance;

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

ShChangeManager* ShChangeManager::getInstance() {

	return &(ShChangeManager::instance);
}

void ShChangeManager::Register(ShStatusBar *statusBar) {

	this->statusBar = statusBar;
}

void ShChangeManager::Register(ShCommandDock *commandDock) {

	this->commandDock = commandDock;
}

void ShChangeManager::notify(ShCADWidget *view, ShNotifyEvent *event) {

	//this->statusBar->Update(event);

}