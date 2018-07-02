#pragma once
#include <utility>
#include <string>
#include <memory>
#include "node.h"

#define CHAR_SIZE 1
#define DYMINFO(x) (x == minfo::MTEXT) 

#define TABLE_HEADER 32

#define IDF_CHEADER "$c.."
#define IDF_TABLE "$t.."
#define IDF_RECORD "$r.."

#define COLUMN_HEADER 8



enum minfo{
	MINT = 1,
	MTEXT = 2
};

typedef struct cinfo {
	int index;
	minfo mi;
	int tsz;
	int ssz;

	char header[COLUMN_HEADER];
	char* cname;

	cinfo() {
		mi = minfo::MINT;
		cname = 0;
		tsz = 0;
		ssz = 0;
	}

} cinfo;

void set_string(char**, std::string);
void set_string(char** p, const char* c);
cinfo make_type(const char* tname, const minfo m, int size);

struct table {
	int colcnt;
	struct oned_list<cinfo>* columns;
	cinfo* info;

	int offset;
	int tt_alloc;
	int sz_record;

	char header[TABLE_HEADER];

	table() {
		columns = 0;
		info = 0;
		tt_alloc = TABLE_HEADER;
		sz_record = 0;
		memcpy(header, IDF_TABLE, strlen(IDF_TABLE));

		colcnt = 0;
	}
};

void add_columns(table&, cinfo& colum);
std::pair<char*, int> slize_table(table&);


