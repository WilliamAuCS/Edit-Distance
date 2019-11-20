#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class EditDistance
{
private:
	int findMin(int a, int b, int c)
	{
		return std::min({ a, b, c });
	}
	void printVector(std::vector<int, int> matchVec)
	{
		std::vector<int, int>::iterator it;
		for (it = matchVec.begin(); it != matchVec.end(); it++)
		{
			std::cout << "(" << it->first << ", " << it->second << ")" << " " << std::endl;
		}
		std::cout << std::endl;
	}
	void printMatrix(std::vector<std::vector<int>> edit, int str2Length, int str1Length)
	{
		// Print matrix
		for (size_t j = 0; j < str2Length + 1; j++)
		{
			for (size_t i = 0; i < str1Length + 1; i++)
			{
				std::cout << edit[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
public:
	void findMatrix(std::string s1, std::string s2)
	{
		// s1 is thought to be "horizontal" and
		// s2 is thought to be "vertical" within the matrix
		int str1Length = s1.length();
		int str2Length = s2.length();

		// Creating 2-D vector to store values
		using matrix = std::vector<std::vector<int>>;
		matrix edit(str1Length + 1, std::vector<int>(str2Length + 1));

		// Contains [i][j] cordinates of edit where characters of s1 and s2 are equal
		std::vector<int, int> matchVec;

		// Coordinates (0, 0) in matrix is the starting point (used in reverse transversal to find alignment)
		matchVec.push_back(( 0, 0 ));

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
					matchVec.push_back(( i, j ));
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
		printMatrix(edit, str2Length, str1Length);
		printVector(matchVec);
		findDistance(edit, matchVec, str1Length, str2Length);
	}
private:
	void findDistance(std::vector<std::vector<int>> edit, std::vector<int, int> matchVec, int str1Length, int str2Length)
	{
		std::vector<int, int> alignment;
		int maxDistance = -1;
		while (true)
		{
			int temp = -1;
			alignment.push_back(( str1Length, str2Length ));
			temp = findMin(edit[str1Length][str2Length - 1], edit[str1Length - 1][str2Length], edit[str1Length - 1][str2Length - 1]);
			if (edit[str1Length - 1][str2Length - 1] == temp)
			{
				str1Length -= 1;
				str2Length -= 1;
			}
			else if (edit[str1Length][str2Length - 1] == temp)
			{
				str2Length -= 1;
			}
			else if (edit[str1Length - 1][str2Length] == temp)
			{
				str1Length -= 1;
			}
		}
	}
};
