#include <string>
#include <iostream>
class Table; // 전방 선언

// 셀 클래스: 각 셀의 데이터와 위치, 소속 테이블 정보 보유
class Cell {
    Table* table;        // 소속 테이블 포인터
    std::string data;    // 셀에 저장되는 문자열 데이터
    int x, y;            // 셀의 좌표
public:
    Cell(Table* table, const std::string& data, int x, int y) : table(table), data(data), x(x), y(y) {}
    std::string get_data() const {
        return data;
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
        data_base[row][col] = c;
    }
    // 셀 조회
    Cell* get_cell(int row, int col) const {
        return data_base[row][col];
    }
    // 순수 가상 함수: 테이블 출력 형식은 자식 클래스에서 구현
    virtual std::string print_table() const = 0;
};

// 텍스트 테이블 클래스: 탭/개행으로 구분
class TextTable : public Table {
public:
    TextTable(int rows, int cols)
        : Table(rows, cols) {}
    std::string print_table() const override {
        std::string result;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Cell* cell = get_cell(i, j);
                if (cell)
                    result += cell->get_data();
                else
                    result += " ";
            }
            result += "\n";
        }
        return result;
    }
};

// CSV 테이블 클래스: 쉼표로 구분
class CSVTable : public Table {
public:
    CSVTable(int rows, int cols)
        :Table(rows, cols) {}
    std::string print_table() const override
    {
        std::string result;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Cell* cell = get_cell(i, j);
                if (cell)
                    result += cell->get_data();
                else
                    result += " ";

                if (j < cols - 1)
                    result += ",";
            }
            result += "\n";
        }
        return result;
    }
};

// HTML 테이블 클래스: <table>, <tr>, <td> 태그로 구분
class HTMLTable : public Table {
public:
    HTMLTable(int rows, int cols)
        : Table(rows, cols) {}
    std::string print_table() const override
    {
        std::string result = "<table>\n";
        for (int i = 0; i < rows; i++)
        {
            result += "   <tr>";
            for (int j = 0; j < cols; j++)
            {
                result += " <td>";
                Cell* cell = get_cell(i, j);
                if (cell)
                    result += cell->get_data();
                else
                    result += " ";
                result += " </td>";

            }
            result += " </tr>\n";
        }
        result += "</table>\n";
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
    TextTable t(2, 2);
    t.reg_cell(new Cell(&t, "A", 0, 0), 0, 0);
    t.reg_cell(new Cell(&t, "B", 0, 1), 0, 1);
    t.reg_cell(new Cell(&t, "C", 1, 0), 1, 0);
    t.reg_cell(new Cell(&t, "D", 1, 1), 1, 1);

    std::cout << t << std::endl;

    // CSV 테이블 생성 및 셀 등록
    CSVTable csv(2, 2);
    csv.reg_cell(new Cell(&csv, "1", 0, 0), 0, 0);
    csv.reg_cell(new Cell(&csv, "2", 0, 1), 0, 1);
    csv.reg_cell(new Cell(&csv, "3", 1, 0), 1, 0);
    csv.reg_cell(new Cell(&csv, "4", 1, 1), 1, 1);

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