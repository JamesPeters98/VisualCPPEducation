// Chapter10-Question2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>

using namespace std;

int main()
{
	istream_iterator<char> charInput{ cin }, end;

	priority_queue<char, vector<char>, greater<>> queue;

	while (charInput != end)
	{
		queue.push(*charInput++);
	}

	while(!queue.empty())
	{
		cout << queue.top();
		queue.pop();
	}

}
