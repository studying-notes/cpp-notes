---
date: 2022-01-30T13:50:57+08:00  # 创建日期
author: "Rustle Karl"  # 作者

# 文章
title: "Clion与WSL设置"  # 文章标题
# description: "文章描述"
url:  "posts/cpp/docs/Clion与WSL设置"  # 设置网页永久链接
tags: [ "cpp" ]  # 标签
series: [ "C/C++ 学习笔记"]  # 文章主题/文章系列
categories: [ "学习笔记"]  # 文章分类

# 章节
weight: 20 # 排序优先级
chapter: false  # 设置为章节

index: true  # 是否可以被索引
toc: true  # 是否自动生成目录
draft: false  # 草稿
---

https://nicolosonnino.it/clion-guide/#version-2021-and-newer

## CLion Installation

Create an educational account using your university email:

https://www.jetbrains.com/shop/eform/students

Download, install and login into CLion.

## Setup Windows Subsystem for Linux (WSL)

Open Windows Powershell in Admin mode by using **Win+X** shortcut and use the following command (In this guide we will install **WSL version 1**, this saves us a lot of troubleshooting. Feel free to try version WSL 2 if you like it)

```
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1628701092/clion-guide/powershell_zhvhcg.png)

Reboot your system

Choose your preferred distro (I suggest using Ubuntu because most of packages are updated and accessible, if you want a lightweight heavy distro use Debian) and download it from Microsoft Store.

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086145/clion-guide/31a005e092c4585e8f4f1_zbmvj0.png)

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086145/clion-guide/ApplicationFrameHost_gkN8zaUT22_gq5mgj.png)

Once installed, open it by searching it in Start Menu.

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086145/clion-guide/827e38e78d0afd13c1c66_ktmmne.png)

Create a UNIX user with a password (You need it later so choose one you can actually remember).

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086145/clion-guide/7f51bc6b960ca04554a0e_fjsfz6.png)

Update the distro with:

```
sudo apt update && sudo apt upgrade -y
```

## Package installation

Install packages with this command:

```
sudo apt install -y build-essential cmake gdb valgrind wget kcachegrind
```

## Configure CLion

Create a SSH profile with the following command (this assures that CLion connects to WSL):

```
wget https://raw.githubusercontent.com/JetBrains/clion-wsl/master/ubuntu_setup_env.sh && bash ubuntu_setup_env.sh
```

Open CLion, go to `File>Settings>Build, Execution, Deployment>Toolchains`, click on `+` and choose WSL.

### Version 2021 and newer

It should detect automatically your WSL distro and version like the following screenshot:

![here](https://res.cloudinary.com/s0nn1/image/upload/v1628701308/clion-guide/clion64_79rK7ZKtXv_qwaho3.png)

## Setup Valgrind on CLion

Go to `File>Settings`, search for Valgrind, set valgrind path (`/usr/bin/valgrind`) and all its arguments (view the FAQ guide).

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086145/clion-guide/01e17f519fbd54a499cee_kr4ptd.png)

Now you can run your program with Valgrind by clicking on the top right icon (I use Atom Material Icons plugin which I strongly recommend:

https://plugins.jetbrains.com/plugin/10044-atom-material-icons.

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086146/clion-guide/b6aaaef70d26aaf403c89_ecddo7.png)

## Redirect Input from file on CLion

Under `Edit Configurations` inthe top right corner you can change to redirect the input from file like the following images

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1628708815/clion-guide/clion64_6zEWxmRG7Z_jvdi4e.png)

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1628708815/clion-guide/clion64_A2YGQwLMiI_rkopbi.png)

## Setup WSL Terminal on CLion

If you want to run CLI commands directly into the project directory you can use the built-in terminal in CLion.

Go to `File>Seetings>Tools>Terminal`, under `Shell Path` you should already see the WSL terminal unless type the following :

```
wsl.exe
```

or this if you have multiple distros installed:

```
wsl.exe --distribution <distroName>
```

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1628708410/clion-guide/clion64_tG40WFVkEA_lth0jw.png)

## Setup WSL Xserver [Optional]

If you want to run kcachegrind, massif-visualizer or any Linux app with a GUI follow the next steps.

Open WSL, modify your `.bashrc` (`nano ~/.bashrc`) file and append this line at the end of the file:

```
export DISPLAY=:0
```

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623086931/clion-guide/wsl_DTJ8zdZG3A_vwcrdh.png)

This will forward your Linux GUI to the Xserver (installed later).

Download and install VcXsrv Xserver (any other Xserver is fine, I just prefer this one): https://sourceforge.net/projects/vcxsrv/files/latest/download

Launch it and choose **Multiple windows** (just continue, all the other options are not relevant for our purpose) and then press Finish.

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623087309/clion-guide/chrome_cK9jHj41Gq_brd5we.png)

![kek](https://res.cloudinary.com/s0nn1/image/upload/v1623087356/clion-guide/xlaunch_R7HHKhqYkN_t3pcsk.png)

You should see in the bottom right on the taskbar the Xserver icon indicating it’s active.

------

**NOTE**

Remember to run XLaunch after every reboot to use it again

------

## Troubleshooting GUI errors

**`cannot open shared object file: No such file or directory...`**

If you encounter the following error:

```
failed: libQt5Core.so.5: cannot open shared object file: No such file or directory
```

while running kcachegrind, fix it by executing the following commands:

```
sudo apt install -y binutils
sudo strip --remove-section=.note.ABI-tag /usr/lib/x86_64-linux-gnu/libQt5Core.so.5
```

**`Could not load the Qt platform plugin "xcb" in ""...`**

If you encounter the following error:

```
qt.qpa.xcb: could not connect to display :0
qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found.
This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.
```

Congratulations 🎉 you have installed WSL2! (naughty user, you have not followed my guide 😠!).

Replace the previous export with:

```
export DISPLAY=$(route.exe print | grep 0.0.0.0 | head -1 | awk '{print $4}'):0.0
```

If it does not work follow this guide (Firewall section only): [📖](https://github.com/cascadium/wsl-windows-toolbar-launcher#firewall-rules).
