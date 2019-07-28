#include "Lib.h"

template <u64 TBase>
class Modular {
public:
    Modular(const i64& = 0);

    const i64& GetNumber() const noexcept;

    Modular operator+() const noexcept;
    Modular operator-() const noexcept;

    Modular& operator+=(const Modular&) noexcept;
    Modular& operator-=(const Modular&) noexcept;
    Modular& operator*=(const Modular&) noexcept;
    Modular& operator/=(const Modular&);

    Modular& operator+=(const i64&) noexcept;
    Modular& operator-=(const i64&) noexcept;
    Modular& operator*=(const i64&) noexcept;
    Modular& operator/=(const i64&);

    template <u64 OtherBase>
    friend Modular<OtherBase> operator+(Modular<OtherBase>, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend Modular<OtherBase> operator-(Modular<OtherBase>, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend Modular<OtherBase> operator*(Modular<OtherBase>, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend Modular<OtherBase> operator/(Modular<OtherBase>, const Modular<OtherBase>&);

    template <u64 OtherBase>
    friend bool operator<(const Modular<OtherBase>&, const Modular<OtherBase>&) noexcept;  // operator<

    template <u64 OtherBase>
    friend bool operator<(const i64&, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend bool operator<(const Modular<OtherBase>&, const i64&) noexcept;

    template <u64 OtherBase>
    friend bool operator>(const Modular<OtherBase>&, const Modular<OtherBase>&) noexcept;  // operator>

    template <u64 OtherBase>
    friend bool operator>(const i64&, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend bool operator>(const Modular<OtherBase>&, const i64&) noexcept;
    
    template <u64 OtherBase>
    friend bool operator<=(const Modular<OtherBase>&, const Modular<OtherBase>&) noexcept;  // operator<=

    template <u64 OtherBase>
    friend bool operator<=(const i64&, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend bool operator<=(const Modular<OtherBase>&, const i64&) noexcept;
    
    template <u64 OtherBase>
    friend bool operator>=(const Modular<OtherBase>&, const Modular<OtherBase>&) noexcept;  // operator>=

    template <u64 OtherBase>
    friend bool operator>=(const i64&, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend bool operator>=(const Modular<OtherBase>&, const i64&) noexcept;
    
    template <u64 OtherBase>
    friend bool operator==(const Modular<OtherBase>&, const Modular<OtherBase>&) noexcept;  // operator==

    template <u64 OtherBase>
    friend bool operator==(const i64&, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend bool operator==(const Modular<OtherBase>&, const i64&) noexcept;
    
    template <u64 OtherBase>
    friend bool operator!=(const Modular<OtherBase>&, const Modular<OtherBase>&) noexcept;  // operator!=

    template <u64 OtherBase>
    friend bool operator!=(const i64&, const Modular<OtherBase>&) noexcept;

    template <u64 OtherBase>
    friend bool operator!=(const Modular<OtherBase>&, const i64&) noexcept;

    template <u64 OtherBase>
    friend Modular<OtherBase> pow(const Modular<OtherBase>&, i32) noexcept;

    template <u64 OtherBase>
    friend Modular<OtherBase> InverseElement(const Modular<OtherBase>&);

    template <u64 OtherBase>
    friend std::ostream& operator<<(std::ostream&, const Modular<OtherBase>&) noexcept;

private:
    void Reduce() noexcept;

    i64 number_{};
};

template <u64 TBase>
Modular<TBase>::Modular(const i64& value) {
    if (!is_prime(TBase)) {
        throw std::runtime_error("Base is not a prime number.");
    }
    number_ = value;
    Reduce();
}

template <u64 TBase>
const i64& Modular<TBase>::GetNumber() const noexcept {
    return number_;
}

template <u64 TBase>
Modular<TBase> Modular<TBase>::operator+() const noexcept {
    return *this;
}

template <u64 TBase>
Modular<TBase> Modular<TBase>::operator-() const noexcept {
    return Modular<TBase>(TBase - GetNumber());
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator+=(const Modular<TBase>& other) noexcept {
    number_ += other.GetNumber();
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator-=(const Modular<TBase>& other) noexcept {
    number_ -= other.GetNumber();
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator*=(const Modular<TBase>& other) noexcept {
    number_ *= other.GetNumber();
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator/=(const Modular<TBase>& other) {
    *this *= InverseElement(other);
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator+=(const i64& number) noexcept {
    number_ += number;
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator-=(const i64& number) noexcept {
    number_ -= number;
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator*=(const i64& number) noexcept {
    number_ *= number;
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase>& Modular<TBase>::operator/=(const i64& number) {
    *this *= InverseElement(Modular<TBase>(number));
    Reduce();
    return *this;
}

template <u64 TBase>
Modular<TBase> operator+(Modular<TBase> left, const Modular<TBase>& right) noexcept {  // opeartor+
    left += right;
    return left;
}

template <u64 TBase>
Modular<TBase> operator+(Modular<TBase> mod, const i64& number) noexcept {
    mod += number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator+(const i64& number, Modular<TBase> mod) noexcept {
    mod += number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator-(Modular<TBase> left, const Modular<TBase>& right) noexcept {  // operator-
    left -= right;
    return left;
}

template <u64 TBase>
Modular<TBase> operator-(Modular<TBase> mod, const i64& number) noexcept {
    mod -= number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator-(const i64& number, Modular<TBase> mod) noexcept {
    mod -= number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator*(Modular<TBase> left, const Modular<TBase>& right) noexcept {  // opearor*
    left *= right;
    return left;
}

template <u64 TBase>
Modular<TBase> operator*(Modular<TBase> mod, const i64& number) noexcept {
    mod *= number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator*(const i64& number, Modular<TBase> mod) noexcept {
    mod *= number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator/(Modular<TBase> left, const Modular<TBase>& right) {  // operator/
    left /= right;
    return left;
}

template <u64 TBase>
Modular<TBase> operator/(Modular<TBase> mod, const i64& number) {
    mod /= number;
    return mod;
}

template <u64 TBase>
Modular<TBase> operator/(const i64& number, Modular<TBase> mod) {
    mod /= number;
    return mod;
}

template <u64 TBase>
bool operator<(const Modular<TBase>& left, const Modular<TBase>& right) noexcept {  // operator<
    return left.GetNumber() < right.GetNumber();
}

template <u64 TBase>
bool operator<(const Modular<TBase>& mod, const i64& number) noexcept {
    return mod < Modular<TBase>(number);
}

template <u64 TBase>
bool operator<(const i64& number, const Modular<TBase>& mod) noexcept {
    return Modular<TBase>(number) < mod;
}

template <u64 TBase>
bool operator>(const Modular<TBase>& left, const Modular<TBase>& right) noexcept {  // operator>
    return right < left;
}

template <u64 TBase>
bool operator>(const Modular<TBase>& mod, const i64& number) noexcept {
    return number < mod;
}

template <u64 TBase>
bool operator>(const i64& number, const Modular<TBase>& mod) noexcept {
    return mod < number;
}

template <u64 TBase>
bool operator<=(const Modular<TBase>& left, const Modular<TBase>& right) noexcept {  // operator<=
    return !(left > right);
}

template <u64 TBase>
bool operator<=(const Modular<TBase>& mod, const i64& number) noexcept {
    return !(mod > number);
}

template <u64 TBase>
bool operator<=(const i64& number, const Modular<TBase>& mod) noexcept {
    return !(number > mod);
}

template <u64 TBase>
bool operator>=(const Modular<TBase>& left, const Modular<TBase>& right) noexcept {  // operator>=
    return !(left < right);
}

template <u64 TBase>
bool operator>=(const Modular<TBase>& mod, const i64& number) noexcept {
    return !(mod < number);
}

template <u64 TBase>
bool operator>=(const i64& number, const Modular<TBase>& mod) noexcept {
    return !(number < mod);
}

template <u64 TBase>
bool operator==(const Modular<TBase>& left, const Modular<TBase>& right) noexcept {  // operator==
    return left <= right && left >= right;
}

template <u64 TBase>
bool operator==(const Modular<TBase>& mod, const i64& number) noexcept {
    return mod <= number && mod >= number;
}

template <u64 TBase>
bool operator==(const i64& number, const Modular<TBase>& mod) noexcept {
    return mod <= number && mod >= number;
}

template <u64 TBase>
bool operator!=(const Modular<TBase>& left, const Modular<TBase>& right) noexcept {  // operator!=
    return !(left == right);
}

template <u64 TBase>
bool operator!=(const Modular<TBase>& mod, const i64& number) noexcept {
    return !(mod == number);
}

template <u64 TBase>
bool operator!=(const i64& number, const Modular<TBase>& mod) noexcept {
    return !(mod == number);
}

template <u64 TBase>
Modular<TBase> pow(const Modular<TBase>& number, i32 power) noexcept {
    if (power < 0) {
        return pow(InverseElement(number), -power);
    } else if (power == 0) {
        return 1;
    } else if (power % 2 != 0) {
        return number * pow(number, power - 1);
    } else {
        auto tmp = pow(number, power / 2);
        return tmp * tmp;
    }
}

template <u64 TBase>
Modular<TBase> InverseElement(const Modular<TBase>& number) {
    if (number == 0) {
        throw std::runtime_error("Division by zero.");
    }
    return pow(number, TBase - 2);
}

template <u64 TBase>
std::ostream& operator<<(std::ostream& out, const Modular<TBase>& number) noexcept {
    return out << number.GetNumber();
}

template <u64 TBase>
void Modular<TBase>::Reduce() noexcept {  // private
    if (GetNumber() < 0) {
        number_ += (-number_ / TBase + 1) * TBase;
    }
    number_ %= TBase;
}
