#!/usr/bin/python3
print("Preparing...")
import tensorflow as tf
from tqdm import tqdm
import generate
import forward
import cv2
import sys
import numpy as np
print("Finish!")

def save_kernal(fp, val):
    print(val.shape[2], file=fp)
    print(val.shape[3], file=fp)
    print(val.shape[1], file=fp)
    print(val.shape[0], file=fp)
    for in_channel in range(val.shape[2]):
        for out_channel in range(val.shape[3]):
            for row in range(val.shape[0]):
                for col in range(val.shape[1]):
                    print(val[row][col][in_channel][out_channel], file=fp)


def save_weight_mat(fp, val):
    print(val.shape[0], file=fp)
    print(val.shape[1], file=fp)
    for row in range(val.shape[0]):
        for col in range(val.shape[1]):
            print(val[row][col], file=fp)


def save_bias(fp, val):
    print(val.shape[0], file=fp)
    for i in range(val.shape[0]):
        print(val[i], file=fp)


def save_para(folder, paras):
    with open(folder + "/conv1_w", "w") as fp:
        save_kernal(fp, paras[0])
    with open(folder + "/conv1_b", "w") as fp:
        save_bias(fp, paras[1])
    with open(folder + "/conv2_w", "w") as fp:
        save_kernal(fp, paras[2])
    with open(folder + "/conv2_b", "w") as fp:
        save_bias(fp, paras[3])
    with open(folder + "/fc1_w", "w") as fp:
        save_weight_mat(fp, paras[4])
    with open(folder + "/fc1_b", "w") as fp:
        save_bias(fp, paras[5])
    with open(folder + "/fc2_w", "w") as fp:
        save_weight_mat(fp, paras[6])
    with open(folder + "/fc2_b", "w") as fp:
        save_bias(fp, paras[7])


STEPS = 100000
BATCH = 30
LEARNING_RATE_BASE  = 0.01
LEARNING_RATE_DECAY = 0.99
MOVING_AVERAGE_DECAY = 0.99


def train(dataset, show_bar=False):
    x = tf.placeholder(tf.float32, [None, generate.SRC_ROWS, generate.SRC_COLS, generate.SRC_CHANNELS])
    y_= tf.placeholder(tf.float32, [None, forward.OUTPUT_NODES])
    nodes, vars = forward.forward(x, 0.001)
    y = nodes[-1]

    ce  = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=y, labels=tf.argmax(y_, 1))
    cem = tf.reduce_mean(ce)
    loss= cem + tf.add_n(tf.get_collection("losses"))

    global_step = tf.Variable(0, trainable=False)
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE_BASE,
        global_step,
        len(dataset.train_samples) / BATCH,
        LEARNING_RATE_DECAY,
        staircase=False)
    train_step = tf.train.AdamOptimizer(learning_rate).minimize(loss, global_step=global_step)

    ema = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DECAY, global_step)
    ema_op = ema.apply(tf.trainable_variables())
    with tf.control_dependencies([train_step, ema_op]):
        train_op = tf.no_op(name='train')

    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    with tf.Session() as sess:
        init_op = tf.global_variables_initializer()
        sess.run(init_op)

        bar = tqdm(range(STEPS), dynamic_ncols=True)
        for i in bar:
            images_samples, labels_samples = dataset.sample_train_sets(BATCH)

            _, loss_value, step = sess.run(
                [train_op, loss, global_step],
                feed_dict={x: images_samples, y_: labels_samples}
            )

            if i % 100 == 0:
                if i % 1000 == 0:
                    test_samples, test_labels = dataset.sample_test_sets(5000)
                    acc = sess.run(accuracy, feed_dict={x: test_samples, y_: test_labels})
                bar.set_postfix({"loss": loss_value, "acc": acc})

        # video = cv2.VideoCapture("/home/xinyang/Desktop/Video.mp4")
        # _ = True
        # while _:
        #     _, frame = video.read()
        #     cv2.imshow("Video", frame)
        #     k = cv2.waitKey(10)
        #     if k == ord(" "):
        #         bbox = cv2.selectROI("frame", frame, False)
        #         print(bbox)
        #         roi = frame[bbox[1]:bbox[1]+bbox[3], bbox[0]:bbox[0]+bbox[2]]
        #         roi = cv2.resize(roi, (48, 36))
        #         cv2.imshow("roi", roi)
        #         cv2.waitKey(0)
        #         roi = roi.astype(np.float32)
        #         roi /= 255.0
        #         roi = roi.reshape([1, 36, 48, 3])
        #         res = sess.run(y, feed_dict={x: roi})
        #         res = res.reshape([forward.OUTPUT_NODES])
        #         print(np.argmax(res))
        #     elif k==ord("q"):
        #         break
        # keep = True
        # while keep:
        #     n = input()
        #     im = cv2.imread(n)
        #     im = cv2.resize(im, (48, 36))
        #     cv2.imshow("im", im)
        #     if cv2.waitKey(0) == ord("q"):
        #         keep = False
        #     im = im.astype(np.float32)
        #     im /= 255.0
        #     im = im.reshape([1, 36, 48, 3])
        #     res = sess.run(y, feed_dict={x: im})
        #     res = res.reshape([forward.OUTPUT_NODES])
        #     print(np.argmax(res))
    
        test_samples, test_labels = dataset.sample_test_sets(100)
        vars_val = sess.run(vars)
        save_para("/home/xinyang/Desktop/AutoAim/tools/para", vars_val)
        nodes_val = sess.run(nodes, feed_dict={x:test_samples})
        return vars_val, nodes_val, test_samples


if __name__ == "__main__":
    print("Loading data sets...")
    dataset = generate.DataSet("/home/xinyang/Desktop/DataSets")
    print("Finish!")
    train(dataset, show_bar=True)
    input("Press any key to end...")
