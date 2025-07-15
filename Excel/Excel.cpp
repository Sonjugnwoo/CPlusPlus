#include <string>
#include <iostream>
#include "stack.h"
#include "vector.h"

class Table; // 전방 선언

// 셀 클래스: 각 셀의 데이터와 위치, 소속 테이블 정보 보유
class Cell {
protected:
    Table* table;        // 소속 테이블 포인터
    std::string data;    // 셀에 저장되는 문자열 데이터
    int x, y;            // 셀의 좌표
public:
    virtual std::string stringify() { return data; }  // 해당 셀값 문자열 변환 
    virtual int to_numeric() { return 0; }  // 해당 셀값 문자열 변환
    Cell(Table* table, const std::string& data, int x, int y) : table(table), data(data), x(x), y(y) {}


};

// 테이블 추상 클래스: 셀 2차원 배열을 동적 할당하여 관리
class Table {
protected:
    int rows, cols;         // 행, 열 개수
    Cell*** data_base;      // 2차원 배열 (이중 포인터)
public:

    // 생성자: 2차원 배열 동적 할당 및 nullptr로 초기화
    Table(int rows, int cols) : rows(rows), cols(cols) {
        data_base = new Cell * *[rows];
        for (int i = 0; i < rows; i++) {
            data_base[i] = new Cell * [cols];
            for (int j = 0; j < cols; j++)
                data_base[i][j] = nullptr;
        }
    }

    // 소멸자: 각 셀과 배열 메모리 해제
    virtual ~Table() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                delete data_base[i][j];    // 셀 객체 해제
            delete[] data_base[i];         // 행 배열 해제
        }
        delete[] data_base;                // 전체 배열 해제
    }

    // 셀 등록
    void reg_cell(Cell* c, int row, int col) {
        if (!(row < rows && col < cols)) return;

        if (data_base[row][col])
            delete data_base[row][col];

        data_base[row][col] = c;
    }

    // 문자열 셀 주소("A1", "B2" 등)를 정수로 변환하여, 해당 셀의 숫자 값을 반환
    int to_numeric(const std::string& str) {
        int row = str[0] - 'A';                     // 첫 문자에서 행 인덱스 구함 ('A' = 0, 'B' = 1, ...)
        int col = atoi(str.c_str() + 1) - 1;        // 나머지 숫자 부분에서 열 인덱스 구함 (1-based → 0-based 보정)

        // 유효한 범위이고 셀이 존재하면 to_numeric 실행
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->to_numeric();

        // 셀이 없거나 범위 밖이면 0 반환
        return 0;
    }

    // 행, 열 인덱스를 받아 해당 셀의 숫자 값을 반환
    int to_numeric(int row, int col) {
        // 유효한 범위이고 셀이 존재하면 to_numeric 실행
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->to_numeric();

        // 잘못된 경우 0 반환
        return 0;
    }

    // 문자열 주소("B3" 등)로부터 문자열 내용을 반환
    std::string stringify(const std::string& str) {
        int row = str[0] - 'A';                     // 첫 문자 = 행
        int col = atoi(str.c_str() + 1) - 1;        // 숫자 부분 = 열 (1부터 시작하므로 -1)

        // 유효한 셀일 경우 문자열 반환
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->stringify();

        // 셀이 없거나 범위 벗어나면 빈 문자열 반환
        return "";
    }

    // 행, 열 인덱스를 받아 해당 셀의 문자열 내용을 반환
    std::string stringify(int row, int col) {
        // 유효한 범위와 셀 존재 여부 확인
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->stringify();

        // 잘못된 경우 빈 문자열 반환
        return "";
    }
    // 순수 가상 함수: 테이블 출력 형식은 자식 클래스에서 구현
    virtual std::string print_table() = 0;
};

// 텍스트 테이블 클래스: 탭/개행으로 구분
class TextTable : public Table {
    // 주어진 문자 c를 n번 반복하여 만든 문자열을 반환
    std::string repeat_char(int n, char c) {
        std::string s = "";                  // 결과 문자열 초기화
        for (int i = 0; i < n; i++)          // n번 반복하여
            s.push_back(c);                  // 문자 c를 하나씩 뒤에 붙임
        return s;                            // 완성된 문자열 반환
    }

    // 열 번호(0부터 시작)를 문자열로 변환하여 반환 (A, B, ..., Z, AA, AB, ... 형식)
    std::string col_num_to_str(int n) {
        std::string s = "";

        if (n < 26)  // A부터 Z까지
            s.push_back('A' + n);
        else {
            char first = 'A' + n / 26 - 1;  // 앞 자리 문자 (예: 'A', 'B'...)
            char second = 'A' + n % 26;     // 뒷 자리 문자 (예: 'A', 'B'...)

            s.push_back(first);
            s.push_back(second);
        }

        return s;
    }
public:
    TextTable(int rows, int cols)
        : Table(rows, cols) {}
    std::string print_table()  override {
        std::string result;
        int* col_max = new int[cols];  // 각 열의 최대 너비(문자 길이)를 저장할 배열 동적 할당

        for (int i = 0; i < cols; i++) {
            unsigned int max_wide = 2;  // 초기값: 최소 너비 2 (헤더나 빈 값 고려)

            for (int j = 0; j < rows; j++) {
                // 해당 셀이 비어 있지 않고 문자열이 현재 최대 너비보다 길면 갱신
                if (data_base[j][i] && data_base[j][i]->stringify().length() > max_wide)
                    max_wide = data_base[j][i]->stringify().length();
            }

            col_max[i] = max_wide;  // i번째 열의 최대 너비 저장
        }

        result += "    ";                 // 상단 좌측 여백 (행 번호 부분 차지)
        int total_wide = 4;              // 전체 표 너비 추적 (구분선 출력 시 사용)

        // 열 제목 (A, B, C...) 출력
        for (int i = 0; i < cols; i++) {
            if (col_max[i]) {                         // 열이 존재하는 경우
                int max_len = std::max(2, col_max[i]); // 최소 열 너비는 2

                result += " | " + col_num_to_str(i);   // 열 이름 붙이고
                result += repeat_char(max_len - col_num_to_str(i).length(), ' '); // 공간 채우기

                total_wide += (max_len + 3);           // 열 하나당 너비 누적 (구분선 길이 계산용)
            }
        }
        result += '\n';

        // 각 행 출력
        for (int i = 0; i < rows; i++) {
            result += repeat_char(total_wide, '-');               // 구분선 출력
            result += "\n" + std::to_string(i + 1);                // 행 번호 출력 (1부터 시작)
            result += repeat_char(4 - std::to_string(i + 1).length(), ' '); // 숫자 자리 맞춤

            for (int j = 0; j < cols; j++) {
                if (col_max[j]) {
                    int max_len = std::max(2, col_max[j]);

                    std::string s = "";
                    if (data_base[i][j])
                        s = data_base[i][j]->stringify();  // 셀 내용 문자열 가져오기

                    result += " | " + s;  // 셀 앞에 구분자 + 내용
                    result += repeat_char(max_len - s.length(), ' '); // 열 너비 맞춤
                }
            }
            result += '\n';
        }

        return result;  // 완성된 표 문자열 반환
    }
};

// CSV 테이블 클래스: 쉼표로 구분
class CSVTable : public Table {
public:
    CSVTable(int rows, int cols) : Table(rows, cols) {}

    std::string print_table() override {
        std::string result = "";

        // 행마다 반복
        for (int i = 0; i < rows; i++) {
            // 열마다 반복
            for (int j = 0; j < cols; j++) {
                // 첫 번째 열이 아니면 쉼표(,) 추가 (열 구분자 역할)
                if (j >= 1) result += ",";

                std::string temp;
                // 셀이 존재하면 문자열로 변환
                if (data_base[i][j])
                    temp = data_base[i][j]->stringify();

                // 큰따옴표 내부 이스케이프 처리: " → ""
                for (int k = 0; k < (int)temp.length(); k++) {
                    if (temp[k] == '"') {
                        temp.insert(k, 1, '"'); // 큰따옴표 앞에 추가 삽입
                        k++;                   // 삽입 후 인덱스 조정
                    }
                }

                // 전체 값을 큰따옴표로 감싸기 (CSV 규칙 준수)
                temp = '"' + temp + '"';

                // 결과 문자열에 추가
                result += temp;
            }
            // 행 끝냈으니 줄바꿈 추가
            result += "\n";
        }
        return result;
    }
};

// HTML 테이블 클래스: <table>, <tr>, <td> 태그로 구분
class HTMLTable : public Table {
public:
    // 생성자: Table 객체 초기화
    HTMLTable(int rows, int cols)
        : Table(rows, cols) {}

    // 테이블을 HTML 문자열 형식으로 출력
    std::string print_table() override {
        std::string result = "<table border='1' cellpadding='10'>"; // 테이블 시작

        // 각 행에 대해 반복
        for (int i = 0; i < rows; i++) {
            result += "<tr>";  // 행 시작
            for (int j = 0; j < cols; j++) {
                result += "<td>";  // 셀 시작

                // 셀이 존재할 경우 문자열 출력
                if (data_base[i][j])
                    result += data_base[i][j]->stringify();

                result += "</td>";  // 셀 종료
            }
            result += "</tr>\n";  // 행 종료
        }

        result += "</table>\n";  // 테이블 종료
        return result;
    }
};

// Table 객체를 스트림에 출력할 수 있도록 하는 연산자 오버로딩
std::ostream& operator <<(std::ostream& o, Table& t) {
    o << t.print_table();
    return o;
}

int main() {
    // 텍스트 테이블 생성 및 셀 등록
    TextTable table(5, 5);
    table.reg_cell(new Cell(&table, "Hello~", 0, 0), 0, 0);
    table.reg_cell(new Cell(&table, "C++", 0, 1), 0, 1);
    table.reg_cell(new Cell(&table, "Programming~", 1, 1), 1, 1);
    std::cout << table << std::endl;

    // CSV 테이블 생성 및 셀 등록
    CSVTable csv(5, 5);

    csv.reg_cell(new Cell(&csv, "Hello~", 0, 0), 0, 0);
    csv.reg_cell(new Cell(&csv, "C++", 0, 1), 0, 1);

    csv.reg_cell(new Cell(&csv, "Programming", 1, 1), 1, 1);

    std::cout << csv << std::endl;

    // HTML 테이블 생성 및 셀 등록
    HTMLTable html(2, 2);
    html.reg_cell(new Cell(&html, "X", 0, 0), 0, 0);
    html.reg_cell(new Cell(&html, "Y", 0, 1), 0, 1);
    html.reg_cell(new Cell(&html, "Z", 1, 0), 1, 0);
    html.reg_cell(new Cell(&html, "W", 1, 1), 1, 1);

    std::cout << html << std::endl;

    return 0;
}