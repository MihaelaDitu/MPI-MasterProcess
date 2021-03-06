// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include <time.h> 


int noOfProcceses = 5;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	srand(time(NULL));
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	bool isMaster = false;
	bool isOut = false;
	int generatedNumber = rand() % 10 + rank;
	while (isMaster == false) {
		for (int i = 0; i < noOfProcceses; i++) {
			if (i == noOfProcceses) {
				MPI_Send(&generatedNumber, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
			else {
				MPI_Send(&generatedNumber, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
			}
			int receivedNumber;
			if (i == 0) {
				MPI_Recv(&receivedNumber, 1, MPI_INT, noOfProcceses, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			else {
				MPI_Recv(&receivedNumber, 1, MPI_INT, i - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			if (receivedNumber > generatedNumber) {
				isOut = true;
				generatedNumber = receivedNumber;
			}
			else {
				if (isOut == false && receivedNumber == generatedNumber) {
					isMaster = true;
					printf("Process %d is master/n", rank);
				}
			}
		}
	}

	MPI_Finalize();
    return 0;
}

