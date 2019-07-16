#include <Magick++.h>
#include "Matrix.h"
#include <string>

using namespace Magick;
using namespace std;

void getData(vector<Matrix *> & x, vector<Matrix *> &y, int n)
{
    Image pic;
    Matrix * M;
    Matrix * N;
    int m = 28;
    ColorGray c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            try
            {

                pic = Image("trainingSet/" + to_string(j) +"/img_" + to_string(i) + ".jpg");
                pic.quantizeColorSpace();
                M = new Matrix(m * m, 1);
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        c = pic.pixelColor(i, j);
                        (*M)[i * m + j][0] = c.shade(); 
                    }
                }


                N = new Matrix(10, 1);
                (*N)[j][0] = 1.;
                y.push_back(N);
            }
            catch (...)
            {
                int a = 1;
            }
        
        

        }

        x.push_back(M);
    }
}