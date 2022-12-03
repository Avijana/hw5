// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wHelper(std::string current, const std::set<std::string>& dict, std::set<std::string>& match, size_t pos, std::string fLetters);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> output;
		size_t pos = 0;
		wHelper(in, dict, output, pos, floating);
		return output;
}

// Define any helper functions here

void wHelper(std::string current, const std::set<std::string>& dict, std::set<std::string>& match, size_t pos, std::string fLetters)
{
	int numDashes = 0; 
	string fL = fLetters; //floating letters

	if(pos == current.size()) //if word found return
	{
		if(fL.empty()) 
		{
			if(dict.find(current)!=dict.end())
			{
				match.insert(current);
			}
			return;
		}
	}

	if(current[pos] != '-') //if letter in pos go to next space
	{
		wHelper(current, dict,match, pos+1,fL);
		return;
	}

	for(size_t s = 0; s < current.size(); s++) //keep track of num dashes
	{
		if(current[s] == '-')
		{
			numDashes++;
		}
	}

	if(numDashes > (int)fL.size()) //if there are more empty spaces than floating letters check a-z
	{
		for(char check = 'a'; check <= 'z'; check++)
		{
			if(fL.find(check) != string::npos)
			{
				string temp = fL;
				current[pos] = check;
				temp.erase(fL.find(check),1);
				wHelper(current, dict, match, pos+1, temp);
			}
			else
			{
				current[pos] = check;
				wHelper(current, dict, match, pos+1, fL);
			}
		}
	}
	else //otherwise use floating
	{
		for(size_t s = 0; s < fL.size(); s++)
		{
			string temp = fL;
			current[pos] = fL[s];
			temp.erase(s,1);
			wHelper(current,dict,match,pos+1,temp);
		}
	}
}
