#include <iostream>
#include <cassert>
#include "JSON.h"

int main()
{
	// define the json object
	JSON json;

	// json is an object
	json = Object();

	// json["a"] is an array
	json["a"] = Array();

	// assigning a value into the array
	json["a"][0] = false;

	// more options
	{
		json["a"][2] = "hello, world!"; // this resize the array to 3

		assert(json["a"][1].isNull()); // not initialized elements are null

		json["a"][1] = Object();
		json["a"][1]["b"] = "c";  // string are accepted
		json["a"][1]["d"] = 4;	  // integers are accepted
		json["a"][1]["e"] = true; // booleans are accepted
		json["b"] = "d";
	}

	// range based for-loop are accepted for Arrays and Objects
	int i = 0;
	for (JSON part : json["a"].get<Array>())
		std::cout << "Element number " << i++ << " of json[\"a\"] is : " << part.strigify() << std::endl;

	// print the json data in one line
	std::cout << json.strigify() << std::endl;

	// preaty print of json data
	// equals to : cout << json.strigify(true) << endl;
	std::cout << json << std::endl;

	JSON json2;

	// reading the json data from the input
	// equals to : json2 = readJSON(cin);
	std::cin >> json2;

	// print the json input
	std::cout << json2 << std::endl;

	return 0;
}