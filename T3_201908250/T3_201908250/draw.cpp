#include "game.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>


const std::vector<std::pair<int, int>> oneSeed{
	std::make_pair(7, 3)
};
const std::vector<std::pair<int, int>> twoSeed{
	std::make_pair(4, 3), std::make_pair(10, 3)
};
const std::vector<std::pair<int, int>> threeSeed{
	std::make_pair(4, 4), std::make_pair(10, 4), std::make_pair(7, 2)
};
const std::vector<std::pair<int, int>> fourSeed{
	std::make_pair(4, 4), std::make_pair(10, 4), std::make_pair(4, 2), std::make_pair(10, 2)
};
const std::vector<std::pair<int, int>> fiveSeed{
	std::make_pair(4, 5), std::make_pair(10, 5), std::make_pair(4, 3), std::make_pair(10, 3),
	std::make_pair(7, 1)
};
const std::vector<std::pair<int, int>> sixSeed{
	std::make_pair(4, 5), std::make_pair(10, 5), std::make_pair(4, 3), std::make_pair(10, 3),
	std::make_pair(4, 1), std::make_pair(10, 1)
};
const std::vector<std::pair<int, int>> sevenSeed{
	std::make_pair(3, 5), std::make_pair(11, 5), std::make_pair(3, 3), std::make_pair(11, 3),
	std::make_pair(3, 1), std::make_pair(11, 1), std::make_pair(7, 3)
};
const std::vector<std::pair<int, int>> eightSeed{
	std::make_pair(3, 5), std::make_pair(11, 5), std::make_pair(3, 3), std::make_pair(11, 3),
	std::make_pair(3, 1), std::make_pair(11, 1), std::make_pair(7, 1), std::make_pair(7, 5)
};
const std::vector<std::pair<int, int>> nineSeed{
	std::make_pair(3, 5), std::make_pair(11, 5), std::make_pair(3, 3), std::make_pair(11, 3),
	std::make_pair(3, 1), std::make_pair(11, 1), std::make_pair(7, 1), std::make_pair(7, 5),
	std::make_pair(7, 3)
};

const std::vector<std::pair<int, int>> graphicsArray[9] = { oneSeed, twoSeed, threeSeed, fourSeed, fiveSeed, sixSeed, sevenSeed, eightSeed, nineSeed };

std::vector<std::string> storeHouse(int numOfSeeds);


void drawBoard(int player, Board gameBoard) {
	std::vector<std::string>::iterator it;
	std::vector<std::string> output = storeHouse(12);

	for (it = output.begin(); it != output.end(); it++) {
		std::cout << (*it) << std::endl;
	}
}

std::vector<std::string> storeHouse(int numOfSeeds) {
	int x, y;
	std::vector<std::pair<int, int>>::iterator it;
	std::vector<std::string> box{
		"+-------------+",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"+-------------+"
	};
	
	if (numOfSeeds == 0) return box;

	std::vector<std::pair<int, int>> seedPlacement;
	if (numOfSeeds >= 10) {
		seedPlacement = eightSeed;

		box[3][6] = (char)(numOfSeeds / 10) + '0';
		box[3][8] = (char)(numOfSeeds % 10) + '0';
	}
	else {
		seedPlacement = graphicsArray[numOfSeeds - 1];
	}
	 
	for (it = seedPlacement.begin(); it != seedPlacement.end(); it++) {
		x = (*it).first;
		y = (*it).second;

		box[y][x] = 'O';
	}

	return box;
}

//+-------------+    
//|             | 
//|             |
//|      O      |
//|             |
//|             |  
//+-------------+
//+-------------+    
//|             | 
//|             |
//|   O     O   |
//|             |
//|             |  
//+-------------+
//+-------------+    
//|             |  
//|      O      |
//|             |
//|   O     O   |
//|             |  
//+-------------+
//+-------------+    
//|             |  
//|   O     O   |
//|             |
//|   O     O   |
//|             |  
//+-------------+
//+-------------+    
//|      O      |  
//|             |
//|   O     O   |
//|             |
//|   O     O   |  
//+-------------+
//+-------------+    
//|   O     O   |  
//|             |
//|   O     O   |
//|             |
//|   O     O   |  
//+-------------+
//+-------------+    
//|  O       O  |  
//|             |
//|  O   O   O  |
//|             |
//|  O       O  |  
//+-------------+
//+-------------+    
//|  O   O   O  |  
//|             |
//|  O       O  |
//|             |
//|  O   O   O  |  
//+-------------+
//+-------------+    
//|  O   O   O  |  
//|             |
//|  O   O   O  |
//|             |
//|  O   O   O  |  
//+-------------+
//+-------------+    
//|  O   O   O  | 
//|             |
//|  O   12  O  |
//|             |
//|  O   O   O  |  
//+-------------+
