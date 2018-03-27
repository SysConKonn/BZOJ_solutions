## BZOJ_solutions
我的一点BZOJ做题记录.

主要用来云端备份，也可以当作分享之类的。

## 题目分析
###  1001 狼抓兔子
+ 网络流加优化（堵路）， 然而我并不会。

+ *平面图转对偶图* ， 然后跑最短路。

### 1002 轮状病毒
好像是基尔霍夫矩阵。。。我不太会，看了个式子打完高精推掉就跑了。
### 1003 物流运输
最短路+DP

设cost[i][j]为第i天到第j天都走一条路的最短路。
设f[i]为考虑到第i天的最小花费。

可以推出：f[i] = min{f[j] + cost[j + 1][i] + k | 0 <= j < i} 。

将f[0 ]初始化为-k。将f[i](0<i<=k)初始化为cost[1 ][i] * i;
### 1004 Cards
  题中已经给出：任何洗牌方式的重复叠加得到的效果肯定会与给出的某个置换效果一样。
  
  =>那么就说明，题中给出的置换已经构成了一个置换群，那么就不用考虑多次叠加的效果。 

  需要注意一点就是还有一个置换是自己不变即(1, 2, 3, 4, 5...)

  然后就是一个burnside定理的模板题了。

  我们将每个置换f()写成循环的形式。

  比如说将置换（省去上面一排） (2, 1, 3) 写成循环 => (1 2)(3)

  很显然的，同一个循环中所有颜色必须要一样。

  那我们如果要求出总方案只需要将对于每一个置换的不动点个数算出然后再求平均值即可。

  然后问题就转化成了求每一个置换对应的不动点个数。

#### 如何求不动点个数
   可以使用一个背包。
   
   设f[i][j][k]为第一种颜色取i个，第二种颜色取j个，第三种颜色取k个的方案数。

   根据每个循环的大小更新f即可。

#### 需要注意的
   因为是平均数所以需要除以总置换个数。

   然后需要求一下乘法逆元。

### 1005 明明的烦恼
使用prufer编码然后组合数学上去乱搞推式子方案数就被推出来了。然后分解质因数手工约分。
最后拿个高精度吧剩下的乘起来就是的。

### 1007 水平可见直线
+ 半平面交。然而我并不太会。

+ 半平面交转化 *凸包* 求解。

### 1013 球形空间产生器
多维求球的球心，可以推一下由方程求球心的公式然后 *高斯消元* 解决。

### 1014 火星人prefix
Splay+二分答案+贪心

插入删除操作直接用splay维护，查询操作二分答案split区间hash

我觉得这题还可以加入翻转字符串区间。

### 1022 小约翰的游戏
SJ定理裸题，SJ定理的(DRA的)讲课资料在文件夹中。

### 1036 树的统计
+ 树链剖分裸题， 线段树维护重链即可。

+ 也可以使用LCT， 使用splay维护重链每次统计。

### 1042 硬币统计
dp+容斥原理

设F[i]为不考虑每种硬币的数量限制的情况下，得到面值i的方案数。则状态转移方程为：

F[i]=Sum{F[i-C[k]] | i-C[k]>=0 且 k=1..4}

为避免方案重复，要以k为阶段递推，边界条件为F[0 ]=1，这样预处理的时间复杂度就是O(S)。

接下来对于每次询问，奇妙的解法如下：根据容斥原理，

答案为得到面值S的超过限制的方案数 – 第1种硬币超过限制的方案数 – 第2种硬币超过限制的方案数 – 第3种硬币超过限制的方案数 – 第4种硬币超过限制的方案数 + 第1,2种硬币同时超过限制的方案数 + 第1,3种硬币同时超过限制的方案数 + …… + 第1,2,3,4种硬币全部同时超过限制的方案数。

当第1种硬币超过限制时，只要要用到D[1 ]+1枚硬币，剩余的硬币可以任意分配，所以方案数为 

F[ S – (D[1 ]+1)C[1 ] ]，当且仅当(S – (D[1 ]+1)C[1 ])>=0，否则方案数为0。
其余情况类似，每次询问只用问16次，所以询问的时间复杂度为O(1)。
### 1149 风铃Mobiles
一道水题， 模拟即可。

### 1150 数据备份
贪心， 每次取某个点将它左右的点删除并且与他缩起来。变成权值为l+r-now的点，优先队列维护。

### 1151 动物园zoo
状压DP，每个小朋友只能看到5个动物，将状态一一枚举计算是否喜欢即可。

### 1208 宠物收养所
splay模板题

用一棵Splay维护当前待在宠物店中的生物，很显然，对于任意一个时间两种生物的数量不可能同时大于1。 

每次加入生物判断是否与当前splay中维护的类型一致，一致则直接加入splay，否则找到前驱后继判断取哪个并将其删除。

### 1500 维修数列
splay模板题

但是较难。
需要维护的较多

+ c分别是结点左右儿子，fa是结点父亲
+ size是子树大小，sum是子树权值和，v是结点权值，mx是当前子树的最大子串和
+ lx是一个子树以最左端为起点向右延伸的最大子串和，rx类似
+ tag是结点的修改标记，修改值为v，rev是翻转标记

### 1588 营业额统计
二分查找树模板题。

找前驱后继

### 1878 HH的项链
莫队模板题。

将每个询问分块然后莫队处理。

### 2002 弹飞绵羊
LCT模板题

将i的父亲设为i位置的弹力+i，即i+k_i, 按照深度维护LCT。

如果修改某个点的弹力值相当与将当前位置做代表的值与父亲断开(cut(pos,fa[pos])), 然后再与新的到达节点相连(link(pos, pos+newk_pos))
### 2152 聪聪可可
点分治模板题。

处理跨过区间的答案就将子树到当前点的距离%3判断即可

答案为c[1] × c[2] × 2 + c[0] ^ 2

### 2190 仪仗队
用phi函数解的水题

### 2242 计算器
#### 第一问
就用快速幂解就行
#### 第二问
将x × y = z (mod p)转化为x=z × ine(y) (mod p)

然后利用p为质数的性质用费马小定理求出ine(y)解决问题。
#### 第三问
使用BSGS解决问题

[好博客](http://blog.csdn.net/clover_hxy/article/details/50683832)

### 2724 蒲公英
可以考虑用(区间众数)分块做。

首先离散化一下比较方便。

最初可能会有一个想法，是不是众数只可能是完整的块的众数，或者不完整的块出现的数呢？显然很容易得出反例。

应该是完整的所有块的众数，和不完整块中出现的数。

所以我们可以预处理f(i,j)表示第 i 块到第 j 块的众数（枚举 i 开个桶扫一遍）。

那么只要能快速得出一个数在某个区间内出现次数即可，每次只要比较至多2√n+1个元素的出现次数，这题就解决了。

对上面那段话的解释：就是先将连续的整块的贡献算出来，然后对于两侧(也可能两个端点在同一块)的每种颜色一一扫过去使用lower(upper)\_bound计算出在询问的这段区间中出现的次数更新答案。

由于没有修改，只要离散化以后，给每个数 x 开个vector，按顺序存下 x 出现的位置，每次询问 x 时把区间的左右端点放进对应 vector 二分一下即可。

根据均值不等式，可以算出分块大小大概是√(n/logn)

### 2818 Gcd
phi函数可以解决的水题。

如果满足gcd(x, y)=质数p_i,那么就是gcd(x/p_i, y/p_i)=1.

其实对于每一个质数p_i的贡献就是[1,n/p_i]的这段区间中互质的有序数对个数。

其实就是[1,n/p_i]中所有数的phi函数之和*2-1，减一是因为有序数对会在(1,1)时多算一次。

然后将phi函数取前缀然后将所有N之内的质数统计一遍贡献就出答案了。
### 3223 文艺平衡树
splay模板题， 分离区间打翻转标记，查询时pushdown即可。

### 3626 LCA
用树链剖分配线段树维护区间和然后转化成某个状态z点到根的路径大小最后用差分就行了。

[有用的博客](http://hzwer.com/3891.html)

[有用的博客2](https://www.cnblogs.com/JoeFan/p/4229141.html)


### 5212 历史
问题的本质是,给出一棵树,给定每一个点的 access 次数,计算轻重链切换次数的最大值。

首先可以考虑算出不修改(也就是初始的)答案。

假设节点i的子树access次数为sz[i],子树中(包括当前节点的值(不是这棵子树的权值和而是当前这一个节点的权值))sz最大的值为mx[i].

那么贡献为$\sum_{i=1}^{n} min(sz[i] - 1, 2 \times (sz[i] - mx[i])$ (证明见solution.pdf)

然后一个节点肯定只有一个节点满足$2\times sz[i] > sz[fa[i]]$使贡献为$2*(sz[i]-mx[i])$，那我们把这个节点设为它父亲的重儿子然后每次用类似于LCT的access的方法求答案。