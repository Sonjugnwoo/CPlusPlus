#include <string>
#include <iostream>
#include <map>
#include <set>
#include <typeinfo>
#include "Stack.h"
#include "Vector.h"

class Table; // ���� ����


// �� Ŭ����: �� ���� �����Ϳ� ��ġ, �Ҽ� ���̺� ���� ����
class Cell {
protected:

    Table* table;        // �Ҽ� ���̺� ������
    int x, y;            // ���� ��ǥ

public:
	virtual std::string stringify() = 0;                              //�� ������ ���ڿ��� ��ȯ (��: ȭ�� ���, ���� ���� ��)
	virtual int to_numeric(std::set<std::string>&) = 0;               // ��ȯ ���� ������ ���� �湮 ����(visited)�� �Բ� ���� "���ڰ�" ��ȯ(��: ���� ����)
	virtual int to_numeric() { std::set<std::string> v; return to_numeric(v); }   // �Ķ���� ���� to_numeric ���� (���ο��� �� visited ������ ����� ��� ó����)
	Cell(Table* table, int x, int y) : table(table), x(x), y(y) {}
	
	virtual ~Cell() = default;
};
   
// --- �� ���� �� (���ø�) ---
// �ڷ���(int, string ��)�� ���� �پ��� ValueCell ������ �� ���� ����
template <typename T>
class DataCell : public Cell {
    T data; // ���� ������ ����(����, ���ڿ� ��)

public:
    DataCell(Table* table, int x, int y, const T& value) : Cell(table, x, y), data(value) {}

    // �� ������ ���ڿ��� ��ȯ
    std::string stringify() override {
        if constexpr (std::is_same_v<T, int>)
            return std::to_string(data);         // int���̸� string���� ��ȯ
        else if constexpr (std::is_same_v<T, std::string>)
            return data;                         // string���̸� �״�� ��ȯ
        else {
            std::cout << "����" << std::endl;    // �������� �ʴ� Ÿ���̸� ��� �� �� ���ڿ� ��ȯ
            return "";
        }
    }

    // "���ڰ�" ��ȯ (��: ���� ���, �հ� ��)
    int to_numeric(std::set<std::string>&) override {
        if constexpr (std::is_same_v<T, int>)
            return data;                 // int�� ������ �״�� ��ȯ
        else if constexpr (std::is_same_v<T, std::string>)
            return 0;                    // ���ڿ��� ���� ��ȯ �Ұ��� 0 ��ȯ
        else {
            std::cout << "����" << std::endl;  // �������� �ʴ� Ÿ���� ��� �� 0 ��ȯ
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

        // ������ ���� ��� ȣ���
        int to_numeric(const std::string& str, std::set<std::string>& visited) {
            int row = atoi(str.c_str() + 1) - 1; // ======= �� �ε���(����-1)
            int col = str[0] - 'A';              // ======= �� �ε���(����)

            // "A1" �� ��ȯ
            std::string cell_addr = str; // �ּ� ���ڿ� ��� (��: "A1")

            // ��ȯ ���� üũ
            if (visited.count(cell_addr)) { //���� �湮 ��λ� �̹� �� ���� ������ ����
                std::cerr << "��ȯ ���� ����: " << cell_addr << std::endl;
                return 0;
            }
            visited.insert(cell_addr);  //�̹� �� �ּҸ� �湮 ��ο� �߰� (��� ���� ���� ��� ����)

            //���� ������ ���� �� & ���� �����ϸ�
            int result = 0;
            if (row < rows && col < cols && data_base[row][col]) {
                result = data_base[row][col]->to_numeric(visited);
            }
            visited.erase(cell_addr); // �� ������ ����

            return result;
        }

        // �ܺο��� ȣ���� ��(��ȯ��� ���� �⺻ ����)
        // ���ο��� ����� set�� ���� ����� to_numeric(str, set&) ȣ��
        int to_numeric(const std::string& str) {
            std::set<std::string> visited;
            return to_numeric(str, visited);
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
                if (isalpha(data[i])) {
                    int idx = 0;
                    // ���ӵ� ���ĺ�(��) �κ� �ľ� (��: "AB" in "AB12")
                    while (isalpha(data[i + idx]))  idx++;
                    // ���ӵ� ����(��) �κ� �ľ� (��: "12" in "AB12")
                    while (isdigit(data[i + idx])) idx++;
                    // i ~ (i + idx - 1)�� ���ڿ�, �� �� �� �ּ� ��ū(��: "AB12")�� ����
                    exp_vec.push_back(data.substr(i, idx));
                    // i�� idx��ŭ �������� �ߺ� ó�� ����
                    i += idx;
                }
                //idx ���� ��ŭ ���� 
                else if (isdigit(data[i])) {
                    int idx = 0;
                    // ���ӵ� ����(���) �κ� �ľ� (��: "123")
                    while (isdigit(data[i + idx])) idx++;
                    // i ~ (i + idx - 1)�� ���ӵ� ���� ��ū ����
                    exp_vec.push_back(data.substr(i, idx));
                    // �̹� ������ ���� ���̸�ŭ i ����
                    i += idx;
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
        ExprCell(Table* table, std::string str, int x, int y) : Cell(table, x, y), data(str) { parse_expression(); }

        // ���� ���� ���ڿ��� ��� (����: ����+���� �޽���, ����: ��ġ��)
        std::string stringify() {
            std::set<std::string> visited;           // ��ȯ���� ���� context
            int result = to_numeric(visited);        // ���� ���
            if (result == 0 && !data.empty())
                return data + " (��ȯ/����)";        // �����ų� ��ȯ�̸� ���� ǥ��
            return std::to_string(result);           // ���� ��� �� ���ڸ�
        }

        // ���� ���� ���: visited�� ��ȯ �˻��, ��ȯ���� ��� ���
        int to_numeric(std::set<std::string>& visited) override {

            double result = 0;
            Excel::Stack stack;   // ���� ���� �ӽ� ���� (���ڿ� ����: ��, ���� ��)

            // exp_vec���� �Ľ̵� ���� ǥ�� ��ū(�ǿ�����, ������)�� ���ʴ�� �������
            for (int i = 0; i < exp_vec.size(); i++) {
                std::string str = exp_vec[i];   // i��° ��ū ����

                if (isalpha(str[0]))
                    // �� �ּ�(��: "A1", "B2" ��) �� ���ÿ� �״�� push
                    stack.push(str);
                else if (isdigit(str[0]))
                    // ���� ���(��: "13") �� ���ÿ� �״�� push
                    stack.push(str);
                else if (str[0] == ':') {
                    //���� ������(":") �� �� �� �ּ� pop, ���� �� ��� �� �ּҸ� �ٽ� push
                    std::string rigth = stack.pop();
                    std::string left = stack.pop();

                    // �� �ּ� �� (row, col) ��ǥ ��ȯ
                    int row_1 = atoi(left.c_str() + 1) - 1;
                    int col_1 = left[0] - 'A';
                    int row_2 = atoi(rigth.c_str() + 1) - 1;
                    int col_2 = rigth[0] - 'A';

                    // ������ ��� �� �ּҸ� A1~B5 ������ ���ÿ� push
                    for (int j = std::min(row_1, row_2); j <= std::max(row_1, row_2); j++) {
                        for (int k = std::min(col_1, col_2); k <= std::max(col_1, col_2); k++) {
                            std::string addr;
                            addr += (char)('A' + k);               // ��
                            addr += std::to_string(j + 1);         // �� (1-based)
                            stack.push(addr);                      // ���� �� ���� push
                        }
                    }
                }
                //SUM �Լ� ��ū : ���ÿ� ���� ��� �� pop�� ���� �� ����� �� result �Է�  
                else if (str == "SUM") {
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        result += table->to_numeric(addr, visited);// ���ּҸ� ���� �� ���
                    }
                    stack.push(std::to_string(result)); // �հ� ����� �ٽ� push
                }
                //AVE �Լ� ��ū : ���ÿ� ���� ��� �� pop�� �� �ջ� �� ��� ���ϱ� 
                else if (str == "AVE") {
                    int count = 0;
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        result += table->to_numeric(addr, visited);
                        count++;
                    }
                    if (count == 0) stack.push("0"); // 0���� ������ ���� ����
                    else stack.push(std::to_string(result / count));

                }
                //MIN �Լ� ��ū : �� ���� �� Ǫ��
                else if (str == "MIN") {
                    double min = table->to_numeric(stack.pop(), visited);
                    while (!stack.is_empty()) {
                        std::string addr = stack.pop();
                        double v = table->to_numeric(addr, visited);
                        if (v < min) min = v;
                    }
                    stack.push(std::to_string(min));
                }
                //MAX �Լ� ��ū : �� �� �� �� Ǫ�� 
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
                    // ��Ģ���� ������(+, -, *, /)

                    // ���ÿ��� ������ �ǿ�����(y), ���� �ǿ�����(x)�� pop�� �� ���� �� ���
                    double y = table->to_numeric(stack.pop(), visited); // ������
                    double x = table->to_numeric(stack.pop(), visited); // ����

                    // ��� ���� �� ������� ���ڿ��� stack�� push
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
            // ���� �����(���� top)�� double�� ��ȯ�Ͽ� ��ȯ
            return std::stod(stack.pop());
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

    // CSV ���̺� Ŭ����: ��ǥ�� ����
    class CSVTable : public Table {
    public:
        CSVTable(int rows, int cols) : Table(rows, cols) {}

        std::string print_table() override {
            std::string result = "";

            // �ึ�� �ݺ�
            for (int i = 0; i < rows; i++) {
                // ������ �ݺ�
                for (int j = 0; j < cols; j++) {
                    // ù ��° ���� �ƴϸ� ��ǥ(,) �߰� (�� ������ ����)
                    if (j >= 1) result += ",";

                    std::string temp;
                    // ���� �����ϸ� ���ڿ��� ��ȯ
                    if (data_base[i][j])
                        temp = data_base[i][j]->stringify();

                    // ū����ǥ ���� �̽������� ó��: " �� ""
                    for (int k = 0; k < (int)temp.length(); k++) {
                        if (temp[k] == '"') {
                            temp.insert(k, 1, '"'); // ū����ǥ �տ� �߰� ����
                            k++;                   // ���� �� �ε��� ����
                        }
                    }

                    // ��ü ���� ū����ǥ�� ���α� (CSV ��Ģ �ؼ�)
                    temp = '"' + temp + '"';

                    // ��� ���ڿ��� �߰�
                    result += temp;
                }
                // �� �������� �ٹٲ� �߰�
                result += "\n";
            }
            return result;
        }
    };

    // HTML ���̺� Ŭ����: <table>, <tr>, <td> �±׷� ����
    class HTMLTable : public Table {
    public:
        // ������: Table ��ü �ʱ�ȭ
        HTMLTable(int rows, int cols)
            : Table(rows, cols) {}

        // ���̺��� HTML ���ڿ� �������� ���
        std::string print_table() override {
            std::string result = "<table border='1' cellpadding='10'>"; // ���̺� ����

            // �� �࿡ ���� �ݺ�
            for (int i = 0; i < rows; i++) {
                result += "<tr>";  // �� ����
                for (int j = 0; j < cols; j++) {
                    result += "<td>";  // �� ����

                    // ���� ������ ��� ���ڿ� ���
                    if (data_base[i][j])
                        result += data_base[i][j]->stringify();

                    result += "</td>";  // �� ����
                }
                result += "</tr>\n";  // �� ����
            }

            result += "</table>\n";  // ���̺� ����
            return result;
        }
    };

    // Table ��ü�� ��Ʈ���� ����� �� �ֵ��� �ϴ� ������ �����ε�
    std::ostream& operator <<(std::ostream& o, Table& t) {
        o << t.print_table();
        return o;
    }
    class ExcelProgram {
        Table* current_table;    // ���� ������� ���̺�

    public:
        ExcelProgram(int max_row, int max_col, int choice = 0) {
            switch (choice)   // ������: ���̺� ����(choice)�� ���� ��ü ����
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
        // ����� �Է� �Ľ� �� ��� ���� �Լ�
        int parse_user_input(std::string str) {
            int next = 0;                 // �Ľ� �� ���� ��Ʈ�� ������ ��ġ
            std::string command = "";     // ��ɾ� ���� ����

             // ��ɾ� ù �ܾ� ���� (���� ������)
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
            std::string to = "";     // �� ��ġ �Ľ� ��: "A1"

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
            // �� ��ġ �Ľ� (��: "A1" �� col: 0, row: 0)
            int col = to[0] - 'A';                      // ��: 'A'->0, 'B'->1 ...
            int row = atoi(to.c_str() + 1) - 1;         // ��: "A1"�� 1 -> 0��° ����(0-indexed)

            std::string rest = str.substr(next); // ������ ���ڿ�(���� �� ��)

            // ��� �б� ó��: ���� �� ���
            if (command == "sets")
                current_table->reg_cell(new DataCell<std::string>(current_table, row, col, rest), row, col); // ���ڿ� ��
            else if (command == "setn")
                current_table->reg_cell(new DataCell<int>(current_table, row, col, std::stoi(rest)), row, col); // ���� ��
            else if (command == "sete")
                current_table->reg_cell(new ExprCell(current_table, rest, row, col), row, col); // ���� ��
            else if (command == "setd")
                current_table->reg_cell(new DateCell(current_table,  row, col, rest), row, col); // ��¥ ��
            else if (command == "exit")
                return 0; // ����

            return 1; // ���
        }

        // ��� �Է� �� ��� ��� ����
        void command_line() {
            std::string str;
            std::getline(std::cin, str); // ù �� �Է�
            while (parse_user_input(str)) { // ��� �ؼ� �� �ݺ�
                std::cout << *current_table << std::endl << ">>";
                getline(std::cin, str);
            }
        }
    };

    int main() {

        std::cout << "���̺� (Ÿ��) (�ִ���ũ��) (�ִ� �� ũ��) �� �Է�" << std::endl;
        std::cout << "*1.Text, 2.HTML, 3.CSV" << std::endl;

        int type, max_row, max_col;
        std::cin >> type >> max_row >> max_col;
        ExcelProgram e(max_row, max_col, type);
        e.command_line();


        return 0;
    }
