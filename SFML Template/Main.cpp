#include <iostream>
#include <time.h>
#include "Window/Window.h"

int main()
{
    srand(time(NULL));

    Window window;

    window.run();

    return 0;
}