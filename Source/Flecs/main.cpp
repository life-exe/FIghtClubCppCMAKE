#include <iostream>
#include <flecs.h>

struct Position
{
    double x;
    double y;
};

struct Velocity
{
    double x;
    double y;
};

// Tag types
struct Eats
{
};
struct Apples
{
};

int main(void)
{
    // Create the world
    flecs::world ecs;

    // Register system
    ecs.system<Position, Velocity>().each(
        [](Position& p, Velocity& v)
        {
            p.x += v.x;
            p.y += v.y;
        });

    // Create an entity with name Bob, add Position and food preference
    flecs::entity Bob = ecs.entity("Bob").set(Position{0, 0}).set(Velocity{1, 2}).add<Eats, Apples>();

    // Show us what you got
    std::cout << Bob.name() << "'s got [" << Bob.type().str().c_str() << "]\n";

    // Run systems twice. Usually this function is called once per frame
    ecs.progress();
    ecs.progress();

    // See if Bob has moved (he has)
    const Position* p = Bob.get<Position>();
    std::cout << Bob.name() << "'s position is {" << p->x << "," << p->y << "}\n";

    return EXIT_SUCCESS;
}
