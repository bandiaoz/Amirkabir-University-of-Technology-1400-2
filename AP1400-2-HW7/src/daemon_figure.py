import matplotlib.image as mpimg
import matplotlib.pyplot as plt

img = mpimg.imread(r"../resources/image.jpg")
fig = plt.figure()
ax1 = fig.add_subplot()
ax1.imshow(img)
ax1.axis("off")
plt.show()
