## 第一周

### 源码编译

#### clone

遇到最大的问题就是Git拉取到一半报错： early EOF Fetch-pack: invalid index-pack output，拼尽全力无法战胜，只要depth大于1就拉取不了，最后也不了了之（只拉取depth=1的部分也能用不是吗。）

![image-20241122210104939](https://github.com/user-attachments/assets/4f4083b2-852d-4ef4-a9b3-42932f780939)


#### generate、build

这部分倒是没什么问题，编译了我九个小时，从半夜十二点半编译到早上十点，听知乎上说incredibuild很好用，折腾了一下发现需要在分布式环境内用，遂不了了之

![image-20241122210352074](https://github.com/user-attachments/assets/62d88560-b462-4216-81dc-f3945fee8f19)


（有几个库文件没引用好导致编译失败两次，当我拼尽两天终于看到这个logo的时候如释重负）

### 安装项目、配置VS

![image-20241122210702623](https://github.com/user-attachments/assets/96ac4fc9-7ae2-4e6b-9dac-e8bebde44e0d)


配置的时候发现插件要在epic商城对应的版本下，下载完了又发现

![image-20241122210800799](https://github.com/user-attachments/assets/4b7cb496-9328-42e7-8bb6-32c7150e91d7)


这个VS Integration Tool不支持我的5.5，心碎。

不过好在问题不大。

### 打包安卓端

遇到两个大问题：

第一个是Android Studio安装好SDK之后不知道为什么，不停弹出

![image-20241122211127407](https://github.com/user-attachments/assets/690b4eb4-29f9-4413-95a0-bdc9aea96013)


点了Yes还会继续弹，我看网上这一步已经自动帮你配好环境变量了，但是我的就是进行不下去，所以识别不出我的SDK

![image-20241122211215487](https://github.com/user-attachments/assets/9c592f30-7ae1-43be-bf5c-ed03635b2082)


解决方案就是，我重新设置了一下它的SDK路径，


![image-20241122211306713](https://github.com/user-attachments/assets/5e6f79ca-d79f-4d2d-9d3d-f99b305ca050)

能跑就行吧。

然后就是打包的时候疯狂给我爆这个错

![image-20241122210908183](https://github.com/user-attachments/assets/7f1dc442-18f6-4321-9e75-013f7e913c35)

![image-20241122210912073](https://github.com/user-attachments/assets/b3436e27-bcd5-40bc-96b0-18e1dee72c07)

发现是下载gardle的时候因为网络环境出错，于是自己在网上下载一版放到了gardle文件夹里

![image-20241122211558150](https://github.com/user-attachments/assets/fb0f75d4-5ec7-44a7-8bb5-8974659d72a6)

然后终于打包完成

![image-20241122211615855](https://github.com/user-attachments/assets/43b26aaa-c981-4504-96bb-3f2e8e45f232)
