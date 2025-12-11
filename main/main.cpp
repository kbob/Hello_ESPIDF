// C++ standard headers
#include <cstdio>

// ESP-IDF and FreeRTOS headers

// Component headers
#include "board_defs.h"


// //  //   //    //     //      //       //      //     //    //   //  // //
// App Level Settings

// (add settings variables here)


// //  //   //    //     //      //       //      //     //    //   //  // //
// App Main Task

extern "C" void app_main()
{
    printf("Hello, ESP-IDF!\n");
    printf("board = \"%s\"\n", board_name);
}
