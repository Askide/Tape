// Tape.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Tape.h"
#include <direct.h>
#include <algorithm>
#include <random>
#include <climits>

void sortData(std::vector<int>& tapeData);

int main()
{
    int N = 1000000;    
    
    //std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution(0, INT_MAX);
    //
    //char current_work_dir[FILENAME_MAX];
    //char* dir = _getcwd(current_work_dir, sizeof(current_work_dir));
    //
    //int blockWidth = std::to_string(INT_MAX).length();

    //std::ofstream in_file;          // поток для записи

    //in_file.open(std::string(dir) + "\\Data\\input.txt"); // окрываем файл для записи
    //if (in_file.is_open())
    //{
    //    for (auto i = 0; i < 10; i++)
    //    {
    //        int tempNum = distribution(generator);
    //        int tempNumLength = std::to_string(tempNum).length();
    //        int spacersNum = blockWidth - tempNumLength + 1;
    //        in_file << tempNum;
    //        for (int j = 0; j < spacersNum; j++)
    //        {
    //            in_file << " ";
    //        }
    //    }
    //}
    //in_file.close();

    char current_work_dir[FILENAME_MAX];
    char* dir = _getcwd(current_work_dir, sizeof(current_work_dir));
    
    std::string sourceFilepath = "\\Data\\input.txt";
    std::string resultFilepath = "\\Data\\output.txt";
    std::string timeoutSettings = "\\Data\\timeout.ini";

    std::fstream* in_file = new std::fstream();
    in_file->open(std::string(dir) + sourceFilepath);
    
    std::vector<int> tapeData;
    
    if (in_file->is_open())
    {
        Tape* sourceTape;

        try
        {
            sourceTape = new Tape(in_file, N);
        }
        catch (std::bad_alloc ba)
        {
            std::cout << "Память не выделена" << std::endl;
            std::cout << ba.what() << std::endl;
            return -1;
        }

        timeoutSettings = std::string(dir) + timeoutSettings;
        std::wstring temp = std::wstring(timeoutSettings.begin(), timeoutSettings.end());
        sourceTape->setTimeouts(GetPrivateProfileIntW(L"timeouts", L"move", 0, temp.c_str()),
            GetPrivateProfileIntW(L"timeouts", L"rewind", 0, temp.c_str()), 
            GetPrivateProfileIntW(L"timeouts", L"read", 0, temp.c_str()), 
            GetPrivateProfileIntW(L"timeouts", L"write", 0, temp.c_str()));

        sourceTape->readFile(tapeData);
        sourceTape->Delete();
    }
    
    in_file->close();

    sortData(tapeData);

    std::fstream* out_file = new std::fstream();
    out_file->open(std::string(dir) + resultFilepath);
       
    if (out_file->is_open())
    {
        Tape* resultTape;

        try
        {
            resultTape = new Tape(out_file, N);
        }
        catch (std::bad_alloc ba)
        {
            std::cout << "Память не выделена" << std::endl;
            std::cout << ba.what() << std::endl;
            return -1;
        }

        resultTape->writeFile(&tapeData);
        resultTape->Delete();
    }

    out_file->close();
    return 0;
}

void sortData(std::vector<int>& tapeData) {
    std::sort(tapeData.begin(), tapeData.end());
}
