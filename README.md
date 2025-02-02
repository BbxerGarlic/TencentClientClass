https://github.com/user-attachments/assets/e76102f7-1b54-4ffb-b7d6-71856e1dc190

成果展示

https://github.com/user-attachments/assets/08d54336-028d-4a0f-bf3a-a3bec20bb427

鱼群模拟


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

## 第二周

### 网络同步

尝试了一下用蓝图+OnlineSession做一个局域网联机

#### 功能

![image-20241128015127434](https://github.com/user-attachments/assets/86e53d6a-210d-440b-ab78-74437f3ecb9c)


直连、会话搜索
没什么好说的，直接用的OnlineSession的接口

![image-20241128015253120](https://github.com/user-attachments/assets/819e41c1-1f2c-4263-b079-08c67d4caaff)


房间达到两个人就会开始倒计时，倒计时结束显示计分板

基本的网络同步、用PlayerState维护的分数，用GameInstance跨场景保存的名字，GameMode进行的流程控制，UMG计分板

以及作业要求的计分系统，一开始变小的方块就是重要方块

（图片左侧实际上是我用枪的模型代替了人物模型，折腾一晚上懒得导入其它模型了）

#### 坑

##### 生成实体只能在服务端

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212212208522.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212212240760.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212212302552.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212212314408.png)

在服务端生成后同步到客户端

##### UE蓝图的异步

![image-20241127115840119](https://github.com/user-attachments/assets/62dc1402-9040-46d0-a4b6-268ba226cf1e)

FindSessions是一个异步方法，所以在它后面同步输出Results的个数，会是0

![image-20241127120118888](https://github.com/user-attachments/assets/c2998e96-6aab-4f8a-a775-9d6162e75e3a)

这样输出就没问题

##### UE同步问题

这里出了很多问题，主要原因还是在一开始没搞懂他的同步机制和跨场景机制

![img](https://pic4.zhimg.com/v2-60783129f61eb507a45e6c66404079ef_1440w.jpg)

总结：同步方面应当尽量把客户端逻辑写在Controller的Event里，然后服务端广播，需要跨场景的重要信息可以使用GameInstance或者Subsystem进行存储（类似单例），也可以使用无缝加载



## 第三周

考试+乱七八糟的东西，鸽了（）

## 第四周

![image-20241212212426368](C:\Users\ekamer\AppData\Roaming\Typora\typora-user-images\image-20241212212426368.png)

### 登录界面

之前已经实现了基本的会话连接，此处直接用GameInstance维护一个本地的账号验证map就可以（服务器验证也是一个道理，图省事直接做成本地的了）

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212212749352.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212212958695.png)



### 加载界面

#### UI

先用UMG搓一个UI

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212213102472.png)

因为场景加载是离散的，为了好看一点就做个假进度条

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212213242353.png)

因为一直在按deltaTime插值，所以最后会越来越慢，只需要加载完成的时候填满就好了。

#### 主机

UE没提供OpenLevel的Async版本，要用流式加载，不过因为我这项目加载几乎是瞬间，就直接做个假进度条凑合凑合舒服一点就行

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212213848055.png)

#### 客户端

客户端使用JoinSession，同样是连接处理完毕后瞬间加入（加入后会自动销毁UI），这里直接同步创建一个进度条

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212213941975.png)

### 射击游戏操作面板

#### 改成射线检测

因为涉及击中目标准星要发生变化，所以生成子弹球就不太合适了

改为射线检测（在服务端）

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212214807192.png)

广播到客户端以显示弹道

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212214930887.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212214913983.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212215036896.png)

#### 生命值和子弹数

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212214238991.png)

依旧是先创建UI

生命值和子弹数依旧记录在PlayerState里

##### 生命值

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212215246776.png)

生命值很好处理，只有两个玩家，似了一个直接调用结束

##### 子弹数

因为之前UE给的模板直接把Fire跟输入绑定了，所以懒得改代码直接给Fire加一个判断就好

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212215619207.png)

又因为子弹数是写在蓝图里的，所以我们要开放给蓝图

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212220401144.png)

设定为虚函数，直接在蓝图类里继承写个判断

效果：

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212230426165.png)

##### 准星

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241212231742982.png)

没什么好说的，打到的时候通知给PlayerController再通知给UI

## 第五周

### 动画

上周已经做过了，这周微调了一下，加了个Died状态

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241225155511325.png)

### 敌人AI

稍微研究了一下行为树、黑板、AI感知

#### 行为树和黑板

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241225155648016.png)

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241225160337701.png)

#### 敌人Character和Controller

新建了个敌人Character，实现接口

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241225155933025.png)

Controller负责执行行为树和处理感知

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20241225160146926.png)

## 第十周

（期末好多事就鸽了，不过发现中间那几周的作业我基本之前就已经做完了）

### 鱼群模拟

不限引擎，所以用我最熟悉的Unity来做吧，再熟悉熟悉DOTS和SOA编程

#### 需求分析

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20250202230209585.png)

1.一个鱼群要有一个虚拟领袖：需要有一个组件或是bool值标记一条鱼是否是领袖。

2.鱼和鱼之间要有间距，鱼群和鱼群之间也要有间距：计算时要留出这些可调节的间距

3.最多鱼数（这个我想多调一点，测试以下DOTS性能）

4.性能优化：使用IJobEntity并行处理鱼的移动。性能数据：使用Unity自带的Stats显示和Profiler就可以看到Job的分配情况和主要性能瓶颈。

#### 数据结构

```c#
public struct FishData : IComponentData
{
    public int GroupId;     // 鱼群编号
    public float2 Velocity; // 当前速度（2D向量）
    public bool IsLeader;   // 是否为虚拟领袖
}
```

#### 算法

Wiki上对Boid规则三要素的阐述：

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20250202230652964.png)

Separation：若距离过近，则个体会尝试远离。

Alignment：若个体离群体过远，则尝试靠近中心。

Cohesion：个体会尝试匹配邻居的速度和方向。

#### DOTS

##### System：

作用：查询所有旧帧数据并将其分配给Job、调度Job

```c#
/// <summary>
/// 因为我们需要收集旧帧数据作为参考，用一个新的数据结构存储
/// </summary>
public struct FishInfo
{
    public int GroupId;
    public float2 Position;
    public float2 Velocity;
    public bool IsLeader;
}
[BurstCompile]
public partial struct FlockingSystem : ISystem
{
    private EntityQuery query;
    
    public void OnCreate(ref SystemState state)
    {
        //初始化query，用来计算鱼的数量，方便我们alloc
        query = state.GetEntityQuery(ComponentType.ReadOnly<FishData>(), ComponentType.ReadOnly<LocalTransform>());
    }

    public void OnUpdate(ref SystemState state)
    {

        int fishCount = query.CalculateEntityCount();

        // 为后续计算分配全局数据数组与每个Entity的index映射的HashMap
        // 为什么要用数组+索引映射？因为之后要涉及大量连续访问，HashMap缓存效率太低
        NativeArray<FishInfo> fishInfos = new NativeArray<FishInfo>(fishCount, Allocator.TempJob);
        NativeParallelHashMap<Entity, int> entityIndices = new NativeParallelHashMap<Entity, int>(fishCount, Allocator.TempJob);

        int index = 0;
        foreach (var ( fish, translation,entity) in SystemAPI.Query< FishData, LocalTransform>().WithEntityAccess())
        {
            entityIndices.TryAdd(entity, index);
            fishInfos[index] = new FishInfo
            {
                GroupId  = fish.GroupId,
                Position = new float2(translation.Position.x, translation.Position.y),
                Velocity = fish.Velocity,
                IsLeader = fish.IsLeader
            };
            index++;
        }

        // 运动参数，这里hardcode一下
        float deltaTime = SystemAPI.Time.DeltaTime;
        float neighborRadius = 20.0f; //能感知到多远的邻居
        float separationDistance = 5f; //安全距离，防止碰撞
        float alignmentWeight = 1.0f; //对齐行为的权重
        float cohesionWeight = 1.0f; //凝聚行为的权重
        float separationWeight = 1.5f;//分离行为的权重
        float leaderFollowWeight = 2.0f;//跟随领袖的权重
        float maxSpeed = 5.0f;//最大移速

        // 构造 IJobEntity 任务，并将全局数据传入
        var job = new FlockingJobEntity
        {
            FishInfos = fishInfos,
            EntityIndices = entityIndices,
            DeltaTime = deltaTime,
            NeighborRadius = neighborRadius,
            SeparationDistance = separationDistance,
            AlignmentWeight = alignmentWeight,
            CohesionWeight = cohesionWeight,
            SeparationWeight = separationWeight,
            LeaderFollowWeight = leaderFollowWeight,
            MaxSpeed = maxSpeed
        };

        // 调度 Job（使用ScheduleParallel并行更新所有的鱼）
        state.Dependency = job.ScheduleParallel(state.Dependency);
        
        //Job结束的时候销毁entityIndices（NativeParallelHashMap无法使用[DeallocateOnJobCompletion]自动销毁）
        state.Dependency = entityIndices.Dispose(state.Dependency);
    }
}
```

##### Job：

作用：对每条鱼分别执行逻辑判断和移动

```c#
[BurstCompile]
public partial struct FlockingJobEntity : IJobEntity
{
    /// <summary>
    /// 全局鱼数据数组
    /// </summary>
    [ReadOnly]
    [DeallocateOnJobCompletion] //Job结束后销毁
    public NativeArray<FishInfo> FishInfos;

    /// <summary>
    /// 从 Entity 到全局数据数组索引的映射
    /// </summary>
    [ReadOnly]
    public NativeParallelHashMap<Entity, int> EntityIndices;

    //所有运动参数
    public float DeltaTime;
    public float NeighborRadius;
    public float SeparationDistance;
    public float AlignmentWeight;
    public float CohesionWeight;
    public float SeparationWeight;
    public float LeaderFollowWeight;
    public float MaxSpeed;

    void Execute(Entity entity, ref FishData fish, ref LocalTransform translation)
    {
        // 找到自己的数据
        int index = EntityIndices[entity];
        FishInfo currentFish = FishInfos[index];

        // 旋转速度，直接hardcode
        float rotationSpeed = 10f;

        // 如果该鱼为领袖，单独计算，简单更新位置
        if (currentFish.IsLeader)
        {
            float2 newPos = currentFish.Position + currentFish.Velocity * DeltaTime;
            translation.Position = new float3(newPos.x, newPos.y, translation.Position.z);

            // 若速度足够大，则更新旋转
            if (math.length(currentFish.Velocity) > 0.001f)
            {
                // 插值旋转使它更平滑
                quaternion targetRotation = quaternion.RotateZ(math.atan2(currentFish.Velocity.y, currentFish.Velocity.x));
                translation.Rotation = math.slerp(translation.Rotation, targetRotation, DeltaTime * rotationSpeed);
            }
            return;
        }

        // 非领袖鱼，计算力：分离、对齐、聚合
        float2 separation = float2.zero;
        float2 alignment = float2.zero;
        float2 cohesion  = float2.zero;

        //自己同群的数目
        int neighborCount = 0;

        // 遍历所有鱼数据，计算同群邻居影响
        for (int i = 0; i < FishInfos.Length; i++)
        {
            if (i == index)
                continue;

            FishInfo other = FishInfos[i];
            float dist = math.distance(currentFish.Position, other.Position);

            // 对于同群鱼
            if (other.GroupId == currentFish.GroupId)
            {
                if (dist < NeighborRadius)
                {
                    alignment += other.Velocity;
                    cohesion += other.Position;
                    neighborCount++;
                } //凝聚和对齐
                if (dist < SeparationDistance)
                {
                    separation += (currentFish.Position - other.Position) / (dist + 0.0001f);
                } //分离
            }
            // 对于不同群鱼：采用较大范围内的分离，效果明显
            else
            {
                if (dist < SeparationDistance * 2.0f)
                {
                    separation += (currentFish.Position - other.Position) / (dist + 0.0001f);
                }
            }
        }

        if (neighborCount > 0)
        {
            alignment /= neighborCount;
            cohesion  /= neighborCount;
            // 聚合力：指向群体中心
            cohesion = cohesion - currentFish.Position;
        }

        // 寻找该鱼群的虚拟领袖（取第一个找到的领袖）
        float2 leaderForce = float2.zero;
        bool leaderFound = false;
        for (int i = 0; i < FishInfos.Length; i++)
        {
            FishInfo other = FishInfos[i];
            if (other.GroupId == currentFish.GroupId && other.IsLeader)
            {
                leaderForce = other.Velocity;
                leaderFound = true;
                break;
            }
        }
        if (!leaderFound)
        {
            leaderForce = float2.zero;
        }

        // 综合各个行为力
        float2 acceleration = alignment * AlignmentWeight +
                              cohesion  * CohesionWeight +
                              separation * SeparationWeight +
                              leaderForce * LeaderFollowWeight;

        float2 newVelocity = currentFish.Velocity + acceleration * DeltaTime;
        float speed = math.length(newVelocity);
        if (speed > MaxSpeed)
        {
            newVelocity = newVelocity / speed * MaxSpeed;
        }
        float2 newPosition = currentFish.Position + newVelocity * DeltaTime;

        // 更新鱼的速度和位置
        fish.Velocity = newVelocity;
        translation.Position = new float3(newPosition.x, newPosition.y, translation.Position.z);

        // 平滑旋转
        if (math.length(newVelocity) > 0.001f)
        {
            quaternion targetRotation = quaternion.RotateZ(math.atan2(newVelocity.y, newVelocity.x));
            translation.Rotation = math.slerp(translation.Rotation, targetRotation, DeltaTime * rotationSpeed);
        }
    }
}
```

#### 测试

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/image-20250202234607475.png)

上千只鱼也可以稳定在较高帧率

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/image-20250202234748168.png)

可以看到Job被分配到多个线程

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20250202234953363.png)

cpu高峰出现在Render上，由于我渲染层采用的是SpriteRender，在SRP Batcher的加持下可以看到Batch达到了三千多，Drawcall达到了二百多。优化的话可能要用到Entities Graphics Batcher，不过没了解太深，就这样吧。

![](https://raw.githubusercontent.com/BbxerGarlic/BbxerGarlic/main/20250202235225454.png)
