#include <ctime>
#include <set>
#include <string>
#include "PolynomialSet.h"  // not GroebnerLib.h or smf like that

void PrintLine(i32 = 1);
std::string TrueFalse(bool);

void test_Rational();
void test_Modular();
void test_Monomial();
void test_Term();
void test_TermOrder();
void test_Polynomial();
void test_PolynomialOrder();
void test_PolynomialSet();
void test_Sigma(i32);
void test_SigmaTime(i32);

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
            std::cout << minuties << (minuties > 1 ? " minuties " : " minutie ");
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
