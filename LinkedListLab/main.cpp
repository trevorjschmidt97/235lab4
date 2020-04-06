#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char* argv[])
{
	VS_MEM_CHECK

		if (argc < 3)
		{
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	string input;
	string input2;
	bool tIntFString;
	LinkedList<int> intList;
	LinkedList<string> stringList;
	out << boolalpha;

	while (in >> input)
	{
		out << input << " ";

		if (input == "INT")
		{
			out << "true" << " ";
			tIntFString = true;
		}

		else if (input == "STRING")
		{
			out << "true" << " ";
			tIntFString = false;
		}

		else if (input == "insertHead")
		{
			in >> input;
			out << input << " ";
			
			if (tIntFString == true)
			{
				out << intList.insertHead(atoi(input.c_str()));
			}
			else
			{
				out << stringList.insertHead(input);
			}
		}

		else if (input == "insertTail")
		{
			in >> input;
			out << input << " ";
			if (tIntFString == true)
			{
				if (intList.size() == 0)
				{
					out << intList.insertHead(atoi(input.c_str()));
				}
				else
				{
					out << intList.insertTail(atoi(input.c_str()));
				}
				
			}
			else
			{
				if (stringList.size() == 0)
				{
					out << stringList.insertHead(input);
				}
				else
				{
					out << stringList.insertTail(input);
				}
			}
		}

		else if (input == "insertAfter")
		{
			in >> input;
			out << input << " ";
			in >> input2;
			out << input2 << " ";
			if (tIntFString == true)
			{
				out << intList.insertAfter(atoi(input.c_str()), atoi(input2.c_str()));
			}
			else
			{
				out << stringList.insertAfter(input, input2);
			}
		}

		else if (input == "remove")
		{
			in >> input;
			out << input << " ";
			if (tIntFString == true)
			{
				out << intList.remove(atoi(input.c_str()));
			}
			else
			{
				out << stringList.remove(input);
			}
		}

		else if (input == "printList")
		{
			if (tIntFString == true)
			{
				out << intList.toString();
			}
			else
			{
				out << stringList.toString();
			}
		}

		else if (input == "clear")
		{
			if (tIntFString == true)
			{
				out << intList.clear();
			}
			else
			{
				out << stringList.clear();
			}
		}

		else if (input == "at")
		{
			in >> input;
			out << input << " ";
			if (tIntFString == true)
			{
				try
				{
					out << intList.at(atoi(input.c_str()));
					out << true;
				}
				catch (int bob)
				{
					out << "Invalid Index" << endl;
				}
			}
			else
			{
				try
				{
					out << stringList.at(atoi(input.c_str()));
					out << true;
				}
				catch (int bob)
				{
					out << "Invalid Index" << endl;
				}
			}
		}

		else if (input == "size")
		{
			if (tIntFString == true)
			{
				out << intList.size();
			}
			else
			{
				out << stringList.size();
			}
		}
		

		else if (input == "iterateList")
		{
			if (tIntFString == true)
			{
				out << intList.toString();
			}
			else
			{
				out << stringList.toString();
			}
		}

		out << endl;
	}

	intList.clear();
	stringList.clear();

	system("pause");
	return 0;
}