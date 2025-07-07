#include <cstring>
#include <iostream>

class Complex {
private:
    double real, img; // 실수부, 허수부

    double get_number(const char* str, int from, int to) const; // 문자열에서 허수부 계수 추출

public:
    Complex(double real, double img) : real(real), img(img) {} // 실수, 허수로 생성
    Complex(const Complex& c) { real = c.real, img = c.img; }  // 복사 생성자
    Complex(const char* str); // 문자열로부터 생성자

    // 사칙연산 연산자 오버로딩
    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    // 문자열과의 연산 오버로딩
    Complex operator+(const char* str) const;
    Complex operator-(const char* str) const;
    Complex operator*(const char* str) const;
    Complex operator/(const char* str) const;

    // 복합 대입 연산자 오버로딩
    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex& operator=(const Complex& c); // 대입 연산자

    void println() {
        std::cout << "( " << real << " , " << img << " ) " << std::endl;
    }
};

// 문자열로부터 복소수 생성자
Complex::Complex(const char* str) {
    // 입력 받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 한다.
    // 문자열의 꼴은 다음과 같습니다 "[부호](실수부)(부호)i(허수부)"
    // 이 때 맨 앞의 부호는 생략 가능합니다. (생략시 + 라 가정)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // 먼저 가장 기준이 되는 'i' 의 위치를 찾는다.
    int pos_i = -1;
    for (int i = 0; i != end; i++) {
        if (str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // 만일 'i' 가 없다면 이 수는 실수 뿐이다.
    if (pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // 만일 'i' 가 있다면,  실수부와 허수부를 나누어서 처리하면 된다.
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end - 1);

    if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;    // 허수부 부호 적용
}

// 문자열에서 실수부/허수부 추출 (from~to 범위)
double Complex::get_number(const char* str, int from, int to) const {
    char buf[100] = { 0 };
    int idx = 0;
    for (int i = from; i <= to; ++i) {
        if (str[i] != ' ' && str[i] != 'i') // 공백, 'i' 제외
            buf[idx++] = str[i];
    }
    buf[idx] = '\0';
    return atof(buf);
}

// 사칙연산 연산자 오버로딩
Complex Complex::operator+(const Complex& c) const {
    Complex temp(real + c.real, img + c.img); // 실수부, 허수부 각각 더함
    return temp;
}
Complex Complex::operator-(const Complex& c) const {
    Complex temp(real - c.real, img - c.img); // 실수부, 허수부 각각 뺌
    return temp;
}
Complex Complex::operator*(const Complex& c) const {
    Complex temp(real * c.real - img * c.img, real * c.img + img * c.real); // 복소수 곱셈 공식
    return temp;
}
Complex Complex::operator/(const Complex& c) const {
    Complex temp(
        (real * c.real + img * c.img) / (c.real * c.real + c.img * c.img), // 실수부
        (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img)); // 허수부
    return temp;
}

// 문자열과의 연산 오버로딩 (문자열을 Complex로 변환 후 연산)
Complex Complex::operator+(const char* str) const {
    Complex temp(str);
    return (*this) + temp;
}
Complex Complex::operator-(const char* str) const {
    Complex temp(str);
    return (*this) - temp;
}
Complex Complex::operator*(const char* str) const {
    Complex temp(str);
    return (*this) * temp;
}
Complex Complex::operator/(const char* str) const {
    Complex temp(str);
    return (*this) / temp;
}

// 복합 대입 연산자 오버로딩
Complex& Complex::operator+=(const Complex& c) {
    (*this) = (*this) + c;
    return *this;
}
Complex& Complex::operator-=(const Complex& c) {
    (*this) = (*this) - c;
    return *this;
}
Complex& Complex::operator*=(const Complex& c) {
    (*this) = (*this) * c;
    return *this;
}
Complex& Complex::operator/=(const Complex& c) {
    (*this) = (*this) / c;
    return *this;
}

// 대입 연산자 오버로딩
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = a + "-1.1 + i3.923"; // 문자열을 Complex로 변환 후 덧셈
    a.println();
    a = a - "1.2 -i1.823";   // 문자열을 Complex로 변환 후 뺄셈
    a.println();
    a = a * "2.3+i22";       // 문자열을 Complex로 변환 후 곱셈
    a.println();
    a = a / "-12+i55";       // 문자열을 Complex로 변환 후 나눗셈
    a.println();
}