# Mash Programming Language – Official Guide

Mash is a lightweight, general-purpose, interpreted programming language designed for simplicity and ease of use.

## 1. Download and Installation

### 🔹 Download Mash
Mash is available for Linux and Windows. You can download the latest version from the GitHub Releases page:
👉 [Mash Releases](https://github.com/Okaymisba/Mash/releases/tag/v1.0.0)

### 🔹 Install on Linux
1. Download the Linux package:
```sh 
wget https://github.com/Okaymisba/mash/releases/download/v1.0.0/mash-1.0.0-Linux.tar.gz
```

2. Extract the package:
```sh
tar -xvzf mash-1.0.0-Linux.tar.gz
```

3. Move Mash to `/usr/local/bin` for easy access:
```sh
sudo mv mash /usr/local/bin/
```

4. Run Mash:
```sh
mash
``` 

If it returns:
```
Usage: mash <script.msh>
```
It means Mash is successfully installed on your device.

# 2. Running a Mash Program

You can execute Mash scripts as follows:

1. Save your script in a file (e.g., `script.msh`):
```
x = 10;
y = x * 5;
print(y)
```

2. Run it using:
```
mash script.msh
```

# 3. Contributing
We welcome contributions! If you'd like to help improve this project, feel free to fork the repository, make your changes, and submit a pull request. If you find any issues or have suggestions, please open an issue.