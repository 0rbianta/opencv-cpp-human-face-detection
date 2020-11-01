//OpenCV libs (cmake required)
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

//C++ libs
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace cv;
using namespace std;

//Variables
CascadeClassifier face_cascade;
vector<string> vec_example_file_paths;

//Functions
void mode_selection();

void mode_auto();
void mode_auto_selection();
void mode_manual();
bool check_files_exist(string path_to_check);
bool check_human_face(string file_path);
void exit_app();
void about_dev();




int main() {

    //Load example files vector
    vec_example_file_paths.push_back("example_imgs/black.jpeg");
    vec_example_file_paths.push_back("example_imgs/dragon.jpg");
    vec_example_file_paths.push_back("example_imgs/human.webp");
    vec_example_file_paths.push_back("example_imgs/sources.txt");
    vec_example_file_paths.push_back("face.xml");

    mode_selection();
    
    return 0;
}


void mode_selection(){

    cout << "Please select a mode to continue." << endl << endl << "1)Automatic mode\n2)Manual mode\n3)About developer and this tool" << endl << endl << "What is that modes?" << endl << "First mode for selecting photos from example photos and second mode for selecting image manually." << endl << "USER>> ";
    int usr;

    cin >> usr;

    switch (usr)
    {
    case 1:
        //Auto
        mode_auto();
        break;
    case 2:
        //Manual
        mode_manual();
        break;

    case 3:
        about_dev();
        exit_app();
        break;

    default:
        cout << "Please enter a number from field. Exiting..." << endl;
        exit_app();
        break;
    }

}


void mode_auto(){

    bool i1=false,i2=false,i3=false,source_file_b=false,face_model=false;


    for(string proc : vec_example_file_paths){

        if(proc == "example_imgs/black.jpeg" && check_files_exist(proc)){
            i1=true;
        }
        if(proc == "example_imgs/dragon.jpg" && check_files_exist(proc)){
            i2=true;
        }
        if(proc == "example_imgs/human.webp" && check_files_exist(proc)){
            i3=true;
        }
        if(proc == "example_imgs/sources.txt" && check_files_exist(proc)){
            source_file_b=true;
        }
        if(proc == "face.xml" && check_files_exist(proc)){
            face_model=true;
        }


    }

    if(!i1 || !i2 || !i3 || !source_file_b || !face_model){
        cout << "Error. Dumping report:";
    }

    if(!i1){
        cout << "example_imgs/black.jpeg    --> missing file" << endl;
    }
    if(!i2){
        cout << "example_imgs/dragon.jpg    --> missing file" << endl;
    }
    if(!i3){
        cout << "example_imgs/human.webp    --> missing file" << endl;
    }
    if(!source_file_b){
        cout << "example_imgs/sources.txt    --> missing file" << endl;
    }
    if(!face_model){
        cout << "face.xml    --> missing file" << endl;
    }

    if(!i1 || !i2 || !i3 || !source_file_b || !face_model){
        cout << "Please dont use automatic mode or use redownload this tool." << endl;
        exit_app();
    }

    mode_auto_selection();


}



void mode_auto_selection(){

    int usr;

    cout << "Please select a file to check is it contains human face from example files." << endl << "1)example_imgs/black.jpeg\n2)example_imgs/dragon.jpg\n3)example_imgs/human.webp" << endl << "USER>> ";
    cin >> usr;
    switch (usr)
    {
    case 1:
        //example_imgs/black.jpeg

        if(check_human_face("example_imgs/black.jpeg")){
            cout << "Human face detected." << endl;
        }else{
            cout << "Human face not found." << endl;
        }

        break;
    
    case 2:
        //example_imgs/dragon.jpg

        if(check_human_face("example_imgs/dragon.jpg")){
            cout << "Human face detected." << endl;
        }else{
            cout << "Human face not found." << endl;
        }

        break;

    case 3:
        //example_imgs/human.webp

        if(check_human_face("example_imgs/human.webp")){
            cout << "Human face detected." << endl;
        }else{
            cout << "Human face not found." << endl;
        }

        break;

    default:
        cout << "Please enter a number from field. Exiting..." << endl;
        exit_app();
        break;
    }

}


void mode_manual(){

    string usr;

    cout << "This file will be read from manual directory. You should only enter image name." << endl << "Example: example.png" << endl << "Please enter name of the image." << endl << "USER>> ";
    cin >> usr;

    if(check_human_face("manual/"+usr)){
        cout << "Human face detected." << endl;
    }else{
        cout << "Human face not found." << endl;
    }
    
}

bool check_files_exist(string path_to_check){

    fstream fchecker;
    fchecker.open(path_to_check);
    if(!fchecker.fail()){
        return true; //File opens without any problem 
    }
    return false; //File not found or permission error to read

}



bool check_human_face(string file_path){

    //Normal image = bitmap source --> bitmap converts to matrix(mat)

    Mat image_mat = imread(file_path, IMREAD_COLOR);
    if(image_mat.empty())
    {
        cout << "Error. Image not found or unable to read. Exiting..." << endl;
        exit_app();
    }

    face_cascade.load("face.xml"); //Load face model

    Mat image_mat_gray;
    cvtColor(image_mat, image_mat_gray, COLOR_BGR2GRAY);
    equalizeHist(image_mat_gray, image_mat_gray); //Image color changed to gray
    
    //Detect face
    vector<Rect> face;
    face_cascade.detectMultiScale(image_mat_gray, face);

    //Out
    if(face.empty()){
        return false; //Not detected
    }else{
        return true; //Detected
    }


    cout << "Unknown error. Exiting... Please retry." << endl;
    exit_app();

}

void exit_app(){

    fstream fchecker;
    fchecker.open("token_to_exit(Expection)_hahaha");
    exit(fchecker.fail());

}

void about_dev(){

    cout << "Developed by 0rbianta. The impossible story, life is a test. To be defeated, to win is a new test." << endl << "Copyright 2020 0rbianta" << endl << endl << "This software was written in 4 hours. Sometimes it can give erroneous results. There are 2 options for using it. Put the picture you want to try on the manual directory and own the example_imgs directory. This is enough. Have a nice day." << endl;

}