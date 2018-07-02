#ifndef MMAP
#define MMAP

#define MM_HEADER_SIZE 1024
#define DEBUG_MODE 1

#include <fstream>
#include <iostream>
#include "element.h"

using namespace std;

#define FILE_FOR_DEBUG "db.db"
#define OFFSET_INITED_FLAG 0
#define SIZE_INITED_FLAG 4
#define INITED_OK_STR "init"

#define INIT_TABLE_OFFSET 128
#define INIT_TABLE_ALLOCD 256
#define INIT_RECORD 512

enum rConfig{
	recordHeader = 16
};


typedef struct map_config {
	void* sp_table;
	void* sp_record;

	int ntable;
	const char* nm_file;
	
	int tt_amount;

	map_config() {
		this->sp_table = 0;
		this->sp_record = 0;
		this->nm_file = 0;
	}

	map_config(const char* c) {
		this->sp_record = 0;
		this->sp_table = 0;
		this->nm_file = c;
	}

} map_config;

class mmap {
	map_config conf;
private:
	int of_record;
	int of_table;
	int ar_table;

public :

	mmap();
	mmap(const map_config& conf);

	void init(const char* c);
	void registry_table(table& i);

	const map_config get_config() {		return conf;	};
	int get_record_offset() { return of_record; };
	void record_offset_move(int a) { of_record += a; };


	~mmap();
};

void insertf(mmap& map, table& t, char* buffer);
bool check_first_insert(const char*);
bool check_first_commit(const char*);
void init_data_base(const map_config& idb);


#endif