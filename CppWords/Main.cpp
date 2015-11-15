// Main.cpp - точка входа

#include <iostream>
#include <string>

#include "AppManager.h"

using namespace std;

int main(int argc, char* argv[])
{
	AppManager app;

	if (argc < 2){
		return app.print_welcome();
	}

	if (strcmp(argv[1], "-h") == 0){
		return app.print_help();
	}

	if (argc < 5) {
		return app.print_bad_arguments();
	}

	if (strcmp(argv[1], "-f") == 0){
		const char * filename = argv[2];

		if (!AppManager::file_can_be_opened(filename)) {
			return app.print_cannot_open_file(filename);
		}

		if (strcmp(argv[3], "-m") == 0){
			if (strcmp(argv[4], "checksum") == 0){
				return app.print_checksum(filename);
			}
			if (argc == 7 && strcmp(argv[4], "words") == 0 && strcmp(argv[5], "-v") == 0){
				const char * word = argv[6];
				if (!AppManager::is_word_valid(word)){
					return app.print_the_word_is_invalid(word);
				}

				return app.print_found_words_count(filename, word);
			}
		}
	}

	return app.print_bad_arguments();
}
