# Ram_tes (systest)

A high-performance command-line benchmarking utility for RAM and Storage (UFS/SSD).

## 🚀 Auto-Installation
Download and install the latest version automatically based on your system:

curl -sL https://api.github.com/repos/Genta-ta/Ram_tes/releases/latest | grep "browser_download_url" | grep "$(uname -m|grep -q aarch64 && echo termux || echo ubuntu)" | cut -d '"' -f 4 | xargs curl -LO && dpkg -i *$(uname -m|grep -q aarch64 && echo termux || echo ubuntu).deb && rm *.deb

## 🛠️ Local Compilation
To build manually:
- make
- make clean

## 📊 Usage Guide
- **RAM Test**: `systest ram [Size_in_MB] [Loops]`
- **Storage Test**: `systest storage [Size_in_MB]`
