#ifndef __Hotel_H
#define __Hotel_H

#include "Room.h"

struct Hotel
{
	int floorsAmmount;
	int roomsAmmount;
	room **roomsMatrix;

}typedef hotel;

void receiveHotelInformation(hotel *theHotel);
void printHotelInformation(hotel *theHotel);
void printRoomsInformationUpholdTheAttribute(hotel *theHotel, int attributeIndex);

#endif