#include <string>
#include <iostream>
#include "Stack.h"
#include "Vector.h"

class Table; // ���� ����


// �� Ŭ����: �� ���� �����Ϳ� ��ġ, �Ҽ� ���̺� ���� ����
class Cell {
protected:

    Table* table;        // �Ҽ� ���̺� ������
    int x, y;            // ���� ��ǥ

public:
    virtual std::string stringify() = 0;  // �ش� ���� ���ڿ� ��ȯ 
    virtual int to_numeric() = 0;  // �ش� ���� ���ڿ� ��ȯ
    Cell(Table* table,  int x, int y) : table(table), x(x), y(y) {}


};

// ���ڿ��� �����ϴ� �� Ŭ����
class StringCell : public Cell {
    std::string data; // ���� ������ ���ڿ� ������

public:
    // ���� �����͸� ���ڿ��� ��ȯ
    std::string stringify()  { return data; }

    // ���ڿ� ���� ���� ��ȯ�� �ǹ� �����Ƿ� 0�� ��ȯ
    int to_numeric() { return 0; }

    // ������: table, ��ǥ(x, y), ������(data)�� �޾� �ʱ�ȭ
    // ��� �ʱ�ȭ ����Ʈ�� ����ؼ� data�� �θ� Ŭ����(Cell) �����ڸ� ȣ��
    StringCell(Table* table, std::string data, int x, int y)
        : data(data), Cell(table, x, y) {}
};


// ���ڸ� �����ϴ� �� Ŭ����
class NumCell : public Cell {
    int data; // ���� ������ ������ ������

public:
    // ���� �����͸� ���ڿ��� ��ȯ
    std::string stringify()  { return std::to_string(data); }

    // ���� ���� ���ڰ��� ��ȯ
    int to_numeric() { return data; }

    // ������: table, ��ǥ(x, y), ������(data)�� �޾� �ʱ�ȭ
    // ��� �ʱ�ȭ ����Ʈ�� ����ؼ� data�� �θ� Ŭ����(Cell) �����ڸ� ȣ��
    NumCell(Table* table, int data, int x, int y)
        : data(data), Cell(table, x, y) {}
};

// DateCell�� Cell Ŭ������ ��ӹ޾� ��¥ �����͸� �����ϰ� ���ڿ��� ��ȯ
class DateCell :public Cell {
    time_t data;    //time_t Ÿ�� 1970�� ���� ���� �ð����� �� �ʰ� �귶���� �����ϴ� ���� �� ����

public:
    // ��¥�� ���ڿ�(��: 2024-07-16)�� ��ȯ�Ͽ� ��ȯ�ϴ� �Լ�
    std::string stringify()  {
        char buf[50];   // ��ȯ�� ��¥ ���ڿ��� ������ ����
        tm temp;        // ��¥�� �ð��� ��/��/��/��/��/�� ������ �����Ͽ� �����ϴ� ����ü

        // data ����� ��(time_t)�� tm ����ü�� ��ȯ (���� Ÿ�� ����)
        localtime_s(&temp, &data);

        // ��ȯ�� tm ����ü�� "YYYY-MM-DD" ������ ���ڿ��� ����
        strftime(buf, 50, "%F", &temp);

        // ���ڿ��� ��ȯ
        return std::string(buf);
    }

    // ����� ��¥(time_t)�� ������ ��ȯ�ϴ� �Լ�(��: ��/����)
    int to_numeric() { return static_cast<int>(data); }

    // ������: Cell Ŭ������ ��ӹ����Ƿ� �θ� �����ڵ� ȣ��
    // str�� �׻� "yyyy-mm-dd" ������ ��¥ ���ڿ����� ����
    DateCell(Table* table, std::string str, int x, int y) : Cell(table, x, y) {
        // ��/��/���� ���� ������ ��ȯ
        int year = atoi(str.c_str());        // ��  : ���ڿ��� 0~3��° ����(yyyy)
        int month = atoi(str.c_str() + 5);   // ��  : ���ڿ��� 5~6��° ����(mm)
        int day = atoi(str.c_str() + 8);     // ��  : ���ڿ��� 8~9��° ����(dd)

        tm timeinfo; // ��¥ ������ ������ ����ü

        // tm ����ü�� ��¥ ���� ���� (����: tm_year�� 1900�� �� ��, tm_mon�� 0���� ����)
        timeinfo.tm_year = year - 1900; // tm_year: (�⵵ - 1900)
        timeinfo.tm_mon = month - 1;    // tm_mon : 0���� �����ϹǷ� 1�� ��
        timeinfo.tm_mday = day;         // tm_mday: ��
        timeinfo.tm_hour = 0;           // ��, ��, �ʴ� 0���� �ʱ�ȭ
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;

        // tm ����ü�� time_t(���н� Ÿ��)�� ��ȯ�Ͽ� data�� ����
        data = mktime(&timeinfo);
    }
};

// ���̺� �߻� Ŭ����: �� 2���� �迭�� ���� �Ҵ��Ͽ� ����
class Table {
protected:
    int rows, cols;         // ��, �� ����
    Cell*** data_base;      // 2���� �迭 (���� ������)
public:

    // ������: 2���� �迭 ���� �Ҵ� �� nullptr�� �ʱ�ȭ
    Table(int rows, int cols) : rows(rows), cols(cols) {
        data_base = new Cell * *[rows];
        for (int i = 0; i < rows; i++) {
            data_base[i] = new Cell * [cols];
            for (int j = 0; j < cols; j++)
                data_base[i][j] = nullptr;
        }
    }

    // �Ҹ���: �� ���� �迭 �޸� ����
    virtual ~Table() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                delete data_base[i][j];    // �� ��ü ����
            delete[] data_base[i];         // �� �迭 ����
        }
        delete[] data_base;                // ��ü �迭 ����
    }

    // �� ���
    void reg_cell(Cell* c, int row, int col) {
        if (!(row < rows && col < cols)) return;

        if (data_base[row][col])
            delete data_base[row][col];

        data_base[row][col] = c;
    }

    // ���ڿ� �� �ּ�("A1", "B2" ��)�� ������ ��ȯ�Ͽ�, �ش� ���� ���� ���� ��ȯ
    int to_numeric(const std::string& str) {
        int row = str[0] - 'A';                     // ù ���ڿ��� �� �ε��� ���� ('A' = 0, 'B' = 1, ...)
        int col = atoi(str.c_str() + 1) - 1;        // ������ ���� �κп��� �� �ε��� ���� (1-based �� 0-based ����)

        // ��ȿ�� �����̰� ���� �����ϸ� to_numeric ����
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->to_numeric();

        // ���� ���ų� ���� ���̸� 0 ��ȯ
        return 0;
    }

    // ��, �� �ε����� �޾� �ش� ���� ���� ���� ��ȯ
    int to_numeric(int row, int col) {
        // ��ȿ�� �����̰� ���� �����ϸ� to_numeric ����
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->to_numeric();

        // �߸��� ��� 0 ��ȯ
        return 0;
    }

    // ���ڿ� �ּ�("B3" ��)�κ��� ���ڿ� ������ ��ȯ
    std::string stringify(const std::string& str) {
        int row = str[0] - 'A';                     // ù ���� = ��
        int col = atoi(str.c_str() + 1) - 1;        // ���� �κ� = �� (1���� �����ϹǷ� -1)

        // ��ȿ�� ���� ��� ���ڿ� ��ȯ
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->stringify();

        // ���� ���ų� ���� ����� �� ���ڿ� ��ȯ
        return "";
    }

    // ��, �� �ε����� �޾� �ش� ���� ���ڿ� ������ ��ȯ
    std::string stringify(int row, int col) {
        // ��ȿ�� ������ �� ���� ���� Ȯ��
        if (row < rows && col < cols && data_base[row][col])
            return data_base[row][col]->stringify();

        // �߸��� ��� �� ���ڿ� ��ȯ
        return "";
    }
    // ���� ���� �Լ�: ���̺� ��� ������ �ڽ� Ŭ�������� ����
    virtual std::string print_table() = 0;
};

class ExprCell : public Cell {
    std::string data;                 // ���� �Էµ� ���� ���� ���ڿ� (��: "A1+B2*3")
    std::string* parsed_expr;

    Excel::Vector exp_vec;            // �Ľ̵� ����(��ū��, �� ����ǥ���)�� �����ϴ� ���� �ڷᱸ��

    // ������ �켱���� �Ǵ� �Լ�: ������ ���ڸ� �޾Ƽ� �켱���� ���ڸ� ��ȯ
    int precedence(char c) {
        switch (c)
        {
        case '(':
        case '[':
        case '{':
            return 0;   // ��ȣ���� ������
        case '+':
        case '-':
            return 1;   // ���ϱ�, ����
        case '*':
        case '/':
            return 2;   // ���ϱ�, ������
        }
        return 0;       // ��Ÿ ���� ���
    }

    //���� ǥ��� -> ���� ǥ��� ��ȯ
    void parse_expression() {
        Excel::Stack stack;
        data.insert(0, "(");     // ������ �� �տ� '('�� �߰��մϴ� (�Ľ��� ��� ó��)
        data.push_back(')');     // ������ �� �ڿ� ')'�� �߰��մϴ�

        for (int i = 0; i < data.length(); ) { // i ������ �б⿡�� ���� ����
            //  �� ����(A1, B2 ...) : �׻� �� ���ڶ�� ���� (ex: "B2")
            if (isalpha(data[i])) {
                exp_vec.push_back(data.substr(i, 2)); // �� ���� �� ���� ��ū ����
                i += 2; // �� ���ڸ� �� ���� ó��
            }
            //  ����(�� �ڸ�): �� ���� ���ڸ� ����
            else if (isdigit(data[i])) {
                exp_vec.push_back(data.substr(i, 1)); // ���� ��ū ����
                i++;
            }
            //  ���� ��ȣ((), [], {}): ���ÿ� push
            else if (data[i] == '(' || data[i] == '[' || data[i] == '{') {
                stack.push(data.substr(i, 1));
                i++;
            }
            // �ݴ� ��ȣ: ���� ��ȣ ���� ������ ���ÿ��� pop�ؼ� exp_vec�� push
            else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
                std::string temp = stack.pop();
                // ���� ��ȣ�� ���� ������ ���ÿ��� �����ڸ� ���� exp_vec�� �ִ´�
                while (temp != "(" && temp != "[" && temp != "{") {
                    exp_vec.push_back(temp);
                    temp = stack.pop();
                }
                i++;
            }
            //������(+ - * /): ���� top�� ������ �켱������ ũ�ų� ������ pop�ؼ� exp_vec�� ����
            else if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/') {
                // ���� top�� ������ �켱������ ���� �����ں��� ũ�ų� ������ pop�ؼ� exp_vec�� ����
                while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i]))
                    exp_vec.push_back(stack.pop());
                stack.push(data.substr(i, 1)); // ���� ������ ���ÿ� push
                i++;
            }
            //�� ��(���� ��): �ѱ�
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
        Excel::NumStack stack;  // ��� �������� ����� ����

        // exp_vec���� �Ľ̵� ���� ǥ�� ��ū(�ǿ�����, ������)�� ���ʴ�� �������
        for (int i = 0; i < exp_vec.size(); i++) {
            std::string str = exp_vec[i];   // i��° ��ū ����

            if (isalpha(str[0]))
                // �� ����(A1, B3 ��)�� ��� �� ���̺� ��ü���� �ش� �� �� ��� �� push
                stack.push(table->to_numeric(str));
            else if (isdigit(str[0]))
                // ����(��: "13")�� ������ ��ȯ�� push
                stack.push(atoi(str.c_str()));
            else {
                // �������� ���(+, -, *, /)
                double y = stack.pop(); // ����: ���ÿ��� ���� pop�ϴ� ���� ������(�� ��° �ǿ�����)
                double x = stack.pop(); // ���ÿ��� �������� pop�ϴ� ���� ����(ù ��° �ǿ�����)

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
        return stack.pop();          // �������� ���ÿ� ���� ���� ��ü ���� ��� ���
    }    
};


// �ؽ�Ʈ ���̺� Ŭ����: ��/�������� ����
class TextTable : public Table {
    // �־��� ���� c�� n�� �ݺ��Ͽ� ���� ���ڿ��� ��ȯ
    std::string repeat_char(int n, char c) {
        std::string s = "";                  // ��� ���ڿ� �ʱ�ȭ
        for (int i = 0; i < n; i++)          // n�� �ݺ��Ͽ�
            s.push_back(c);                  // ���� c�� �ϳ��� �ڿ� ����
        return s;                            // �ϼ��� ���ڿ� ��ȯ
    }

    // �� ��ȣ(0���� ����)�� ���ڿ��� ��ȯ�Ͽ� ��ȯ (A, B, ..., Z, AA, AB, ... ����)
    std::string col_num_to_str(int n) {
        std::string s = "";

        if (n < 26)  // A���� Z����
            s.push_back('A' + n);
        else {
            char first = 'A' + n / 26 - 1;  // �� �ڸ� ���� (��: 'A', 'B'...)
            char second = 'A' + n % 26;     // �� �ڸ� ���� (��: 'A', 'B'...)

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
        int* col_max = new int[cols];  // �� ���� �ִ� �ʺ�(���� ����)�� ������ �迭 ���� �Ҵ�

        for (int i = 0; i < cols; i++) {
            unsigned int max_wide = 2;  // �ʱⰪ: �ּ� �ʺ� 2 (����� �� �� ���)

            for (int j = 0; j < rows; j++) {
                // �ش� ���� ��� ���� �ʰ� ���ڿ��� ���� �ִ� �ʺ񺸴� ��� ����
                if (data_base[j][i] && data_base[j][i]->stringify().length() > max_wide)
                    max_wide = data_base[j][i]->stringify().length();
            }

            col_max[i] = max_wide;  // i��° ���� �ִ� �ʺ� ����
        }

        result += "    ";                 // ��� ���� ���� (�� ��ȣ �κ� ����)
        int total_wide = 4;              // ��ü ǥ �ʺ� ���� (���м� ��� �� ���)

        // �� ���� (A, B, C...) ���
        for (int i = 0; i < cols; i++) {
            if (col_max[i]) {                         // ���� �����ϴ� ���
                int max_len = std::max(2, col_max[i]); // �ּ� �� �ʺ�� 2

                result += " | " + col_num_to_str(i);   // �� �̸� ���̰�
                result += repeat_char(max_len - col_num_to_str(i).length(), ' '); // ���� ä���

                total_wide += (max_len + 3);           // �� �ϳ��� �ʺ� ���� (���м� ���� ����)
            }
        }
        result += '\n';

        // �� �� ���
        for (int i = 0; i < rows; i++) {
            result += repeat_char(total_wide, '-');               // ���м� ���
            result += "\n" + std::to_string(i + 1);                // �� ��ȣ ��� (1���� ����)
            result += repeat_char(4 - std::to_string(i + 1).length(), ' '); // ���� �ڸ� ����

            for (int j = 0; j < cols; j++) {
                if (col_max[j]) {
                    int max_len = std::max(2, col_max[j]);

                    std::string s = "";
                    if (data_base[i][j])
                        s = data_base[i][j]->stringify();  // �� ���� ���ڿ� ��������

                    result += " | " + s;  // �� �տ� ������ + ����
                    result += repeat_char(max_len - s.length(), ' '); // �� �ʺ� ����
                }
            }
            result += '\n';
        }

        return result;  // �ϼ��� ǥ ���ڿ� ��ȯ
    }
};


// Table ��ü�� ��Ʈ���� ����� �� �ֵ��� �ϴ� ������ �����ε�
std::ostream& operator <<(std::ostream& o, Table& t) {
    o << t.print_table();
    return o;
}

int main() {
    // �ؽ�Ʈ ���̺� ���� �� �� ���
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