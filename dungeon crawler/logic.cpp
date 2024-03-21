#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    char tile;
    int counter = 0;
    ifstream myFile;
    if (myFile.fail()) {
        return nullptr;
    }
    myFile.open(fileName);
    myFile >> maxRow;
    if (myFile.fail()) {
        return nullptr;
    }
    myFile >> maxCol;
    if (myFile.fail()) {
        return nullptr;
    }
    myFile >> player.row;
    if (myFile.fail()) {
        return nullptr;
    }
    myFile >> player.col;
    if (myFile.fail()) {
        return nullptr;
    }
    //if max row/col are negative
    if (maxRow < 1 || maxCol < 1) {
        return nullptr;
    }
    //if player location invalid
    if (player.row < 0 || player.col < 0 || player.row >= maxRow || player.col >= maxCol) {
        return nullptr;
    }

    char** level = createMap(maxRow, maxCol); //initialize 2d array
    if (level == nullptr) {
        return nullptr;
    }
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { //load array with file contents
	    for (int colIdx = 0; colIdx < maxCol; colIdx++) {
            if (myFile) {
                myFile >> tile;
                counter++;
                level[rowIdx][colIdx] = tile;
            }
        }
    }
    //if invalid number of row/column
    if (counter != maxRow * maxCol || counter < 1 || counter > INT32_MAX) {
        return nullptr; 
    }
    //set player to tile_player
    level[player.row][player.col] = TILE_PLAYER;
    
    //check for invalid symbols
    bool invalidSymbol = true;
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { 
	    for (int colIdx = 0; colIdx < maxCol; colIdx++) {
            if (level[rowIdx][colIdx] == TILE_OPEN || level[rowIdx][colIdx] == TILE_PLAYER || level[rowIdx][colIdx] == TILE_TREASURE) {
                invalidSymbol = false;
            }
            else if (level[rowIdx][colIdx] == TILE_AMULET || level[rowIdx][colIdx] == TILE_MONSTER || level[rowIdx][colIdx] == TILE_PILLAR) {
                invalidSymbol = false;
            }
            else if (level[rowIdx][colIdx] == TILE_DOOR || level[rowIdx][colIdx] == TILE_EXIT) {
                invalidSymbol = false; 
            }
        }
    }
    if (invalidSymbol) {
        return nullptr;
    }

    //if player is on monster or pillar
    if (level[player.row][player.col] == TILE_MONSTER || level[player.row][player.col] == TILE_PILLAR) {
        return nullptr;
    }

    bool wayOut = false; //check for way out
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { 
	    for (int colIdx = 0; colIdx < maxCol; colIdx++) {
            if (level[rowIdx][colIdx] == TILE_DOOR || level[rowIdx][colIdx] == TILE_EXIT) {
                wayOut = true;
            }
        }
    }
    if (!wayOut) {
        return nullptr;
    }
    return level;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if (input != MOVE_UP && input != MOVE_LEFT && input != MOVE_DOWN && input != MOVE_RIGHT) {
        return;
    }
    if (input == MOVE_UP) {
        nextCol = nextCol;
        nextRow--;
    }
    else if (input == MOVE_LEFT) {
        nextRow = nextRow;
        nextCol--;
    }
    else if (input == MOVE_DOWN) {
        nextCol = nextCol;
        nextRow++;
    }
    else if (input == MOVE_RIGHT) {
        nextRow = nextRow;
        nextCol++;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) { 
    if (maxRow < 1 || maxCol < 1) { //if invalid input
        return nullptr;
    }
    char** map = new char*[maxRow]; 
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { //allocate 2d dynamic array
        map[rowIdx] = new char[maxCol];
    }
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { //initialize all elements with '-'
        for (int colIdx = 0; colIdx < maxCol; colIdx++) {
            map[rowIdx][colIdx] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr) {
        maxRow = 0;
        return;
    }
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) {
        delete [] map[rowIdx];
    }
    delete [] map;
    map = nullptr;
    maxRow = 0;
}


/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr || maxRow < 1 || maxCol < 1) {
        return nullptr;
    }
    char** tempMap = new char*[maxRow]; //with TILE_PLAYER, same as original map
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) {
        tempMap[rowIdx] = new char[maxCol];
    }
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) {
        for (int colIdx = 0; colIdx < maxCol; colIdx++) {
            tempMap[rowIdx][colIdx] = map[rowIdx][colIdx];
        }
    }
    char** newMap = new char*[maxRow]; //without TILE_PLAYER
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) {
        newMap[rowIdx] = new char[maxCol];
    }
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { 
        for (int colIdx = 0; colIdx < maxCol; colIdx++) { 
            if (map[rowIdx][colIdx] == TILE_PLAYER) { //changes TILE_PLAYER to TILE_OPEN
                newMap[rowIdx][colIdx] = TILE_OPEN;
            }
            else {
                newMap[rowIdx][colIdx] = map[rowIdx][colIdx];
            }
        }
    }

    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) { //deallocate original map
        delete[] map[rowIdx];
    }
    delete[] map;

    maxRow *= 2; //update dimensions
    maxCol *= 2;

    map = new char*[maxRow]; //update original map to new size
    for (int rowIdx = 0; rowIdx < maxRow; rowIdx++) {
        map[rowIdx] = new char[maxCol];
    }

    for (int rowIdx = 0; rowIdx < maxRow/2; rowIdx++) { //top left quadrant
        for (int colIdx = 0; colIdx < maxCol/2; colIdx++) {
            map[rowIdx][colIdx] = tempMap[rowIdx][colIdx];
        }
    }
    for (int rowIdx = 0; rowIdx < maxRow/2; rowIdx++) { //top right quadrant
        for (int colIdx = maxCol/2; colIdx < maxCol; colIdx++) {
            map[rowIdx][colIdx] = newMap[rowIdx][colIdx - maxCol / 2];
        }
    }
    for (int rowIdx = maxRow/2; rowIdx < maxRow; rowIdx++) { //bottom left quadrant
        for (int colIdx = 0; colIdx < maxCol/2; colIdx++) {
            map[rowIdx][colIdx] = newMap[rowIdx - maxRow / 2][colIdx];
        }
    }
    for (int rowIdx = maxRow/2; rowIdx < maxRow; rowIdx++) { //bottom right quadrant
        for (int colIdx = maxCol/2; colIdx < maxCol; colIdx++) {
            map[rowIdx][colIdx] = newMap[rowIdx - maxRow / 2][colIdx - maxCol / 2];
        }
    }

    for (int rowIdx = 0; rowIdx < maxRow/2; rowIdx++) { //delete temporary arrays
        delete[] tempMap[rowIdx];
        delete[] newMap[rowIdx];
    }
    delete[] tempMap;
    delete[] newMap;
    return map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    int status = 0;
    //if next is out of boundary or on pillar/monster
    if (nextRow >= maxRow || nextCol >= maxCol || nextRow < 0 || nextCol < 0) {
        status = STATUS_STAY;
        nextRow = player.row;
        nextCol = player.col;
    }
    else if (map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER) {
        status = STATUS_STAY;
        nextRow = player.row;
        nextCol = player.col;
    }
    //else if next is treasure
    else if (map[nextRow][nextCol] == TILE_TREASURE) {
        status = STATUS_TREASURE;
        player.treasure++;
    }
    //else if next is amulet
    else if (map[nextRow][nextCol] == TILE_AMULET) {
        status = STATUS_AMULET;
    }
    //else if next is door
    else if (map[nextRow][nextCol] == TILE_DOOR) {
        status = STATUS_LEAVE;
    }
    //else if next is exit and treasure >= 1
    else if (map[nextRow][nextCol] == TILE_EXIT && player.treasure >= 1) {
        status = STATUS_ESCAPE;
    }
    //else if next is exit and treasure = 0
    else if (map[nextRow][nextCol] == TILE_EXIT && player.treasure < 1) {
        status = STATUS_STAY;
        nextRow = player.row;
        nextCol = player.col;
    }
    else {
        status = STATUS_MOVE;
    }
    //set old position to tile_open, update player contents, set new position to tile_player
    map[player.row][player.col] = TILE_OPEN;
    player.row = nextRow;
    player.col = nextCol;
    map[player.row][player.col] = TILE_PLAYER;
    return status;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool monster = false;
    //check up
        //start 1 above player, work up. 
        //if pillar, break. if monster, move 1 closer
    for (int rowIdx = player.row - 1; rowIdx >= 0; rowIdx--) {
        if (map[rowIdx][player.col] == TILE_PILLAR) {
            break;
        }
        else if (map[rowIdx][player.col] == TILE_MONSTER) {
            map[rowIdx + 1][player.col] = TILE_MONSTER;
            map[rowIdx][player.col] = TILE_OPEN;
        }
    }

    //check down
    for (int rowIdx = player.row + 1; rowIdx < maxRow; rowIdx++) {
        if (map[rowIdx][player.col] == TILE_PILLAR) {
            break;
        }
        else if (map[rowIdx][player.col] == TILE_MONSTER) {
            map[rowIdx - 1][player.col] = TILE_MONSTER;
            map[rowIdx][player.col] = TILE_OPEN;
        }
    }

    //check left
    for (int colIdx = player.col - 1; colIdx >= 0; colIdx--) {
        if (map[player.row][colIdx] == TILE_PILLAR) {
            break;
        }
        else if (map[player.row][colIdx] == TILE_MONSTER) {
            map[player.row][colIdx + 1] = TILE_MONSTER;
            map[player.row][colIdx] = TILE_OPEN;
        }
    }

    //check right
    for (int colIdx = player.col + 1; colIdx < maxCol; colIdx++) {
        if (map[player.row][colIdx] == TILE_PILLAR) {
            break;
        }
        else if (map[player.row][colIdx] == TILE_MONSTER) {
            map[player.row][colIdx - 1] = TILE_MONSTER;
            map[player.row][colIdx] = TILE_OPEN;
        }
    }

    //if monster on player position, monster = true
    if (map[player.row][player.col] == TILE_MONSTER) {
        monster = true;
    }
    return monster;
}
