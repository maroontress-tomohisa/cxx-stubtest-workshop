#include "wed3pm/Affairs.h"
#include "wed3pm/DefaultToolkit.h"

int main()
{
    auto kit = wed3pm::DefaultToolkit {};
    for (;;) {
        wed3pm::Affairs::broadcastOnTime(kit);
    }
}
