

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Hotel.h"
#include "Room.h"
#include "Functions.h"

int main(int argc, char* argv[])
{
	int userChoise;
	hotel theHotel;

	printf("Hello And Welcome!\n");

	if (argv[1] != NULL)
	{
		if (strcmp(argv[1], "roomsEncryptedData.bin") == 0)
		{
			decryptTheFile(&theHotel);
			if (3 <= theHotel.roomsAmmount)
			{
				indicatorForMultipleRooms(1, &(theHotel.roomsMatrix[0][0]), &(theHotel.roomsMatrix[0][1]), &(theHotel.roomsMatrix[0][2]), NULL);
			}
		}
	}
	else
	{
		receiveHotelInformation(&theHotel);
	}

	do
	{
		flushall();
		printf("Press 1 To View The Hotel entire info\n");
		printf("Press 2 To print all the rooms available in the hotel Uphold specific attribute\n");
		printf("Press 0 to exit\n\n");
		printf("Please enter your choise: ");
		scanf("%d", &userChoise);
		printf("\n");

		switch (userChoise)
		{
		case 1:
		{
			printHotelInformation(&theHotel);
		}
		break;
		case 2:
		{
			int attribute;
			printf("Atrributes:\n");
			printf("0 for pool\n");
			printf("1 for balcony\n");
			printf("2 for kettle\n");
			printf("3 for free wifi\n");
			printf("4 for couch\n");
			printf("5 for television\n");
			printf("6 for taken or not taken\n");

			printf("please enter the attribute index:");

			scanf("%d", &attribute);

			printRoomsInformationUpholdTheAttribute(&theHotel, attribute);
		}
		break;
		case 0:
		{
			/*open the files and close in order to clear them before writing*/
			FILE* roomsFile = fopen("roomsEncryptedData.bin", "wb");
			if (roomsFile == NULL)
			{
				printf("Failed opening the file. Exiting!\n");
				return;
			}
			FILE* veriablesFile = fopen("xVariable.txt", "w");
			if (veriablesFile == NULL)
			{
				printf("Failed opening the file. Exiting!\n");
				return;
			}
			fclose(veriablesFile);
			fclose(roomsFile);

			encryptToFile(&theHotel);
			userChoise = 0;
		}
		break;
		default:
		{

		}
		break;
		}

	} while (userChoise != 0);
	system("pause");
}
