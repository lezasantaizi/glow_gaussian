#include <iostream>
#include <math.h>
#include "../3rdparty/include/opencv.hpp"

using namespace std;
using namespace cv;
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")
#pragma comment(lib, "opencv_core249d.lib")
#pragma comment(lib, "opencv_highgui249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_core249.lib")
int main(int argc, char** argv)
{

	const char* filename = argc >= 2 ? argv[1] : "hello.jpg";
	Mat src = imread(filename,0);
	if(src.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat dst, cdst;
	//Canny(src, dst, 50, 200, 3);
	namedWindow("hello1");
	imshow("hello1",src);
	int width = src.cols;
	int height = src.rows;
	src.copyTo(dst);

	float alpha = 1.2;

		int n = 1;
		float sigma = 1;
		int size = 2*n +1;  
		int PI = 3.1415926;
		float sigma22 = 2*sigma*sigma;  
		float sigma22PI = (float) PI* sigma22;  
		float ** kernalArr ;
		kernalArr = new float *[size];
		for (int i = 0 ;i < size ;i++)
		{
			kernalArr[i] = new float[size];
			for (int j = 0;j< size ;j++)
			{
				kernalArr[i][j] = 0;
			}
		}
		int row = 0;  
		for(int i=-n; i<=n; i++) {  
			int column = 0;  
			for(int j=-n; j<=n; j++) {  
				float xDistance = i*i;  
				float yDistance = j*j;  
				kernalArr[row][column] = (float)exp(-(xDistance + yDistance)/sigma22)/sigma22PI;  
				column++;  
			}  
			row++;  
		}  

		for(int i=0; i<size; i++) {  
			for(int j=0; j<size; j++) {  
				printf("%f ",kernalArr[i][j]);  
			}  
			printf("\n");  
		}  


		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width ; col++)
			{
				float sum = 0;
				for (int subrow = -n ; subrow <= n ; subrow++)
				{
					for (int subcol = -n; subcol <= n; subcol++ )
					{
						int newrow = row + subrow;
						int newcol = col + subcol;

					if(newrow < 0 || newrow >= height)  
					{   
						newrow = row;   
					}   
					if(newcol < 0 || newcol >= width)  
					{   
						newcol = col;   
					}   

						sum += src.at<uchar>(newrow,newcol) * kernalArr[subrow+n][subcol+n];
					}
				}
				dst.at<uchar>(row,col) = sum + alpha*src.at<uchar>(row,col);
			}
		}

	namedWindow("hello2");
	imshow("hello2",dst);
	waitKey(0);
	return 0;
}