#include "Steps.h"


Steps Steps::readSteps(const std::string& filename)
{
    Steps res;
    int iteration;
    char key;
    int random_seed;
    int final_itr;

    std::ifstream steps_f(filename);
    if (!steps_f.is_open()) {
        std::cout << "Error opening file\n";
        return Steps();  //to change
    }
    steps_f >> res.random_seed;
    steps_f >> res.final_itr;
    size_t size;
    steps_f >> size;

    for (int i = 0; i < size; i++)
    {
        steps_f >> iteration;
        steps_f >> key;
        res.pushToStack(iteration, key);
    }
    steps_f.close();
    return res;
}

void Steps::saveSteps(const std::string& filename) const
{

    std::ofstream steps_f(filename);
    steps_f << random_seed << '\n' << final_itr << '\n' << steps.size();
    for(const auto& step : steps)
        steps_f << '\n' << step.first << ' ' << step.second;
    steps_f.close();
}

std::pair<int, char> Steps::popStep()
{
    if (steps.empty())
    {
        std::cout << "no steps in !";
        return std::pair<int, char>{};
    }
    std::pair<int, char> step = steps.front();
    steps.pop_front();
    return step;
}
