#pragma once
#include <vector>
#include <string>
#include <random>

class CellularAutomaton
{
    std::mt19937 rng;

    int width, height;
    std::string rule;
    std::string boundaryCondition;
    std::vector<std::vector<int>> field;
    std::vector<std::vector<int>> nextField;

public:
    CellularAutomaton(int width, int height, std::string rule, std::string boundaryCondition, bool randomInit = false);

    void evolve();

    void display() const;

    void setInitialState();
    
private:
    void generateInitialState();

    unsigned int countAliveNeighbors(int x, int y) const;

    int getCell(int x, int y) const;
};

