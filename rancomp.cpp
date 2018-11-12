#include <iostream> 

#include <random>

using namespace std; 

int main(int argc, char* argv[]) {
	int V = atoi(argv[1]);
	int range = atoi(argv[2]);
	int max = -1;
	cout<<V<<endl;
	mt19937 rng;

	rng.seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, range);

	for(int i = 0; i < V; i++)
		for(int j = i+1; j < V; j++){
			int temp = dist6(rng);
			cout<<temp<<endl;
		}
	cout<<range<<endl;
}