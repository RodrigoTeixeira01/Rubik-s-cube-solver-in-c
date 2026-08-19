#include <stdio.h>
#include <stdlib.h>

#include "cube.h"

#define BUFFER_SIZE 100
//#define PRINT_TABLES
//#define PRINT_CP_TABLE

int EOTable[2048];
int COTable[2187];
int EPTable[40320];
int CPTable[40320];

char solution1[BUFFER_SIZE];
// measures how many CHARACTERS solution1 is long
int solution1Length = 0;
char solution2[BUFFER_SIZE];
// measures how many CHARACTERS solution2 is long
int solution2Length = 0;

void cappedGenEOTable(int depth, int cap, int prev) {
	if (depth == cap) {
		int h = 0;
		for (int i = 0; i < 11; i++) {
			h = h * 2 + eo[i];
		}
		EOTable[h] = cap;
		return;
	}
	for (int idx = 0; idx < 6; idx++) {
		if (idx == prev || (idx > 2 && idx - 3 == prev)) {
			continue;
		}
		for (int count = 0; count < 3; count++) {
			move[idx]();
			cappedGenEOTable(depth + 1, cap, idx);
		}
		move[idx]();
	}
}
void genEOTable() {
	for (int i = 0; i < 2048; i++) {
		EOTable[i] = 7;
	}
	for (int cap = 6; cap >= 0; cap--) {
		cappedGenEOTable(0, cap, 0);
	}
	#ifdef PRINT_TABLES
		printf("EOTable:\n");
		for (int i = 0; i < 2048; i++) {
			printf("%d ", EOTable[i]);
		}
		printf("\n");
	#endif
}
void cappedGenCOTable(int depth, int cap, int prev) {
	if (depth == cap) {
		int h = 0;
		for (int i = 0; i < 7; i++) {
			h = h * 3 + co[i];
		}
		COTable[h] = cap;
		return;
	}
	for (int idx = 0; idx < 6; idx++) {
		if (idx == prev || (idx > 2 && idx - 3 == prev)) {
			continue;
		}
		for (int count = 0; count < 3; count++) {
			move[idx]();
			cappedGenCOTable(depth + 1, cap, idx);
		}
		move[idx]();
	}
}
void genCOTable() {
	for (int i = 0; i < 2187; i++) {
		COTable[i] = 6;
	}
	for (int cap = 5; cap >= 0; cap--) {
		cappedGenCOTable(0, cap, 0);
	}
	#ifdef PRINT_TABLES
		printf("COTable:\n");
		for (int i = 0; i < 2187; i++) {
			printf("%d ", COTable[i]);
		}
		printf("\n");
	#endif
}
void cappedGenEPTable(int depth, int cap, int prev) {
	if (depth == cap) {
		int h = 0;
		for (int i = 0; i < 7; i++) {
			int temp = ep[i];
			for (int j = 0; j < i; j++) {
				if (ep[j] < ep[i]) {
					temp--;
				}
			}
			
			h = h * (8-i) + temp;
		}
		EPTable[h] = cap;
		return;
	}
	for (int idx = 0; idx < 6; idx++) {
		if (idx == prev || (idx > 2 && idx - 3 == prev)) {
			continue;
		}
		for (int count = 0; count < 3; count++) {
			move[idx]();
			if (idx != 0 && idx != 3 && count != 1) {
				continue;
			}
			cappedGenEPTable(depth + 1, cap, idx);
		}
		move[idx]();
	}
}
void genEPTable() {
	for (int i = 0; i < 40320; i++) {
		EPTable[i] = 9;
	}
	for (int cap = 8; cap >= 0; cap--) {
		cappedGenEPTable(0, cap, 0);
	}
	#ifdef PRINT_EP_TABLE
		printf("EPTable:\n");
		int max = 0;
		for (int i = 0; i < 40320; i++) {
			printf("%d ", EPTable[i]);
			int Max(int a, int b);
			max = Max(max, EPTable[i]);
		}
		printf("\nMax = %d\n", max);
	#endif
}
void cappedGenCPTable(int depth, int cap, int prev) {
	if (depth == cap) {
		int h = 0;
		for (int i = 0; i < 7; i++) {
			int temp = cp[i];
			for (int j = 0; j < i; j++) {
				if (cp[j] < cp[i]) {
					temp--;
				}
			}
			
			h = h * (8-i) + temp;
		}
		CPTable[h] = cap;
		return;
	}
	for (int idx = 0; idx < 6; idx++) {
		if (idx == prev || (idx > 2 && idx - 3 == prev)) {
			continue;
		}
		for (int count = 0; count < 3; count++) {
			move[idx]();
			if (idx != 0 && idx != 3 && count != 1) {
				continue;
			}
			cappedGenCPTable(depth + 1, cap, idx);
		}
		move[idx]();
	}
}
void genCPTable() {
	for (int i = 0; i < 40320; i++) {
		CPTable[i] = 9;
	}
	for (int cap = 8; cap >= 0; cap--) {
		cappedGenCPTable(0, cap, 0);
	}
	#ifdef PRINT_CP_TABLE
		printf("CPTable:\n");
		int max = 0;
		for (int i = 0; i < 40320; i++) {
			printf("%d ", CPTable[i]);
			int Max(int a, int b);
			max = Max(max, CPTable[i]);
		}
		printf("\nMax = %d\n", max);
	#endif
}

int Max(int a, int b) {
	return a > b ? a : b;
}

int cappedBruteForceDR(int depth, int cap, int prev) {
	int EOidx = 0;
	for (int i = 0; i < 11; i++) {
		EOidx = EOidx * 2 + eo[i];
	}
	int COidx = 0;
	for (int i = 0; i < 7; i++) {
		COidx = COidx * 3 + co[i];
	}
	int h = Max(EOTable[EOidx], COTable[COidx]);
	if (h == 0) {
		for (int i = 8; i < 12; i++) {
			if (ep[i] < 8) {
				h = 1;
				goto notESlice;
			}
		}
		return -1;
	}
	notESlice:
	if (h + depth > cap) {
		return h + depth;
	}
	int min = 999;
	for (int idx = 0; idx < 6; idx++) {
		if (idx == prev || (idx > 2 && idx - 3 == prev)) {
			continue;
		}
		for (int count = 0; count < 3; count++) {
			move[idx]();
			int temp = cappedBruteForceDR(depth + 1, cap, idx);
			if (temp < min) {
				if (temp == -1) {
					//printf("%c%d ", "ULFDRB"[idx], count+1);
					solution1[solution1Length++] = ' ';
					switch (count) {
						case 1: {
							solution1[solution1Length++] = '2';
						} break;
						case 2: {
							solution1[solution1Length++] = '\'';
						} break;
					}
					solution1[solution1Length++] = "ULFDRB"[idx];
					return -1;
				}
				min = temp;
			}
		}
		move[idx]();
	}
	return min;
}
void bruteForceDR() {
	int cap = 0;
	while (cap > -1) {
		cap = cappedBruteForceDR(0, cap, -1);
	}
	printf("\n");
}

int cappedBruteForce(int depth, int cap, int prev) {
	int h1 = 0;
	for (int i = 0; i < 7; i++) {
		int temp = cp[i];
		for (int j = 0; j < i; j++) {
			if (cp[j] < cp[i]) {
				temp--;
			}
		}
		h1 = h1 * (8-i) + temp;
	}
	int h2 = 0;
	for (int i = 0; i < 7; i++) {
		int temp = ep[i];
		for (int j = 0; j < i; j++) {
			if (ep[j] < ep[i]) {
				temp--;
			}
		}
		h2 = h2 * (8-i) + temp;
	}
	int g = Max(CPTable[h1], EPTable[h2]);
	if (g == 0) {
		for (int i = 0; i < 11; i++) {
			if (ep[i] != i) {
				goto noReturn;
			}
		}
		//printf("h = %d; g = %d\n", h, g);
		return -1;
	}
	noReturn:
	if (g + depth > cap) {
		return g + depth;
	}
	int min = 999;
	for (int idx = 0; idx < 6; idx++) {
		if (idx == prev || (idx > 2 && idx - 3 == prev)) {
			continue;
		}
		for (int count = 0; count < 3; count++) {
			move[idx]();
			if (idx != 0 && idx != 3 && count != 1) {
				continue;
			}
			int temp = cappedBruteForce(depth + 1, cap, idx);
			if (temp < min) {
				if (temp == -1) {
					solution2[solution2Length++] = ' ';
					switch (count) {
						case 1: {
							solution2[solution2Length++] = '2';
						} break;
						case 2: {
							solution2[solution2Length++] = '\'';
						} break;
					}
					solution2[solution2Length++] = "ULFDRB"[idx];
					return -1;
				}
				min = temp;
			}
		}
		move[idx]();
	}
	return min;
}
void bruteForce() {
	int cap = 0;
	while (cap > -1) {
		cap = cappedBruteForce(0, cap, -1);
	}
}


int main(int argc, char **argv) {
	seed = time(NULL);
	initCube();
	printf("Generating tables...\n");
	genCOTable();
	genEOTable();
	genCPTable();
	genEPTable();
	shuffle();
	printCube();

	bruteForceDR();
	//printCube();
	while (solution1Length--) {
		putchar(solution1[solution1Length]);
	}
	bruteForce();
	while (solution2Length--) {
		putchar(solution2[solution2Length]);
	}
	printf("\n");
	printCube();

	return 0;
}
