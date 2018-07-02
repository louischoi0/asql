
#include "os.h"
#include "insert.h"

qAction get_opcode(char* qr){
	int len = strlen(qr);
	char* op = new char[MIN_QUERY_STRING_LEN];

	for (int i = 0; i < OP_CODES; i++) {

		if (strncmp(op, opCodes[i], opCodesLen[i]) == 0) {
			delete[] op;
			return opActions[i];
		}
	}

	delete[] op;
	return UNDEFINED;
}

int insert_routine(mmap* db, table* tinfo, char* buffer) {
	int of_record = db->get_record_offset();
	map_config conf = db->get_config();
	int record_size = tinfo->sz_record;

	write_file(conf.nm_file, buffer, record_size, of_record);

	return 0;
}

char* finsert(table& table, const char** cols) {
	int i = 0;
	const char** col_pointer = cols;
	auto it = table.columns;

	char* buffer = new char[table.sz_record];
	char* pointer = buffer;
	for ( ; it ; it = it->next , i++) {
		auto cont = it->element;
		memcpy(pointer, *col_pointer, strlen(*col_pointer));
		pointer += cont->tsz;
		col_pointer++;
	}

	return buffer;
}

char* query(char* qr) {
	int query_string_len = strlen(qr);
	char* OPQUERY = 0;


	if (query_string_len < MIN_QUERY_STRING_LEN) {
		cout << "Query is too short" << endl;
		return 0;
	}
}