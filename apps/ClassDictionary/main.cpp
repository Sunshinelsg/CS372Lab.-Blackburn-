#include "Dictionary.hpp"

int main() {
	Dictionary<std::string, int> dict;
	dict.insert("apple", 1);
	dict.insert("banana", 2);
	dict["cherry"] = 3;
	try {
		std::cout << "apple: " << dict.at("apple") << std::endl;
		std::cout << "banana: " << dict.at("banana") << std::endl;
		std::cout << "cherry: " << dict.at("cherry") << std::endl;
		std::cout << "date: " << dict.at("date") << std::endl; // This will throw
	} catch (const std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Size of dictionary: " << dict.size() << std::endl;
	std::cout << "Is dictionary empty? " << (dict.empty() ? "Yes" : "No") << std::endl;
	return 0;
}