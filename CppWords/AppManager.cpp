#include "AppManager.h"

#include <fstream>

using namespace std;

const int ENGLISH_ABC_CASE_DELTA = abs('A' - 'a');

long AppManager::get_checksum(ifstream& binaryFile){
	long result = 0;
	while (!binaryFile.eof()){
		char buf[4];
		binaryFile.read(buf, 4);

		unsigned long p = convert_bytes_to_ulong(buf);
		result += p;
	}
	return result;
}

int AppManager::get_found_words_count(ifstream& file, const char* word){
	int count = 0;
	int len = strlen(word);
	char ch;

	bool can_start_search = true;
	bool found_word = false;
	while (!file.eof())
	{
		for (int i = 0; i < len && !file.eof(); i++){
			file.get(ch);
			if (file.eof()) return count;

			char right = word[i];

			if (is_valid_char(right) && !is_valid_char(ch)){
				can_start_search = true;
				found_word = false;
				break;
			}

			if (found_word){
				can_start_search = false;
				found_word = false;
				count--;
			}

			if (!can_start_search) break;

			if (!are_equal(ch, right)){
				can_start_search = false;
				break;
			}
			if (i == len - 1){
				count++;
				can_start_search = false;
				found_word = true;
			}
		}
	}

	return count;
}

int AppManager::print_welcome(){
	*out << "Hello. Here's CppWords application. Use \"-h\" for help." << endl;
	return 0;
}

int AppManager::print_help(){
	*out << "CppWords application help." << "\n\n";
	*out << "Usage: \t\tcppwords.exe [-h] [[-f <file> [-m checksum|words -v <word>]]" << "\n\n";
	*out << "  -h\t\t\t\tPrints application manual." << "\n";
	*out << "  -f <file> -m checksum\t\tPrints checksum of <file>." << "\n";
	*out << "  -f <file> -w words -v <word>\tFinds number of occurences of word <word> in <file>." << "\n";
	return 0;
}

int AppManager::print_bad_arguments()
{
	*out << "Incorrent arguments are passed. Use \"-h\" for help." << endl;
	return 1;
}

int AppManager::print_checksum(const char* filename)
{
	ifstream binaryFile;
	binaryFile.open(filename, ios::in | ios::binary);
	int checksum = get_checksum(binaryFile);
	*out << checksum;
	return 0;
}

int AppManager::print_found_words_count(const char* filename, const char* word)
{
	ifstream file;
	file.open(filename, ios::in);
	int foundWordsCount = get_found_words_count(file, word);
	*out << foundWordsCount;
	return 0;
}

int AppManager::print_cannot_open_file(const char * filename)
{
	*err << "Could not open file: \"" << filename << "\"" << endl;
	return 2;
}

int AppManager::print_the_word_is_invalid(const char * word)
{
	*err << "The entered word is not suppored: \"" << word << "\"" << endl;
	*err << "Possible characters are [A-Z, a-z, 0-9], one word supported." << endl;
	return 2;
}

bool AppManager::file_can_be_opened(const char* filename){
	ifstream file(filename);
	if (file) return true;
	return false;
}

bool AppManager::is_word_valid(const char* word){
	int len = strlen(word);
	for (int i = 0; i < len; i++){
		if (!is_valid_char(word[i])){
			return false;
		}
	}
	return true;
}

bool are_equal(const char a, const char b){
	if (a == b) return true;
	if (abs(a - b) == ENGLISH_ABC_CASE_DELTA) return true;
	return false;
}

bool is_valid_char(const char c){
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= '0' && c <= '9') return true;
	return false;
}

unsigned long convert_bytes_to_ulong(char* bytes){
	return static_cast<unsigned long>(bytes[0]) |
		static_cast<unsigned long>(bytes[1]) << 8 |
		static_cast<unsigned long>(bytes[2]) << 16 |
		static_cast<unsigned long>(bytes[3]) << 24;
}