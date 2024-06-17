#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct NumberRecord {
    uint32_t line_number;
    uint8_t odd_number;
};

bool isOdd(int number) {
    return number % 2 != 0;
}

vector<NumberRecord> processFile(const string& filename) {
    ifstream input_file(filename);
    vector<NumberRecord> records;
    string line;
    uint32_t line_number = 0;

    while (getline(input_file, line)) {
        ++line_number;
        stringstream line_stream(line);
        int number;

        while (line_stream >> number) {
            if (isOdd(number) && number >= 0 && number <= 255) {
                NumberRecord record = { line_number, static_cast<uint8_t>(number) };
                records.push_back(record);
            }
        }
    }

    return records;
}

void writeBinaryFile(const string& filename, const vector<NumberRecord>& records) {
    ofstream output_file(filename, ios::binary);

    for (const auto& record : records) {
        output_file.write(reinterpret_cast<const char*>(&record), sizeof(record));
    }
}

void readBinaryFile(const string& filename) {
    ifstream input_file(filename, ios::binary);
    NumberRecord record;

    while (input_file.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        cout << "Строка: " << record.line_number << ", Нечетное число: " << static_cast<int>(record.odd_number) << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Практика 5 | Вариант 8\r\n\r\n";
    
    string input_filename = "input.txt";
    string output_filename = "output.bin";

    auto records = processFile(input_filename);
    writeBinaryFile(output_filename, records);
    readBinaryFile(output_filename);

    return 0;
}
