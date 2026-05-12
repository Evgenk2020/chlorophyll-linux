[![Version](https://img.shields.io/badge/version-1.0.3-blue)](https://github.com/Evgenk2020/chlorophyll-linux)
[![Latest Release](https://img.shields.io/github/v/release/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/releases)
[![License](https://img.shields.io/github/license/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/blob/main/LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/commits)
[![Repo Size](https://img.shields.io/github/repo-size/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux)
[![Stars](https://img.shields.io/github/stars/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/stargazers)
[![Forks](https://img.shields.io/github/forks/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux/network/members)
[![Top Language](https://img.shields.io/github/languages/top/Evgenk2020/chlorophyll-linux)](https://github.com/Evgenk2020/chlorophyll-linux)


# Chlorophyll A and B maintenance

Lab utility for determining the maintenance of chlorophylls A and B in plant material
  
Run it with specified keys

```

chloro -d | -df [data...]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)

.sh file example to run in terminal

```SH

#!/bin/bash

echo "measurement 1"
chloro -d 1 25 3 1 1.256 0.8
echo ""

echo "measurement 2"
chloro -d 1.5 25 3 1 1.1 0.7
echo ""

exec $SHELL

```

.sh file example for writing to `.csv`

```SH

#!/bin/bash

chloro -df 1 25 3 1 1.256 0.8
chloro -df 1.5 25 3 1 1.1 0.7
chloro -df 1.3 25 3 1 0.9 0.6
chloro -df 2 25 3 1 0.965 0.65
chloro -df 1.5 25 3 1 1.025 0.6
chloro -df 1.5 25 3 1 0.984 0.625

exec $SHELL

```
<hr>

You need to be installed on your Linux system previously:

- GCC g++
- CMake

(Fedora/CentOS Stream)
- rpm-build

On Fedora based systems run
<br>

```SH

sudo dnf groupinstall "Development Tools"
sudo dnf install cmake
sudo dnf install rpm-build

```

On Debian based systems run
<br>

```SH

sudo apt update
sudo apt install build-essential
sudo apt install cmake

```

On other systems see the details of your distro

<hr>

<b>To compile and run the utility (Fedora/CentOS Stream)</b>

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/chlorophyll-linux

cd chlorophyll-linux

```

2. Build the Project with `.rpm` setup package for Fedora/CentOS Stream by default

```SH

./build.sh

cd build

```

3. Install `.rpm` package from build folder

```SH

sudo dnf install *.rpm

```

4. Run the application in terminal directly

```SH

chloro -h

```

<hr>

<b>If using either than Fedora/CentOS Stream</b>

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/chlorophyll-linux

cd chlorophyll-linux

```

2. Change the string `set(assemble_tgz OFF)` to `set(assemble_tgz ON)` in CMakeLists.txt

```SH

nano CMakeLists.txt

```

3. Build the Project

```SH

./build.sh

```

4. Move `.tar.gz` file from `build` folder to any folder and unpack it

5. Run the program to check it from unpacked folder

```SH

./chloro -h

```

For more convenience add the application path into `.bashrc` file

```SH

export PATH="$PATH:/path/to/application/folder"

```

This will allow you to run the application in terminal directly

```SH

chloro -h

```
