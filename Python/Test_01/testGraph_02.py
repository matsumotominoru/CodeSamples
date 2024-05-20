# ライブラリのインポート
import matplotlib.pyplot as plt
import numpy as np

# グラフとして描画するデータ
x = np.arange(0, 10, 0.1)
y = 4 ** x

# グラフのタイトル、軸ラベルを編集
plt.title("Exponential function to the base 4")
plt.xlabel("x")
plt.ylabel("y")

# グラフを描画
plt.plot(x, y, lineStyle="dashed") #破線のグラフを書く
plt.show()