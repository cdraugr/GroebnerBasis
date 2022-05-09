#include "Tests.hpp"

void test_modular() {
    std::cout << "Test Modular:\n";
    const u64 TBase = 53;
    std::cout << "TBase = " << TBase << ":\n";

    gb::fields::Modular<TBase> a(200);  // 41
    asserts::assert_modular_(a, 41);
    gb::fields::Modular<TBase> b(INT32_MIN);  // 32
    asserts::assert_modular_(b, 32);
    gb::fields::Modular<TBase> one(1);  // 1
    asserts::assert_modular_(one, 1);
    gb::fields::Modular<TBase> zero;  // 0
    asserts::assert_modular_(zero, 0);

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "one = " << one << '\n';
    std::cout << "zero = " << zero << '\n';
    std::cout << std::boolalpha << "a < b is " << (a < b) << '\n';
    assert(a < b == false);
    std::cout << std::boolalpha << "a > b is " << (a > b) << '\n';
    assert(a > b == true);
    std::cout << std::boolalpha << "a <= b is " << (a <= b) << '\n';
    assert(a <= b == false);
    std::cout << std::boolalpha << "a >= b is " << (a >= b) << '\n';
    assert(a >= b == true);
    std::cout << std::boolalpha << "a == 4 is " << (a == 4) << '\n';
    assert(a == b == false);
    utils::print_line();

    std::cout << "+a = " << +a << '\n';
    asserts::assert_modular_(+a, 41);

    std::cout << "-one = " << -one << '\n';
    asserts::assert_modular_(-one, 52);

    std::cout << "-zero = " << -zero << '\n';
    asserts::assert_modular_(-zero, 0);

    std::cout << "5 * a = " << 5 * a << '\n';
    asserts::assert_modular_(5 * a, 46);

    std::cout << "b * 4 = " << b * 4 << '\n';
    asserts::assert_modular_(b * 4, 22);

    std::cout << "1 / a = " << 1 / a << '\n';
    asserts::assert_modular_(1 / a, 22);

    std::cout << "pow(a, 5) = " << pow(a, 5) << '\n';
    asserts::assert_modular_(pow(a, 5), 3);

    std::cout << "pow(b, -5) = " << pow(b, -5) << '\n';
    asserts::assert_modular_(pow(b, -5), 51);

    std::cout << "a / b = " << a / b << '\n';
    asserts::assert_modular_(a / b, 46);

    std::cout << "b / pow(a, 2) = " << b / pow(a, 2) << '\n';
    asserts::assert_modular_(b / pow(a, 2), 12);
    utils::print_line();

    std::cout << "a * b = " << a * b << '\n';
    asserts::assert_modular_(a * b, 40);

    std::cout << "pow(a, -1) * pow(b, -1) = " << pow(a, -1) * pow(b, -1) << '\n';
    asserts::assert_modular_(pow(a, -1) * pow(b, -1), 4);

    std::cout << "a ^ (-1) * b ^ (-1) = " << InverseElement(a) * InverseElement(b) << '\n';
    asserts::assert_modular_(InverseElement(a) * InverseElement(b), 4);

    std::cout <<  "a * b * a ^ (-1) * b ^ (-1) = " << a * b * InverseElement(a) * InverseElement(b) << '\n';
    asserts::assert_modular_(a * b * InverseElement(a) * InverseElement(b), 1);
    utils::print_line();

    std::cout << "b * zero = " << b * zero << '\n';
    asserts::assert_modular_(b * zero, 0);
    assert(b * zero == zero);

    std::cout << "a - b + one = " << a - b + one << '\n';
    asserts::assert_modular_(a - b + one, 10);

    std::cout << "b - a * b = " << b - a * b << '\n';
    asserts::assert_modular_(b - a * b, 45);

    std::cout << "b / a + a * b = " << b / a + a * b << '\n';
    asserts::assert_modular_(b / a + a * b, 2);

    std::cout << "zero / one - (a + b * 4 + one + a / 4) = " << zero / one - (a + b * 4 + one + a / 4) << '\n';
    asserts::assert_modular_(zero / one - (a + b * 4 + one + a / 4), 45);

    std::cout << a << " / " << zero << " = ";
    try {
        std::cout << (a / zero) << '\n';
        assert(false);
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << '\n';
    }
    utils::print_line(2);
}
