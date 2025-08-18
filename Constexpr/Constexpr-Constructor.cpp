#include <iostream>

class Vector {
public:
	// constexpr 생성자: 컴파일 타임에 객체 생성 가능
	constexpr Vector(int x, int y) : x_(x), y_(y) {}

	// x, y 구성 요소를 constexpr 함수로 반환
	constexpr int x() const { return x_; }
	constexpr int y() const { return y_; }

private:
	int x_, y_;
};

//constexpr 함수: 두 Vector의 합을 컴파일 타임에 계산
constexpr Vector AddVec(const Vector& v1, const Vector& v2) {
	return { v1.x() + v2.x() , v1.y() + v2.y() };
}

template <int N>
struct A {
	int operator () () { return N; }
};

int main() {
	constexpr Vector v1(1, 2);
	constexpr Vector v2(3, 4);

	A<v1.x()> a;		// v1.x() = 1 이 템플릿 인자로 전달
	std::cout << a() << std::endl;

	A<AddVec(v1, v2).x()> b;		 // v1 + v2 = (4, 6), x 값인 4가 템플릿 인자로 전달
	std::cout << b() << std::endl;
}