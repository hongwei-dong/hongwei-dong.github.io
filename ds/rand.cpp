#include<cstdlib>
#include<ctime>

int main(){
	std::srand(std::time(0));  // needed once per program run
	int r = std::rand() % 35 + 1; printf("%d",r); 
        return 0;
}