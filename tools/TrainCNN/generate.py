import numpy as np
import os
import cv2
import random
from tqdm import tqdm
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
            dir = "%s/id%d" % (folder, i)
            files = os.listdir(dir)
            for file in tqdm(files, postfix={"loading id": i}, dynamic_ncols=True):
                if file[-3:] == "jpg":
                    sample = self.file2nparray("%s/%s" % (dir, file))
                    label = self.id2label(i)
                    if random.random() > 0.7:
                        self.train_samples.append(sample)
                        self.train_labels.append(label)
                        if i == 0:
                            tmp = sample.copy()
                            tmp = tmp[:, :, ::-1]
                            self.train_samples.append(tmp)
                            self.train_labels.append(label)
                        else:
                            tmp = sample.copy()
                            tmp = 1.2 * tmp
                            tmp = np.where(tmp > 1, 1, tmp)
                            tmp = np.where(tmp < 0, 0, tmp)
                            self.train_samples.append(tmp)
                            self.train_labels.append(label)
                            tmp = sample.copy()
                            tmp = 0.8 * tmp
                            tmp = np.where(tmp > 1, 1, tmp)
                            tmp = np.where(tmp < 0, 0, tmp)
                            self.train_samples.append(tmp)
                            self.train_labels.append(label)
                    else:
                        self.test_samples.append(sample)
                        self.test_labels.append(label)
        self.train_samples = np.array(self.train_samples)
        self.train_labels = np.array(self.train_labels)
        self.test_samples = np.array(self.test_samples)
        self.test_labels = np.array(self.test_labels)
        return sets

    def sample_train_sets(self, length, std=0.0):
        samples = []
        labels = []
        for i in range(length):
            id = random.randint(0, len(self.train_samples) - 1)
            samples.append(self.train_samples[id])
            labels.append(self.train_labels[id])
        samples = np.array(samples).copy()
        samples += np.random.normal(0, std, samples.shape)
        labels = np.array(labels)
        return samples, labels

    def sample_test_sets(self, length, std=0.0):
        samples = []
        labels = []
        for i in range(length):
            id = random.randint(0, len(self.test_samples) - 1)
            samples.append(self.test_samples[id])
            labels.append(self.test_labels[id])
        samples = np.array(samples).copy()
        samples += np.random.normal(0, std, samples.shape)
        labels = np.array(labels)
        return samples, labels

    def all_train_sets(self, std=0.0):
        return self.train_samples[:], self.train_labels[:]

    def all_test_sets(self, std=0.0):
        return self.test_samples[:], self.test_labels[:]
