#include "mmap.h"
#include "insert.h"

int main() {
	map_config conf(FILE_FOR_DEBUG);
	mmap m(conf);

	table t;
	cinfo c0 = make_type("todo\0", minfo::MINT, 10);
	cinfo c1 = make_type("date\0", minfo::MINT, 10);
	
	add_columns(t, c0);
	add_columns(t, c1);

	m.registry_table(t);

	const char* a[2];
	a[0] = "eat";
	a[1] = "today";
	
	char* res =  finsert(t,a);
	cout << res;
	insertf(m, t, res);
	
	return 0;
}



