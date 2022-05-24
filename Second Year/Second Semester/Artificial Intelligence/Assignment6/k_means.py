import csv

import numpy as np
from scipy.spatial.distance import cdist
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt


def KMeans(x, k, no_of_iterations, debug_plot=True):
    cid = np.random.choice(len(x), k, replace=False)
    centroids = x[cid, :]

    distances = cdist(x, centroids, 'euclidean')
    labels = np.array([np.argmin(distance) for distance in distances])

    for times in range(no_of_iterations):
        distances = cdist(x, centroids, 'euclidean')
        labels = np.array([np.argmin(distance) for distance in distances])

        old_centroids = centroids.copy()
        for cid in range(k):
            cluster_points = np.squeeze(x[np.argwhere(labels == cid), :])
            centroids[cid] = np.mean(cluster_points, axis=0)

        if np.array_equal(old_centroids, centroids):
            return labels, centroids

        if debug_plot:
            plot(x, labels, centroids)
            plt.pause(0.5)
            plt.clf()

    return labels, centroids


def match_clusters(x, initial_labels, labels, centroids):
    match_dict = {}

    distances = cdist(x, centroids, 'euclidean')

    for i in range(len(centroids)):
        closest_point = np.argmin(distances[:, i])

        if initial_labels[closest_point] in match_dict:
            raise RuntimeError("Cluster matching failed! Two centroids have the same closest point.")

        match_dict[initial_labels[closest_point]] = labels[closest_point]

    return match_dict


def statistics(x, cluster_matching, initial_labels, labels, centroids):
    reverse_matching = dict(zip(cluster_matching.values(), cluster_matching.keys()))

    statistics_dict = {}

    for i in np.unique(labels):
        predicted_cluster = np.squeeze(x[np.argwhere(labels == i), :])

        matched_cluster = reverse_matching[i]
        actual_cluster = np.squeeze(x[np.argwhere(initial_labels == matched_cluster), :])

        """
        tp = true positives
        fp = false positives
        fn = false negatives
        tn = true negatives
        """
        predicted_set = set((tuple(point) for point in predicted_cluster))
        actual_set = set((tuple(point) for point in actual_cluster))

        tp = len(actual_set.intersection(predicted_set))
        fp = len(predicted_set.difference(actual_set))
        fn = len(actual_set.difference(predicted_set))
        tn = len(x) - tp - fp - fn
        p = tp + fp
        n = fn + tn

        statistics_dict[matched_cluster] = {
            'precision': tp / p,
            'accuracy': (tp + tn) / (p + n),
            'recall': tp / (tp + fn),
            'f1_score': (2 * tp) / (2 * tp + fp + fn)
        }

    return statistics_dict


def readData():
    initial_labels, points = [], []
    with open('dataset.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader, None)

        for row in csv_reader:
            points.append((float(row[1]), float(row[2])))
            initial_labels.append(row[0])

    return np.array(initial_labels), np.array(points)


def pretty_dict_print(d, indent=0):
    for key, value in d.items():
        print('\t' * indent + str(key))

        if isinstance(value, dict):
            pretty_dict_print(value, indent + 1)
        else:
            print('\t' * (indent + 1) + str(value))


def plot(x, labels, centroids, cluster_matching=None):
    if cluster_matching is None:
        cluster_labels = np.unique(labels)
    else:
        cluster_labels = np.array([
            cluster_matching['A'],
            cluster_matching['B'],
            cluster_matching['C'],
            cluster_matching['D']
        ])

    colors = dict(zip(cluster_labels, ['r', 'g', 'b', 'y']))
    legend_labels = dict(zip(cluster_labels, ['A', 'B', 'C', 'D']))

    for i in cluster_labels:
        cluster_points = np.squeeze(x[np.argwhere(labels == i), :])

        plt.scatter(x=cluster_points[:, 0], y=cluster_points[:, 1], c=colors[i], label=legend_labels[i])
        plt.scatter(x=centroids[i][0], y=centroids[i][1], marker='s', c=colors[i], edgecolor='black')
    plt.legend()


if __name__ == "__main__":
    initial_labels, points = readData()
    pca = PCA(2)
    df = pca.fit_transform(points)

    labels, centroids = KMeans(df, 4, 100, debug_plot=True)

    cluster_matching = match_clusters(df, initial_labels, labels, centroids)
    pretty_dict_print(statistics(df, cluster_matching, initial_labels, labels, centroids))

    plot(df, labels, centroids, cluster_matching)
    plt.show()
