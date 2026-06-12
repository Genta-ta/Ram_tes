# Ram_tes — `systest`

> Utilitas benchmarking RAM dan Storage (UFS/SSD) berkinerja tinggi untuk command-line.

---


> - Arsitektur `aarch64` (ARM 64-bit) → paket **Termux**
> - Arsitektur lainnya (x86_64, dll.) → paket **Ubuntu**

---

## 🛠️ Kompilasi Lokal

```bash
make        # Build binary
make clean  # Hapus hasil build
```

---

## 🚀 Cara Penggunaan

### Test RAM

```bash
systest ram [Ukuran_MB] [Jumlah_Loop]
```

| Parameter     | Deskripsi                          | Contoh |
|---------------|------------------------------------|--------|
| `Ukuran_MB`   | Ukuran blok memori yang diuji (MB) | `512`  |
| `Jumlah_Loop` | Berapa kali pengujian diulang      | `10`   |

**Contoh:** `systest ram 512 10`
→ Uji RAM 512 MB sebanyak 10 putaran

---

### Test Storage (UFS/SSD)

```bash
systest storage [Ukuran_MB]
```

| Parameter   | Deskripsi                            | Contoh |
|-------------|--------------------------------------|--------|
| `Ukuran_MB` | Ukuran data baca/tulis saat uji (MB) | `1024` |

**Contoh:** `systest storage 1024`
→ Uji baca/tulis storage dengan data 1024 MB

---

## 📋 Platform yang Didukung

| Platform         | Arsitektur | Paket         |
|------------------|------------|---------------|
| Android (Termux) | `aarch64`  | `*termux.deb` |
| Linux (Ubuntu)   | `x86_64`   | `*ubuntu.deb` |
