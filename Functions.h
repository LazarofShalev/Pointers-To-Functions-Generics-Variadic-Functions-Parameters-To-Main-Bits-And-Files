#ifndef __Functions_H
#define __Functions_H

#include "Hotel.h"
#include "Room.h"

const char answersArray[7][40] =
{
	"does the room has view to the pool?",
	"does the room has a balcony?",
	"does the room has a kettle?",
	"does the room has free wifi?",
	"does the room has open couch?",
	"does the room has a television?",
	"is the room taken?"
};

int checkTheRoomAttribute(room *selectedRoom, int attributeIndex)
{
	unsigned char mask = 1;
	mask = mask << attributeIndex;
	if ((selectedRoom->allAttributsValues & mask) == 0)
		return 0;
	else
		return 1;
}

void updateTheRoomAttribute(room *selectedRoom, int index, int answer)
{
	unsigned char mask = 1;
	unsigned char result;
	mask <<= index;
	if (answer == 1)
		selectedRoom->allAttributsValues = selectedRoom->allAttributsValues | mask;
	else{
		mask = ~mask;
		selectedRoom->allAttributsValues = selectedRoom->allAttributsValues & mask;
	}
}

void printRoomInformation(room *selectedRoom, int roomNumber)
{
	int attributeValue;

	printf("\nnumber of beds in room %d: %d\n", roomNumber, selectedRoom->numOfBeds);

	for (int index = 0; index < 7; index++)
	{
		attributeValue = checkTheRoomAttribute(selectedRoom, index);
		if (attributeValue == 1)
			printf("%s -> Yes", answersArray[index]);
		else
			printf("%s -> No", answersArray[index]);
		printf("\n");
	}
	printf("\n");
}

void receiveRoomInformation(room *selectedRoom, int roomNumber)
{
	int answer;
	selectedRoom->allAttributsValues = 0;

	printf("\nroom Information receiving system\n");
	printf("please enter how many bads are in room %d: ", roomNumber);
	scanf("%d", &(selectedRoom->numOfBeds));

	selectedRoom->allAttributsValues = 0;

	printf("answer on the next questions please, 1 means yes, 0 means no\n\n");
	for (int index = 0; index < 7; index++)
	{
		do
		{
			flushall();
			printf("%s :", answersArray[index]);
			scanf("%d", &answer);
		} while (!(0 == answer || answer == 1));
		updateTheRoomAttribute(selectedRoom, index, answer);
	}
}

void receiveHotelInformation(hotel *theHotel)
{
	flushall();
	printf("\nhotel Information receiving system\n");
	do
	{
		printf("Please enter How many floors are in the hotel: ");
		scanf("%d", &theHotel->floorsAmmount);
	} while (!(0 < theHotel->floorsAmmount));

	do
	{
		printf("Please enter How many rooms are in the hotel: ");
		scanf("%d", &theHotel->roomsAmmount);
	} while (!(0 < theHotel->roomsAmmount));

	theHotel->roomsMatrix = (room**)calloc(theHotel->floorsAmmount, sizeof(room*));

	if (!theHotel->roomsMatrix)
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	for (int i = 0; i < theHotel->floorsAmmount; i++)
	{
		theHotel->roomsMatrix[i] = (room*)calloc(theHotel->roomsAmmount, sizeof(room));
	}

	if (!theHotel->floorsAmmount)
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	for (int i = 0; i < theHotel->floorsAmmount; i++)
	{
		for (int j = 0; j < theHotel->roomsAmmount; j++)
		{
			int roomNumber = ((i + 1) * 100 + j);
			receiveRoomInformation(&(theHotel->roomsMatrix[i][j]), roomNumber);
		}
	}
}

void printRoomsInformationUpholdTheAttribute(hotel *theHotel, int attributeIndex)
{
	for (int i = 0; i < theHotel->floorsAmmount; i++)
	{
		for (int j = 0; j < theHotel->roomsAmmount; j++)
		{
			if ((checkTheRoomAttribute(&(theHotel->roomsMatrix[i][j]), attributeIndex) == 1))
			{
				int roomNumber = ((i + 1) * 100 + j);
				printRoomInformation(&(theHotel->roomsMatrix[i][j]), roomNumber);
			}
		}
	}
}

void printHotelInformation(hotel *theHotel)
{
	printf("\nHotel Information: \n");
	printf("number of floors: %d\n", theHotel->floorsAmmount);
	printf("number of rooms in every floor: %d\n", theHotel->roomsAmmount);

	printf("\nRooms information: \n");

	for (int i = 0; i < theHotel->floorsAmmount; i++)
	{
		for (int j = 0; j < theHotel->roomsAmmount; j++)
		{
			int roomNumber = ((i + 1) * 100 + j);
			printRoomInformation(&(theHotel->roomsMatrix[i][j]), roomNumber);
		}
	}
}

void updateTheBit(char *tempChar, int index, int answer)
{
	unsigned char mask = 1;
	unsigned char result;

	mask <<= index;

	if (answer == 1)
		*tempChar = *tempChar | mask;
	else
	{
		mask = ~mask;
		*tempChar = *tempChar & mask;
	}
}

void flipTheBits(int x, char *tempByte)
{
	unsigned char mask1 = 1;
	unsigned char mask2 = 1;

	mask1 <<= x;

	if (x != 7)
		mask2 <<= (x + 1);

	mask1 = mask1 & *tempByte;
	mask2 = mask2 & *tempByte;

	if (mask1 == 0 && mask2 != 0)
	{
		updateTheBit(&*tempByte, x, 1);
		if (x != 7)
			updateTheBit(&*tempByte, x + 1, 0);
		else
			updateTheBit(&*tempByte, 0, 0);
	}
	else if (mask1 != 0 && mask2 == 0)
	{
		updateTheBit(&*tempByte, x, 0);
		if (x != 7)
			updateTheBit(&*tempByte, x + 1, 1);
		else
			updateTheBit(&*tempByte, 0, 1);
	}
	else if (mask1 != 0 && mask2 != 0)
	{
		updateTheBit(&*tempByte, x, 1);
		if (x != 7)
			updateTheBit(&*tempByte, x + 1, 1);
		else
			updateTheBit(&*tempByte, 0, 1);
	}
	else
	{
		updateTheBit(&*tempByte, x, 0);
		if (x != 7)
			updateTheBit(&*tempByte, x + 1, 0);
		else
			updateTheBit(&*tempByte, 0, 0);
	}
}

void encryption(void *variableToEncrypt, int variableSize, FILE *variableFile)
{

	int x = rand() % (7 - 0) + 0;

	fprintf(variableFile, "%d\n", x);

	unsigned char mask1;
	unsigned char mask2;

	char tempByte;
	char *encrypt = (char*)variableToEncrypt;

	for (int i = 0; i < variableSize; i++)
	{
		tempByte = *(encrypt + i);

		flipTheBits(x, &tempByte);

		for (int i = 0; i < x; i++)
		{
			mask1 = 1;
			mask1 = mask1 & tempByte;

			if (mask1 != 0)
			{
				tempByte = tempByte >> 1;
				updateTheBit(&tempByte, 7, 1);
			}
			else

			{
				tempByte = tempByte >> 1;
				updateTheBit(&tempByte, 7, 0);
			}
		}
		*(encrypt + i) = *(encrypt + i) & 0;
		*(encrypt + i) = *(encrypt + i) & 1;
		*(encrypt + i) = *(encrypt + i) | tempByte;
	}

	fflush(variableFile);
	int fclose(FILE* variableFile);
}

void decryption(void *variabletoDecrypt, int variableSize, FILE *variableFile)
{

	int x;
	unsigned char mask1;
	unsigned char mask2;

	fscanf(variableFile, "%d\n", &x);

	char tempByte;
	char *encrypt = (char*)variabletoDecrypt;

	for (int i = 0; i < variableSize; i++)
	{

		tempByte = *(encrypt + i);
		for (int i = 0; i < x; i++)
		{
			mask1 = 128;
			mask1 = mask1 & tempByte;

			if (mask1 != 0)
			{
				tempByte = tempByte << 1;
				updateTheBit(&tempByte, 0, 1);
			}
			else
			{
				tempByte = tempByte << 1;
				updateTheBit(&tempByte, 0, 0);
			}
		}
		mask1 = 1;
		mask2 = 1;
		mask1 <<= x;
		if (x != 7)
			mask2 <<= (x + 1);

		mask1 = mask1 & tempByte;
		mask2 = mask2 & tempByte;

		flipTheBits(x, &tempByte);

		*(encrypt + i) = *(encrypt + i) & 0;
		*(encrypt + i) = *(encrypt + i) & 1;
		*(encrypt + i) = *(encrypt + i) | tempByte;
	}
}

void encryptToFile(hotel *theHotel)
{
	FILE* roomsFile = fopen("roomsEncryptedData.bin", "ab");
	if (roomsFile == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	FILE* veriablesFile = fopen("xVariable.txt", "a");
	if (veriablesFile == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	int floorAmmountBeforeEncrypt = theHotel->floorsAmmount;
	int roomsAmmountBeforeEncrypt = theHotel->roomsAmmount;

	encryption(&(theHotel->floorsAmmount), sizeof(int), veriablesFile);
	encryption(&(theHotel->roomsAmmount), sizeof(int), veriablesFile);

	fwrite(&(theHotel->floorsAmmount), sizeof(int), 1, roomsFile);
	fwrite(&(theHotel->roomsAmmount), sizeof(int), 1, roomsFile);

	for (int i = 0; i < floorAmmountBeforeEncrypt; i++)
	{
		for (int j = 0; j < roomsAmmountBeforeEncrypt; j++)
		{
			encryption(&(theHotel->roomsMatrix[i][j].numOfBeds), sizeof(int), veriablesFile);
			encryption(&(theHotel->roomsMatrix[i][j].allAttributsValues), sizeof(int), veriablesFile);
			fwrite(&(theHotel->roomsMatrix[i][j].numOfBeds), sizeof(int), 1, roomsFile);
			fwrite(&(theHotel->roomsMatrix[i][j].allAttributsValues), sizeof(int), 1, roomsFile);
		}
	}
	fclose(veriablesFile);
	fclose(roomsFile);

	for (int i = 0; i < floorAmmountBeforeEncrypt; i++)
	{
		free(theHotel->roomsMatrix[i]);
	}
}

void decryptTheFile(hotel *theHotel)
{
	FILE* roomsFile = fopen("roomsEncryptedData.bin", "rb");
	if (roomsFile == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}
	FILE* veriablesFile = fopen("xVariable.txt", "r");
	if (veriablesFile == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		return;
	}

	fread(&(theHotel->floorsAmmount), sizeof(int), 1, roomsFile);
	fread(&(theHotel->roomsAmmount), sizeof(int), 1, roomsFile);

	decryption(&(theHotel->floorsAmmount), sizeof(int), veriablesFile);
	decryption(&(theHotel->roomsAmmount), sizeof(int), veriablesFile);

	theHotel->roomsMatrix = (room**)calloc(theHotel->floorsAmmount, sizeof(room*));

	if (!theHotel->roomsMatrix)
	{
		printf("ERROR! Not enough memory!\n");
		exit(1);
	}

	for (int i = 0; i < theHotel->floorsAmmount; i++)
	{
		theHotel->roomsMatrix[i] = (room*)calloc(theHotel->roomsAmmount, sizeof(room));
	}

	for (int i = 0; i < theHotel->floorsAmmount; i++)
	{
		for (int j = 0; j < theHotel->roomsAmmount; j++)
		{
			fread(&(theHotel->roomsMatrix[i][j].numOfBeds), sizeof(int), 1, roomsFile);
			fread(&(theHotel->roomsMatrix[i][j].allAttributsValues), sizeof(int), 1, roomsFile);
			decryption(&(theHotel->roomsMatrix[i][j].numOfBeds), sizeof(int), veriablesFile);
			decryption(&(theHotel->roomsMatrix[i][j].allAttributsValues), sizeof(int), veriablesFile);
		}
	}
	fclose(veriablesFile);
	fclose(roomsFile);
}

void indicatorForMultipleRooms(int indecetor, room *roomToCheck, ...)
{
	va_list rooms;
	room* currentRoom;
	int i = 0;
	va_start(rooms, roomToCheck);
	currentRoom = roomToCheck;
	while (currentRoom != NULL)
	{
		if (checkTheRoomAttribute(currentRoom, indecetor) == 1)
		{
			printRoomInformation(currentRoom, (100 + i));
		}
		currentRoom = va_arg(rooms, room*);
		i++;
	}
	va_end(rooms);

}

#endif