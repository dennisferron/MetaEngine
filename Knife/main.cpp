#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

using namespace std;

enum class ArgMode
{
    none,
    out_dir,
    inputs,
    outputs
};

int main(int argc, char* argv[])
{
    std::ofstream ofs;
    ofs.open("C:\\temp\\log.txt", std::fstream::app);

    ofs << "argc=" << argc;
    for (int i=0; i<argc; i++)
        ofs << " " << argv[i];
    ofs << std::endl;
    ofs.close();

    optional<string> out_dir;
    vector<string> inputs;
    vector<string> outputs;
    ArgMode state = ArgMode::none;

    for (int i=1; i<argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--out-dir")
            state = ArgMode::out_dir;
        else if (arg == "--inputs")
            state = ArgMode::inputs;
        else if (arg == "--outputs")
            state = ArgMode::outputs;
        else
        {
            switch (state)
            {
                case ArgMode::out_dir:
                    out_dir = arg;
                    break;
                case ArgMode::inputs:
                    inputs.push_back(arg);
                    break;
                case ArgMode::outputs:
                    outputs.push_back(arg);
                    break;
                default:
                    throw std::runtime_error("Invalid argument");
            }

            if (!out_dir)
                throw std::runtime_error("Missing --out-dir value");

            for (auto output : outputs)
            {
                std::string file_name = *out_dir + string("/") + output;
                std::ofstream out_file;
                out_file.open(file_name, std::fstream::out);
                out_file << "/* Generated */" << std::endl;
                out_file.close();
            }
        }
    }

    return 0;
}