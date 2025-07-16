#include <string>
#include <iostream>
#include "Stack.h"
#include "Vector.h"

class Table; // 전방 선언


// 셀 클래스: 각 셀의 데이터와 위치, 소속 테이블 정보 보유
class Cell {
protected:

    Table* table;        // 소속 테이블 포인터
    int x, y;            // 셀의 좌표

public:
    virtual std::string stringify() = 0;  // 해당 셀값 문자열 변환 
    virtual int to_numeric() = 0;  // 해당 셀값 문자열 변환
    Cell(Table* table,  int x, int y) : table(table), x(x), y(y) {}


};

// 문자열을 저장하는 셀 클래스
class StringCell : public Cell {
    std::string data; // 셀에 저장할 문자열 데이터

public:
    // 셀의 데이터를 문자열로 반환
    std::string stringify()  { return data; }

    // 문자열 셀은 숫자 변환이 의미 없으므로 0을 반환
    int to_numeric() { return 0; }

    // 생성자: table, 좌표(x, y), 데이터(data)를 받아 초기화
    // 멤버 초기화 리스트를 사용해서 data와 부모 클래스(Cell) 생성자를 호출
    StringCell(Table* table, std::string data, int x, int y)
        : data(data), Cell(table, x, y) {}
};


// 숫자를 저장하는 셀 클래스
class NumCell : public Cell {
    int data; // 셀에 저장할 정수형 데이터

public:
    // 셀의 데이터를 문자열로 반환
    std::string stringify()  { return std::to_string(data); }

    // 숫자 셀의 숫자값을 반환
    int to_numeric() { return data; }

    // 생성자: table, 좌표(x, y), 데이터(data)를 받아 초기화
    // 멤버 초기화 리스트를 사용해서 data와 부모 클래스(Cell) 생성자를 호출
    NumCell(Table* table, int data, int x, int y)
        : data(data), Cell(table, x, y) {}
};

// DateCell은 Cell 클래스를 상속받아 날짜 데이터를 저장하고 문자열로 변환
class DateCell :public Cell {
    time_t data;    //time_t 타입 1970년 부터 현재 시간까지 몇 초가 흘렀는지 보관하는 정수 형 변수

public:
    // 날짜를 문자열(예: 2024-07-16)로 변환하여 반환하는 함수
    std::string stringify()  {
        char buf[50];   // 변환된 날짜 문자열을 저장할 버퍼
        tm temp;        // 날짜와 시간을 년/월/일/시/분/초 단위로 분해하여 저장하는 구조체

        // data 멤버의 값(time_t)을 tm 구조체로 변환 (로컬 타임 기준)
        localtime_s(&temp, &data);

        // 변환된 tm 구조체를 "YYYY-MM-DD" 형태의 문자열로 저장
        strftime(buf, 50, "%F", &temp);

        // 문자열로 반환
        return std::string(buf);
    }

    // 저장된 날짜(time_t)를 정수로 반환하는 함수(예: 비교/계산용)
    int to_numeric() { return static_cast<int>(data); }

    // 생성자: Cell 클래스를 상속받으므로 부모 생성자도 호출
    // str은 항상 "yyyy-mm-dd" 형태의 날짜 문자열임을 가정
    DateCell(Table* table, std::string str, int x, int y) : Cell(table, x, y) {
        // 연/월/일을 각각 정수로 변환
        int year = atoi(str.c_str());        // 연  : 문자열의 0~3번째 문자(yyyy)
        int month = atoi(str.c_str() + 5);   // 월  : 문자열의 5~6번째 문자(mm)
        int day = atoi(str.c_str() + 8);     // 일  : 문자열의 8~9번째 문자(dd)

        tm timeinfo; // 날짜 정보를 저장할 구조체

        // tm 구조체에 날짜 정보 대입 (주의: tm_year는 1900을 뺀 값, tm_mon은 0부터 시작)
        timeinfo.tm_year = year - 1900; // tm_year: (년도 - 1900)
        timeinfo.tm_mon = month - 1;    // tm_mon : 0부터 시작하므로 1을 뺌
        timeinfo.tm_mday = day;         // tm_mday: 일
        timeinfo.tm_hour = 0;           // 시, 분, 초는 0으로 초기화
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;

        // tm 구조체를 time_t(유닉스 타임)로 변환하여 data에 저장
        data = mktime(&timeinfo);
    }
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

class ExprCell : public Cell {
    std::string data;                 // 셀에 입력된 원본 수식 문자열 (예: "A1+B2*3")
    std::string* parsed_expr;

    Excel::Vector exp_vec;            // 파싱된 수식(토큰들, 즉 후위표기법)을 저장하는 벡터 자료구조

    // 연산자 우선순위 판단 함수: 연산자 문자를 받아서 우선순위 숫자를 반환
    int precedence(char c) {
        switch (c)
        {
        case '(':
        case '[':
        case '{':
            return 0;   // 괄호들은 최하위
        case '+':
        case '-':
            return 1;   // 더하기, 빼기
        case '*':
        case '/':
            return 2;   // 곱하기, 나누기
        }
        return 0;       // 기타 문자 대비
    }

    //중위 표기법 -> 후위 표기법 변환
    void parse_expression() {
        Excel::Stack stack;
        data.insert(0, "(");     // 수식의 맨 앞에 '('를 추가합니다 (파싱의 경계 처리)
        data.push_back(')');     // 수식의 맨 뒤에 ')'를 추가합니다

        for (int i = 0; i < data.length(); ) { // i 증가를 분기에서 따로 제어
            //  셀 참조(A1, B2 ...) : 항상 두 글자라고 가정 (ex: "B2")
            if (isalpha(data[i])) {
                exp_vec.push_back(data.substr(i, 2)); // 두 글자 셀 참조 토큰 추출
                i += 2; // 두 글자를 한 번에 처리
            }
            //  숫자(한 자리): 한 글자 숫자를 추출
            else if (isdigit(data[i])) {
                exp_vec.push_back(data.substr(i, 1)); // 숫자 토큰 추출
                i++;
            }
            //  여는 괄호((), [], {}): 스택에 push
            else if (data[i] == '(' || data[i] == '[' || data[i] == '{') {
                stack.push(data.substr(i, 1));
                i++;
            }
            // 닫는 괄호: 여는 괄호 만날 때까지 스택에서 pop해서 exp_vec에 push
            else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
                std::string temp = stack.pop();
                // 여는 괄호가 나올 때까지 스택에서 연산자를 꺼내 exp_vec에 넣는다
                while (temp != "(" && temp != "[" && temp != "{") {
                    exp_vec.push_back(temp);
                    temp = stack.pop();
                }
                i++;
            }
            //연산자(+ - * /): 스택 top의 연산자 우선순위가 크거나 같으면 pop해서 exp_vec에 넣음
            else if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/') {
                // 스택 top의 연산자 우선순위가 현재 연산자보다 크거나 같으면 pop해서 exp_vec로 보냄
                while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i]))
                    exp_vec.push_back(stack.pop());
                stack.push(data.substr(i, 1)); // 현재 연산자 스택에 push
                i++;
            }
            //그 외(공백 등): 넘김
            else {
                i++;
            }
        }
    }
public:
    ExprCell(Table* table, std::string str, int x, int y) :  Cell(table, x, y), data(str) {  parse_expression(); }

    std::string stringify() { return std::to_string(to_numeric()); }

    int to_numeric() {
        double result = 0;
        Excel::NumStack stack;  // 계산 과정에서 사용할 스택

        // exp_vec에는 파싱된 후위 표기 토큰(피연산자, 연산자)이 차례대로 들어있음
        for (int i = 0; i < exp_vec.size(); i++) {
            std::string str = exp_vec[i];   // i번째 토큰 꺼냄

            if (isalpha(str[0]))
                // 셀 참조(A1, B3 등)인 경우 → 테이블 객체에서 해당 셀 값 계산 후 push
                stack.push(table->to_numeric(str));
            else if (isdigit(str[0]))
                // 숫자(예: "13")면 정수로 변환해 push
                stack.push(atoi(str.c_str()));
            else {
                // 연산자인 경우(+, -, *, /)
                double y = stack.pop(); // 주의: 스택에서 먼저 pop하는 것이 오른쪽(두 번째 피연산자)
                double x = stack.pop(); // 스택에서 다음으로 pop하는 것이 왼쪽(첫 번째 피연산자)

                switch (str[0])
                {
                case '+' :
                    stack.push(x + y);
                    break;
                case '-' :
                    stack.push(x - y);
                    break;
                case '*' :
                    stack.push(x * y);
                    break;
                case '/' :
                    stack.push(x / y);
                    break;
                }
            }
        }
        return stack.pop();          // 마지막에 스택에 남는 값이 전체 식의 계산 결과
    }    
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


// Table 객체를 스트림에 출력할 수 있도록 하는 연산자 오버로딩
std::ostream& operator <<(std::ostream& o, Table& t) {
    o << t.print_table();
    return o;
}

int main() {
    // 텍스트 테이블 생성 및 셀 등록
    TextTable table(5, 5);

    table.reg_cell(new NumCell(&table, 2, 1, 1), 1, 1);   // B2 = 2
    table.reg_cell(new NumCell(&table, 4, 1, 2), 1, 2);   // B3 = 4
    table.reg_cell(new NumCell(&table, 3, 2, 1), 2, 1);   // C2 = 3
    table.reg_cell(new NumCell(&table, 5, 2, 2), 2, 2);   // C3 = 5
    table.reg_cell(new ExprCell(&table, "B2+B3*(C2+C3-2)", 3, 3), 3, 2);
    table.reg_cell(new StringCell(&table, "B2+B3*(C2+C3-2)=", 3, 2), 3, 1);
    std::cout << table << std::endl;


    return 0;
}