#!/usr/bin/python3
print("Preparing...")
import tensorflow as tf
from tqdm import tqdm
import generate
import forward
import cv2
import numpy as np
import mvsdk
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


STEPS = 60000
BATCH = 50
LEARNING_RATE_BASE  = 0.001
LEARNING_RATE_DECAY = 0.99
MOVING_AVERAGE_DECAY = 0.99


def train(dataset, show_bar=False):
    x = tf.placeholder(tf.float32, [None, generate.SRC_ROWS, generate.SRC_COLS, generate.SRC_CHANNELS])
    y_= tf.placeholder(tf.float32, [None, forward.OUTPUT_NODES])
    keep_rate = tf.placeholder(tf.float32)
    nodes, vars = forward.forward(x, 0.01)
    y = nodes[-1]

    ce  = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=y, labels=tf.argmax(y_, 1))
#    ce  = tf.nn.weighted_cross_entropy_with_logits(logits=y, labels=tf.argmax(y_, 1), pos_weight=1)
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

    config = tf.ConfigProto(gpu_options=tf.GPUOptions(allow_growth=True))
    with tf.Session(config=config) as sess:
        init_op = tf.global_variables_initializer()
        sess.run(init_op)

        bar = tqdm(range(STEPS), ascii=True, dynamic_ncols=True)
        for i in bar:
            images_samples, labels_samples = dataset.sample_train_sets(BATCH)

            _, loss_value, step = sess.run(
                [train_op, loss, global_step],
                feed_dict={x: images_samples, y_: labels_samples, keep_rate:0.2}
            )

            if (i-1) % 100 == 0:
                if (i-1) % 500 == 0:
                    test_images, test_labels = dataset.sample_test_sets(5000)
                    test_acc, output = sess.run([accuracy, y], feed_dict={x: test_images, y_: test_labels, keep_rate:1.0})
                    output = np.argmax(output, axis=1)
                    real = np.argmax(test_labels, axis=1)
                    print("=============test-set===============")
                    for n in range(forward.OUTPUT_NODES):
                        print("label: %d, precise: %f, recall: %f" %
                            (n, np.mean(real[output==n]==n), np.mean(output[real==n]==n)))

                    train_images, train_labels = dataset.sample_train_sets(5000)
                    train_acc, output = sess.run([accuracy, y], feed_dict={x: train_images, y_: train_labels, keep_rate:1.0})
                    output = np.argmax(output, axis=1)
                    real = np.argmax(train_labels, axis=1)
                    print("=============train-set===============")
                    for n in range(forward.OUTPUT_NODES):
                        print("label: %d, precise: %f, recall: %f" %
                              (n, np.mean(real[output==n]==n), np.mean(output[real==n]==n)))
                    print("\n")

                bar.set_postfix({"loss": loss_value, "train_acc": train_acc, "test_acc": test_acc})

        vars_val = sess.run(vars)
        save_para("/home/xinyang/Workspace/RM_auto-aim/tools/para", vars_val)
        print("save done!")

        # pred = sess.run(y, feed_dict={x: test_images, keep_rate:1.0})

#        nodes_val = sess.run(nodes, feed_dict={x:test_images})
#        return vars_val, nodes_val
        DevList = mvsdk.CameraEnumerateDevice()
        nDev = len(DevList)
        if nDev < 1:
            print("No camera was found!")
            return

        for i, DevInfo in enumerate(DevList):
            print("{}: {} {}".format(i, DevInfo.GetFriendlyName(), DevInfo.GetPortType()))
        i = 0 if nDev == 1 else int(input("Select camera: "))
        DevInfo = DevList[i]
        print(DevInfo)

        # 打开相机
        hCamera = 0
        try:
            hCamera = mvsdk.CameraInit(DevInfo, -1, -1)
        except mvsdk.CameraException as e:
            print("CameraInit Failed({}): {}".format(e.error_code, e.message) )
            return

        # 获取相机特性描述
        cap = mvsdk.CameraGetCapability(hCamera)

        # 判断是黑白相机还是彩色相机
        monoCamera = (cap.sIspCapacity.bMonoSensor != 0)

        # 黑白相机让ISP直接输出MONO数据，而不是扩展成R=G=B的24位灰度
        if monoCamera:
            mvsdk.CameraSetIspOutFormat(hCamera, mvsdk.CAMERA_MEDIA_TYPE_MONO8)
        else:
            mvsdk.CameraSetIspOutFormat(hCamera, mvsdk.CAMERA_MEDIA_TYPE_BGR8)

        # 相机模式切换成连续采集
        mvsdk.CameraSetTriggerMode(hCamera, 0)

        # 手动曝光，曝光时间30ms
        mvsdk.CameraSetAeState(hCamera, 0)
        mvsdk.CameraSetExposureTime(hCamera, 30 * 1000)

        # 让SDK内部取图线程开始工作
        mvsdk.CameraPlay(hCamera)

        # 计算RGB buffer所需的大小，这里直接按照相机的最大分辨率来分配
        FrameBufferSize = cap.sResolutionRange.iWidthMax * cap.sResolutionRange.iHeightMax * (1 if monoCamera else 3)

        # 分配RGB buffer，用来存放ISP输出的图像
        # 备注：从相机传输到PC端的是RAW数据，在PC端通过软件ISP转为RGB数据（如果是黑白相机就不需要转换格式，但是ISP还有其它处理，所以也需要分配这个buffer）
        pFrameBuffer = mvsdk.CameraAlignMalloc(FrameBufferSize, 16)

        while (cv2.waitKey(1) & 0xFF) != ord('q'):
            # 从相机取一帧图片
            try:
                pRawData, FrameHead = mvsdk.CameraGetImageBuffer(hCamera, 200)
                mvsdk.CameraImageProcess(hCamera, pRawData, pFrameBuffer, FrameHead)
                mvsdk.CameraReleaseImageBuffer(hCamera, pRawData)
                # 此时图片已经存储在pFrameBuffer中，对于彩色相机pFrameBuffer=RGB数据，黑白相机pFrameBuffer=8位灰度数据
                # 把pFrameBuffer转换成opencv的图像格式以进行后续算法处理
                frame_data = (mvsdk.c_ubyte * FrameHead.uBytes).from_address(pFrameBuffer)
                frame = np.frombuffer(frame_data, dtype=np.uint8)
                frame = frame.reshape((FrameHead.iHeight, FrameHead.iWidth, 1 if FrameHead.uiMediaType == mvsdk.CAMERA_MEDIA_TYPE_MONO8 else 3) )

                frame = cv2.resize(frame, (640,480), interpolation = cv2.INTER_LINEAR)
                cv2.imshow("Press q to end", frame)
                if (cv2.waitKey(1)&0xFF) == ord(' '):
                    roi = cv2.selectROI("roi", frame)
                    roi = frame[roi[1]:roi[1]+roi[3], roi[0]:roi[0]+roi[2]]
                    print(roi)
                    cv2.imshow("box", roi)
                    image = cv2.resize(roi, (48, 36))
                    image = image.astype(np.float32) / 255.0
                    out = sess.run(y, feed_dict={x:[image]})
                    print(out)
                    print(np.argmax(out))
                
            except mvsdk.CameraException as e:
                if e.error_code != mvsdk.CAMERA_STATUS_TIME_OUT:
                    print("CameraGetImageBuffer failed({}): {}".format(e.error_code, e.message) )

        # 关闭相机
        mvsdk.CameraUnInit(hCamera)

        # 释放帧缓存
        mvsdk.CameraAlignFree(pFrameBuffer)


if __name__ == "__main__":
    # import os
    # os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID"
    # os.environ["CUDA_VISIBLE_DEVICES"] = "-1"
    dataset = generate.DataSet("/home/xinyang/Workspace/box_resize")
    train(dataset, show_bar=True)
    input("press enter to continue...")
