#include <stdio.h>

#define UBL '\0'
#define UBR '\1'
#define UFR '\2'
#define UFL '\3'
#define DFL '\4'
#define DFR '\5'
#define DBR '\6'
#define DBL '\7'

#define UB '\0'
#define UR '\1'
#define UF '\2'
#define UL '\3'
#define DF '\4'
#define DR '\5'
#define DB '\6'
#define DL '\7'
#define FL '\x08'
#define FR '\x09'
#define BR '\x0a'
#define BL '\x0b'

#define U 0
#define L 1
#define F 2
#define D 3
#define R 4
#define B 5

char cp[8];
char co[8];
char ep[12];
char eo[12];

const char c1[] = {
	1, 2, 0	
};
const char c2[] = {
	2, 0, 1	
};

void u() {
	char temp = cp[UBL];
	cp[UBL] = cp[UFL];
	cp[UFL] = cp[UFR];
	cp[UFR] = cp[UBR];
	cp[UBR] = temp;
	temp = co[UBL];
	co[UBL] = co[UFL];
	co[UFL] = co[UFR];
	co[UFR] = co[UBR];
	co[UBR] = temp;
	temp = ep[UB];
	ep[UB] = ep[UL];
	ep[UL] = ep[UF];
	ep[UF] = ep[UR];
	ep[UR] = temp;
	temp = eo[UB];
	eo[UB] = eo[UL];
	eo[UL] = eo[UF];
	eo[UF] = eo[UR];
	eo[UR] = temp;
}
void d() {
	char temp = cp[DFL];
	cp[DFL] = cp[DBL];
	cp[DBL] = cp[DBR];
	cp[DBR] = cp[DFR];
	cp[DFR] = temp;
	temp = co[DFL];
	co[DFL] = co[DBL];
	co[DBL] = co[DBR];
	co[DBR] = co[DFR];
	co[DFR] = temp;
	temp = ep[DF];
	ep[DF] = ep[DL];
	ep[DL] = ep[DB];
	ep[DB] = ep[DR];
	ep[DR] = temp;
	temp = eo[DF];
	eo[DF] = eo[DL];
	eo[DL] = eo[DB];
	eo[DB] = eo[DR];
	eo[DR] = temp;
}
void r() {
	char temp = cp[UFR];
	cp[UFR] = cp[DFR];
	cp[DFR] = cp[DBR];
	cp[DBR] = cp[UBR];
	cp[UBR] = temp;
	temp = co[UFR];
	co[UFR] = c1[co[DFR]];
	co[DFR] = c2[co[DBR]];
	co[DBR] = c1[co[UBR]];
	co[UBR] = c2[temp];
	temp = ep[UR];
	ep[UR] = ep[FR];
	ep[FR] = ep[DR];
	ep[DR] = ep[BR];
	ep[BR] = temp;
	temp = eo[UR];
	eo[UR] = eo[FR];
	eo[FR] = eo[DR];
	eo[DR] = eo[BR];
	eo[BR] = temp;
}
void l() {
	char temp = cp[UFL];
	cp[UFL] = cp[UBL];
	cp[UBL] = cp[DBL];
	cp[DBL] = cp[DFL];
	cp[DFL] = temp;
	temp = co[UFL];
	co[UFL] = c2[co[UBL]];
	co[UBL] = c1[co[DBL]];
	co[DBL] = c2[co[DFL]];
	co[DFL] = c1[temp];
	temp = ep[UL];
	ep[UL] = ep[BL];
	ep[BL] = ep[DL];
	ep[DL] = ep[FL];
	ep[FL] = temp;
	temp = eo[UL];
	eo[UL] = eo[BL];
	eo[BL] = eo[DL];
	eo[DL] = eo[FL];
	eo[FL] = temp;
}
void f() {
	char temp = cp[UFR];
	cp[UFR] = cp[UFL];
	cp[UFL] = cp[DFL];
	cp[DFL] = cp[DFR];
	cp[DFR] = temp;
	temp = co[UFR];
	co[UFR] = c2[co[UFL]];
	co[UFL] = c1[co[DFL]];
	co[DFL] = c2[co[DFR]];
	co[DFR] = c1[temp];
	temp = ep[UF];
	ep[UF] = ep[FL];
	ep[FL] = ep[DF];
	ep[DF] = ep[FR];
	ep[FR] = temp;
	temp = eo[UF];
	eo[UF] = !eo[FL];
	eo[FL] = !eo[DF];
	eo[DF] = !eo[FR];
	eo[FR] = !temp;
}
void b() {
	char temp = cp[UBL];
	cp[UBL] = cp[UBR];
	cp[UBR] = cp[DBR];
	cp[DBR] = cp[DBL];
	cp[DBL] = temp;
	temp = co[UBL];
	co[UBL] = c2[co[UBR]];
	co[UBR] = c1[co[DBR]];
	co[DBR] = c2[co[DBL]];
	co[DBL] = c1[temp];
	temp = ep[UB];
	ep[UB] = ep[BR];
	ep[BR] = ep[DB];
	ep[DB] = ep[BL];
	ep[BL] = temp;
	temp = eo[UB];
	eo[UB] = !eo[BR];
	eo[BR] = !eo[DB];
	eo[DB] = !eo[BL];
	eo[BL] = !temp;
}


void initCube() {
	for (int i = 0; i < 8; i++) {
		cp[i] = i;
		co[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		ep[i] = i;
		eo[i] = 0;
	}
}

void printCube() {
	for (int i = 0; i < 8; i++) {
		printf("%d ", cp[i]);
	}
	printf(" ");
	for (int i = 0; i < 8; i++) {
		printf("%d ", co[i]);
	}
	printf(" ");
	for (int i = 0; i < 12; i++) {
		printf("%d ", ep[i]);
	}
	printf(" ");
	for (int i = 0; i < 12; i++) {
		printf("%d ", eo[i]);
	}
	printf("\n");
}

// I love clang but why is function pointer notation so weird? 😭
void (*const move[6])() = {
	u, l, f, d, r, b
};

unsigned int seed;
unsigned int random() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	return seed ^= seed << 5;
}

void shuffle() {
	int prev = -1;
	for (int i = 0; i < 25; i++) {
		int idx;
		do {
			idx = random() % 6;
		} while (idx == prev);
		prev = idx;
		int count = random() % 3;
		if (count) {
			printf("%c%c ", "ULFDRB"[idx], "2\'"[count-1]);
		} else {
			printf("%c ", "ULFDRB"[idx]);
		}
		while (count-- >= 0) {
			move[idx]();
		}
	}
	printf("\n");
}