#include <iostream>

namespace MyArray
{
	//Array와 Int 클래스를 미리 선언(전방 선언)하여, 서로 참조할 수 있게 합니다.
	class Array;
	class Int;

	class Array {

		friend Int;			    // Int 클래스가 Array의 private/protected 멤버에 접근 가능
		const int dim;			// N 차원 배열
		int* size;				// size[0] *size[1] * ... * size[dim-1] 배열

		struct Address
		{
			int level;	//맨마지막 레벨은 데이터 배열 ,, 상위 레벨에서는 다음 Address
			void* next;
		};
		Address* top;
	public:
		Array(int dim, int* arr_size) : dim(dim)	// 차원 수 와 각 차원의 크기 정보 
		{
			size = new int[dim];	//차원의 크기를 받을 int 배열 동적 할당
			for (int i = 0; i < dim; i++)
				size[i] = arr_size[i];	//전달받은 값을 size 배열에 복사 

			top = new Address; // 새로운 Address 객체를 생성 (배열의 루트)
			top->level = 0;    // 루트의 level은 0으로 설정

			InitalizeAddress(top);	// top을 시작으로 전체 Address 구조를 초기화 (메모리 할당 및 구조 생성)

		}
		// 복사 생성자 
		Array(const Array& arr) : dim(arr.dim)	// 원본 Array의 dim 을 복사 
		{
			size = new int[dim];
			for (int i = 0; i < dim; i++)
				size[i] = arr.size[i];

			top = new Address;
			top->level = 0;

			InitalizeAddress(top);
			CopyAddress(top, arr.top);
		}
		void InitalizeAddress(Address* cur);
		void CopyAddress(Address* dst, Address* src);
		void DeleteAddress(Address* cur);
		Int operator[](const int idx);
		~Array()
		{
			DeleteAddress(top);
			delete[] size;
		}
	};
	class Int{
		 void* data;

		int level;
		Array* arr;

	public:
		//int _level = 0, void* _data = NULL, Array* _arr = NULL 디폴트 인자
		Int(int idx, int _level = 0, void* _data = NULL, Array* _arr = NULL) : level(_level), data(_data), arr(_arr)
		{
			// 유효성 검사: level이 1 미만이거나, idx가 해당 차원의 크기 이상이면 data를 NULL로 설정하고 종료
			if (_level < 1 || idx >= arr->size[_level - 1]) {
				data = NULL;
				return;
			}

			// 만약 현재 level이 배열의 차원 수와 같다면 (마지막 차원)
			if (level == arr->dim)
				data = static_cast<void*>((static_cast<int*>(static_cast<Array::Address*>(data)->next) + idx));    // data를 int 배열의 idx번째 원소를 가리키는 포인터로 설정

			  // 아직 마지막 차원이 아니면, 다음 Address 객체의 idx번째 주소를 가리키는 포인터로 설정
			else
				data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next) + idx);
		}
		Int(const Int& i) : data(i.data), level(i.level), arr(i.arr) {}
		operator int();
		Int& operator=(const int& a);
		Int operator[](const int idx);
	};
}

//Address 초기화 함수 
void MyArray::Array::InitalizeAddress(Address* cur)
{
	if (!cur) return;					//cur 이 NULL 일때 예외 처리 

	if (cur->level == dim - 1)			// 종료 조건 (최하위 차원에 도달 했음)
	{
		cur->next = new int[size[cur->level]];	// 실제 데이터를 저장할 int 배열 동적 할당
		return;
	}

	cur->next = new Address[size[cur->level]];	// 현재 노드(cur)의 다음 단계 Address 객체들을 위한 메모리(배열) 동적 할당

	for (int i = 0; i != size[cur->level]; i++)	// 현재 단계(cur->level)의 다음 단계 Address 객체들을 순회 (깊이 우선 탐색 )
	{
		// (static_cast<Address*>(cur->next) + i): i번째 Address 객체의 주소
		(static_cast<Address*>(cur->next) + i)->level = cur->level + 1;	 // i번째 Address 객체의 level을 현재보다 1 크게 설정
		InitalizeAddress(static_cast<Address*>(cur->next) + i);
	}
}

// Address 구조체 트리를 재귀적으로 복사하는 함수
void MyArray::Array::CopyAddress(Address* dst, Address* src)
{
	// 만약 현재 레벨이 마지막 차원(실제 데이터 배열)이라면
	if (dst->level == dim - 1)
	{
		// 해당 차원의 크기만큼 반복하면서 int 배열의 값을 복사
		for (int i = 0; i < size[dst->level]; ++i)
			static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];
		return; // 복사 완료 후 함수 종료
	}

	// 마지막 차원이 아니라면(아직 Address 트리의 중간 단계라면)
	for (int i = 0; i != size[dst->level]; i++)
	{
		// dst->next와 src->next를 Address* 배열로 보고, i번째 자식 Address를 얻음
		Address* new_dst = static_cast<Address*>(dst->next) + i;
		Address* new_src = static_cast<Address*>(src->next) + i;
		// 재귀적으로 하위 Address 트리도 복사
		CopyAddress(new_dst, new_src);
	}
}

// Address 구조체(또는 클래스)의 동적 메모리 해제 함수
void MyArray::Array::DeleteAddress(Address* cur)
{
	if (!cur) return;	//cur 이 NULL 일때 예외 처리 

	// 아직 마지막 차원이 아니면, 자식 Address 객체들에 대해 재귀적으로 DeleteAddress 호출 
	// (이 과정에서 함수 호출이 스택처럼 쌓임)
	for (int i = 0; cur->level < dim - 1 && i < size[cur->level]; i++)
		DeleteAddress(static_cast<Address*>(cur->next) + i);

	// 현재 노드의 next(동적 할당된 배열 또는 int 배열) 메모리 해제
	delete[] cur->next;
}

// Array 클래스의 operator[]: 첫 번째 차원 인덱싱을 처리하여 Int 프록시 객체를 반환
MyArray::Int MyArray::Array::operator[](const int idx)
{
	// level=1(첫 번째 차원), 시작 주소는 top, 현재 Array 객체(this)를 넘김
	return Int(idx, 1, static_cast<void*>(top), this);
}

// Int 클래스의 int 변환 연산자: Int 객체를 int형 값으로 변환
MyArray::Int::operator int()
{
	// data가 유효하면 int 값 반환, 아니면 0 반환
	if (data) return *static_cast<int*>(data);
	return 0;
}

// Int 클래스의 int 대입 연산자: Int 객체가 가리키는 위치에 int 값을 대입
MyArray::Int& MyArray::Int::operator=(const int& a)
{
	// data가 유효하면 해당 위치에 a 값을 저장
	if (data) *static_cast<int*>(data) = a;
	return *this;
}

// Int 클래스의 operator[]: 다음 차원 인덱싱을 지원하는 함수
MyArray::Int MyArray::Int::operator[](const int idx)
{
	// data가 유효하지 않으면 0(Int 객체, 암시적 변환) 반환
	if (!data) return 0;
	// 다음 차원의 Int 프록시 객체 생성 및 반환
	return Int(idx, level + 1, data, arr);
}


int main() {
	int size[] = { 2, 3, 4 };
	MyArray::Array arr(3, size);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
					<< std::endl;
			}
		}
	}
}