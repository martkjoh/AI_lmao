import numpy as np
import os
import gzip
import shutil
import codecs
from urllib.request import urlretrieve
from PIL import Image

urls = ['http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz',
       'http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz',
       'http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz',
       'http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz']

path = "data/"

def checkAndMakeDir(path):
    if not os.path.exists(path):
        os.makedirs(path)

checkAndMakeDir(path)

print("Downloading files")
for url in urls:
    filename = url.split("/")[-1]
    urlretrieve(url, path + filename)

files = os.listdir(path)

print("Unzipping files")
for i, file in enumerate(files):
    if file.endswith(".gz"):
        shutil.copyfileobj(
            gzip.open(path + file, "rb"), 
            open(path + file.split(".")[0], "wb"))
        os.remove(path + file)
        files[i] = file.split(".")[0]

def get_int(b):   # CONVERTS 4 BYTES TO A INT
    return int(codecs.encode(b, 'hex'), 16)

data_dict = {}
catoegories = ["images", "labels"]
data_sets = ["test", "train"]

print("Extrancting data from files")
for file in files:
    try:
        with open(path + file, "rb") as f:

            data = f.read()
            datatype = get_int(data[:4]) # 0-3: THE MAGIC NUMBER TO WHETHER IMAGE OR LABEL
            length = get_int(data[4:8])  # 4-7: LENGTH OF THE ARRAY  (DIMENSION 0)

            if (datatype == 2051):
                category = catoegories[0]
                num_rows = get_int(data[8:12])  # NUMBER OF ROWS  (DIMENSION 1)
                num_cols = get_int(data[12:16])  # NUMBER OF COLUMNS  (DIMENSION 2)
                parsed = np.frombuffer(data, dtype = np.uint8, offset = 16)  # READ THE PIXEL VALUES AS INTEGERS
                parsed = parsed.reshape(length, num_rows * num_cols)  # RESHAPE THE ARRAY AS [NO_OF_SAMPLES x HEIGHT x WIDTH]           

            elif(datatype == 2049):
                category = catoegories[1]
                temp = np.frombuffer(data, dtype=np.uint8, offset=8) # READ THE LABEL VALUES AS INTEGERS
                temp = temp.reshape(length)  # RESHAPE THE ARRAY AS [NO_OF_SAMPLES]
                parsed = np.zeros((len(temp), 10))
                for i in range(len(temp)):
                    parsed[i][temp[i]] = 1

            if (length == 10000):
                data_set = data_sets[0]

            elif (length == 60000):
                data_set = data_sets[1]

            data_dict[data_set + '_' + category] = parsed  # SAVE THE np ARRAY TO A CORRESPONDING KEY

            os.remove(path + file)
    except:
        files.remove(file)

print("Saving prictures:")
for data_set in data_sets:
    print("\t Saving " + data_set  + "_" + catoegories[0])
    data = data_dict[data_set + "_" + catoegories[0]]
    n = 28
    
    checkAndMakeDir(path + data_set)
    for i in range(10):
        checkAndMakeDir(path + data_set + "/" + str(i))

    for a in range(len(data)):
        im = Image.new("L", (n, n))
        pxs = im.load()
        for i in range(n):
            for j in range(n):
                pxs[i, j] = int(data[a, j * n + i] * 255)
        
        label = data_dict[data_set + "_" + catoegories[1]][a].argmax()

        im.save(path +  data_set + "/" + str(label) + "/img_" + str(a) + ".png")