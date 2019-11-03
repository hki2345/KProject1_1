// multimap_upper_bound.cpp
// compile with: /EHsc
#include <map>
#include <iostream>

int main()
{
	using namespace std;
	multimap <int, int> m1;
	multimap <int, int> ::const_iterator m1_AcIter, m1_RcIter;
	typedef pair <int, int> Int_Pair;

	m1.insert(Int_Pair(1, 10));
	m1.insert(Int_Pair(2, 20));
	m1.insert(Int_Pair(3, 30));
	m1.insert(Int_Pair(3, 40));

	m1_RcIter = m1.upper_bound(1);
	cout << "The 1st element of multimap m1 with "
		<< "a key greater than 1 is: "
		<< m1_RcIter->second << "." << endl;

	m1_RcIter = m1.upper_bound(2);
	cout << "The first element of multimap m1 with a key "
		<< " greater than 2 is: "
		<< m1_RcIter->second << "." << endl;

	m1_RcIter = m1.lower_bound(3);

	// If no match is found for the key, end( ) is returned
	m1_RcIter = m1.lower_bound(4);

	if (m1_RcIter == m1.end())
		cout << "The multimap m1 doesn't have an element "
		<< "with a key of 4." << endl;
	else
		cout << "The element of multimap m1 with a key of 4 is: "
		<< m1_RcIter->second << "." << endl;

	// The element at a specific location in the multimap can be
	// found using a dereferenced iterator addressing the location
	m1_AcIter = m1.begin();
	m1_RcIter = m1.upper_bound(m1_AcIter->first);
	cout << "The first element of m1 with a key greater than\n"
		<< "that of the initial element of m1 is: "
		<< m1_RcIter->second << "." << endl;
}