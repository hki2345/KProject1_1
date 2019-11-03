#include <vector>
#include <crtdbg.h>
#include <algorithm>


using namespace std;


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	vector<double> input(10, 1.);//input_vector for testing
	auto f = [](double t) {return sin(t); };

	auto fun = [f, input](double t)->vector<double>
	{
		vector<double> dest(input.size());
		transform(input.begin(), input.end(), dest.begin(), [=](double a) {return a * f(t); });
		return dest;
	};
	return 0;
}