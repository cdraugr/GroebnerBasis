#include "../includes/Tests.h"

void test_Rational() {
    std::cout << "Test Rational:\n";
    Rational a(20, 25);  // (4 / 5)
    Rational b(21, 6);  // (7 / 2)
    Rational one(1);  // 1
    Rational zero;  // 0
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "one = " << one << '\n';
    std::cout << "zero = " << zero << '\n';
    std::cout << "a < b is " << TrueFalse(a < b) << '\n';
    std::cout << "a > b is " << TrueFalse(a > b) << '\n';
    std::cout << "a <= b is " << TrueFalse(a <= b) << '\n';
    std::cout << "a >= b is " << TrueFalse(a >= b) << '\n';
    PrintLine();

    std::cout << "+a = " << +a << '\n';
    std::cout << "-one = " << -one << '\n';
    std::cout << "-zero = " << -zero << '\n';
    std::cout << "5 * a = " << 5 * a << '\n';
    std::cout << "b * 4 = " << b * 4 << '\n';
    std::cout << "one / a = " << one / a << '\n';
    std::cout << "pow(a, 5) = " << pow(a, 5) << '\n';
    std::cout << "pow(b, -5) = " << pow(b, -5) << '\n';
    std::cout << "a / b = " << a / b << '\n';
    std::cout << "b / pow(a, 2) = " << b / pow(a, 2) << '\n';
    std::cout << "a * b = " << a * b << '\n';
    std::cout << "pow(a, -1) * pow(b, -1) = " << pow(a, -1) * pow(b, -1) << '\n';
    std::cout << "b * zero = " << b * zero << '\n';
    std::cout << "a - b + one = " << a - b + one << '\n';
    std::cout << "b - a * b = " << b - a * b << '\n';
    std::cout << "b / a + a * b = " << b / a + a * b << '\n';
    std::cout << "zero / one - (a + b * 4 + one + a / 4) = " << zero / one - (a + b * 4 + one + a / 4) << '\n';
    std::cout << a << " / " << zero << " = ";
    try {
        std::cout << (a / zero) << '\n';
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << '\n';
    }
    PrintLine(2);
}
