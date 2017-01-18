#include <string>
#include "readable_file.h"
#include "writable_file.h"

void File::open() {
    if(this->fp.empty()) {
        // Error: No filepath
        std::cerr << "[File] No filepath\n";
        return;
    }
    if(this->fs.is_open()) {
        // Error: File already opened
        std::cerr << "[File] File already opened\n";
        return;
    }

    this->fs.open(this->fp.c_str());
}

void File::close() {
    if(!this->fs.is_open()) {
        // No file opened
        std::cerr << "[File] No open file\n";
        return;
    }

    this->fs.close();
}

std::string ReadableFile::read() {
    if(!this->fs.is_open()) {
        // No file opened
        std::cerr << "[File] No open file\n";
        return NULL;
    }

    std::string buf = "";
    std::string line;
    unsigned int i = 0;
    while(!this->fs.eof()) {
        std::getline(this->fs, line);
        buf += line;
        if(!this->fs.eof()) buf += "\n";
        i++;
        if(i >= 10) {
            // Error: file too big
            std::cerr << "[File] File too big\n";
            buf = "";
            line = "";
            return NULL;
        }
    }
    return buf;

}

void WritableFile::write(std::string val) {
    if(!this->fs.is_open()) {
        if(this->fp.empty()) {
            // No file path
            std::cerr << "[File] No file path\n";
            return;
        }
        if(!this->file_exist()) {
            this->file_create();
        }
        this->open();
    }

    this->fs << val;
}

bool WritableFile::file_exist() {
    if (FILE *f = fopen(this->fp.c_str(), "r")) {
        fclose(f);
        return true;
    } else {
        return false;
    }
}

void WritableFile::file_create() {
    std::ofstream os (this->fp);
    os.close(); 
}
