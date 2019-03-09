

#include "ShSnapPointFinder.h"
#include "ShFootOfPerpendicularVisitor.h"
#include "Entity\Leaf\ShLine.h"
#include "ShMath.h"
ShSnapPointFinder::ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY,bool &isValid)
	:objectSnap(objectSnap), x(x), y(y), snapX(snapX), snapY(snapY),isValid(isValid),mode(Mode::Normal) {


}

ShSnapPointFinder::ShSnapPointFinder(ObjectSnap objectSnap, double x, double y, double &snapX, double &snapY, bool &isValid,
	double perpendicularX, double perpendicularY)
	: objectSnap(objectSnap), x(x), y(y), snapX(snapX), snapY(snapY), isValid(isValid), mode(Mode::FootOfPerpendicular),
	perpendicularX(perpendicularX), perpendicularY(perpendicularY) {

}

ShSnapPointFinder::~ShSnapPointFinder() {

}


void ShSnapPointFinder::Visit(ShLine *line) {

	if (this->objectSnap == ObjectSnap::ObjectSnapEndPoint) {
		
		ShLineData data = line->GetData();
		ShPoint3d start = data.start;
		ShPoint3d end = data.end;

		double disStart = Math::GetDistance(this->x, this->y, start.x, start.y);
		double disEnd = Math::GetDistance(this->x, this->y, end.x, end.y);

		if (Math::Compare(disStart, disEnd) == 1) {
			this->snapX = end.x;
			this->snapY = end.y;
		}
		else {
			this->snapX = start.x;
			this->snapY = start.y;
		}

		this->isValid = true;
		return;


	}
	else if (this->objectSnap == ObjectSnap::ObjectSnapMidPoint) {

		ShPoint3d mid = line->GetMid();

		this->snapX = mid.x;
		this->snapY = mid.y;
		this->isValid = true;
		return;
	}
	else if (this->objectSnap == ObjectSnap::ObjectSnapPerpendicular) {

		double x, y;

		if (mode == Mode::Normal) {
			x = this->x;
			y = this->y;
		}
		else {
			x = this->perpendicularX;
			y = this->perpendicularY;
		}
		
		ShFootOfPerpendicularVisitor visitor(this->snapX, this->snapY, ShPoint3d(x, y));
		line->Accept(&visitor);
		
		this->isValid = true;
		return;
		
	}

	this->isValid = false;

}

void ShSnapPointFinder::Visit(ShCircle *circle) {

}

void ShSnapPointFinder::Visit(ShArc *arc) {


}