#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <fstream>
#include <iostream>

using namespace std;

bool are_equal(const char a, const char b);
bool is_valid_char(const char c);
unsigned long convert_bytes_to_ulong(char* bytes);

class AppManager {

private:
	ostream* out;
	ostream* err;

	long get_checksum(ifstream& binaryFile);
	int get_found_words_count(ifstream& file, const char* word);
public:
	AppManager(ostream* out, ostream* err){
		this->out = out;
		this->err = err;
	}
	AppManager() : AppManager(&cout, &cerr){

	}

	int print_welcome();
	int print_help();
	int print_bad_arguments();
	int print_checksum(const char* filename);
	int print_found_words_count(const char* filename, const char* word);
	int print_cannot_open_file(const char* filename);
	int print_the_word_is_invalid(const char* word);
	static bool file_can_be_opened(const char* filename);
	static bool is_word_valid(const char* word);
};

#endif