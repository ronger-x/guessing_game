# 数字竞猜游戏
一款运行在单片机上的数字竞猜游戏
## 运行环境
- Nebula Pi 单片机
- PlatformIO 平台
- CLion IDE
## 游戏规则
1. 开始游戏
2. 生成随机数
3. 用户竞猜随机数
4. 系统判断用户输入的数值是否正确
## Todo
[x] 随机数生成函数  
[x] 数码管展示随机数  
[ ] 红外遥控器输入  
[ ] 数码管展示用户输入的数字  
[ ] 红外遥控器控制程序  

## 其他
下载程序后无法运行请检查 `Settings` -> `Build,Execution,Deployment` -> `CMake` -> `Build type` 为 `stc89c52rc`(你的单片机型号)
![img.png](img.png)