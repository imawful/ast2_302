// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 2 attack of the matryoshkas
//   use recurssion to check if input gives valid 
//   matryoshka dolls
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool dollTest(vector<int>, int);
bool matchTest(int,int);
int main()
{
	string temp;
	vector<int> daisy; 
	while(cin >> temp)
		daisy.push_back(stoi(temp));
	// daisy = our doll from input 
	
	// run the doll test 
	bool isDoll = dollTest(daisy, 0);
	
	//output 
	if(isDoll)
		cout << ":-) matryoshka!" << endl;
	else 
		cout << ":-( Try again." << endl;
	
	return 0;
}

/*
	this function will take two numbers (endpoints from doll)
	and see if it matches its positive to negative 
	returns true if match is found 
*/
bool matchTest(int l, int r)
{
	bool leftisNeg, rightisNeg;
	if (l < 0)
	{
		l = l * -1;
		leftisNeg = true;
	}
	else 
		leftisNeg = false;
	
	if (r < 0)
	{
		r = r * -1;
		rightisNeg = true;
	}
	else 
		rightisNeg = false;
	
	if(l == r && (leftisNeg != rightisNeg))
		return true;
	else 
		return false;
}


/*
	this is our main recurssive function that will test to see if all dolls are valid 
	we input our vector of our initial doll and the weight of its parent 
	if we don't have a parent for our initial doll we will pass 0
*/
bool dollTest(vector<int> d, int s)
{
	
	//if is empty (valid doll)  * base case for if we have empty doll*
	if (d.size() == 0)
		return true;
	
	//if size ODD size (INVALID doll) * base case for if we have invalid size doll *
	if (d.size() % 2 != 0)
		return false;
	
	//if not empty we check endpoints
	int left = d.front();
	int right = d.back();
	bool match;
	
	match = matchTest(left, right);
	
	if(match)
	{
		// initial end points matched 
		// check if weight of doll is valid 
		// if weight is 0 we are valid because its the start 
		// if match is less than the old (parent) weight we are valid 
		if(s == 0 || d.back() < s)
		{
			// match was found and we are valid 
			// first we get rid of the first and last element 
			d.erase(d.begin());
			d.pop_back();
			// call the function again to check if inside dolls are valid 
			// we pass 'right' as the weight since we found a valid match 
			// this will act as our parent weight for the future call
			return dollTest(d, right); 
		}
		else 
			return false; // we found a match but the weights are invalid so return false
	}
	else 
	{
		// initial end points did not match 
		// since initial end points did not match 
		// we know that there exits more than one 
		// potential subdoll
		// we enter the case of the augmented Matryoshka
		
		
		//find a match inside the doll to look for valid subdolls
		bool innerMatch = false;
		// we are going to loop thru all the endpoints 
		// keeping the left endpoint the same 
		// but traversing the right end point from right to left 
		// we are testing to find valid subdolls 
		for(int i = d.size()-1; i != 0; i--)
		{
			innerMatch = matchTest(left, d[i]); // test if endpoints match 
			if(innerMatch)
			{
				// we found a match in the inner doll 
				// we must extract the potential subdolls from 
				// left of match and right of match 
				
				// get left 
				vector<int> leftSub;
				for(int j = 0; j < i+1; j++)
					leftSub.push_back(d[j]);
				// get right 
				vector<int> rightSub;
				for(int k = i+1; k < d.size(); k++)
					rightSub.push_back(d[k]);
				
				// recurssive call the same function to check the subdolls 
				// since these are subdolls we don't have a CERTAIN parent weight yet 
				// so we will pass 0 as the start weight since it's the beggining
				bool leftTest = dollTest(leftSub, 0);
				bool rightTest = dollTest(rightSub, 0);
				
				if(leftTest && rightTest)
				{
					// if both sub dolls are valid 
					// we must get the size of both subdolls and add them
					// this size MUST be lower than parents weight 
					int subsSize = leftSub.back() + rightSub.back();
					if(subsSize < s)
						return true; // subdolls and size are valid 
					else 
						return false; // subdolls may have been valid but size was NOT
				}
			}
		}
	}
	
	
	return false; // no matches ever found 
}
