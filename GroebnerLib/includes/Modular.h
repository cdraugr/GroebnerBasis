#pragma once

#include "Lib.h"

template <u64 TBase>
class Modular {
public:
    Modular(i64 = 0);

    const i64& GetNumber() const noexcept;

    Modular operator+() const noexcept;
    Modular operator-() const noexcept;

    Modular& operator+=(const Modular&) noexcept;
    Modular& operator-=(const Modular&) noexcept;
    Modular& operator*=(const Modular&) noexcept;
    Modular& operator/=(const Modular&);

    friend Modular<TBase> operator+(Modular left, const Modular& right) noexcept {
        left += right;
        return left;
    }

    friend Modular<TBase> operator-(Modular left, const Modular& right) noexcept {
        left -= right;
        return left;
    }

    friend Modular<TBase> operator*(Modular left, const Modular& right) noexcept {
        left *= right;
        return left;
    }

    friend Modular<TBase> operator/(Modular left, const Modular& right) {
        left /= right;
        return left;
    }

    friend bool operator<(const Modular& left, const Modular& right) noexcept {
        return left.GetNumber() < right.GetNumber();
    }

    friend bool operator>(const Modular& left, const Modular& right) noexcept {
        return right < left;
    }

    friend bool operator<=(const Modular& left, const Modular& right) noexcept {
        return !(left > right);
    }

    friend bool operator>=(const Modular& left, const Modular& right) noexcept {
        return !(left < right);
    }

    friend bool operator==(const Modular& left, const Modular& right) noexcept {
        return left <= right && left >= right;;
    }

    friend bool operator!=(const Modular& left, const Modular& right) noexcept {
        return !(left == right);
    }

    template <u64 OtherBase>
    friend Modular<OtherBase> pow(const Modular<OtherBase>&, const i64&);

    template <u64 OtherBase>
    friend Modular<OtherBase> InverseElement(const Modular<OtherBase>&);

    template <u64 OtherBase>
    friend std::ostream& operator<<(std::ostream&, const Modular<OtherBase>&) noexcept;

private:
    void Reduce() noexcept;

    i64 number_{};
};

template <u64 TBase>
Modular<TBase>::Modular(i64 value) {
    if (!is_prime(TBase)) {
        throw std::runtime_error("Base is not a prime number.");
    }
    number_ = std::move(value);
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
Modular<TBase> pow(const Modular<TBase>& number, const i64& power) {
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
    if (number.GetNumber() == 0) {
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
