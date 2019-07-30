#include "../header/Interface.h"


void makeNN(string name)
{
    NeuralNet net(L, l);
    net.saveNet(name);
}

void trainNN(string name, int timesTrainig, int batchNum)
{
    NeuralNet net(name);
    Data d = getData();

    train(net, d, timesTrainig, batchNum);

    net.saveNet(name);
}

void testNN(string name)
{
    NeuralNet net(name);
    Data d = getData(DataType::TEST);
    test(net, d);
}

void guessNubmer(string name, string path)
{
    Image im(path);
    Matrix input(28 * 28, 1), output;
    imToMat(im, &input);
    NeuralNet net(name);
    net.activate(input);
    output = net.getOutput();
    cout << "AI_lmao guesses: " << output.absMaxIndex().m << endl;
}

void Interface(int argc, char ** argv)
{
    srand (time(NULL));

    if (argc < 2)
    {
        cout << "Argument needed" << endl;
    }

    else if (string(argv[1]) == "train")
    {
        string name = argv[2];
        if (argc == 4)
        {
            int n = stoi(argv[3]);
            trainNN(name, n);
        }
        else if (argc == 5)
        {
            int n = stoi(argv[3]);
            int m = stoi(argv[4]);
            trainNN(name, n, m);
        }
        else
        {
            cout << "Too many arguments. Syntax:" << endl;
            cout << "train (number of times) (number of batches)" << endl;
        }
    }

    else if(string(argv[1]) == "make")
    {
        if (argc < 3)
        {
            cout << "Missing name of Neural Net. Syntatx:" << endl;
            cout << "make <name>" << endl;
        }
        else if(argc = 3)
        {
            string name = argv[2];
            makeNN(name);
        }
        else
        {
            cout << "Too many arguments. Syntax:" << endl;
            cout << "make <name>" << endl;
        }
    }

    else if(string(argv[1]) == "test")
    {
        if (argc < 3)
        {
            cout << "Missing name of Neural Net. Syntatx:" << endl;
            cout << "test <name>" << endl;
        }
        else if(argc = 3)
        {
            string name = argv[2];
            testNN(name);
        }
        else
        {
            cout << "Too many arguments. Syntax:" << endl;
            cout << "test <name>" << endl;
        }
    }

    else if(string(argv[1]) == "guess")
    {
    if (argc < 4)
        {
            cout << "Too few arguments. Syntatx:" << endl;
            cout << "guess <name> <path>" << endl;
        }
        else if(argc = 4)
        {
            string name = argv[2];
            string path = argv[3];
            guessNubmer(name, path);
        }
        else
        {
            cout << "Too many arguments. Syntax:" << endl;
            cout << "guess <path> <name>" << endl;
        }
    }

    else
    {
        cout << "Invalid argument" << endl;
        cout << "Arguments:" << endl;
        for (int i = 1; i < argc; i++)
            cout << argv[i] << endl;
    }
}
