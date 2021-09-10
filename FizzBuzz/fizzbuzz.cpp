#include "fizzbuzz.h"

void fizzBuzz(int n) {

	if (n >= 200000)
		return;

	for (int i = 1; i <= n; i++)
	{
		std::string s = "";

		//conditions
		bool bDefault = true;
		for (const auto& iter : Rules)
		{
			if (i % iter.first == 0)
			{
				s += Rules[iter.first];
				bDefault = false;
			}
		}

		//default
		if (bDefault)
		{
			s = std::to_string(i);
		}

		std::cout << s << std::endl;
	}
}