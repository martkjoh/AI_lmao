#include "../header/dataPrep.h"

void imToMat(Image & im, Matrix * M)
{
    ColorGray c;
    for (int i = 0; i < im.rows(); i++)
    {
        for (int j = 0; j < im.columns(); j++)
        {
            c = im.pixelColor(i, j);
            (*M)[i * im.columns() + j][0] = c.shade(); 
        }
    }
}

void matToIm(Image & im, Matrix * M)
{
    ColorGray c;
    for (int i = 0; i < im.rows(); i++)
    {
        for (int j = 0; j < im.columns(); j++)
        {
            c.shade((*M)[i * im.columns() + j][0]);
            im.pixelColor(i, j, c); 
        }
    }
}


void getData(vector<Matrix *> & x, vector<Matrix *> &y, int n)
{
    Image pic;
    Matrix * M;
    Matrix * N;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            try
            {
                pic = Image("trainingSet/" + to_string(j) +"/img_" + to_string(i) + ".jpg");
                pic.quantizeColorSpace();
                
                M = new Matrix(pic.rows() * pic.columns(), 1);
                imToMat(pic, M);
                x.push_back(M);
                
                N = new Matrix(10, 1);
                (*N)[j][0] = 1.;
                y.push_back(N);
            }
            catch (...) {}
        }
    }
}
