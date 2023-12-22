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

struct Position
{
    int x, y;
    Direction dir;
    int straight;

    bool operator==(const Position &pos) const
    {
        return x == pos.x && y == pos.y && dir == pos.dir && straight == pos.straight;
    }

    // Define a less-than operator for ordering
    bool operator<(const Position &pos) const
    {
        if (x != pos.x)
            return x < pos.x;
        if (y != pos.y)
            return y < pos.y;
        if (dir != pos.dir)
            return dir < pos.dir;
        return straight < pos.straight;
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

vector<Cell> getValidNeighbours(const Position &pos, const vector<vector<int>> &grid, int maxStraight, int minStraight)
{
    const int width = grid[0].size(), height = grid.size();
    vector<Cell> neighbours;

    for (Direction dir : getDirections(pos.dir))
    {
        if (pos.dir != NONE && pos.dir == dir && pos.straight >= maxStraight)
            continue;
        else if (pos.dir != NONE && pos.dir != dir && pos.straight < minStraight)
            continue; // Allow changing direction only after min straight moves

        int newX = pos.x, newY = pos.y;
        switch (dir)
        {
        case UP:
            newY = pos.y - 1;
            break;
        case DOWN:
            newY = pos.y + 1;
            break;
        case LEFT:
            newX = pos.x - 1;
            break;
        case RIGHT:
            newX = pos.x + 1;
            break;
        default:
            break;
        }

        if (newX >= 0 && newX < width && newY >= 0 && newY < height)
        {
            int newStraight;
            if (dir == pos.dir)
            {
                // If the current direction is the same as the previous direction,
                // increment the straight count.
                newStraight = pos.straight + 1;
            }
            else
            {
                // If the direction has changed, reset the straight count to 1.
                newStraight = 1;
            }
            neighbours.push_back({{newX, newY, dir, newStraight}, grid[newY][newX]});
        }
    }

    return neighbours;
}

int dijkstraSearch(const vector<vector<int>> &grid, const Position &start, const Position &end, int maxStraight, int minStraight)
{
    priority_queue<Cell, vector<Cell>, greater<Cell>> queue;
    map<Position, int> bestCosts;

    queue.push({start, 0});

    while (!queue.empty())
    {
        Cell cur = queue.top();
        queue.pop();

        if (cur.position.x == end.x && cur.position.y == end.y && cur.position.straight >= 4)
            return cur.cost;

        if (bestCosts.find(cur.position) != bestCosts.end() && bestCosts[cur.position] <= cur.cost)
            continue;
        bestCosts[cur.position] = cur.cost;

        for (Cell &neighbour : getValidNeighbours(cur.position, grid, maxStraight, minStraight))
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

    Position start = {0, 0, NONE, 1};
    Position end = {static_cast<int>(grid[0].size() - 1), static_cast<int>(grid.size() - 1), NONE, 1};

    int shortestPathCost = dijkstraSearch(grid, start, end, 10, 4);
    cout << shortestPathCost << endl;

    return 0;
}