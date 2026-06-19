## 🎮 Raylib Mobile Game — Android

A 2D Android game built with Raylib and C++, using **raymob** as the compatibility layer for Android. You control a circle with an orbiting satellite that acts as an attack hitbox — drag your finger to move and strike enemies.

 **Looking for the desktop (PC) version?** It is in a separate repository → https://github.com/kevinnach0/Orbit-Defender-PC

---

##  How to Play

* **Move:** Drag your finger across the screen to move your circle toward your touch point.
* **Attack:** While dragging, a red satellite orbits around you — this is your attack hitbox.
* **Enemies:** Red enemies move toward you. If they touch you, you lose health.
* **Combat:** If your satellite touches an enemy, it knocks them away.
* **Game Over:** If your health reaches zero, the game restarts.

---

##  Project Structure

```text
Orbit-Defender-Android/
└── app/
    └── src/
        └── main/
            └── cpp/
                ├── Engine/           # Game engine files
                ├── Game/             # Game-specific logic
                ├── deps/             # External dependencies
                ├── CMakeLists.txt    # Build configuration
                └── main.cpp          # Main entry point

```

---

##  How to Run on Android

You don't need to do anything special — Android Studio handles everything. Just follow these steps:

### 1. Prerequisites

* **Android Studio** installed.
* **NDK and CMake** installed via Android Studio (SDK Manager → SDK Tools).
* **Android Phone** with Developer Mode enabled.
* *Enable Developer Mode:* Go to Settings → About Phone and tap "Build Number" seven times. Then, in Settings → Developer Options, enable **USB Debugging**.



### 2. Connect Your Phone

Connect your phone to your computer via USB cable. When prompted on your phone, choose "File Transfer" or allow "USB Debugging."

### 3. Open the Project

Open Android Studio and select **Open** → choose the root folder of the project.

### 4. Run

Press the **▶ Run** button (or `Shift + F10`). Android Studio will compile the project and install it directly onto your phone. The game will appear on your screen in seconds. It's that simple!

---

## 🛠️ Dependencies

| Library | Description |
| --- | --- |
| **Raylib** | Simple and powerful 2D/3D graphics engine |
| **raymob** | Raylib Android compatibility layer |
| **Android NDK** | Native C++ compiler for Android |

---

## 🖥️ PC Version

This project has a sibling repository designed exclusively for Windows / Linux / macOS, without the Android dependencies or raymob — just pure Raylib.
👉 **https://github.com/kevinnach0/Orbit-Defender-PC**

The core mechanics are the same, but the PC project is easier to compile and modify if you want to experiment without connecting a phone.

---

##  Technical Notes

* **Language:** The project uses **C++17**.
* **Collision:** Body collision uses overlap separation with a 38px radius.
* **Satellite:** The orbital hitbox has a 20px radius and applies a knockback force of 688 px/s.
* **Damage:** Contact damage has a **0.4-second cooldown** to prevent enemies from draining your health in a single frame.
* **Physics:** Enemy separation is symmetric — both entities move apart equally when overlapping.
