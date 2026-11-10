# 🪟 AtLaT Game — Windows Version

Technical specification and build instructions for the Windows executable.

---

## 🛠️ Build Information

* **Target OS:** Windows 10 / 11 (`.exe`)
* **Compilation Environment:** Cross-compiled using **MinGW-w64** on **Arch Linux**
* **Build Tool:** x86_64-w64-mingw32-gcc (16.2.0)

---

## 🧩 Runtime DLL Dependencies

If you compiled the Windows version using MinGW on Linux, the executable depends on GCC runtime DLLs. Make sure the following files are located in the same directory as `AtLaT.exe`:

* **`libgcc_s_seh-1.dll`** — GCC exception handling and runtime support library.
* **`libstdc++-6.dll`** — GNU Standard C++ Library runtime (required for C++ features).
* **`libwinpthread-1.dll`** — POSIX threads implementation for Windows.
