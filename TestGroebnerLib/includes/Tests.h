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
void test_Time();

template <typename TFunction>
class TimerWrapper {
public:
    TimerWrapper(TFunction function, clock_t& elapsedTime):
        call(function), startTime_(::clock()), elapsedTime_(elapsedTime) {}

    operator TFunction() {
        return call;
    }

    ~TimerWrapper() {
        const clock_t endTime_ = ::clock();
        const clock_t diff = (endTime_ - startTime_);
        elapsedTime_ += diff;
    }

    TFunction call;
private:
    const clock_t startTime_;
    clock_t& elapsedTime_;
};


template <typename TFunction>
TimerWrapper<TFunction> test_time(TFunction function, clock_t& elapsedTime) {
    return TimerWrapper<TFunction>(function, elapsedTime);
}
