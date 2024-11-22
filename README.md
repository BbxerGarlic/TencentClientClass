## 第一周

### 源码编译

#### clone

遇到最大的问题就是Git拉取到一半报错： early EOF Fetch-pack: invalid index-pack output，拼尽全力无法战胜，只要depth大于1就拉取不了，最后也不了了之（只拉取depth=1的部分也能用不是吗。）

![image-20241122210104939](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122210104939.png)

#### generate、build

这部分倒是没什么问题，编译了我九个小时，从半夜十二点半编译到早上十点，听知乎上说incredibuild很好用，折腾了一下发现需要在分布式环境内用，遂不了了之

![image-20241122210352074](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122210352074.png)

（有几个库文件没引用好导致编译失败两次，当我拼尽两天终于看到这个logo的时候如释重负）

### 安装项目、配置VS

![image-20241122210702623](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122210702623.png)

配置的时候发现插件要在epic商城对应的版本下，下载完了又发现

![image-20241122210800799](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122210800799.png)

这个VS Integration Tool不支持我的5.5，心碎。

不过好在问题不大。

### 打包安卓端

遇到两个大问题：

第一个是Android Studio安装好SDK之后不知道为什么，不停弹出

![image-20241122211127407](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122211127407.png)

点了Yes还会继续弹，我看网上这一步已经自动帮你配好环境变量了，但是我的就是进行不下去，所以识别不出我的SDK![image-20241122211215487](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122211215487.png)

解决方案就是，我重新设置了一下它的SDK路径，

![image-20241122211306713](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122211306713.png)

能跑就行吧。

然后就是打包的时候疯狂给我爆这个错

![image-20241122210908183](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122210908183.png)

![image-20241122210912073](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122210912073.png)

发现是下载gardle的时候因为网络环境出错，于是自己在网上下载一版放到了gardle文件夹里

![image-20241122211558150](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122211558150.png)

然后终于打包完成

![image-20241122211615855](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241122211615855.png)
