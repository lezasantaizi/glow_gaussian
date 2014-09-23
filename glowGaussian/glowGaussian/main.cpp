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

	const char* filename = argc >= 2 ? argv[1] : "bat.jpg";
	Mat src = imread(filename,1);
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
				float sumR = 0, sumG = 0, sumB = 0;
				for (int subrow = -n ; subrow <= n ; subrow++)
				{
					for (int subcol = -n; subcol <= n; subcol++ )
					{
						int newrow = row + subrow;
						int newcol = col + subcol;

						//if(newrow < 0 || newrow >= height)  
						//{   
						//	newrow = row;   
						//}   
						//if(newcol < 0 || newcol >= width)  
						//{   
						//	newcol = col;   
						//}   
						if (newrow<0)
						{
							newrow *= -1;
						}
						if (newrow>=height)
						{
							newrow = (height -1) - (newrow - (height - 1));
						}  

						if (newcol<0)
						{
							newcol *= -1;
						}
						if (newcol>=width)
						{
							newcol = (width -1) - (newcol - (width - 1));
						} 

						if (src.channels() == 1)
						{
							sumR += src.at<uchar>(newrow,newcol) * kernalArr[subrow+n][subcol+n];
						}
						else
						{
							sumR += src.at<Vec3b>(newrow,newcol)[2] * kernalArr[subrow+n][subcol+n];
							sumG += src.at<Vec3b>(newrow,newcol)[1] * kernalArr[subrow+n][subcol+n];
							sumB += src.at<Vec3b>(newrow,newcol)[0] * kernalArr[subrow+n][subcol+n];

						}
					}
				}
				if (src.channels() == 1)
				{
					dst.at<uchar>(row,col) = sumR; //- src.at<uchar>(row,col);
				}
				else
				{
					dst.at<Vec3b>(row,col)[2] = sumR; //- src.at<uchar>(row,col);
					dst.at<Vec3b>(row,col)[1] = sumG; //- src.at<uchar>(row,col);
					dst.at<Vec3b>(row,col)[0] = sumB; //- src.at<uchar>(row,col);

				}
			}
		}

	namedWindow("hello2");
	imshow("hello2",dst + src);
	waitKey(0);
	return 0;
}