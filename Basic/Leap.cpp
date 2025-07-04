#include <iostream>

// 달력 배열: 0번째 행은 평년, 1번째 행은 윤년
// 0번째 열은 더미(사용하지 않음), 1~12월의 일 수 저장
int calendar[][13] = {
   {0,31,28,31,30,31,30,31,31,30,31,30,31},
   {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

class Date {
    int year_;   // 연도
    int month_;  // 월(1~12)
    int day_;    // 일(1~31)
    int leap;    // 윤년 여부(0: 평년, 1: 윤년)
public:

    // 날짜 설정 및 윤년 여부 초기화
    void SetDate(int year, int month, int day)
    {
        year_ = year;
        month_ = month;
        day_ = day;
        leap = Isleap(year);
    }

    // 윤년 판별 함수 (윤년이면 1, 아니면 0 반환)
    int Isleap(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // 일(day) 더하기
    void AddDay(int inc)
    {
        day_ += inc;
        // day_가 현재 월의 마지막 날을 넘으면 다음 달로 넘김
        while (day_ > calendar[leap][month_])
        {
            month_++; // 월 증가
            day_ -= calendar[leap][month_ - 1]; // 지난 달의 일 수만큼 day_에서 빼줌

            // 12월을 넘으면 다음 해로 넘김
            if (month_ > 12)
            {
                month_ = 1;
                year_++;
                leap = Isleap(year_); // 윤년 여부 갱신
            }
        }
    }

    // 월(month) 더하기
    void AddMonth(int inc)
    {
        month_ += inc;
        // month_가 12를 넘으면 연도 증가
        while (month_ > 12)
        {
            month_ -= 12;
            year_++;
            leap = Isleap(year_); // 윤년 여부 갱신
        }
        // 월이 바뀐 후, 해당 월의 마지막 날보다 day_가 크면 마지막 날로 보정
        if (day_ > calendar[leap][month_])
            day_ = calendar[leap][month_];
    }

    // 연(year) 더하기
    void AddYear(int inc)
    {
        year_ += inc;
        leap = Isleap(year_); // 윤년 여부 갱신

        // 연도가 바뀐 후, 해당 월의 마지막 날보다 day_가 크면 마지막 날로 보정
        if (day_ > calendar[leap][month_])
            day_ = calendar[leap][month_];
    }

    // 날짜 출력
    void ShowDate()
    {
        std::cout << year_ << "년도" << std::endl;
        std::cout << month_ << "월" << std::endl;
        std::cout << day_ << "일" << std::endl;
    }
};


int main()
{
    Date date;
    date.SetDate(2005, 12, 25); // 2005년 12월 25일로 날짜 설정
    date.AddDay(51);            // 51일 더하기
    date.ShowDate();            // 결과 출력
}

