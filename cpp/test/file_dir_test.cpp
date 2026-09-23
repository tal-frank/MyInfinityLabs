#include <string>
#include <iostream>

#include "ood_file_dir.hpp"

using namespace ilrd_178;

int main()
{
    std::string Dir1 = "dir 1";
    std::string Dir2 = "dir 2";
    std::string Dir3 = "dir 3";
    std::string Dir4 = "dir 4";
    std::string Dir5 = "dir 5";
    std::string Dir6 = "dir 6";
    std::string Dir7 = "dir 7";
    std::string Dir8 = "dir 8";
    std::string Dir9 = "dir 9";
    std::string Dir10 = "dir 10";
    std::string Dir11 = "dir 11";

    std::string File1 = "file 1";
    std::string File2 = "file 2";
    std::string File3 = "file 3";
    std::string File4 = "file 4";
    std::string File5 = "file 5";
    std::string File6 = "file 6";
    std::string File7 = "file 7";
    std::string File8 = "file 8";
    std::string File9 = "file 9";
    
    Dir* dir1 = new Dir(Dir1);
    Dir* dir2 = new Dir(Dir2);
    dir1->Add(dir2);
    Dir* dir3 = new Dir(Dir3);
    dir1->Add(dir3);
    Dir* dir4 = new Dir(Dir4);
    dir1->Add(dir4);
    Dir* dir5 = new Dir(Dir5);
    dir3->Add(dir5);
    Dir* dir6 = new Dir(Dir6);
    dir3->Add(dir6);
    Dir* dir7 = new Dir(Dir7);
    dir6->Add(dir7);
    Dir* dir8 = new Dir(Dir8);
    dir3->Add(dir8);
    Dir* dir9 = new Dir(Dir9);
    dir5->Add(dir9);
    Dir* dir10 = new Dir(Dir10);
    dir2->Add(dir10);
    Dir* dir11 = new Dir(Dir11);
    dir1->Add(dir11);

    File* file1 = new File(File1);
    dir1->Add(file1);
    File* file2 = new File(File2);
    dir1->Add(file2);
    File* file3 = new File(File3);
    dir3->Add(file3);
    File* file4 = new File(File4);
    dir3->Add(file4);
    File* file5 = new File(File5);
    dir3->Add(file5);
    File* file6 = new File(File6);
    dir6->Add(file6);
    File* file7 = new File(File7);
    dir6->Add(file7);
    File* file8 = new File(File8);
    dir8->Add(file8);
    File* file9 = new File(File9);
    dir8->Add(file9);

    dir1->Print();
    std::cout << std::endl;

    dir3->Print();
    std::cout << std::endl;

    dir1->Delete(dir4);
    delete dir4;
    dir1->Print();
    std::cout << std::endl;

    dir3->Delete(dir6);
    dir1->Print();
    std::cout << std::endl;

    FileComponent* dir12 = dir3->clone();
    dir12->Print();
    std::cout << std::endl;

    (*(Dir*)dir12).Delete(dir4);
    dir3->Delete(dir5);
    delete dir5;
    dir3->Add(dir6);

    dir12->Print();
    std::cout << std::endl;
    dir3->Print();
    std::cout << std::endl;

    delete dir1;
    delete dir12;

    return 0;
}