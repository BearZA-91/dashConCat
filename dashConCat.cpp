// Program to concat video files from a cyclic source such as a dashcam or CCTV.
// Requiers FFMPEG
// This currently has no error handling, use with caution.
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <set>
using namespace std;

//Function Declarations go here
void listClear();
void listFiles();
void conCatVids();
void cheersAndExit();
//string dir = "/testvids";
string vidDir= "";


int main()
{
    //Main will grab the video directory, I will make a function to vet this input later.
    cout<< "Welcome to dashConCat!\n";
    cout<< "\tPlease input video directory by dragging and dropping the folder from your file browser.\n"<< "\tThen, press enter.\n"<<"Alternatively, you may type in the full path to the folder, such as /home/user/videos/date. \n";
    cout<< "\tPlease ensure that there are no other files, expept the ones that you want to concatenate in the folder.\n";
    cin>> vidDir;
    //Funtion to clear the old dashConCatList.txt file
    listClear();
    //Call Function to create dashConCatList.txt (listFiles) for use with FFMPEG
    listFiles();
    //Function to Concatenate the files in 'merged.TS'
    conCatVids();
    //notify and exit
    cheersAndExit();


    //cout<< "\n DONE, Exiting! \n";
    return 0;
}

void listFiles()
{
    //Now accepts user input via drag and drop or typing.
    //string path = std::filesystem::current_path(); - Old Do not use
    string videos = vidDir; //path + dir;
    set<std::filesystem::path> sortedName;
    
        for (const auto & entry : std::filesystem::directory_iterator(videos))
        {
            sortedName.insert(entry.path());
            

        }

        for (auto & filename : sortedName)
        {
            string fileRaw = filename.c_str();
            string singleQ = "\'";
            string fileLine = "file " + singleQ + fileRaw + singleQ;
            cout<< fileLine << "\n";
            //This needs to be updated to take the iterator into an array variable, and then only make the txt file, or alternatively use regex when writing to the txt file to filter out the txt file and the output file if it already exists.
            ofstream ListOfInput;
            ListOfInput.open((""+vidDir+"/dashConCatList.txt").c_str(), std::ios_base::app);
            ListOfInput << fileLine << "\n";

        }
}

void listClear()
{
    ofstream ListOfInput((""+vidDir+"/dashConCatList.txt").c_str());
}

void conCatVids()
{
    cout<< endl << endl;
    cout<< "Running FFMPEG & Concatenating Your Videos!"<< endl;
    ifstream ListToRead("dashConCatList.txt");
    system(("ffmpeg -f concat -safe 0 -i "+vidDir+"/dashConCatList.txt -c:a copy -c:v copy "+vidDir+"/merged.mp4").c_str());
    ListToRead.close();
    cout<< "\n\n****Done, Please check your folder for \'merged.mp4\'****"<< endl;
}

void cheersAndExit()
{
    system("notify-send \"dashConCat\" \"The job is finished, please check the terminal for more information.\"");
}