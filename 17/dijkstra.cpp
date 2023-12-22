#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct Position {
    int x, y;

    // Define a less-than operator for ordering (needed for map)
    bool operator<(const Position &pos) const {
        if (x != pos.x) return x < pos.x;
        return y < pos.y;
    }
};


struct Cell
{
    Position position;
    int cost;

    bool operator>(const Cell &other) const
    {
        return cost > other.cost;
    }
};

vector<Direction> getDirections(Direction dir)
{
    switch (dir)
    {
    case UP:
        return {LEFT, UP, RIGHT};
    case DOWN:
        return {LEFT, DOWN, RIGHT};
    case LEFT:
        return {UP, LEFT, DOWN};
    case RIGHT:
        return {UP, RIGHT, DOWN};
    default:
        return {LEFT, UP, RIGHT, DOWN};
    }
}

vector<Cell> getValidNeighbours(const Position &pos, const vector<vector<int>> &grid) {
    const int width = grid[0].size(), height = grid.size();
    vector<Cell> neighbours;
    vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // UP, DOWN, LEFT, RIGHT

    for (auto &move : moves) {
        int newX = pos.x + move.first;
        int newY = pos.y + move.second;

        if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
            neighbours.push_back({{newX, newY}, grid[newY][newX]});
        }
    }

    return neighbours;
}


int dijkstraSearch(const vector<vector<int>> &grid, const Position &start, const Position &end)
{
    priority_queue<Cell, vector<Cell>, greater<Cell>> queue;
    map<Position, int> bestCosts;

    queue.push({start, 0});

    while (!queue.empty())
    {
        Cell cur = queue.top();
        queue.pop();

        if (cur.position.x == end.x && cur.position.y == end.y)
            return cur.cost;

        if (bestCosts.find(cur.position) != bestCosts.end() && bestCosts[cur.position] <= cur.cost)
            continue;
        bestCosts[cur.position] = cur.cost;

        for (Cell &neighbour : getValidNeighbours(cur.position, grid))
        {
            neighbour.cost += cur.cost;
            queue.push(neighbour);
        }
    }
    // No path found
    return 2147483647;
}

vector<vector<int>> readInput(const string &fileName)
{
    ifstream file(fileName);
    vector<vector<int>> grid;
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<int> row;
            for (char ch : line)
            {
                row.push_back(ch - '0');
            }
            grid.push_back(row);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }

    return grid;
}

int main()
{
    vector<vector<int>> grid = readInput("input.txt");
    if (grid.empty() || grid[0].empty())
    {
        cout << "Grid is empty or not properly formatted." << endl;
        return 1;
    }

    Position start = {0, 0};
    Position end = {static_cast<int>(grid[0].size() - 1), static_cast<int>(grid.size() - 1)};

    int shortestPathCost = dijkstraSearch(grid, start, end);
    cout << shortestPathCost << endl;

    return 0;
}