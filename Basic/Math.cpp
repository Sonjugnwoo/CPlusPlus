#include <iostream>
#include <cmath> // sqrt, pow �Լ� ���

// 2���� ����� ���� ��Ÿ���� Ŭ����
class Point
{
	int x, y;

public:
	// ������: x, y ��ǥ�� �ʱ�ȭ
	Point(int pos_x, int pos_y)
	{
		x = pos_x;
		y = pos_y;
	}

	// x��ǥ ��ȯ
	int getX() const { return x; }
	// y��ǥ ��ȯ
	int getY() const { return y; }
};

// ���� ���� �����ϴ� Ŭ����
class Geometry {
public:
	Geometry() 
	{
		point_idx = 0;
	}

	// ���� �迭�� �߰�
	void AddPoint(const Point& point) {
		point_arr[point_idx++] = new Point(point.getX(), point.getY());
	}

	// ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
	void PrintDistance()
	{
		for (int i = 0; i < point_idx; i++)
		{
			for (int j = i + 1; j < point_idx; j++)
			{
				int x1 = point_arr[i]->getX();
				int x2 = point_arr[j]->getX();
				int y1 = point_arr[i]->getY();
				int y2 = point_arr[j]->getY();

				double distance = std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
				std::cout << "Point" << i  << " - Point " << j << "�Ÿ� " << distance << std::endl;
			}
		}
	}

	// ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
	// ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
	// �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
	// ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
	void PrintNumMeets()
	{
		int count = 0;
		for (int i = 0; i < point_idx; i++)
			for (int j = i + 1; j < point_idx; j++)
				for (int k = j + 1; k < point_idx; k++)
					for (int l = k + 1; l < point_idx; l++)
						count++;
				
		std::cout << "������ ��: " << count << std::endl;
	}
	~Geometry()
	{
		for (int i = 0; i < point_idx; i++)
			delete point_arr[i];
	}
private:
	// �� 100 ���� �����ϴ� �迭.
	Point* point_arr[100];
	int point_idx;
};
int main() {
	Geometry geo;
	// ������ 5�� �� �߰�
	geo.AddPoint(Point(0, 0));
	geo.AddPoint(Point(1, 2));
	geo.AddPoint(Point(2, 1));
	geo.AddPoint(Point(3, 3));
	geo.AddPoint(Point(4, 0));

	geo.PrintNumMeets(); // ������ �� ��� (5���� ���̸� 5��)

	geo.PrintDistance(); // ���� ���� �Ÿ��� ���

	return 0;
}