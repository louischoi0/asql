#include "element.h"



void add_columns(table& table , cinfo& column) {
	int mlen = COLUMN_HEADER;
	
	std::string name_string(column.cname);
	
	mlen += name_string.length();
	table.tt_alloc += mlen;
	table.sz_record += column.tsz;
	
	column.index = table.colcnt++;
	
	
	std::string header = std::string(IDF_CHEADER) + std::to_string(column.index);
	memcpy(column.header, header.c_str(), COLUMN_HEADER);

	if (table.columns) {
		link<cinfo>(*table.columns, column);
	}

	else {
		table.columns = new oned_list<cinfo>(column);
	}
}

cinfo make_type(const char* tname, const minfo m, int size) {
	cinfo res;
	
	res.cname = (char*)malloc(strlen(tname) + 1);
	memcpy(res.cname, tname, strlen(tname) + 1);

	res.tsz = size;
	res.ssz = strlen(tname) + 1;


	if (DYMINFO(m)) {	
		res.tsz = -1;
	}

	return res;
}

std::pair<char*, int> slize_table(table& t) {
	struct oned_list<cinfo>* pcol = t.columns;
	
	char* buffer = (char*)malloc(t.tt_alloc);
	char* pointer = buffer;

	memcpy(pointer, t.header , TABLE_HEADER);
	pointer += TABLE_HEADER;

	for (; pcol; pcol = pcol->next) {
		memcpy(pointer, pcol->element->header, COLUMN_HEADER);
		pointer += COLUMN_HEADER;
		memcpy(pointer, pcol->element->cname, pcol->element->ssz - 1);
		pointer += pcol->element->ssz - 1;
	}
	
	return std::pair<char*, int>(buffer, t.tt_alloc);
}
