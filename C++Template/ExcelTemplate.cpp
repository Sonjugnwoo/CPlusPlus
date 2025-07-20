#include <string>
#include <iostream>
#include <map>
#include <set>
#include <typeinfo>
#include "Stack.h"
#include "Vector.h"

class Table; // 전방 선언


// 셀 클래스: 각 셀의 데이터와 위치, 소속 테이블 정보 보유
class Cell {
protected:

    Table* table;        // 소속 테이블 포인터
    int x, y;            // 셀의 좌표

public:
	virtual std::string stringify() = 0;                              //셀 내용을 문자열로 반환 (예: 화면 출력, 파일 저장 등)
	virtual int to_numeric(std::set<std::string>&) = 0;               // 순환 참조 방지를 위한 방문 집합(visited)와 함께 셀의 "숫자값" 반환(예: 수식 계산용)
	virtual int to_numeric() { std::set<std::string> v; return to_numeric(v); }   // 파라미터 없는 to_numeric 버전 (내부에서 빈 visited 집합을 만들어 재귀 처리용)
	Cell(Table* table, int x, int y) : table(table), x(x), y(y) {}
	
	virtual ~Cell() = default;
};
   
// --- 값 저장 셀 (템플릿) ---
// 자료형(int, string 등)에 따라 다양한 ValueCell 구현을 한 번에 제공
template <typename T>
class DataCell : public Cell {
    T data; // 실제 데이터 보관(숫자, 문자열 등)

public:
    DataCell(Table* table, int x, int y, const T& value) : Cell(table, x, y), data(value) {}

    // 셀 내용을 문자열로 반환
    std::string stringify() override {
        if constexpr (std::is_same_v<T, int>)
            return std::to_string(data);         // int형이면 string으로 변환
        else if constexpr (std::is_same_v<T, std::string>)
            return data;                         // string형이면 그대로 반환
        else {
            std::cout << "오류" << std::endl;    // 지원하지 않는 타입이면 경고 후 빈 문자열 반환
            return "";
        }
    }

    // "숫자값" 반환 (예: 수식 계산, 합계 등)
    int to_numeric(std::set<std::string>&) override {
        if constexpr (std::is_same_v<T, int>)
            return data;                 // int면 데이터 그대로 반환
        else if constexpr (std::is_same_v<T, std::string>)
            return 0;                    // 문자열은 숫자 변환 불가로 0 반환
        else {
            std::cout << "오류" << std::endl;  // 지원하지 않는 타입은 경고 및 0 반환
            return 0;
        }
    }
};

class DateCell : public Cell {
    time_t data;

public:
    DateCell(Table* table, int x, int y, std::string& str) : Cell(table, x, y) {
        int year = std::stoi(str.substr(0, 4));
        int month = std::stoi(str.substr(5, 2));
        int day = std::stoi(str.substr(8, 2));
        tm timeinfo;

        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = 0;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;

        data = mktime(&timeinfo);
    }
    std::string stringify()  override {
        char buf[20];
        tm temp;
        localtime_s(&temp, &data);
        strftime(buf, sizeof(buf), "%F", &temp); // YYYY-MM-DD
        return buf;
    }

    int to_numeric(std::set<std::string>&)  override {
        return static_cast<int>(data);
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

        // 실질적 내부 재귀 호출용
        int to_numeric(const std::string& str, std::set<std::string>& visited) {
            int row = atoi(str.c_str() + 1) - 1; // ======= 행 인덱스(숫자-1)
            int col = str[0] - 'A';              // ======= 열 인덱스(문자)

            // "A1" → 변환
            std::string cell_addr = str; // 주소 문자열 기록 (예: "A1")

            // 순환 참조 체크
            if (visited.count(cell_addr)) { //만약 방문 경로상 이미 이 셀이 있으면 에러
                std::cerr << "순환 참조 감지: " << cell_addr << std::endl;
                return 0;
            }
            visited.insert(cell_addr);  //이번 셀 주소를 방문 경로에 추가 (재귀 깊이 따라 계속 누적)

            //실제 데이터 범위 내 & 셀이 존재하면
            int result = 0;
            if (row < rows && col < cols && data_base[row][col]) {
                result = data_base[row][col]->to_numeric(visited);
            }
            visited.erase(cell_addr); // 평가 끝나면 빼줌

            return result;
        }

        // 외부에서 호출할 때(순환경로 없는 기본 버전)
        // 내부에서 사용할 set을 새로 만들고 to_numeric(str, set&) 호출
        int to_numeric(const std::string& str) {
            std::set<std::string> visited;
            return to_numeric(str, visited);
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
                if (isalpha(data[i])) {
                    int idx = 0;
                    // 연속된 알파벳(열) 부분 파악 (예: "AB" in "AB12")
                    while (isalpha(data[i + idx]))  idx++;
                    // 연속된 숫자(행) 부분 파악 (예: "12" in "AB12")
                    while (isdigit(data[i + idx])) idx++;
                    // i ~ (i + idx - 1)의 문자열, 즉 한 셀 주소 토큰(예: "AB12")을 추출
                    exp_vec.push_back(data.substr(i, idx));
                    // i를 idx만큼 증가시켜 중복 처리 방지
                    i += idx;
                }
                //idx 길이 만큼 추출 
                else if (isdigit(data[i])) {
                    int idx = 0;
                    // 연속된 숫자(상수) 부분 파악 (예: "123")
                    while (isdigit(data[i + idx])) idx++;
                    // i ~ (i + idx - 1)의 연속된 숫자 토큰 추출
                    exp_vec.push_back(data.substr(i, idx));
                    // 이미 추출한 숫자 길이만큼 i 증가
                    i += idx;
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
        ExprCell(Table* table, std::string str, int x, int y) : Cell(table, x, y), data(str) { parse_expression(); }

        // 셀의 값을 문자열로 출력 (에러: 수식+오류 메시지, 정상: 수치값)
        std::string stringify() {
            std::set<std::string> visited;           // 순환참조 감지 context
            int result = to_numeric(visited);        // 수식 계산
            if (result == 0 && !data.empty())
                return data + " (순환/오류)";        // 오류거나 순환이면 수식 표시
            return std::to_string(result);           // 정상 계산 시 숫자만
        }

        // 실제 수식 계산: visited는 순환 검사용, 반환값은 계산 결과
        int to_numeric(std::set<std::string>& visited) override {

            double result = 0;
            Excel::Stack stack;   // 수식 계산용 임시 스택 (문자열 저장: 셀, 숫자 등)

            // exp_vec에는 파싱된 후위 표기 토큰(피연산자, 연산자)이 차례대로 들어있음
            for (int i = 0; i < exp_vec.size(); i++) {
                std::string str = exp_vec[i];   // i번째 토큰 꺼냄

                if (isalpha(str[0]))
                    // 셀 주소(예: "A1", "B2" 등) → 스택에 그대로 push
                    stack.push(str);
                else if (isdigit(str[0]))
                    // 숫자 상수(예: "13") → 스택에 그대로 push
                    stack.push(str);
                else if (str[0] == ':') {
                    //범위 연산자(":") → 두 셀 주소 pop, 범위 내 모든 셀 주소를 다시 push
                    std::string rigth = stack.pop();
                    std::string left = stack.pop();

                    // 셀 주소 → (row, col) 좌표 변환
                    int row_1 = atoi(left.c_str() + 1) - 1;
                    int col_1 = left[0] - 'A';
                    int row_2 = atoi(rigth.c_str() + 1) - 1;
                    int col_2 = rigth[0] - 'A';

                    // 범위의 모든 셀 주소를 A1~B5 순서로 스택에 push
                    for (int j = std::min(row_1, row_2); j <= std::max(row_1, row_2); j++) {
                        for (int k = std::min(col_1, col_2); k <= std::max(col_1, col_2); k++) {
                            std::string addr;
                            addr += (char)('A' + k);               // 열
                            addr += std::to_string(j + 1);         // 행 (1-based)
                            stack.push(addr);                      // 범위 내 셀들 push
                        }
                    }
                }
                //SUM 함수 토큰 : 스택에 남은 모든 값 pop해 실제 값 계산합 후 result 입력  
                else if (str == "SUM") {
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        result += table->to_numeric(addr, visited);// 셀주소면 실제 값 얻기
                    }
                    stack.push(std::to_string(result)); // 합계 결과를 다시 push
                }
                //AVE 함수 토큰 : 스택에 남은 모든 값 pop해 값 합산 후 평균 구하기 
                else if (str == "AVE") {
                    int count = 0;
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        result += table->to_numeric(addr, visited);
                        count++;
                    }
                    if (count == 0) stack.push("0"); // 0으로 나누는 예외 방지
                    else stack.push(std::to_string(result / count));

                }
                //MIN 함수 토큰 : 젤 낮은 값 푸쉬
                else if (str == "MIN") {
                    double min = table->to_numeric(stack.pop(), visited);
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        double v = table->to_numeric(addr, visited);
                        if (v < min) min = v;
                    }
                    stack.push(std::to_string(min));
                }
                //MAX 함수 토큰 : 젤 높 은 값 푸쉬 
                else if (str == "MAX") {
                    double max = table->to_numeric(stack.pop(), visited);
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        double v = table->to_numeric(addr, visited);
                        if (v > max) max = v;
                    }
                    stack.push(std::to_string(max));
                }
                else {
                    // 사칙연산 연산자(+, -, *, /)

                    // 스택에서 오른쪽 피연산자(y), 왼쪽 피연산자(x)를 pop한 뒤 실제 값 계산
                    double y = table->to_numeric(stack.pop(), visited); // 오른쪽
                    double x = table->to_numeric(stack.pop(), visited); // 왼쪽

                    // 산술 연산 후 결과값을 문자열로 stack에 push
                    switch (str[0])
                    {
                    case '+':
                        stack.push(std::to_string(x + y));
                        break;
                    case '-':
                        stack.push(std::to_string(x - y));
                        break;
                    case '*':
                        stack.push(std::to_string(x * y));
                        break;
                    case '/':
                        stack.push(std::to_string(x / y));
                        break;
                    }
                }
            }
            // 최종 결과값(스택 top)을 double로 변환하여 반환
            return std::stod(stack.pop());
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
    class ExcelProgram {
        Table* current_table;    // 현재 사용중인 테이블

    public:
        ExcelProgram(int max_row, int max_col, int choice = 0) {
            switch (choice)   // 생성자: 테이블 종류(choice)에 따라 객체 생성
            {
            case 1:
                current_table = new TextTable(max_row, max_col);
                break;
            case 2:
                current_table = new HTMLTable(max_row, max_col);
                break;
            case 3:
                current_table = new CSVTable(max_row, max_col);
                break;
            }
        }
        ~ExcelProgram() {
            delete current_table;
        }
        // 사용자 입력 파싱 및 명령 수행 함수
        int parse_user_input(std::string str) {
            int next = 0;                 // 파싱 중 다음 파트를 시작할 위치
            std::string command = "";     // 명령어 저장 변수

             // 명령어 첫 단어 추출 (공백 전까지)
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == ' ') {
                    command = str.substr(0, i);
                    next = i + 1;
                    break;
                }
                else if (i == str.length() - 1) {
                    command = str.substr(0, i + 1);
                    next = i + 1;
                    break;
                }
            }
            std::string to = "";     // 셀 위치 파싱 예: "A1"

            for (int i = next; i < str.length(); i++) {
                if (str[i] == ' ' || i == str.length() - 1) {
                    to = str.substr(next, i - next + 1);
                    next = i + 1;
                    break;
                }
                else if (i == str.length() - 1) {
                    to = str.substr(0, i + 1);
                    next = i + 1;
                    break;
                }
            }
            // 셀 위치 파싱 (예: "A1" → col: 0, row: 0)
            int col = to[0] - 'A';                      // 열: 'A'->0, 'B'->1 ...
            int row = atoi(to.c_str() + 1) - 1;         // 행: "A1"의 1 -> 0번째 라인(0-indexed)

            std::string rest = str.substr(next); // 나머지 문자열(셀에 들어갈 값)

            // 명령 분기 처리: 셀에 값 등록
            if (command == "sets")
                current_table->reg_cell(new DataCell<std::string>(current_table, row, col, rest), row, col); // 문자열 셀
            else if (command == "setn")
                current_table->reg_cell(new DataCell<int>(current_table, row, col, std::stoi(rest)), row, col); // 숫자 셀
            else if (command == "sete")
                current_table->reg_cell(new ExprCell(current_table, rest, row, col), row, col); // 수식 셀
            else if (command == "setd")
                current_table->reg_cell(new DateCell(current_table,  row, col, rest), row, col); // 날짜 셀
            else if (command == "exit")
                return 0; // 종료

            return 1; // 계속
        }

        // 명령 입력 및 결과 출력 루프
        void command_line() {
            std::string str;
            std::getline(std::cin, str); // 첫 줄 입력
            while (parse_user_input(str)) { // 명령 해석 후 반복
                std::cout << *current_table << std::endl << ">>";
                getline(std::cin, str);
            }
        }
    };

    int main() {

        std::cout << "테이블 (타입) (최대행크기) (최대 열 크기) 를 입력" << std::endl;
        std::cout << "*1.Text, 2.HTML, 3.CSV" << std::endl;

        int type, max_row, max_col;
        std::cin >> type >> max_row >> max_col;
        ExcelProgram e(max_row, max_col, type);
        e.command_line();


        return 0;
    }
