#include "Tests.h"

void test_Modular() {
    std::cout << "Test Modular:\n";
    const u64 TBase = 53;
    std::cout << "TBase = " << TBase << ":\n";
    Modular<TBase> a(200);  // 41
    Modular<TBase> b(INT32_MIN);  // 32
    Modular<TBase> one(1);  // 1
    Modular<TBase> zero;  // 0
    Modular<TBase> big_number(INT32_MAX * static_cast<i64>(7));
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "one = " << one << '\n';
    std::cout << "zero = " << zero << '\n';
    std::cout << std::boolalpha << "a < b is " << (a < b) << '\n';
    std::cout << std::boolalpha << "a > b is " << (a > b) << '\n';
    std::cout << std::boolalpha << "a <= b is " << (a <= b) << '\n';
    std::cout << std::boolalpha << "a >= b is " << (a >= b) << '\n';
    std::cout << std::boolalpha << "a == 4 is " << (a == 4) << '\n';
    PrintLine();

    std::cout << "+a = " << +a << '\n';
    std::cout << "-one = " << -one << '\n';
    std::cout << "-zero = " << -zero << '\n';
    std::cout << "5 * a = " << 5 * a << '\n';
    std::cout << "b * 4 = " << b * 4 << '\n';
    std::cout << "1 / a = " << 1 / a << '\n';
    std::cout << "pow(a, 5) = " << pow(a, 5) << '\n';
    std::cout << "pow(b, -5) = " << pow(b, -5) << '\n';
    std::cout << "a / b = " << a / b << '\n';
    std::cout << "b / pow(a, 2) = " << b / pow(a, 2) << '\n';
    PrintLine();

    std::cout << "a * b = " << a * b << '\n';
    std::cout << "pow(a, -1) * pow(b, -1) = " << pow(a, -1) * pow(b, -1) << '\n';
    std::cout << "a ^ (-1) * b ^ (-1) = " << InverseElement(a) * InverseElement(b) << '\n';
    std::cout <<  "a * b * a ^ (-1) * b ^ (-1) = " << a * b * InverseElement(a) * InverseElement(b) << '\n';
    PrintLine();

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
    std::cout << big_number << " * " << INT32_MAX << " = " << big_number * INT32_MAX << '\n';
    PrintLine(2);
}
