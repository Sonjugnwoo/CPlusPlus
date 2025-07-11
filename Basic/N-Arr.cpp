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
		operator int();
		Int& operator=(const int& a);
		Int operator[](const int idx);
	};
}

//Address �ʱ�ȭ �Լ� 
void MyArray::Array::InitalizeAddress(Address* cur)
{
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
void MyArray::Array::CopyAddress(Address* dst, Address* src)
{
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
void MyArray::Array::DeleteAddress(Address* cur)
{
	if (!cur) return;	//cur �� NULL �϶� ���� ó�� 

	// ���� ������ ������ �ƴϸ�, �ڽ� Address ��ü�鿡 ���� ��������� DeleteAddress ȣ�� 
	// (�� �������� �Լ� ȣ���� ����ó�� ����)
	for (int i = 0; cur->level < dim - 1 && i < size[cur->level]; i++)
		DeleteAddress(static_cast<Address*>(cur->next) + i);

	// ���� ����� next(���� �Ҵ�� �迭 �Ǵ� int �迭) �޸� ����
	delete[] cur->next;
}

// Array Ŭ������ operator[]: ù ��° ���� �ε����� ó���Ͽ� Int ���Ͻ� ��ü�� ��ȯ
MyArray::Int MyArray::Array::operator[](const int idx)
{
	// level=1(ù ��° ����), ���� �ּҴ� top, ���� Array ��ü(this)�� �ѱ�
	return Int(idx, 1, static_cast<void*>(top), this);
}

// Int Ŭ������ int ��ȯ ������: Int ��ü�� int�� ������ ��ȯ
MyArray::Int::operator int()
{
	// data�� ��ȿ�ϸ� int �� ��ȯ, �ƴϸ� 0 ��ȯ
	if (data) return *static_cast<int*>(data);
	return 0;
}

// Int Ŭ������ int ���� ������: Int ��ü�� ����Ű�� ��ġ�� int ���� ����
MyArray::Int& MyArray::Int::operator=(const int& a)
{
	// data�� ��ȿ�ϸ� �ش� ��ġ�� a ���� ����
	if (data) *static_cast<int*>(data) = a;
	return *this;
}

// Int Ŭ������ operator[]: ���� ���� �ε����� �����ϴ� �Լ�
MyArray::Int MyArray::Int::operator[](const int idx)
{
	// data�� ��ȿ���� ������ 0(Int ��ü, �Ͻ��� ��ȯ) ��ȯ
	if (!data) return 0;
	// ���� ������ Int ���Ͻ� ��ü ���� �� ��ȯ
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