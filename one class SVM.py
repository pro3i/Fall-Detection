
import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm
from numpy import genfromtxt

xx, yy = np.meshgrid(np.linspace(-5, 5, 500), np.linspace(-5, 5, 500))

#Extract data from csv file
myX_train = genfromtxt('train-data.csv', delimiter=',')
myX_train=myX_train[0:70000, 1:7]
myX_trainA=myX_train[0000:4000, 1:4]
myX_trainG=myX_train[0000:4000, 4:7]
print("Length of training data: ",len(myX_train))

myX_test = genfromtxt('fall-data.csv', delimiter=',')
myX_test_time = myX_test[0000:4000, 0]
myX_test=myX_test[0000:4000, 1:7]
myX_testA=myX_test[0000:4000, 1:4]
myX_testG=myX_test[0000:4000, 4:7]

print("Length of test data: ",len(myX_test))

# fit the model
clf = svm.OneClassSVM(nu=0.00001, kernel="rbf", gamma=0.1)
clf.fit(myX_train)
y_pred_train = clf.predict(myX_train)
y_pred_test = clf.predict(myX_test)


#Plot results
fig, axs = plt.subplots(3)
axs[0].set_title('Acceleration')
axs[1].set_title('Gyroscope')
axs[2].set_title('One Class SVM')
axs[0].set(ylabel="Acceleration(G's)")
axs[1].set(ylabel='Gyroscope(degrees/s)')
axs[0].set(xlabel="Datapoint")
axs[1].set(xlabel='Datapoint')
axs[2].set(xlabel='Datapoint')
#
axs[0].plot(myX_testA)
axs[1].plot(myX_testG)
axs[2].plot(y_pred_test)

# axs[0].plot(myX_trainA)
# axs[1].plot(myX_trainG)
# axs[2].plot(y_pred_train)

axs[0].legend(['a1','a2','a3'])
axs[1].legend(['g1','g2','g3'])
plt.show()
