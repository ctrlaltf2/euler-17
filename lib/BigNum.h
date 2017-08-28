#include <bitset>
#include <cmath>
#include <cstdint>
#include <exception>

class BigNum {
private:
    friend std::ostream& operator<< (std::ostream& os, const BigNum& num);
    friend std::istream& operator>> (std::istream& is, const BigNum& num);

    std::vector<uint_fast8_t> m_digits;
    bool signBit{0}; // True if negative

public:

    /* Constructors */
    BigNum() { m_digits.push_back(0); }

    BigNum(const char * cstr);
    BigNum(const std::string& s);

    BigNum(int i);
    BigNum(long l);
    BigNum(long long ll);

    BigNum(unsigned int ui);
    BigNum(unsigned long ul);
    BigNum(unsigned long long ull);

    BigNum(const BigNum& bn);
    BigNum(BigNum&& bn);

    /* Assignment Operators */
    const BigNum& operator= (const char * cstr);
    const BigNum& operator= (const std::string& s);

    const BigNum& operator= (int i);
    const BigNum& operator= (long l);
    const BigNum& operator= (long long ll);

    const BigNum& operator= (unsigned int ui);
    const BigNum& operator= (unsigned long ul);
    const BigNum& operator= (unsigned long long ull);

    const BigNum& operator= (const BigNum& bn);
    const BigNum& operator= (BigNum&& bn);

    /* Operational Assignment Operators */
    const BigNum& operator+= (const BigNum& rhs) noexcept;
    const BigNum& operator+= (const std::size_t rhs) noexcept;

    const BigNum& operator-= (const BigNum& rhs) noexcept;
    const BigNum& operator-= (const std::size_t rhs) noexcept;

    const BigNum& operator*= (const BigNum& rhs) noexcept;
    const BigNum& operator*= (const std::size_t rhs) noexcept;

    const BigNum& operator/= (const BigNum& rhs);
    const BigNum& operator/= (const std::size_t rhs);

    const BigNum& operator%= (const BigNum& rhs);
    const BigNum& operator%= (const std::size_t rhs);

    const BigNum& operator^= (const BigNum& rhs);
    const BigNum& operator^= (const std::size_t rhs);

    /* Arithmetic Operators */l
    BigNum operator- () const;

    BigNum operator+ (const BigNum& rhs) const noexcept;
    BigNum operator+ (const std::size_t rhs) const noexcept;

    BigNum operator- (const BigNum& rhs) const noexcept;
    BigNum operator- (const std::size_t rhs) const noexcept;

    BigNum operator* (const BigNum& rhs) const noexcept;
    BigNum operator* (const std::size_t rhs) const noexcept;

    BigNum operator/ (const BigNum& rhs) const ;
    BigNum operator/ (const std::size_t rhs) const;

    BigNum operator% (const BigNum& rhs) const;
    BigNum operator% (const std::size_t rhs) const;

    BigNum operator^ (const BigNum& rhs) const;
    BigNum operator^ (const std::size_t rhs) const;

    /* Decrement and Increment Operators */
    const BigNum& operator++ () noexcept;
    const BigNum& operator-- () noexcept;

    BigNum operator++ (int) noexcept;
    BigNum operator-- (int) noexcept;

    /* Relational Operators */
    bool operator== (const BigNum& rhs) const noexcept;
    bool operator!= (const BigNum& rhs) const noexcept;
    bool operator<  (const BigNum& rhs) const noexcept;
    bool operator<= (const BigNum& rhs) const noexcept;
    bool operator>  (const BigNum& rhs) const noexcept;
    bool operator>= (const BigNum& rhs) const noexcept;

    /* Exponents */
    static BigNum pow(const std::size_t base,   const std::size_t exponent);
    static BigNum pow(const std::size_t base,   const BigNum& exponent);
    static BigNum pow(const BigNum& base,       const std::size_t exponent);
    static BigNum pow(const BigNum& base,       const BigNum& exponent);
    // Integer approximation of square root (same as floor(sqrt(n)) )
    static BigNum sqrt(const BigNum& bn);

    /* Conversions to other useful types */
    std::string to_string() const noexcept;

    int toInt() const;
    long toLong() const;
    long long toLongLong() const;

    unsigned int toUInt() const;
    unsigned long toULong() const;
    unsigned long long toULongLong() const;

    /* Other stuff */
    // Calls shrink_to_fit then removes leading zeros
    void shrink() {
        if(m_digits.front() == 0)
            m_digits.erase(m_digits.begin(), std::find_if_not(m_digits.begin(), m_digits.end(),  [](const auto& i)->bool { return i == 0; }) );
        m_digits.shrink_to_fit();
    }
    long sumOfDigits() const noexcept { return std::accumulate(m_digits.begin(), m_digits.end(), 0); }

};
