#include <iostream>
#include "Edits.cpp"
int main()
{
	EditDistance edit;
	edit.findMatrix("broad", "board");

	return 0;
}