#include "solver.h"

int main(int argc, char* argv[]) {
	if(argc == 2){
		std::string paths[] = {
        std::string("data/") + argv[1],     
        std::string("../data/") + argv[1],   
        std::string("../../data/") + argv[1] 
    	};
    
    	std::string foundPath;
		for (const auto& path : paths) {
			std::ifstream file(path);
			if (file) {
				foundPath = path;
				break;
			}
    	}
		Solver S(foundPath);
	}
	return 0;
}