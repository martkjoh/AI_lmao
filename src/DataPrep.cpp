#include "../header/DataPrep.h"

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

void loadData(Data & d, string path, int n)
{
    Image pic;
    Matrix * M;
    Matrix * N;
    cout << "Loading data from " << path << endl;
    for (int i = 0; i < n; i++)
    {
        bool loaded = false;
        for (int j = 0; j < 10; j++)
        {
            try
            {
                pic = Image(path + to_string(j) +"/img_" + to_string(i) + ".png");
                pic.quantizeColorSpace();
                M = new Matrix(pic.rows() * pic.columns(), 1);
                imToMat(pic, M);
                d.x.push_back(M);
                
                N = new Matrix(10, 1);
                (*N)[j][0] = 1.;
                d.y.push_back(N);
                loaded = true;
            }
            catch (...) {}
        }

        if (not loaded)
            cout << "loading image " + to_string(i) + " failed." << endl;
    }
}

Data getData(DataType DT)
{
    Data d;
    int n;
    string path;

    if (DT = DataType::TRAIN)
    {    
        n = TRAING_SIZE;
        path = "data/train/";
    }
    else if (DT = DataType::TEST)
    {
        n = TESTING_SIZE; 
        path = "data/test/";
    }

    loadData(d, path, n);
    return d;
}

