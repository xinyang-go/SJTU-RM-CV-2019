import numpy as np
import os
import cv2
import random
from forward import OUTPUT_NODES
# 原图像行数
SRC_ROWS = 36

# 原图像列数
SRC_COLS = 48

# 原图像通道数
SRC_CHANNELS = 3


class DataSet:
    def __init__(self, folder):
        self.train_samples = []
        self.train_labels = []
        self.test_samples = []
        self.test_labels = []
        self.generate_data_sets(folder)

    def file2nparray(self, name):
        image = cv2.imread(name)
        image = cv2.resize(image, (SRC_COLS, SRC_ROWS))
        image = image.astype(np.float32)
        return image / 255.0

    def id2label(self, id):
        a = np.zeros([OUTPUT_NODES])
        a[id] = 1
        return a[:]

    def generate_data_sets(self, folder):
        sets = []
        for i in range(OUTPUT_NODES):
            dir = "%s/%d" % (folder, i)
            files = os.listdir(dir)
            for file in files:
                if file[-3:] == "jpg":
                    if random.random() > 0.2:
                        self.train_samples.append(self.file2nparray("%s/%s" % (dir, file)))
                        self.train_labels.append(self.id2label(i))
                    else:
                        self.test_samples.append(self.file2nparray("%s/%s" % (dir, file)))
                        self.test_labels.append(self.id2label(i))
        self.train_samples = np.array(self.train_samples)
        self.train_labels = np.array(self.train_labels)
        self.test_samples = np.array(self.test_samples)
        self.test_labels = np.array(self.test_labels)
        return sets

    def sample_train_sets(self, length):
        samples = []
        labels = []
        for i in range(length):
            id = random.randint(0, len(self.train_samples)-1)
            samples.append(self.train_samples[id])
            labels.append(self.train_labels[id])
        return np.array(samples), np.array(labels)

    def all_train_sets(self):
        return self.train_samples[:], self.train_labels[:]

    def all_test_sets(self):
        return self.test_samples[:], self.test_labels[:]
