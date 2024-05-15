#include <fstream>
#include <string>

using namespace std;

class Logger {
public:
   ofstream file;

    Logger(const string& filename) {
        file.open(filename,ios::out |ios::app);
    }

    ~Logger() {
        if (file.is_open()) {
            file.close();
        }
    }

    void log(const string& message) {
        if (file.is_open()) {
            file << message <<endl;
        }
    }
};