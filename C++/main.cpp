#include <iostream>
#include <unweight.hpp>
#include <weight.hpp>

using namespace std;
using namespace graph;

int main ()
{
	{
		weight <int>::matrix test1 (4);
		test1.add (1, 3, 4);
		test1.add2 (0, 3, 4);
		cout << test1.data [0][3] << " ";
		cout << test1.data [1][3] << " ";
		cout << test1.data [2][0] << " ";

		unweight::matrix test2 = test1.to_unweight ();
		cout << test2.data [0][3] << " ";
		cout << test2.data [1][3] << " ";
		cout << test2.data [2][0] << " ";
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
