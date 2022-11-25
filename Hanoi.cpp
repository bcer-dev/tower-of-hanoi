#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

constexpr int NUMBER_OF_TOWERS = 3;

string operator*(const string& str, size_t times)
{
    string outStr;
    for (int i = 0; i < times; i++)
        outStr += str;
    return outStr;
}

int readTowerNumber(const std::string& message)
{
    int towerNum;
    
    do
    {
        cout << message;
        cin >> towerNum;
    } while (towerNum < 1 || towerNum > NUMBER_OF_TOWERS);

    return towerNum;
}

vector<vector<int>> initTowers()
{
    vector<vector<int>> towers;

    for (int i = 0; i < NUMBER_OF_TOWERS; i++)
        towers.push_back({0, 0, 0, 0});
    
    towers[0] = {0, 1, 2, 3};

    return towers;
}

void drawDisk(int size)
{
    int numSpaces = NUMBER_OF_TOWERS - size;
    constexpr int gap = 2;

    cout << (string(" ") * numSpaces);

    if (size == 0)
    {
        cout << "||" << (string(" ") * (numSpaces + gap));
        return;
    }

    string disk = string("@") * size;
    
    cout << disk << "_" << size << disk;
    cout << (string(" ") * (numSpaces + gap));
}

void drawTowers(const vector<vector<int>>& towers)
{
    const int height = towers.size() + 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < NUMBER_OF_TOWERS; j++)
        {
            drawDisk(towers[j][i]);
        }

        cout << '\n';
    }
}

void moveDisk(vector<int>& src, vector<int>& dst)
{
    int srcTop = 0, dstTop = 0;

    while (srcTop < src.size() && src[srcTop] == 0)
        srcTop++;
    
    while (dstTop < dst.size() && dst[dstTop] == 0)
        dstTop++;

    if (dst[dstTop] > 0 && src[srcTop] > dst[dstTop])
    {
        cerr << "Cannot place larger disk on top of smaller disk.\n";
        return;
    }

    dst[dstTop - 1] = src[srcTop];
    src[srcTop] = 0;
}

bool isComplete(const vector<int>& lastTower)
{
    int diskSize = lastTower.size() - 1;
    for (int i = lastTower.size() - 1; i >= 0; i--)
    {
        if (lastTower[i] != diskSize)
            return false;
        diskSize--;
    }
    return true;
}

int main()
{
    auto towers = initTowers();

    auto& lastTower = towers[NUMBER_OF_TOWERS - 1];
    int srcTowerNumber, dstTowerNumber;
    int totalMoves = 0;

    drawTowers(towers);
    while (!isComplete(lastTower))
    {
        cout << '\n';

        srcTowerNumber = readTowerNumber("Select a tower: ");
        dstTowerNumber = readTowerNumber("Select a tower to move to: ");

        if (srcTowerNumber == dstTowerNumber)
            continue;

        moveDisk(towers[srcTowerNumber - 1], towers[dstTowerNumber - 1]);
        drawTowers(towers);

        totalMoves++;
    }

    cout << '\n';
    cout << "You completed the puzzle in " << totalMoves << " steps.\n";

    return 0;
}

/*
   ||... . ...||      0 -> 3    + 1 +   3
  @_1@.. . ..@_1@     1 -> 2    + 1 +   2
 @@_2@@. . .@@_2@@    2 -> 1    + 1 +   1
@@@_3@@@ . @@@_3@@@   3 -> 0    + 1 +   0

*/