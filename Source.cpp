#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

void update(double& x, double& y);
void paintGreen(Vec3b& bgra);
void paintFractalFernMatrix(Mat& mat);
void paintGreenFractalFern(Mat& mat);

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

    int r = rand() % 100;

    if (r < 1) {
        nextX = 0;
        nextY = 0.16 * y;
    }
    else if (r < 86) {
        nextX = 0.85 * x + 0.04 * y;
        nextY = -0.04 * x + 0.85 * y + 1.6;
    }
    else if (r < 93) {
        nextX = 0.20 * x - 0.26 * y;
        nextY = 0.23 * x + 0.22 * y + 1.6;
    }
    else {
        nextX = -0.15 * x + 0.28 * y;
        nextY = 0.26 * x + 0.24 * y + 0.44;
    }
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


