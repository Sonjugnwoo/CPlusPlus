#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>

int main() {

	std::vector<int> a(1); // 크기 1
	std::vector<int> b(2); // 크기 2
	std::vector<int> c(4); // 크기 4
	std::vector<int> d(6); // 크기 6
	std::vector<int> e(8); // 크기 8

	//벡터들을 2차원 벡터 container에 순서대로 추가한다.
	std::vector<std::vector<int>> container;
	container.push_back(a);
	container.push_back(b);
	container.push_back(c);
	container.push_back(d);
	container.push_back(e);

	std::vector<int> size_vec(5);	//크기 5

	//std::transform(입력_시작, 입력_끝, 출력_시작, 함수)

	//std::mem_fn을 사용해 size 멤버 함수 호출
	// std::mem_fn을 이용해 container 각 요소(벡터)의 size() 멤버 함수를 호출하여 그 결과를 size_vec에 저장
	std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&std::vector<int>::size));
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr)
		std::cout << "벡터 크기 " << *itr << std::endl;

	//람다 함수를 이용하여 container 각 요소의 size() 반환 값을 size_vec에 저장
	std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v) {return v.size(); });
	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr)
		std::cout << "벡터 크기 " << *itr << std::endl;

}