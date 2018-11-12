#include <iostream> 

#include <random>

using namespace std; 

int main(int argc, char* argv[]) {
	int V = atoi(argv[1]);
	int range = atoi(argv[2]);
	int temp = atoi(argv[3]);
	float density = (float)temp/(float)100;
	float total = V*(V-1)/2;
	float count = 0;
	cout<<V<<endl;
	mt19937 rng;

	rng.seed(std::random_device()());

	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, range);
	std::uniform_int_distribution<std::mt19937::result_type> prob(1, 10);

	for(int j = 1;j<V;j++){
		cout<<dist6(rng)<<endl;
		++count;
	}

	for(int i = 1; i < V && count/total < density; i++)
		for(int j = i+1; j < V && count/total < density; j++){
			if(prob(rng)<9){
				cout<<i<<endl;
				cout<<j<<endl;
				cout<<dist6(rng)<<endl;
				++count;
			}
		}
	cout<<-10<<endl;
	cout<<range<<endl;
	//cout<<count/total<<" "<<density<<endl;
}