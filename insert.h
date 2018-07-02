#ifndef INSERT
#define INSERT

#include "mmap.h"

enum qConfig {
	MIN_QUERY_STRING_LEN = 10,
	OP_CODES = 2
};


enum qOpLength {
	INSERT_INV = 6,
	DROP_INV = 4
};

enum qAction {
	QINSERT = 0,
	QDROP = 1,
	UNDEFINED = 100
};

static const char* opCodes[OP_CODES] = { "INSERT" , "DROP" };
static const qOpLength opCodesLen[OP_CODES] = { INSERT_INV, DROP_INV };
static const qAction opActions[OP_CODES] = { QINSERT, QDROP };

char* finsert(table& table, const char** cols);
int insert_routine(mmap* db, table* tinfo, char* buffer);
char* query(char* c);

char* query(char* qr);
qAction get_opcode(char* qr);


#endif

