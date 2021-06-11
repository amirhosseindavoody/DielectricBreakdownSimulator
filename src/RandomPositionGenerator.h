#include "Node.h"
#include <random>
#include "constants.h"

class RandomPositionGenerator
{
private:
    //Will be used to obtain a seed for the random number engine
    std::random_device rd_;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen_;

    std::uniform_int_distribution<> distrib_;

public:
    RandomPositionGenerator(int_t min, int_t max, int16_t seed) : rd_(), gen_(rd_()), distrib_(min, max)
    {
        gen_.seed(seed);
    }

    Node::Position get()
    {
        Node::Position pos;
        for (auto &p : pos)
        {
            p = distrib_(gen_);
        }
        return pos;
    }
};