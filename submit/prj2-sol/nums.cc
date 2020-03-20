#include <cstring>
#include <iostream>
#include <fstream>

#include "arrayseq.hh"
#include "dlinkseq.hh"

using TestType = int;

inline std::string usage(char* pname) {
    return std::string("usage: ") + pname + " [-a] INTS_FILE_PATH";
}

void readFile(const std::string& filename, Seq<TestType>* rsp) {
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cerr << "cannot read " << filename << ": " << std::strerror(ENOENT) << std::endl;
        std::exit(ENOENT);
    }
    while (ifs) {
        TestType temp;
        ifs >> temp;
        rsp->push(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        std::cerr << usage(argv[0]) << std::endl;
        return EINVAL;
    }
    SeqPtr<TestType> sp;
    std::string filename;
    if (argc == 3) {
        if (std::string(argv[1]) == "-a") {
            sp = ArraySeq<TestType>::make();
            filename = argv[2];
        } else if (std::string(argv[1]) == "-x") {
            std::cout << usage(argv[0]) << std::endl;
            return 0;
        } else {
            std::cerr << usage(argv[0]) << std::endl;
            return EINVAL;
        }
    } else {
        sp = DLinkSeq<TestType>::make();
        filename = argv[1];
    }

    readFile(filename, sp.get());

    auto beginp = sp->cbegin();
    auto endp = sp->cend();

    auto& begin = *beginp;
    auto& end = *endp;

    --end;
    while (begin && end) {
        std::cout << *begin << std::endl; 
        std::cout << *end << std::endl;
        ++begin;
        --end;
    }

}
