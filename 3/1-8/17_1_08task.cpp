#include "os_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable: 4996)

struct Dir {
	char name[33];
	int size = 0;
	int children_num = 0;
	struct Dir* parent = NULL;
	struct Dir** children = NULL;
};

bool is_fm_created = false;
int free_size = 0;
Dir* root = NULL;
Dir* cur_dir = NULL;

int create(int disk_size) {
	if (is_fm_created) return 0;

	free_size = disk_size;

	root = (Dir*)malloc(sizeof(Dir));

	strcpy(root->name, "/");
	root->size = 0;
	root->children_num = 0;
	root->parent = NULL;
	root->children = NULL;

	cur_dir = root;

	is_fm_created = true;

	return 1;
}

void destroy_dir(Dir* temp_cur_dir) {
	if (temp_cur_dir->children != NULL) {
		for (int i = 0; i < temp_cur_dir->children_num; i++) destroy_dir(temp_cur_dir->children[i]);
		free(temp_cur_dir->children);
	}

	if (cur_dir == temp_cur_dir) cur_dir = root;

	free(temp_cur_dir);
}

int destroy() {
	if (!is_fm_created) return 0;

	destroy_dir(root);

	root = NULL;
	cur_dir = NULL;

	free_size = 0;
	is_fm_created = false;

	return 1;
}

// the length of the given path and memory allocation for the given path
char* save_path(const char* path, int* path_len) {
	*path_len = strlen(path) + 1;
	char* temp_path = (char*)malloc(*path_len * sizeof(char));
	strcpy(temp_path, path);
	return temp_path;
}

// absolute or relative path
Dir* path_type(char* path, int* type) {
	if (path[0] == '/') {
		*type = 1;
		return root;
	}
	return cur_dir;
}

Dir* next_dir(char* path, Dir* dir, int dir_index, int* next_dir_index, int file_size, bool is_find, bool is_copy) {
	int i = dir_index, k = 0;
	char dir_name[33];

	for (i; i < (dir_index + 32) && path[i] != '/' && path[i] != '\0'; i++, k++) {
		if (((path[i] >= 'a') && (path[i] <= 'z')) ||
			((path[i] >= 'A') && (path[i] <= 'Z')) ||
			((path[i] >= '0') && (path[i] <= '9')) ||
			(path[i] == '_') || (path[i] == '.'))
			dir_name[k] = path[i];
		else return NULL;
	}

	dir_name[k] = '\0';

	if (path[i] == '/') {
		*next_dir_index = i;

		if (strcmp(dir_name, ".") == 0) return dir;
		else if ((strcmp(dir_name, "..") == 0) && (dir != root)) return dir->parent;
		else {
			for (int j = 0; j < dir->children_num; j++)
				if (strcmp(dir->children[j]->name, dir_name) == 0) return dir->children[j];
			return NULL;
		}
	}
	else if (path[i] == '\0') {
		*next_dir_index = i;

		if ((strcmp(dir_name, ".") == 0)) {
			if (is_find) return dir;
			return NULL;
		}

		if ((strcmp(dir_name, "..") == 0)) {
			if (is_find) return dir->parent;
			return NULL;
		}

		if (dir->children_num != 0) {
			for (int j = 0; j < dir->children_num; j++) {
				if (strcmp(dir->children[j]->name, dir_name) == 0) {
					if (is_find) return dir->children[j];
					return NULL;
				}
			}
		}

		// copy function ignores the last dir (does not exist yet)
		if (is_copy) return dir;
		
		// found no dir with the given name
		if (is_find) return NULL;

		// unable to create anything inside a file
		if (dir->size != 0) return NULL;

		if (dir->children == NULL) dir->children = (Dir**)malloc(sizeof(Dir*));
		else dir->children = (Dir**)realloc(dir->children, (dir->children_num + 1) * sizeof(Dir*));

		dir->children[dir->children_num] = (Dir*)malloc(sizeof(Dir));

		strcpy(dir->children[dir->children_num]->name, dir_name);
		dir->children[dir->children_num]->size = file_size;
		dir->children[dir->children_num]->parent = dir;
		dir->children[dir->children_num]->children = NULL;
		dir->children[dir->children_num]->children_num = 0;

		dir->children_num++;

		return dir->children[dir->children_num - 1];
	}
}

int create_dir(const char* path) {
	if (!is_fm_created) return 0;

	int type = 0, next = 0, path_len = 0;
	char* temp_path = NULL;

	temp_path = save_path(path, &path_len);

	Dir* temp_cur_dir;
	
	temp_cur_dir = path_type(temp_path, &type);

	for (int i = type; i < path_len; i++) {
		temp_cur_dir = next_dir(temp_path, temp_cur_dir, i, &next, 0, false, false);
		i = next;

		if (temp_cur_dir == NULL) {
			free(temp_path);
			return 0;
		}
	}

	free(temp_path);

	return 1;
}

int create_file(const char* path, int file_size) {
	if (!is_fm_created || file_size < 0 || file_size > free_size) return 0;

	int type = 0, next = 0, path_len = 0;
	char* temp_path = NULL;

	temp_path = save_path(path, &path_len);

	Dir* temp_cur_dir;

	temp_cur_dir = path_type(temp_path, &type);

	for (int i = type; i < path_len; i++) {
		if (temp_cur_dir->size == 0) {
			temp_cur_dir = next_dir(temp_path, temp_cur_dir, i, &next, file_size, false, false);
			i = next;
		}
		else {
			free(temp_path);
			return 0;
		}

		if (temp_cur_dir == NULL) {
			free(temp_path);
			return 0;
		}
	}

	free_size -= file_size;

	free(temp_path);

	return 1;
}

// find the size (recursive)
void count_size(Dir* temp_cur_dir, int* size) {
	if (temp_cur_dir->size != 0) *size += temp_cur_dir->size;
	else {
		for (int i = 0; i < temp_cur_dir->children_num; i++)
			count_size(temp_cur_dir->children[i], size);
	}
}

int size(const char* path) {
	if (!is_fm_created) return -1;

	int type = 0, next = 0, path_len = 0;
	char* temp_path = NULL;

	temp_path = save_path(path, &path_len);

	Dir* temp_cur_dir;

	temp_cur_dir = path_type(temp_path, &type);

	for (int i = type; i < path_len; i++) {
		temp_cur_dir = next_dir(temp_path, temp_cur_dir, i, &next, 0, true, false);
		i = next;

		if (temp_cur_dir == NULL) {
			free(temp_path);
			return -1;
		}
	}

	free(temp_path);

	int dir_file_size = 0;

	count_size(temp_cur_dir, &dir_file_size);

	return dir_file_size;
}

void remove_child(Dir* child) {
	for (int i = 0; i < child->parent->children_num; i++) {
		if (child->parent->children[i] == child) {
			// move the child to the end and remove the child
			for (int j = i; j < child->parent->children_num - 1; j++)
				child->parent->children[j] = child->parent->children[j + 1];
			child->parent->children = (Dir**)realloc(child->parent->children, (child->parent->children_num - 1) * sizeof(Dir*));
			child->parent->children_num--;
			break;
		}
	}
}

int remove(const char* path, int recursive) {
	if (!is_fm_created) return 0;

	int type = 0, next = 0, path_len = 0;
	char* temp_path = NULL;

	temp_path = save_path(path, &path_len);

	Dir* temp_cur_dir;

	temp_cur_dir = path_type(temp_path, &type);

	for (int i = type; i < path_len; i++) {
		temp_cur_dir = next_dir(temp_path, temp_cur_dir, i, &next, 0, true, false);
		i = next;

		if (temp_cur_dir == NULL) {
			free(temp_path);
			return 0;
		}
	}

	free(temp_path);

	// check remove
	if (temp_cur_dir->children != NULL && recursive == 0) return 0;

	// find the size of the dir (file) which will be deleted
	int dir_file_size = size(path);

	// remove the dir (file) from parent + remove the dir (file) and its children
	remove_child(temp_cur_dir);
	destroy_dir(temp_cur_dir);

	// resize
	free_size += dir_file_size;

	return 1;
}

int change_dir(const char* path) {
	if (!is_fm_created) return 0;

	int type = 0, next = 0, path_len = 0;
	char* temp_path = NULL;

	temp_path = save_path(path, &path_len);

	Dir* temp_cur_dir;

	temp_cur_dir = path_type(temp_path, &type);

	for (int i = type; i < path_len; i++) {
		temp_cur_dir = next_dir(temp_path, temp_cur_dir, i, &next, 0, true, false);
		i = next;

		if (temp_cur_dir == NULL) {
			free(temp_path);
			return 0;
		}
	}

	cur_dir = temp_cur_dir;

	free(temp_path);

	return 1;
}

void get_cur_dir(char* dst) {
	int len = 0, dst_len = 0;

	dst[0] = '\0';

	Dir* temp_dir;
	temp_dir = cur_dir;

	while (temp_dir != root) {
		len = strlen(temp_dir->name);
		dst_len = strlen(dst) + 1;

		// moves dst name
		for (int i = len + dst_len; i > len; i--) dst[i] = dst[i - len - 1];

		dst[0] = '/';

		// adds dir name to dst
		for (int i = 1; i <= len; i++)
			dst[i] = temp_dir->name[i - 1];

		temp_dir = temp_dir->parent;
	}
}

void copy_dir_file(Dir* dir, Dir* to_dir, int* num) {
	for (int j = 0; j < to_dir->children_num; j++) {
		if (strcmp(to_dir->children[j]->name, dir->parent->name) == 0) to_dir = to_dir->children[j];
	}

	// create one dir (file)
	if (to_dir->children == NULL) to_dir->children = (Dir**)malloc(sizeof(Dir*));
	else to_dir->children = (Dir**)realloc(to_dir->children, (to_dir->children_num + 1) * sizeof(Dir*));

	to_dir->children[to_dir->children_num] = (Dir*)malloc(sizeof(Dir));

	strcpy(to_dir->children[to_dir->children_num]->name, dir->name);
	to_dir->children[to_dir->children_num]->size = dir->size;
	to_dir->children[to_dir->children_num]->parent = to_dir;
	to_dir->children[to_dir->children_num]->children = NULL;
	to_dir->children[to_dir->children_num]->children_num = 0;

	to_dir->children_num++;

	// count the number of copied files
	if (dir->size != 0) (*num)++;

	// copy children if they exist (recursive)
	if (dir->children != NULL) {
		for (int i = 0; i < dir->children_num; i++) copy_dir_file(dir->children[i], to_dir, num);
	}
}

int copy(const char* path, const char* to_path) {
	if (!is_fm_created) return -1;

	int type_1 = 0, next_1 = 0, path_len_1 = 0;
	char* temp_path_1 = NULL;

	temp_path_1 = save_path(path, &path_len_1);

	Dir* temp_cur_dir_1;

	temp_cur_dir_1 = path_type(temp_path_1, &type_1);

	for (int i = type_1; i < path_len_1; i++) {
		temp_cur_dir_1 = next_dir(temp_path_1, temp_cur_dir_1, i, &next_1, 0, true, false);
		i = next_1;

		if (temp_cur_dir_1 == NULL) {
			free(temp_path_1);
			return -1;
		}
	}

	free(temp_path_1);

	int type_2 = 0, next_2 = 0, path_len_2 = 0;
	char* temp_path_2 = NULL;

	temp_path_2 = save_path(to_path, &path_len_2);

	Dir* temp_cur_dir_2;

	temp_cur_dir_2 = path_type(temp_path_2, &type_2);

	for (int i = type_2; i < path_len_2; i++) {
		temp_cur_dir_2 = next_dir(temp_path_2, temp_cur_dir_2, i, &next_2, 0, true, true);
		i = next_2;

		if (temp_cur_dir_2 == NULL) {
			free(temp_path_2);
			return -1;
		}
	}

	free(temp_path_2);

	// check copy
	if (temp_cur_dir_1 == temp_cur_dir_2) return -1;
	if (temp_cur_dir_2->size != 0) return -1;

	// number of copied files
	int num = 0;

	copy_dir_file(temp_cur_dir_1, temp_cur_dir_2, &num);

	return num;
}

void setup_file_manager(file_manager_t* fm) {
	fm->create = create;
	fm->destroy = destroy;
	fm->create_dir = create_dir;
	fm->create_file = create_file;
	fm->remove = remove;
	fm->change_dir = change_dir;
	fm->get_cur_dir = get_cur_dir;
	fm->copy = copy;
	fm->size = size;
}
