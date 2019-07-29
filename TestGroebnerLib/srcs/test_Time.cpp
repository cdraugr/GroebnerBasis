#include "../includes/Tests.h"

void test_Time(i32 maximum_variables) {
    for (i32 i = 1; i <= maximum_variables; ++i) {
        clock_t elapsedTime = 0;
        test_time(test_Sigma, elapsedTime)(i);

        double seconds = static_cast<double>(elapsedTime) / CLOCKS_PER_SEC;
        std::cout << "Time spended for calculate Cyclic " << i << " = ";
        if (seconds >= 60.0) {
            std::cout << static_cast<i32>(seconds / 60) << " minuties ";
        }
        std::cout << seconds - 60.0 * static_cast<i32>(seconds / 60) << " seconds." << std::endl;
        PrintLine();
    }
    PrintLine();
}
