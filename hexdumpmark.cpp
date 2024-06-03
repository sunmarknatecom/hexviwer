#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>  // std::strtoul 함수가 정의된 헤더 파일

class FileReader {
public:
    FileReader(const std::string& filePath, std::size_t startByte, std::size_t endByte)
        : filePath(filePath), startByte(startByte), endByte(endByte), fileSize(0) {}

    bool openFile() {
        file.open(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
            return false;
        }
        return true;
    }

    bool readFile() {
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        if (startByte >= fileSize) {
            std::cerr << "시작 바이트가 파일 크기를 초과합니다.\n";
            return false;
        }

        if (endByte >= fileSize) {
            endByte = fileSize - 1;
        }

        buffer.resize(endByte - startByte + 1);
        file.seekg(startByte, std::ios::beg);
        if (!file.read(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
            std::cerr << "파일을 읽는 데 오류가 발생했습니다.\n";
            return false;
        }
        return true;
    }

    void hDash(int n) const {
        std::cout << std::string(n, '-');
    }

    void printDivider() const {
        hDash(8); std::cout << "+";
        hDash(20); std::cout << "+";
        hDash(20); std::cout << "+";
        hDash(16); std::cout << "+";
        hDash(16); std::cout << "+" << std::endl;
    }

    void printFile() const {
        // Divider 1
        std::cout << std::endl << "+";
        printDivider();
        // Header
        std::cout << "|         ";
        for (int i = 1; i <= 10; ++i) {
            std::cout << " " << std::setw(2) << std::setfill('0') << i << " ";
            if (i == 5) std::cout << "|";
        }
        std::cout << "|";
        for (int i = 1; i <= 9; ++i) {
            std::cout << " " << i << " ";
            if (i == 5) std::cout << " |";
        }
        std::cout << " 0  |" << std::endl;
        // Divider 2
        printDivider();
        // Content
        std::size_t startLine = startByte / 10;
        std::size_t endLine = endByte / 10;
        std::size_t startOffset = startByte % 10;
        std::size_t endOffset = endByte % 10;

        for (std::size_t line = startLine; line <= endLine; ++line) {
            std::cout << "|" << std::setw(7) << std::setfill(' ') << std::dec << line << " |";
            for (std::size_t j = 0; j < 10; ++j) {
                if (line == startLine && j < startOffset) {
                    std::cout << "    ";
                }
                else if (line == endLine && j > endOffset) {
                    std::cout << "    ";
                }
                else {
                    std::size_t index = (line - startLine) * 10 + j - (line == startLine ? startOffset : 0);
                    if (index < buffer.size()) {
                        std::cout << " " << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(buffer[index]) << " ";
                    }
                    else {
                        std::cout << "    ";
                    }
                }
                if ((j + 1) % 5 == 0) std::cout << "|";
            }
            for (std::size_t j = 0; j < 10; ++j) {
                if (line == startLine && j < startOffset) {
                    std::cout << "   ";
                }
                else if (line == endLine && j > endOffset) {
                    std::cout << "   ";
                }
                else {
                    std::size_t index = (line - startLine) * 10 + j - (line == startLine ? startOffset : 0);
                    if (index < buffer.size()) {
                        unsigned char c = buffer[index];
                        if (c >= 32 && c <= 127) {
                            std::cout << " " << static_cast<char>(c) << " ";
                        }
                        else {
                            std::cout << " . ";
                        }
                    }
                    else {
                        std::cout << "   ";
                    }
                }
                if ((j + 1) % 5 == 0) std::cout << " |";
            }
            std::cout << " " << std::endl;
        }
        // Divider 3
        std::cout << "+";
        printDivider();
    }

private:
    std::string filePath;
    std::ifstream file;
    std::vector<unsigned char> buffer;
    std::streamsize fileSize;
    std::size_t startByte;
    std::size_t endByte;
};

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 4) {
        std::cerr << "사용법: " << argv[0] << " <파일경로> [<시작 바이트> <끝 바이트>]" << std::endl;
        return 1;
    }

    std::size_t startByte = 0;
    std::size_t endByte = std::numeric_limits<std::size_t>::max();

    if (argc >= 3) {
        char* end;
        startByte = std::strtoul(argv[2], &end, 10);
        if (*end != '\0') {
            std::cerr << "시작 바이트는 유효한 숫자여야 합니다.\n";
            return 1;
        }
    }

    if (argc == 4) {
        char* end;
        endByte = std::strtoul(argv[3], &end, 10);
        if (*end != '\0') {
            std::cerr << "끝 바이트는 유효한 숫자여야 합니다.\n";
            return 1;
        }
        if (endByte < startByte) {
            std::cerr << "끝 바이트는 시작 바이트보다 크거나 같아야 합니다.\n";
            return 1;
        }
    }

    FileReader reader(argv[1], startByte, endByte);

    if (!reader.openFile()) return 1;
    if (!reader.readFile()) return 1;

    reader.printFile();

    return 0;
}
