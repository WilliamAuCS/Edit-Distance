#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class EditDistance
{
private:
	int findMin(int a, int b, int c)
	{
		return std::min({ a, b, c });
	}
public:
	void findDistance(std::string s1, std::string s2)
	{
		// s1 is thought to be "horizontal" and
		// s2 is thought to be "vertical" within the matrix
		int str1Length = s1.length();
		int str2Length = s2.length();

		// Creating 2-D vector to store values
		using matrix = std::vector<std::vector<int>>;
		matrix edit(str1Length + 1, std::vector<int>(str2Length + 1));

		// Contains [i][j] cordinates of edit where characters of s1 and s2 are equal
		std::unordered_map<int, int> umap;

		// Creating standard number line on X and Y axis
		for (size_t i = 1; i < str1Length + 1; i++)
		{
			edit[i][0] = i;
		}
		for (size_t i = 1; i < str2Length + 1; i++)
		{
			edit[0][i] = i;
		}

		bool firstElement = true;
		bool firstRow = true;

		for (size_t j = 1; j < str2Length + 1; j++)
		{
			for (size_t i = 1; i < str1Length + 1; i++)
			{
				// If the two corresponding letters of the string are equivillant
				if (s2[j - 1] == s1[i - 1])
				{
					if (firstElement)
					{
						// If it is the first element and matchs, start with 0
						edit[i][j] = 0;
						firstElement = false;
					}
					else if (firstRow)
					{
						// If in the first row, new element equals element to its left
						edit[i][j] = edit[i - 1][j];
					}
					else if (i == 1)
					{
						// If it is the first element in the column, new element equals element above it
						edit[i][j] = edit[i][j - 1];
					}
					else
					{
						edit[i][j] = findMin(edit[i][j - 1], edit[i - 1][j], edit[i - 1][j - 1]);
					}
					umap.insert({ i, j });
				}
				// If the two corresponding letters of the string are different
				else
				{
					if (firstElement)
					{
						// If it is the first element and does not match, start with 1
						edit[i][j] = 1;
						firstElement = false;
					}
					else if (firstRow)
					{
						// Add one to the element to the left
						edit[i][j] = edit[i - 1][j] + 1;
					}
					else if (i == 1)
					{
						edit[i][j] = edit[i][j - 1] + 1;
					}
					else
					{
						// Add one to the lowest element it can inherit from
						edit[i][j] = findMin(edit[i][j - 1], edit[i - 1][j], edit[i - 1][j - 1]) + 1;
					}
				}
			}
			firstRow = false;
		}
		// Print matrix
		for (size_t j = 0; j < str2Length + 1; j++)
		{
			for (size_t i = 0; i < str1Length + 1; i++)
			{
				std::cout << edit[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};
