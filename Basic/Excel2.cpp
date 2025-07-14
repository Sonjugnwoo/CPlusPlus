#include <string>
#include <iostream>
class Table; // ���� ����

// �� Ŭ����: �� ���� �����Ϳ� ��ġ, �Ҽ� ���̺� ���� ����
class Cell {
    Table* table;        // �Ҽ� ���̺� ������
    std::string data;    // ���� ����Ǵ� ���ڿ� ������
    int x, y;            // ���� ��ǥ
public:
    Cell(Table* table, const std::string& data, int x, int y) : table(table), data(data), x(x), y(y) {}
    std::string get_data() const {
        return data;
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
        data_base[row][col] = c;
    }
    // �� ��ȸ
    Cell* get_cell(int row, int col) const {
        return data_base[row][col];
    }
    // ���� ���� �Լ�: ���̺� ��� ������ �ڽ� Ŭ�������� ����
    virtual std::string print_table() const = 0;
};

// �ؽ�Ʈ ���̺� Ŭ����: ��/�������� ����
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

// CSV ���̺� Ŭ����: ��ǥ�� ����
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

// HTML ���̺� Ŭ����: <table>, <tr>, <td> �±׷� ����
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

// Table ��ü�� ��Ʈ���� ����� �� �ֵ��� �ϴ� ������ �����ε�
std::ostream& operator <<(std::ostream& o, Table& t) {
    o << t.print_table();
    return o;
}

int main() {
    // �ؽ�Ʈ ���̺� ���� �� �� ���
    TextTable t(2, 2);
    t.reg_cell(new Cell(&t, "A", 0, 0), 0, 0);
    t.reg_cell(new Cell(&t, "B", 0, 1), 0, 1);
    t.reg_cell(new Cell(&t, "C", 1, 0), 1, 0);
    t.reg_cell(new Cell(&t, "D", 1, 1), 1, 1);

    std::cout << t << std::endl;

    // CSV ���̺� ���� �� �� ���
    CSVTable csv(2, 2);
    csv.reg_cell(new Cell(&csv, "1", 0, 0), 0, 0);
    csv.reg_cell(new Cell(&csv, "2", 0, 1), 0, 1);
    csv.reg_cell(new Cell(&csv, "3", 1, 0), 1, 0);
    csv.reg_cell(new Cell(&csv, "4", 1, 1), 1, 1);

    std::cout << csv << std::endl;

    // HTML ���̺� ���� �� �� ���
    HTMLTable html(2, 2);
    html.reg_cell(new Cell(&html, "X", 0, 0), 0, 0);
    html.reg_cell(new Cell(&html, "Y", 0, 1), 0, 1);
    html.reg_cell(new Cell(&html, "Z", 1, 0), 1, 0);
    html.reg_cell(new Cell(&html, "W", 1, 1), 1, 1);

    std::cout << html << std::endl;

    return 0;
}