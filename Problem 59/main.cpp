#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::string> commonWords{"the","of","to","and","a","in","is","it","you","that","he","was","for","on","are","with","as","I","his","they","be","at","one","have","this","from","or","had","by","hot","word","but","what","some","we","can","out","other","were","all","there","when","up","use","your","how","said","an","each","she","which","do","their","time","if","will","way","about","many","then","them","write","would","like","so","these","her","long","make","thing","see","him","two","has","look","more","day","could","go","come","did","number","sound","no","most","people","my","over","know","water","than","call","first","who","may","down","side","been","now","find","any","new","work","part","take","get","place","made","live","where","after","back","little","only","round","man","year","came","show","every","good","me","give","our","under","name","very","through","just","form","sentence","great","think","say","help","low","line","differ","turn","cause","much","mean","before","move","right","boy","old","too","same","tell","does","set"};

bool isNormal(char c) {
	if(ispunct(c) || isdigit(c) || isspace(c) || isalpha(c)) {
		return true;
	}
	return false;
}

int main() {
	std::ifstream file("p059_cipher.txt");
	std::vector<unsigned char> values;
	std::string converted;
	std::string max_converted;
	std::string current;
	char character;
	int maxScore{0}, maxAsciiSum, asciiSum;

	constexpr char lc_s{98}, lc_e{122};

	while(file.get(character)) {
		if(character != ',') {
			current += character;
		} else {
			values.push_back(static_cast<unsigned char>(std::stoi(current)));
			current.clear();
		}
	}
	if(!current.empty()) {
		values.push_back(static_cast<unsigned char>(std::stoi(current)));
		current.clear();
	}

	for(unsigned char i = lc_s; i <= lc_e; ++i) {
		for(unsigned char j = lc_s; j <= lc_e; ++j) {
			for(unsigned char k = lc_s; k <= lc_e; ++k) {
				int idx{0}, score{0};
				bool res;
				asciiSum = 0;

				for(auto c : values) {
					switch(idx) {
						case 0:
							res = isNormal(char(c^i));
							converted += char(c^i);
							break;
						case 1:
							res = isNormal(char(c^j));
							converted += char(c^j);
							break;
						case 2:
							res = isNormal(char(c^k));
							converted += char(c^k);
							break;

					}
					asciiSum += converted[converted.size() - 1];
					idx = (idx + 1) % 3;
					if(!res) {
						converted.clear();
						break;
					}
				}
				if(!res) {
					continue;
				}
				
				int pos = 0;
				for(const auto & word : commonWords) {
					while ((pos = converted.find(word, pos )) != std::string::npos) {
						++score;
					    pos += word.length();
					}
				}
				if(maxScore < score) {
					maxScore = score;
					maxAsciiSum = asciiSum;
				}
				converted.clear();
			}
		}
	}

	std::cout << maxAsciiSum << std::endl;
	
	
	file.close();
	return 0;
}