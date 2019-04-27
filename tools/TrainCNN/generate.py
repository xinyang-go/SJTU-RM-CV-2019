import numpy as np
import os
import cv2
import random
from forward import OUTPUT_NODES


class DataSet:
    def __init__(self, folder):
        self.train_sets = []
        self.test_sets = []
        self.generate_data_sets(folder)

    def generate_data_sets(self, folder):
        def file2nparray(name):
            image = cv2.imread(name)
            return image[:, :, 0]

        def id2label(id):
            a = np.zeros([OUTPUT_NODES, 1])
            a[id] = 1
            return a[:]

        sets = []
        for i in range(OUTPUT_NODES):
            dir = "%s/%d" % (folder, i)
            files = os.listdir(dir)
            for file in files:
                sets.append([file2nparray("%s/%s" % (dir, file)), id2label(i)])
        sets = np.array(sets)
        np.random.shuffle(sets)
        length = len(sets)
        self.train_sets = sets[:length*3//4]
        self.test_sets = sets[length*3//4:]

    def sample_train_sets(self, length):
        samples = []
        labels = []
        for i in range(length):
            id = random.randint(0, length-1)
            samples.append(self.train_sets[id][0])
            labels.append(self.train_sets[id][1])
        return np.array(samples), np.array(labels)

    def all_train_sets(self):
        return self.train_sets[:, 0, :, :], self.train_sets[:, 1, :, :]

    def all_test_sets(self):
        return self.test_sets[:, 0, :, :], self.test_sets[:, 1, :, :]
