# Ram_tes (systest)

A lightweight, high-performance, and modular command-line benchmarking utility written in C. It is designed to evaluate RAM bandwidth stability and physical storage (UFS/SSD) I/O throughput by directly bypassing the Linux page cache.

The project is integrated with a GitHub Actions Matrix Build pipeline to automatically generate native `.deb` installation packages for both **Termux (ARM64)** and **Ubuntu/Debian (x86_64)** environments.

---

## 📂 Project Structure
* .github/workflows/build.yml -> CI/CD GitHub Actions pipeline
* include/systest.h          -> Project header file
* src/main.c                 -> CLI parser and application entry point
* src/ram.c                  -> RAM benchmark module
* src/storage.c              -> Physical storage benchmark module

---

## ⚡ Key Features
* **Modular Architecture:** Clean code separation, making it easy to extend and maintain.
* **RAM Stress Tester:** Dynamically allocates large memory blocks to stress-test bandwidth and stability.
* **Storage Benchmark:** Measures raw hardware I/O performance by bypassing the page cache via fsync.
* **Universal Pipeline:** Automated cross-platform builds across different architectures.

---

## 🚀 Auto-Installation (Termux & Ubuntu)

You can automatically download and install the latest `.deb` package compatible with your device using this one-line command:

curl -sL https://api.github.com/repos/Genta-ta/Ram_tes/releases/latest | grep "browser_download_url" | cut -d '"' -f 4 | while read -r url; do if [ -d "/data/data/com.termux" ] && echo "$url" | grep -q "termux"; then echo "Detected Termux. Installing..."; curl -LO "$url"; pkg install ./*_termux.deb -y; rm ./*_termux.deb; break; elif [ ! -d "/data/data/com.termux" ] && echo "$url" | grep -q "ubuntu"; then echo "Detected Ubuntu/Debian. Installing..."; curl -LO "$url"; sudo apt update && sudo apt install ./*_ubuntu.deb -y; rm ./*_ubuntu.deb; break; fi; done

---

## 🛠️ Local Compilation (Manual)
If you prefer to compile the source code manually on your device:
* Build the binary: make
* Clean build files: make clean

---

## 📊 Usage Guide

Once installed, use the following commands globally in your terminal:

1. RAM Stress Test
   Format : systest ram [Size_in_MB] [Total_Loops]
   Example (Stress 5GB RAM for 10 loops):
   systest ram 5120 10

2. Storage Benchmark
   Format : systest storage [Size_in_MB]
   Example (Benchmark 2GB file I/O):
   systest storage 2048
