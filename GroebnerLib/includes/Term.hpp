#pragma once

#include "Lib.hpp"

namespace gb {

class Term;
std::list<Term> GetAllDivisors(const Term&);

class Term {
public:
    using container = std::map<gb::i64, gb::i64>;

    Term();
    Term(const std::vector<gb::i64>&);
    static Term term_from_map(const container&);

    const container& GetDegrees() const noexcept;  // x_(i)^{j} = {i - 1, j} [numeration starts from 0].

    gb::i64 GetDegree(const gb::i64&) const noexcept;
    gb::i64 GetLastVariableIndex() const noexcept;
    friend gb::i64 deg(const Term&) noexcept;
    friend std::list<Term> GetAllDivisors(const Term&);

    bool IsOne() const noexcept;
    bool IsDivisibleBy(const Term&) const noexcept;

    Term& operator*=(const Term&) noexcept;
    friend Term operator*(Term, const Term&) noexcept;

    Term& operator/=(const Term&);
    friend Term operator/(Term, const Term&);

    friend bool operator==(const Term&, const Term&) noexcept;
    friend bool operator!=(const Term&, const Term&) noexcept;

    friend Term gcd(const Term&, const Term&) noexcept;
    friend Term lcm(const Term&, const Term&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Term&) noexcept;

private:
    container data_{};  // (variable number) && (power)
};

std::list<Term> GetAllDivisors_(const Term&, const gb::i64&);

}  // namespace gb
