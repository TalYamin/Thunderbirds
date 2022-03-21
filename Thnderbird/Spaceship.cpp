#include "Spaceship.h"

void SpaceShip::move(ShipSize size){

	switch (size)
	{
	case ShipSize::SMALL:
		break;
	case ShipSize::BIG:
		break;
	default:
		break;
	}
}


void SpaceShip::moveSmallShip() {

}

void SpaceShip::setMat(ShipSize size) {

	switch (size)
	{
	case ShipSize::SMALL:
		mat[0] = new Point; //free is needed
		mat[1] = new Point; //free is needed

		break;
	case ShipSize::BIG:
		mat[0] = new Point[2]; //free is needed
		mat[1] = new Point[2]; //free is needed
		break;
	default:
		break;
	}

}

void SpaceShip::setType(int typeNum) {
	type = static_cast<ShipSize>(typeNum);
}

SpaceShip::ShipSize SpaceShip::getType() {
	return type;
}

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}
