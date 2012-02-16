
#include "FantasyRL.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
    FantasyRL *rogue = new FantasyRL();
    rogue->poll();
	delete(rogue);
    return 0;
}
