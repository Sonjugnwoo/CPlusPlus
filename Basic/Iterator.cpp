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

		class Iterator {
			int* loc;     // 현재 이터레이터가 가리키는 다차원 배열의 인덱스 배열 (예: [i, j, k])
			Array* arr;   // 이터레이터가 순회할 대상 Array 객체의 포인터

			friend Int;   // Int 클래스가 Iterator의 private/protected 멤버에 접근 가능하도록 friend 선언
		public:
			// 생성자: 배열 객체와 (필요시) 인덱스 배열을 받아 이터레이터를 초기화
			Iterator(Array* arr, int* loc = NULL) : arr(arr) {
				// 배열 차원 수만큼 인덱스 배열 동적 할당
				this->loc = new int[arr->dim];

				for (int i = 0; i != arr->dim; i++)
					// loc 인자가 주어지면 그 값을 복사, 아니면 0으로 초기화
					this->loc[i] = (loc != NULL ? loc[i] : 0);
			}

			// 복사 생성자: 다른 Iterator 객체로부터 복사 생성
			Iterator(const Iterator& itr) : arr(itr.arr) {
				loc = new int[arr->dim];

				for (int i = 0; i != arr->dim; i++)
					loc[i] = itr.loc[i]; // 인덱스 배열 값 복사
			}

			// 소멸자: 동적으로 할당한 인덱스 배열 메모리 해제
			~Iterator() {
				delete[] loc;
			}
			Iterator operator++() {
				if (loc[0] > arr->size[0]) return (*this);		 // 첫 번째 차원의 인덱스가 배열 크기를 초과하면 더 이상 증가하지 않음

				bool carry = false; // 자리올림(캐리) 발생 여부
				int i = arr->dim - 1; // 마지막 차원부터 시작

				do {
					loc[i]++; // 현재 차원의 인덱스 증가

					 // 만약 현재 차원의 인덱스가 해당 차원의 크기를 넘으면
					if (loc[i] >= arr->size[i] && i >= 1) {
						loc[i] -= arr->size[i]; // 0으로 초기화(자리올림)
						carry = true;           // 자리올림 발생
						i--;                    // 상위 차원으로 이동
					}
					else
						carry = false;          // 자리올림 없음 → 루프 종료

				} while (i >= 0 && carry);

				return (*this); // 증가된 이터레이터 반환
			}
			Iterator& operator=(const Iterator& itr) {
				arr = itr.arr;
				loc = new int[itr.arr->dim];

				for (int i = 0; i != arr->dim; i++)
					loc[i] = itr.loc[i];

				return (*this);
			}

			Iterator operator++(int) {
				Iterator itr(*this);
				++(*this);
				return itr;
			}

			bool operator!= (const Iterator& itr) {
				if (itr.arr->dim != arr->dim) return true;
				for (int i = 0; i != arr->dim; i++)
					if (itr.arr->dim != loc[i]) return true;

				return false;
			}
			Int operator*();
		};
		friend Iterator;
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

		// Array 클래스의 operator[]: 첫 번째 차원 인덱싱을 처리하여 Int 프록시 객체를 반환
		Int operator[](const int idx) {
			// level=1(첫 번째 차원), 시작 주소는 top, 현재 Array 객체(this)를 넘김
			return Int(idx, 1, static_cast<void*>(top), this);
		}
		~Array()
		{
			DeleteAddress(top);
			delete[] size;
		}
		// 배열의 시작 위치(처음 인덱스)를 가리키는 이터레이터 반환
		Iterator Begin() {
			int* arr = new int[dim];    // 차원 수만큼 인덱스 배열 동적 할당
			for (int i = 0; i != dim; i++)
				arr[i] = 0;             // 모든 차원의 인덱스를 0으로 초기화 (배열의 첫 번째 원소)

			Iterator temp(this, arr);   // 현재 Array 객체와 인덱스 배열로 이터레이터 생성
			delete[] arr;               // 임시 인덱스 배열 메모리 해제

			return temp;                // 시작 위치 이터레이터 반환
		}

		// 배열의 끝 위치(마지막 다음 인덱스)를 가리키는 이터레이터 반환
		Iterator end() {
			int* arr = new int[dim];    // 차원 수만큼 인덱스 배열 동적 할당
			arr[0] = size[0];           // 첫 번째 차원의 인덱스를 size[0]으로 설정 (end 조건)
			for (int i = 1; i != dim; i++)
				arr[i] = 0;             // 나머지 차원은 0으로 초기화

			Iterator temp(this, arr);   // 현재 Array 객체와 인덱스 배열로 이터레이터 생성
			delete[] arr;               // 임시 인덱스 배열 메모리 해제

			return temp;                // 끝 위치 이터레이터 반환
		}
	};
	class Int {
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

		// Int 클래스의 int 변환 연산자: Int 객체를 int형 값으로 변환
		operator int() {
			// data가 유효하면 int 값 반환, 아니면 0 반환
			if (data) return *static_cast<int*>(data);
			return 0;
		}
				
		// Int 클래스의 int 대입 연산자: Int 객체가 가리키는 위치에 int 값을 대입
		Int& operator=(const int& a) {
			// data가 유효하면 해당 위치에 a 값을 저장
			if (data) *static_cast<int*>(data) = a;
			return *this;
		}

		// Int 클래스의 operator[]: 다음 차원 인덱싱을 지원하는 함수
		Int operator[](const int idx) {
			// data가 유효하지 않으면 0(Int 객체, 암시적 변환) 반환
			if (!data) return 0;
			// 다음 차원의 Int 프록시 객체 생성 및 반환
			return Int(idx, level + 1, data, arr);
		}
	};
	
}

//[네임스페이스]::[외부클래스]::[내부클래스]::함수이름
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