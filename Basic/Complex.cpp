#include <cstring>
#include <iostream>

class Complex {
private:
    double real, img; // �Ǽ���, �����

    double get_number(const char* str, int from, int to) const; // ���ڿ����� ����� ��� ����

public:
    Complex(double real, double img) : real(real), img(img) {} // �Ǽ�, ����� ����
    Complex(const Complex& c) { real = c.real, img = c.img; }  // ���� ������
    Complex(const char* str); // ���ڿ��κ��� ������

    // ��Ģ���� ������ �����ε�
    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    // ���ڿ����� ���� �����ε�
    Complex operator+(const char* str) const;
    Complex operator-(const char* str) const;
    Complex operator*(const char* str) const;
    Complex operator/(const char* str) const;

    // ���� ���� ������ �����ε�
    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex& operator=(const Complex& c); // ���� ������

    void println() {
        std::cout << "( " << real << " , " << img << " ) " << std::endl;
    }
};

// ���ڿ��κ��� ���Ҽ� ������
Complex::Complex(const char* str) {
    // �Է� ���� ���ڿ��� �м��Ͽ� real �κа� img �κ��� ã�ƾ� �Ѵ�.
    // ���ڿ��� ���� ������ �����ϴ� "[��ȣ](�Ǽ���)(��ȣ)i(�����)"
    // �� �� �� ���� ��ȣ�� ���� �����մϴ�. (������ + �� ����)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // ���� ���� ������ �Ǵ� 'i' �� ��ġ�� ã�´�.
    int pos_i = -1;
    for (int i = 0; i != end; i++) {
        if (str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // ���� 'i' �� ���ٸ� �� ���� �Ǽ� ���̴�.
    if (pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // ���� 'i' �� �ִٸ�,  �Ǽ��ο� ����θ� ����� ó���ϸ� �ȴ�.
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end - 1);

    if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;    // ����� ��ȣ ����
}

// ���ڿ����� �Ǽ���/����� ���� (from~to ����)
double Complex::get_number(const char* str, int from, int to) const {
    char buf[100] = { 0 };
    int idx = 0;
    for (int i = from; i <= to; ++i) {
        if (str[i] != ' ' && str[i] != 'i') // ����, 'i' ����
            buf[idx++] = str[i];
    }
    buf[idx] = '\0';
    return atof(buf);
}

// ��Ģ���� ������ �����ε�
Complex Complex::operator+(const Complex& c) const {
    Complex temp(real + c.real, img + c.img); // �Ǽ���, ����� ���� ����
    return temp;
}
Complex Complex::operator-(const Complex& c) const {
    Complex temp(real - c.real, img - c.img); // �Ǽ���, ����� ���� ��
    return temp;
}
Complex Complex::operator*(const Complex& c) const {
    Complex temp(real * c.real - img * c.img, real * c.img + img * c.real); // ���Ҽ� ���� ����
    return temp;
}
Complex Complex::operator/(const Complex& c) const {
    Complex temp(
        (real * c.real + img * c.img) / (c.real * c.real + c.img * c.img), // �Ǽ���
        (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img)); // �����
    return temp;
}

// ���ڿ����� ���� �����ε� (���ڿ��� Complex�� ��ȯ �� ����)
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

// ���� ���� ������ �����ε�
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

// ���� ������ �����ε�
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = a + "-1.1 + i3.923"; // ���ڿ��� Complex�� ��ȯ �� ����
    a.println();
    a = a - "1.2 -i1.823";   // ���ڿ��� Complex�� ��ȯ �� ����
    a.println();
    a = a * "2.3+i22";       // ���ڿ��� Complex�� ��ȯ �� ����
    a.println();
    a = a / "-12+i55";       // ���ڿ��� Complex�� ��ȯ �� ������
    a.println();
}