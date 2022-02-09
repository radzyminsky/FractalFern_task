#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void update(double& x, double& y);
void paintGreen(Vec3b& bgra);
void paintFractalFernMatrix(Mat& mat);
void paintGreenFractalFern(Mat& mat);
vector<string> SplitStr(string str, char delimiter1, char delimiter2);
vector<string> SplitStr(string str, char delimiter);



class FractalFunction
{
public:
    double array[7];
    FractalFunction() {}
    FractalFunction(double arr[7])
    {
        for (int i = 0; i < 7; i++)
        {
            array[i] = arr[i];
        }
    }
    ~FractalFunction() {};

    static FractalFunction CreateOne(string str)
    {
        double ar_doubl[7];

        //do manipulation on str to get the values..
        vector<string>sub_str;
        sub_str = SplitStr(str, ',');

        //now, sub_str look: sub_str[0]= "a=5", sub_str[0]= "b=3"..
        for (int i = 0; i < sub_str.size(); i++)
        {
            int index = sub_str[i].find('=');
            string str = (sub_str[i].erase(0, index + 1));
            char** charptr = new char*;
            ar_doubl[i] = std::strtod(str.c_str(), charptr);
        }

        FractalFunction created(ar_doubl);
        return created;
    }
};

class FractalConstruction
{
public:
    FractalFunction fc[4];

    FractalConstruction(vector<FractalFunction>functions)
    {
        for (int i = 0; i < functions.size(); i++)
        {
            fc[i] = functions[i];
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                cout << fc[i].array[j];
            }
        }
    }
    ~FractalConstruction() {}
    static FractalConstruction CreateConstruction(string str)
    {
        //do manipulation on str to get the valus..
        vector<string>sub_str;
        vector<FractalFunction>functions;
        sub_str = SplitStr(str, '(', ')');

        for (int i = 0; i < sub_str.size(); i++)
        {
            functions.push_back(FractalFunction::CreateOne(sub_str[i]));
        }

        FractalConstruction created(functions);
        return created;
    }

};

string str1 = "f1(a=0,b=0,c=0,d=0.16,e=0,f=0,p=0.01)";
string str2 = "f2(a=0.85,b=0.04,c=-0.04,d=0.85,e=0,f=1.6,p=0.85)";
string str3 = "f3(a=0.2,b=-0.26,c=0.23,d=0.22,e=0,f=1.6,p=0.07)";
string str4 = "f4(a=-0.15,b=0.28,c=0.26,d=0.24,e=0,f=0.44,p=0.07)";

string str = str1 + str2 + str3 + str4;

  FractalConstruction fc= FractalConstruction::CreateConstruction(str);

int wid_len = 700;

int main()
{
  

    Mat matrix(wid_len, wid_len, CV_8UC3); // Create a matrix with 3 channel
    paintFractalFernMatrix(matrix);

    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    bool result = false;
    try
    {
        result = imwrite("FractalFern.png", matrix, compression_params);
    }
    catch (const cv::Exception& ex)
    {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
    if (result)
        printf("Saved PNG file with FractalFern data.\n");
    else
        printf("ERROR: Can't save PNG file.\n");
    
    return result ? 0 : 1;

}

void update(double& x, double& y) {

    double nextX, nextY;
    int p1, p2, p3, p4;
    p1 = (int)(fc.fc[0].array[6] * 100);
    p2=p1+ (int)(fc.fc[1].array[6] * 100);
    p3=p2+ (int)(fc.fc[2].array[6] * 100);
  //  p4= p3+(int)(fc.fc[3].array[6] * 100);

    int r = rand() % 100;
    double *arr;

    if (r < p1) {

        arr=fc.fc[0].array;      
    }
    else if (r < p2) {
        
        arr = fc.fc[1].array;
    }
    else if (r < p3) {

        arr = fc.fc[2].array;
    }
    else {

        arr = fc.fc[3].array;
    }
    nextX = arr[0] * x + arr[1] * y + arr[4];
    nextY = arr[2] * x + arr[3] * y + arr[5];
    x = nextX;
    y = nextY;

}
void paintGreen(Vec3b& bgr)
{
    bgr[1] = 255;
}

void paintFractalFernMatrix(Mat& matrix)
{
    CV_Assert(matrix.channels() == 3);
    for (int i = 0; i < matrix.rows; ++i)
    {
        for (int j = 0; j < matrix.cols; ++j)
        {
            Vec3b& bgr = matrix.at<Vec3b>(i, j);
            bgr[0] = bgr[1] = bgr[2] = 0;
        }
    }

    paintGreenFractalFern(matrix);
}

void paintGreenFractalFern(Mat& matrix)
{
    double x, y;
    x = y = 0;

    srand(time(0));

    for (int i = 0;i < 100000;i++)
    {
        paintGreen(matrix.at<Vec3b>(wid_len - wid_len * ((y + 2) / 14), wid_len * (x + 3) / 6));
        update(x, y);
    }
}

//function get a one delimiter and return all substrings Between the delimiter
vector<string> SplitStr(string str, char delimiter)
{
    vector<string>subStrings;
    string temp = "";
    int start = 0;
    while (start != -1)
    {
        start = str.find(delimiter);

        temp.assign(str, 0, start);
        str.erase(0, start + 1);
        subStrings.push_back(temp);
    }return subStrings;
}

//function get a tow delimiters and return all substrings Between the delimiters
vector<string> SplitStr(string str, char delimiter1, char delimiter2)
{
    vector<string>subStrings;
    string temp = "";
    int start, end;
    start = end = 0;
    while (start != -1 && end != -1)
    {
        start = str.find(delimiter1);
        end = str.find(delimiter2);
        temp.assign(str, start + 1, end - start - 1);
        str.erase(0, end + 1);
        subStrings.push_back(temp);
    }return subStrings;
}


