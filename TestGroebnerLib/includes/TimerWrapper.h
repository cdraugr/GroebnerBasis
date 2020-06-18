#include <ctime>
#include <string>
#include <iostream>

using i32 = int32_t;

template <typename TFunction>
class TimerWrapper {
public:
    TimerWrapper(TFunction function, const std::string& text):
        call(function), text_(text), start_time_(::clock()) {}

    operator TFunction() {
        return call;
    }

    ~TimerWrapper() {
        const clock_t end_time_ = ::clock();
        const clock_t diff = (end_time_ - start_time_);
        double seconds = static_cast<double>(diff) / CLOCKS_PER_SEC;
        i32 minuties = static_cast<i32>(seconds / 60);
        std::cout << text_;
        if (minuties > 0) {
            std::cout << minuties << (minuties > 1 ? " minutes " : " minute ");
        }
        std::cout << seconds - 60.0 * minuties << " seconds." << std::endl;
    }

    TFunction call;

private:
    const std::string text_;
    const clock_t start_time_;
};

template <typename TFunction>
TimerWrapper<TFunction> test_time(TFunction function, const std::string& text) {
    return TimerWrapper<TFunction>(function, text);
}
