#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <iomanip> // put_time
#include <string>

#include "sqlite3.h"

using namespace std;

sqlite3* open_db(std::string filename)
{
    sqlite3 *db;
    int rc = sqlite3_open(filename.c_str(), &db);

    if (rc)
    {
        throw std::runtime_error("Unable to open database.");
    }

    return db;
}

void write_to_log(int argc, char* argv[], std::string out_dir)
{
    std::string file_name = out_dir + string("/knife-log.txt");

    std::ofstream ofs;
    ofs.open(file_name, std::fstream::app);

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    ofs << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

    ofs << " argc=" << argc;
    for (int i=0; i<argc; i++)
        ofs << " " << argv[i];
    ofs << std::endl;
    ofs.close();
}

struct ArgList
{
    string out_dir;
    vector<string> inputs;
    vector<string> outputs;
};

ArgList process_args(int argc, char* argv[])
{
    optional<string> out_dir;
    vector<string> inputs;
    vector<string> outputs;

    enum class ArgMode
    {
        none,
        log_file,
        out_dir,
        inputs,
        outputs
    };

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
                    throw std::runtime_error(string("Invalid argument: ") + arg);
            }

            if (!out_dir)
                throw std::runtime_error("Missing --out-dir value");
        }
    }

    return { *out_dir, inputs, outputs };
}

void write_outputs(ArgList const& args)
{
    for (auto output : args.outputs)
    {
        std::string file_name = args.out_dir + string("/") + output;

        if (file_name.substr(file_name.size()-3) == string(".db"))
            open_db(file_name);
        else
        {
            std::ofstream out_file;
            out_file.open(file_name, std::fstream::out);
            out_file << "/* Generated */" << std::endl;
            out_file.close();
        }
    }
}

int main(int argc, char* argv[])
{
    ArgList args = process_args(argc, argv);
    write_to_log(argc, argv, args.out_dir);
    write_outputs(args);

    return 0;
}