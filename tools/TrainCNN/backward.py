import tensorflow as tf
from progressive.bar import Bar
import generate
import forward


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


STEPS = 30000
BATCH = 10
LEARNING_RATE_BASE  = 0.01
LEARNING_RATE_DECAY = 0.99
MOVING_AVERAGE_DECAY = 0.99


def train(dataset, show_bar=False):
    test_images, test_labels = dataset.all_test_sets()

    x = tf.placeholder(tf.float32, [None, forward.SRC_ROWS, forward.SRC_COLS, forward.SRC_CHANNELS])
    y_= tf.placeholder(tf.float32, [None, forward.OUTPUT_NODES])
    nodes, vars = forward.forward(0.001)
    y = nodes[-1]

    ce  = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=y, labels=tf.argmax(y_, 1))
    cem = tf.reduce_mean(ce)
    loss= cem + tf.add_n(tf.get_collection("losses"))

    global_step = tf.Variable(0, trainable=False)
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE_BASE,
        global_step,
        len(dataset.train_sets) / BATCH,
        LEARNING_RATE_DECAY,
        staircase=False)
    train_step = tf.train.AdamOptimizer(learning_rate).minimize(loss, global_step=global_step)

    ema = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DECAY, global_step)
    ema_op = ema.apply(tf.trainable_variables())
    with tf.control_dependencies([train_step, ema_op]):
        train_op = tf.no_op(name='train')

    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    acc = 0

    with tf.Session() as sess:
        init_op = tf.global_variables_initializer()
        sess.run(init_op)

        if show_bar:
            bar = Bar(max_value=STEPS, width=u'50%')
            bar.cursor.clear_lines(1)
            bar.cursor.save()

        for i in range(STEPS):
            images_samples, labels_samples = dataset.sample_train_sets(BATCH)

            _, loss_value, step = sess.run(
                [train_op, loss, global_step],
                feed_dict={x: images_samples, y_: labels_samples}
            )

            if i % 100 == 0:
                if i % 1000 == 0:
                    acc = sess.run(accuracy, feed_dict={x: test_images, y_: test_labels})

            if show_bar:
                bar.title = "step: %d, loss: %f, acc: %f" % (step, loss_value, acc)
                bar.cursor.restore()
                bar.draw(value=i+1)

        vars_val = sess.run(vars)
        save_para("paras", vars_val)
        # nodes_val = sess.run(nodes, feed_dict={x:test})
        # return vars_val, nodes_val


if __name__ == "__main__":
    dataset = generate.DataSet("images")
    train(dataset, show_bar=True)
