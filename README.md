# alex_ws

This repo is the ROS1 Noetic Workspace for Alex (CG2111A).

1) Clone Repo
```
git clone https://github.com/ShengBin-101/alex_ws.git
```
2) Build Workspace
```
catkin_make
```
3) Source built binaries
```
source devel/setup.bash
```
3) Run launch file to visualize Alex in RVIZ
```
roslaunch alex rviz.launch
```


## Install Foxglove:
```
    sudo apt install ros-noetic-foxglove-bridge
```

To start foxglove websocket:
```
    roslaunch --screen foxglove_bridge foxglove_bridge.launch port:=8765
```

![image](https://github.com/ShengBin-101/alex_ws/assets/52733750/7bbd2431-71d5-4141-84cc-da8585d3f1eb)


TLS can be enabled, just need add path to certificates.
More info here: https://github.com/foxglove/ros-foxglove-bridge
