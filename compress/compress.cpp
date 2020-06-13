#include <iostream>
#include <fstream> 
#include <sstream>

std::string compressImage(const std::string& image, int lines, int columns) {
	std::stringstream compressed;
	int sum = 0;
	size_t next, idx = 0;
	char ch;
	compressed << lines << " " << columns << " ";

	while (true) {
		ch = image[idx];
		next = image.find_first_not_of(ch, idx);

		if (next != std::string::npos) {
			compressed << next - idx << ch;
		}
		else {
			compressed << image.size() - idx << ch;
			break;
		}

		idx = next;
	}

	return compressed.str();
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Invalid number of arguments.";
		exit(1);
	}

	std::string uncompressedName, compressedName, image, compressedImage;
	std::fstream file;
	int lines, columns;

	uncompressedName = argv[1];
	compressedName = argv[2];

	file = std::fstream(uncompressedName, std::ios::in);

	if (!file.is_open()) {
		std::cerr << "File not found";
		exit(1);
	}

	file >> lines >> columns >> image;
	file.close();

	compressedImage = compressImage(image, lines, columns);

	file = std::fstream(compressedName, std::ios::out | std::ios::trunc);
	file << compressedImage;
	file.close();

	return 0;
}
