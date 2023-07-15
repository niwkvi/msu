#include "os_file.h"
#include <stdio.h>

int main()
{
	file_manager_t fm;
	setup_file_manager(&fm);

	fm.create(1000);

	int TOTAL_SIZE = 1000;

	fm.create(TOTAL_SIZE);
	fm.create_dir("dir1");
	fm.create_dir("dir1/dir11");
	fm.change_dir("dir1");
	fm.create_dir("../dir2");
	fm.create_dir("../dir2/dir3");
	fm.remove("/dir2/dir3", 0);
	fm.create_dir("/dir3/dir31");
	fm.create_dir("../dir3/dir31");
	fm.create_dir("../dir2");
	fm.create_file("/dir2/file1", 1);
	fm.create_dir("/dir2/dir21");
	fm.create_dir("/dir2/file1");
	fm.create_dir("../dir2/file1");
	fm.create_dir("../dir2/file1/dir");
	fm.create_dir("../dir2/dir22");

	fm.create_dir("../dir2/dir22/dir666");

	fm.change_dir("dir2");
	fm.change_dir("dir11");
	fm.remove("../../dir2/file1", 0);
	fm.create_dir("../../dir2/file1");
	fm.remove("../../dir2/file1", 0);
	fm.create_file("../../dir2/file1", 1);
	fm.change_dir(".");
	fm.change_dir("/dir1/dir11");
	fm.change_dir("/dir1/dir11/dir3");
	fm.change_dir("/dir1");
	//fm.change_dir("./dir11");
	//fm.change_dir("..");
	
	char* dst = (char*)malloc(6 * sizeof(char));

	fm.get_cur_dir(dst);
	printf("%s", dst);

	// /dir1

	fm.destroy();

	return 0;
}