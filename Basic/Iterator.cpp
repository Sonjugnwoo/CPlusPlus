#include <iostream>

namespace MyArray
{
	//Array�� Int Ŭ������ �̸� ����(���� ����)�Ͽ�, ���� ������ �� �ְ� �մϴ�.
	class Array;
	class Int;

	class Array {

		friend Int;			    // Int Ŭ������ Array�� private/protected ����� ���� ����
		const int dim;			// N ���� �迭
		int* size;				// size[0] *size[1] * ... * size[dim-1] �迭

		struct Address
		{
			int level;	//�Ǹ����� ������ ������ �迭 ,, ���� ���������� ���� Address
			void* next;
		};
		Address* top;
	public:

		class Iterator {
			int* loc;     // ���� ���ͷ����Ͱ� ����Ű�� ������ �迭�� �ε��� �迭 (��: [i, j, k])
			Array* arr;   // ���ͷ����Ͱ� ��ȸ�� ��� Array ��ü�� ������

			friend Int;   // Int Ŭ������ Iterator�� private/protected ����� ���� �����ϵ��� friend ����
		public:
			// ������: �迭 ��ü�� (�ʿ��) �ε��� �迭�� �޾� ���ͷ����͸� �ʱ�ȭ
			Iterator(Array* arr, int* loc = NULL) : arr(arr) {
				// �迭 ���� ����ŭ �ε��� �迭 ���� �Ҵ�
				this->loc = new int[arr->dim];

				for (int i = 0; i != arr->dim; i++)
					// loc ���ڰ� �־����� �� ���� ����, �ƴϸ� 0���� �ʱ�ȭ
					this->loc[i] = (loc != NULL ? loc[i] : 0);
			}

			// ���� ������: �ٸ� Iterator ��ü�κ��� ���� ����
			Iterator(const Iterator& itr) : arr(itr.arr) {
				loc = new int[arr->dim];

				for (int i = 0; i != arr->dim; i++)
					loc[i] = itr.loc[i]; // �ε��� �迭 �� ����
			}

			// �Ҹ���: �������� �Ҵ��� �ε��� �迭 �޸� ����
			~Iterator() {
				delete[] loc;
			}
			Iterator operator++() {
				if (loc[0] > arr->size[0]) return (*this);		 // ù ��° ������ �ε����� �迭 ũ�⸦ �ʰ��ϸ� �� �̻� �������� ����

				bool carry = false; // �ڸ��ø�(ĳ��) �߻� ����
				int i = arr->dim - 1; // ������ �������� ����

				do {
					loc[i]++; // ���� ������ �ε��� ����

					 // ���� ���� ������ �ε����� �ش� ������ ũ�⸦ ������
					if (loc[i] >= arr->size[i] && i >= 1) {
						loc[i] -= arr->size[i]; // 0���� �ʱ�ȭ(�ڸ��ø�)
						carry = true;           // �ڸ��ø� �߻�
						i--;                    // ���� �������� �̵�
					}
					else
						carry = false;          // �ڸ��ø� ���� �� ���� ����

				} while (i >= 0 && carry);

				return (*this); // ������ ���ͷ����� ��ȯ
			}

			// ���� ������: �ٸ� Iterator ��ü�� ���� ���� ��ü�� ����
			Iterator& operator=(const Iterator& itr) {

				arr = itr.arr;					// ��� �迭 ������ ����
				loc = new int[itr.arr->dim];	// �ε��� �迭 ���� �Ҵ�

				// �� ������ �ε��� �� ����
				for (int i = 0; i != arr->dim; i++)
					loc[i] = itr.loc[i];

				return (*this);	 // �ڱ� �ڽ� ��ȯ
			}	

			// ���� ���� ������: ���� ���ͷ����� ���¸� ������ ��, �� ĭ �̵�
			Iterator operator++(int) {
				Iterator itr(*this);	// ���� ���¸� ����
				++(*this);				// ���� ����(�� ĭ �̵�)
				return itr;				// �̵� �� ���� ��ȯ
			}

			// �� ������: �� ���ͷ����Ͱ� ���� �ٸ� ��ġ�� ����Ű���� ��
			bool operator!= (const Iterator& itr) {
				// �迭 ���� ���� �ٸ��� �ٸ� �迭�̹Ƿ� true ��ȯ
				if (itr.arr->dim != arr->dim) return true;

				// �� ������ �ε����� �ٸ��� true ��ȯ
				for (int i = 0; i != arr->dim; i++)
					if (itr.loc[i] != loc[i]) return true;

				return false; // ��� ������ false(���� ��ġ)
			}

			// ������ ������: ���ͷ����Ͱ� ����Ű�� �迭 ���(Int ���Ͻ� ��ü) ��ȯ
			Int operator*();
		};
		friend Iterator;

		Array(int dim, int* arr_size) : dim(dim)	// ���� �� �� �� ������ ũ�� ���� 
		{
			size = new int[dim];	//������ ũ�⸦ ���� int �迭 ���� �Ҵ�
			for (int i = 0; i < dim; i++)
				size[i] = arr_size[i];	//���޹��� ���� size �迭�� ���� 

			top = new Address; // ���ο� Address ��ü�� ���� (�迭�� ��Ʈ)
			top->level = 0;    // ��Ʈ�� level�� 0���� ����

			InitalizeAddress(top);	// top�� �������� ��ü Address ������ �ʱ�ȭ (�޸� �Ҵ� �� ���� ����)

		}
		// ���� ������ 
		Array(const Array& arr) : dim(arr.dim)	// ���� Array�� dim �� ���� 
		{
			size = new int[dim];
			for (int i = 0; i < dim; i++)
				size[i] = arr.size[i];

			top = new Address;
			top->level = 0;

			InitalizeAddress(top);
			CopyAddress(top, arr.top);
		}

		//Address �ʱ�ȭ �Լ� 
		void InitalizeAddress(Address* cur) {
			if (!cur) return;					//cur �� NULL �϶� ���� ó�� 

			if (cur->level == dim - 1)			// ���� ���� (������ ������ ���� ����)
			{
				cur->next = new int[size[cur->level]];	// ���� �����͸� ������ int �迭 ���� �Ҵ�
				return;
			}

			cur->next = new Address[size[cur->level]];	// ���� ���(cur)�� ���� �ܰ� Address ��ü���� ���� �޸�(�迭) ���� �Ҵ�

			for (int i = 0; i != size[cur->level]; i++)	// ���� �ܰ�(cur->level)�� ���� �ܰ� Address ��ü���� ��ȸ (���� �켱 Ž�� )
			{
				// (static_cast<Address*>(cur->next) + i): i��° Address ��ü�� �ּ�
				(static_cast<Address*>(cur->next) + i)->level = cur->level + 1;	 // i��° Address ��ü�� level�� ���纸�� 1 ũ�� ����
				InitalizeAddress(static_cast<Address*>(cur->next) + i);
			}
		}

		// Address ����ü Ʈ���� ��������� �����ϴ� �Լ�
		void CopyAddress(Address* dst, Address* src) {
			// ���� ���� ������ ������ ����(���� ������ �迭)�̶��
			if (dst->level == dim - 1)
			{
				// �ش� ������ ũ�⸸ŭ �ݺ��ϸ鼭 int �迭�� ���� ����
				for (int i = 0; i < size[dst->level]; ++i)
					static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];
				return; // ���� �Ϸ� �� �Լ� ����
			}

			// ������ ������ �ƴ϶��(���� Address Ʈ���� �߰� �ܰ���)
			for (int i = 0; i != size[dst->level]; i++)
			{
				// dst->next�� src->next�� Address* �迭�� ����, i��° �ڽ� Address�� ����
				Address* new_dst = static_cast<Address*>(dst->next) + i;
				Address* new_src = static_cast<Address*>(src->next) + i;
				// ��������� ���� Address Ʈ���� ����
				CopyAddress(new_dst, new_src);
			}
		}

		// Address ����ü(�Ǵ� Ŭ����)�� ���� �޸� ���� �Լ�
		void DeleteAddress(Address* cur) {
			if (!cur) return;	//cur �� NULL �϶� ���� ó�� 

			// ���� ������ ������ �ƴϸ�, �ڽ� Address ��ü�鿡 ���� ��������� DeleteAddress ȣ�� 
			// (�� �������� �Լ� ȣ���� ����ó�� ����)
			for (int i = 0; cur->level < dim - 1 && i < size[cur->level]; i++)
				DeleteAddress(static_cast<Address*>(cur->next) + i);

			// ���� ����� next(���� �Ҵ�� �迭 �Ǵ� int �迭) �޸� ����
			delete[] cur->next;
		}

		Int operator[](const int idx);
		~Array()
		{
			DeleteAddress(top);
			delete[] size;
		}
		// �迭�� ���� ��ġ(ó�� �ε���)�� ����Ű�� ���ͷ����� ��ȯ
		Iterator Begin() {
			int* arr = new int[dim];    // ���� ����ŭ �ε��� �迭 ���� �Ҵ�
			for (int i = 0; i != dim; i++)
				arr[i] = 0;             // ��� ������ �ε����� 0���� �ʱ�ȭ (�迭�� ù ��° ����)

			Iterator temp(this, arr);   // ���� Array ��ü�� �ε��� �迭�� ���ͷ����� ����
			delete[] arr;               // �ӽ� �ε��� �迭 �޸� ����

			return temp;                // ���� ��ġ ���ͷ����� ��ȯ
		}

		// �迭�� �� ��ġ(������ ���� �ε���)�� ����Ű�� ���ͷ����� ��ȯ
		Iterator End() {
			int* arr = new int[dim];    // ���� ����ŭ �ε��� �迭 ���� �Ҵ�
			arr[0] = size[0];           // ù ��° ������ �ε����� size[0]���� ���� (end ����)
			for (int i = 1; i != dim; i++)
				arr[i] = 0;             // ������ ������ 0���� �ʱ�ȭ

			Iterator temp(this, arr);   // ���� Array ��ü�� �ε��� �迭�� ���ͷ����� ����
			delete[] arr;               // �ӽ� �ε��� �迭 �޸� ����

			return temp;                // �� ��ġ ���ͷ����� ��ȯ
		}
	};
	class Int {
		void* data;

		int level;
		Array* arr;

	public:
		//int _level = 0, void* _data = NULL, Array* _arr = NULL ����Ʈ ����
		Int(int idx, int _level = 0, void* _data = NULL, Array* _arr = NULL) : level(_level), data(_data), arr(_arr)
		{
			// ��ȿ�� �˻�: level�� 1 �̸��̰ų�, idx�� �ش� ������ ũ�� �̻��̸� data�� NULL�� �����ϰ� ����
			if (_level < 1 || idx >= arr->size[_level - 1]) {
				data = NULL;
				return;
			}

			// ���� ���� level�� �迭�� ���� ���� ���ٸ� (������ ����)
			if (level == arr->dim)
				data = static_cast<void*>((static_cast<int*>(static_cast<Array::Address*>(data)->next) + idx));    // data�� int �迭�� idx��° ���Ҹ� ����Ű�� �����ͷ� ����

			  // ���� ������ ������ �ƴϸ�, ���� Address ��ü�� idx��° �ּҸ� ����Ű�� �����ͷ� ����
			else
				data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next) + idx);
		}
		Int(const Int& i) : data(i.data), level(i.level), arr(i.arr) {}

		// Int Ŭ������ int ��ȯ ������: Int ��ü�� int�� ������ ��ȯ
		operator int() {
			// data�� ��ȿ�ϸ� int �� ��ȯ, �ƴϸ� 0 ��ȯ
			if (data) return *static_cast<int*>(data);
			return 0;
		}
				
		// Int Ŭ������ int ���� ������: Int ��ü�� ����Ű�� ��ġ�� int ���� ����
		Int& operator=(const int& a) {
			// data�� ��ȿ�ϸ� �ش� ��ġ�� a ���� ����
			if (data) *static_cast<int*>(data) = a;
			return *this;
		}

		// Int Ŭ������ operator[]: ���� ���� �ε����� �����ϴ� �Լ�
		Int operator[](const int idx) {
			// data�� ��ȿ���� ������ 0(Int ��ü, �Ͻ��� ��ȯ) ��ȯ
			if (!data) return 0;
			// ���� ������ Int ���Ͻ� ��ü ���� �� ��ȯ
			return Int(idx, level + 1, data, arr);
		}
	};
	
}

// Array Ŭ������ operator[]: ù ��° ���� �ε����� ó���Ͽ� Int ���Ͻ� ��ü�� ��ȯ
MyArray::Int MyArray::Array::operator[](const int idx)
{
	// level=1(ù ��° ����), ���� �ּҴ� top, ���� Array ��ü(this)�� �ѱ�
	return Int(idx, 1, static_cast<void*>(top), this);
}

// ���ͷ����Ͱ� ����Ű�� ������ �迭�� ���� ����(Int ���Ͻ� ��ü)�� ��ȯ�ϴ� �Լ�
MyArray::Int MyArray::Array::Iterator::operator*() {
	//ù ��° ���� �ε����� Int ���Ͻ� ��ü�� ���� (��: arr[loc[0]])
	Int start = arr->operator[](loc[0]);

	// �� ��° �������� ������ �������� �ݺ��ؼ� �ε���
	// ��: start = start[loc[1]], start = start[loc[2]], ...
	for (int i = 1; i <= arr->dim - 1; i++)
		start = start.operator[](loc[i]);

	// ��� ������ �ε����� ������, �ش� ��ġ�� Int(���Ͻ�) ��ü�� ��ȯ
	return start;
}

int main() {
	// 3���� �迭�� �� ���� ũ�� ���� (2 x 3 x 4 �迭)
	int size[] = { 2, 3, 4 };
	MyArray::Array arr(3, size); // 3���� �迭 ��ü ����

	// ���ͷ����͸� �̿��� �迭 ��ü�� 0~23���� ���� ���ʴ�� ����
	MyArray::Array::Iterator itr = arr.Begin(); // ���� ���ͷ�����
	for (int i = 0; itr != arr.End(); itr++, i++)
		(*itr) = i; // �迭�� �� ���ҿ� i��(0,1,2,...,23) ����


	// �迭 ��ü�� ���ͷ����ͷ� ��ȸ�ϸ� �� ���
	for (itr = arr.Begin(); itr != arr.End(); itr++)
		std::cout << *itr << std::endl; // 0~23���� �� �پ� ���

	// 3�� for������ �� ���� ���� (i+1)*(j+1)*(k+1) + ���� ������ ����
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
				// ��: arr[0][0][0] = 1*1*1 + 0 = 1
				//     arr[1][2][3] = 2*3*4 + 23 = 24 + 23 = 47
			}
		}
	}

	// ���ŵ� �迭�� 3�� for������ ��� (�ε����� �� �Բ�)
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 4; k++) {
				std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
					<< std::endl;
			}
		}
	}
}
