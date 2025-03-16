# QAbstractListModelExample
A C++ QML project implementing QAbstractListModel to manage QObject items dynamically, ensuring automatic UI updates in QML through property binding.

# Prerequisites

### 📌 Requirements
- **Qt 6.5 or later** (Ensure it is installed and accessible)
- C++ compiler (such as `g++`)
- CMake (if using a CMake-based project)

---

## 🔧 Installing Qt on Ubuntu

### **Option 1: Using the Qt Online Installer (Latest Version)**
This method provides the **latest** Qt version and extra tools like Qt Creator.

1️⃣ **Download the Qt Online Installer**  
   - Go to [Qt Downloads](https://www.qt.io/download-open-source)  
   - Click **"Download the Qt Online Installer"**  
   - Choose the **Linux** version (`.run` file)

2️⃣ **Make the installer executable**  
   ```
   chmod +x qt-unified-linux-x64-online.run
   ```

3️⃣ Run the installer
```
./qt-unified-linux-x64-online.run
```

# How to build

```
mkdir build
cd build
cmake ..
cmake --build .

```

# How to run

```
cd build
./QAbstractListModelExample

```
