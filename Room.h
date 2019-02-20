#ifndef __Room_H
#define __Room_H

struct Room
{
	int numOfBeds;
	unsigned char allAttributsValues;
}typedef room;

int checkTheRoomAttribute(room *selectedRoom, int attributeIndex);
void updateTheRoomAttribute(room *selectedRoom, int index, int answer);
void printRoomInformation(room *selectedRoom, int roomNumber);
void receiveRoomInformation(room *selectedRoom, int roomNumber);
void indicatorForMultipleRooms(int indecetor, room *roomToCheck, ...);

#endif