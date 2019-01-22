
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#include "ShChangeManager.h"
#include "Interface\ShGraphicView.h"
#include "Interface\ShStatusBar.h"
#include "ShNotifyEvent.h"
#include "Interface\Dock\ShCommandDock.h"
#include "ShWidgetManager.h"
#include "Interface\Ribbon\ShHomeTab.h"

ShChangeManager ShChangeManager::instance;

ShChangeManager::ShChangeManager() {

}

ShChangeManager::~ShChangeManager() {

}

ShChangeManager* ShChangeManager::GetInstance() {

	return &(ShChangeManager::instance);
}

void ShChangeManager::Register(ShStatusBar *statusBar) {

	this->statusBar = statusBar;
}

void ShChangeManager::Register(ShCommandDock *commandDock) {

	this->commandDock = commandDock;
}

void ShChangeManager::Register(ShPropertyColumn *propertyColumn) {

	this->propertyColumn = propertyColumn;
}

void ShChangeManager::Notify(ShGraphicView *view, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::MousePositionChanged) {

		ShMousePositionChangedEvent *event2 = dynamic_cast<ShMousePositionChangedEvent*>(event);
		this->statusBar->Update(event2->GetX(), event2->GetY(), event2->GetZ(), event2->GetZoomRate());
	}
	else if (event->GetType() == ShNotifyEvent::Type::ZoomRateChanged) {

		ShZoomRateChangedEvent *event2 = dynamic_cast<ShZoomRateChangedEvent*>(event);
		this->statusBar->Update(event2->GetX(), event2->GetY(), event2->GetZ(), event2->GetZoomRate());

	}
	else if (event->GetType() == ShNotifyEvent::Type::KeyPressed)
		this->commandDock->Update(dynamic_cast<ShKeyPressedEvent*>(event));

	else if (event->GetType() == ShNotifyEvent::Type::UpdateListText)
		this->commandDock->Update(dynamic_cast<ShUpdateListTextEvent*>(event));
	

	else if (event->GetType() == ShNotifyEvent::Type::ActivatedWidgetChanged) {
	
		this->commandDock->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));
		this->propertyColumn->Update(dynamic_cast<ShActivatedWidgetChangedEvent*>(event));

	}



}


void ShChangeManager::Notify(ShCommandDock* commandDock, ShNotifyEvent *event) {
	
	if (event->GetType() == ShNotifyEvent::Type::KeyPressed) {
	
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

	}

	
}

void ShChangeManager::Notify(ShPropertyColumn *propertyColumn, ShNotifyEvent *event) {

	if (event->GetType() == ShNotifyEvent::Type::PropertyColorComboSelChanged) {
		
		ShWidgetManager *manager = ShWidgetManager::GetInstance();

		if (manager->GetActivatedWidget() == 0)
			return;

		manager->GetActivatedWidget()->Update(event);

	}
}