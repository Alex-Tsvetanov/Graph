#include <iostream>
#include <unweight.hpp>
#include <weight.hpp>

using namespace std;
using namespace graph;

int main ()
{
	{
		weight <int>::ln test1;
		test1.add (1, 3, 4);
		test1.add2 (0, 3, 4);
		cout << test1 [0].size () << " ";
		cout << test1 [1].size () << " ";
		cout << test1 [2].size () << " ";
		cout << test1 [3].size () << "\n";

		unweight::ln test2 = test1.to_unweight ();
		cout << test2 [0].size () << " ";
		cout << test2 [1].size () << " ";
		cout << test2 [2].size () << " ";
		cout << test2 [3].size () << "\n";
	}
	{
		weight <int>::le test1;
		test1.add (1, 3, 4);
		test1.add2 (0, 3, 4);
		cout << test1.l.size () << "\n";

        unweight::le test2 = test1.to_unweight ();
        cout << test2.l.size () << "\n";
	}
}
