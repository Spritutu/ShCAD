
#include "ShFootOfPerpendicularVisitor.h"
#include "Base\ShMath.h"
#include "Entity\Leaf\ShLine.h"
#include "Entity\Leaf\ShCircle.h"

ShFootOfPerpendicularVisitor::ShFootOfPerpendicularVisitor(double &perpendicularX, double &perpendicularY,
	const ShPoint3d& point)
	:perpendicularX(perpendicularX), perpendicularY(perpendicularY), point(point) {


}


ShFootOfPerpendicularVisitor::~ShFootOfPerpendicularVisitor() {

}

void ShFootOfPerpendicularVisitor::visit(ShLine *line) {

	ShLineData data = line->getData();

	double angle = math::getAbsAngle(data.start.x, data.start.y, data.end.x, data.end.y);
	double angleX, angleY;

	double x = point.x;
	double y = point.y;

	math::rotate(angle + 90, x, y, x + 10, y, angleX, angleY);
	ShPoint3d intersect;

	if (math::checkLineLineIntersect(data.start, data.end, ShPoint3d(x, y),
		ShPoint3d(angleX, angleY), intersect) == true) {

		this->perpendicularX = intersect.x;
		this->perpendicularY = intersect.y;

		return;
	}
}

void ShFootOfPerpendicularVisitor::visit(ShCircle *circle) {

	ShCircleData data = circle->getData();

	double angle = math::getAbsAngle(data.center.x, data.center.y, this->point.x, this->point.y);
	math::rotate(angle, data.center.x, data.center.y, data.center.x + data.radius, data.center.y,
		this->perpendicularX, this->perpendicularY);
}