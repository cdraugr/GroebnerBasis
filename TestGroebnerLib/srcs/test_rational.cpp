#include "Tests.hpp"

void test_rational() {
    std::cout << "Test Rational:\n";
    gb::fields::Rational a(20, 25);  // (4 / 5)
    asserts::assert_rational_(a, 4, 5);

    gb::fields::Rational b(21, 6);  // (7 / 2)
    asserts::assert_rational_(b, 7, 2);

    gb::fields::Rational one(1);  // 1
    asserts::assert_rational_(one, 1, 1);

    gb::fields::Rational zero;  // 0
    asserts::assert_rational_(zero, 0, 1);

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "one = " << one << '\n';
    std::cout << "zero = " << zero << '\n';
    std::cout << std::boolalpha << "a < b is " << (a < b) << '\n';
    assert((a < b) == true);
    std::cout << std::boolalpha << "a > b is " << (a > b) << '\n';
    assert((a > b) == false);
    std::cout << std::boolalpha << "a <= b is " << (a <= b) << '\n';
    assert((a <= b) == true);
    std::cout << std::boolalpha << "a >= b is " << (a >= b) << '\n';
    assert((a >= b) == false);
    utils::print_line();

    std::cout << "+a = " << +a << '\n';
    asserts::assert_rational_(+a, 4, 5);

    std::cout << "-one = " << -one << '\n';
    asserts::assert_rational_(-one, -1, 1);

    std::cout << "-zero = " << -zero << '\n';
    asserts::assert_rational_(-zero, 0, 1);

    std::cout << "5 * a = " << 5 * a << '\n';
    asserts::assert_rational_(5 * a, 4, 1);

    std::cout << "b * 4 = " << b * 4 << '\n';
    asserts::assert_rational_(b * 4, 14, 1);

    std::cout << "one / a = " << one / a << '\n';
    asserts::assert_rational_(one / a, 5, 4);

    std::cout << "pow(a, 5) = " << pow(a, 5) << '\n';
    asserts::assert_rational_(pow(a, 5), 1024, 3125);

    std::cout << "pow(b, -5) = " << pow(b, -5) << '\n';
    asserts::assert_rational_(pow(b, -5), 32, 16807);

    std::cout << "a / b = " << a / b << '\n';
    asserts::assert_rational_(a / b, 8, 35);

    std::cout << "b / pow(a, 2) = " << b / pow(a, 2) << '\n';
    asserts::assert_rational_(b / pow(a, 2), 175, 32);

    std::cout << "a * b = " << a * b << '\n';
    asserts::assert_rational_(a * b, 14, 5);

    std::cout << "pow(a, -1) * pow(b, -1) = " << pow(a, -1) * pow(b, -1) << '\n';
    asserts::assert_rational_(pow(a, -1) * pow(b, -1), 5, 14);

    std::cout << "b * zero = " << b * zero << '\n';
    asserts::assert_rational_(b * zero, 0, 1);
    assert(b * zero == zero);

    std::cout << "a - b + one = " << a - b + one << '\n';
    asserts::assert_rational_(a - b + one, -17, 10);

    std::cout << "b - a * b = " << b - a * b << '\n';
    asserts::assert_rational_(b - a * b, 7, 10);

    std::cout << "b / a + a * b = " << b / a + a * b << '\n';
    asserts::assert_rational_(b / a + a * b, 287, 40);

    std::cout << "zero / one - (a + b * 4 + one + a / 4) = " << zero / one - (a + b * 4 + one + a / 4) << '\n';
    asserts::assert_rational_(zero / one - (a + b * 4 + one + a / 4), -16, 1);

    std::cout << a << " / " << zero << " = ";
    try {
        std::cout << (a / zero) << '\n';
        assert(false);
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << '\n';
    }
    utils::print_line(2);
}
