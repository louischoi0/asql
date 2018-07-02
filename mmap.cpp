#include "mmap.h"
#include "element.h"
#include "os_win.h"

mmap::~mmap() {
	return;
}

mmap::mmap(const map_config& conf) :
	of_table(INIT_TABLE_OFFSET),
	ar_table(INIT_TABLE_ALLOCD),
	of_record(INIT_RECORD + recordHeader),
	conf(conf)
{
	if (check_first_commit(conf.nm_file)) {
		init_data_base(conf);
	}
}


bool check_first_commit(const char* ndb) {
	char check[SIZE_INITED_FLAG];
	int length;

	std::ifstream i(ndb);
	i.read(check, SIZE_INITED_FLAG);

	if (i.fail()) {
		std::cout << "failed" << std::endl;
	}

	i.seekg(0, std::ios::end);
	length = i.tellg();

#ifdef DEBUG_MODE
	std::cout << "Length : " << length << std::endl;
#endif

	if (length < SIZE_INITED_FLAG) {
		i.close();
		return true;
	}

	if ( strncmp(check, INITED_OK_STR,SIZE_INITED_FLAG) ) {
		i.close();
		return true;
	}

	i.close();
	return false;
}

void init_data_base(const map_config& idb) {
	std::ofstream of(idb.nm_file);
	of << INITED_OK_STR;
	of.close();
}

void mmap::registry_table(table& idb ) {
	auto res = slize_table(idb);
	write_file(this->conf.nm_file, res.first,res.second, INIT_TABLE_OFFSET);
}

void insertf(mmap& map, table& t, char* buffer) {
	map_config conf = map.get_config();
	write_file( conf.nm_file, buffer, t.sz_record, map.get_record_offset() );
	map.record_offset_move(t.sz_record);
}