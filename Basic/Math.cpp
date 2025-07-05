#include <iostream>
#include <cmath> // sqrt, pow 함수 사용

// 2차원 평면의 점을 나타내는 클래스
class Point
{
	int x, y;

public:
	// 생성자: x, y 좌표를 초기화
	Point(int pos_x, int pos_y)
	{
		x = pos_x;
		y = pos_y;
	}

	// x좌표 반환
	int getX() const { return x; }
	// y좌표 반환
	int getY() const { return y; }
};

// 여러 점을 관리하는 클래스
class Geometry {
public:
	Geometry() 
	{
		point_idx = 0;
	}

	// 점을 배열에 추가
	void AddPoint(const Point& point) {
		point_arr[point_idx++] = new Point(point.getX(), point.getY());
	}

	// 모든 점들 간의 거리를 출력하는 함수 입니다.
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
				std::cout << "Point" << i  << " - Point " << j << "거리 " << distance << std::endl;
			}
		}
	}

	// 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
	// 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
	// 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
	// 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
	void PrintNumMeets()
	{
		int count = 0;
		for (int i = 0; i < point_idx; i++)
			for (int j = i + 1; j < point_idx; j++)
				for (int k = j + 1; k < point_idx; k++)
					for (int l = k + 1; l < point_idx; l++)
						count++;
				
		std::cout << "교점의 수: " << count << std::endl;
	}
	~Geometry()
	{
		for (int i = 0; i < point_idx; i++)
			delete point_arr[i];
	}
private:
	// 점 100 개를 보관하는 배열.
	Point* point_arr[100];
	int point_idx;
};
int main() {
	Geometry geo;
	// 임의의 5개 점 추가
	geo.AddPoint(Point(0, 0));
	geo.AddPoint(Point(1, 2));
	geo.AddPoint(Point(2, 1));
	geo.AddPoint(Point(3, 3));
	geo.AddPoint(Point(4, 0));

	geo.PrintNumMeets(); // 교점의 수 출력 (5개의 점이면 5개)

	geo.PrintDistance(); // 점들 간의 거리도 출력

	return 0;
}