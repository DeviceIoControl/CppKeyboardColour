# CLEVO Keyboard Colour Program (C++)

**A C++ version of the original "keyboard-colour-program" developed in C#.**

This is a cleaner, more organized, and efficient version of the initial program. It is designed to provide enhanced features for customizing CLEVO keyboards with **RGB** lighting, supporting both **3-zone** and **1-zone** keyboards. The program also includes a variety of animated effects to enhance your keyboard’s visual experience.

---

## 🎨 Current Features

- **Support for CLEVO keyboards:**
  - **RGB 3-zone keyboards**.
  - **RGB 1-zone keyboards**.
- **Predefined Animated Effects:**
  - 🌈 **Fading Colors:** Smooth color transitions (predefined themes).
  - 🎥 **Optimized Animations:** Enhanced visual effects using animation objects.

⚠️ **Important Note:** Ensure you run this program **as an administrator**, as Windows Management Instrumentation (WMI) requires administrative privileges to function properly.

⚠️ **Warning:** The predefined fading theme may utilize **15% to 20% of CPU** at certain times. This will be optimized in future updates.

⚠️ **Warning (2):** Ensure that the **InsydeDHCU.dll** file is in the same directory as `KBInsydeColours.exe` if you're using a **Single-Zone** keyboard.

---

## 🔧 Functional Commands

The following commands are supported and can be executed via the **Command Prompt**.

### 🖥️ General Syntax:
Navigate to the folder containing the executable files (e.g., `CppKeyboardColour/Test/Build/`) and run the commands in **administrator mode**. To execute the `.exe` files, prepend the `.\` before the command.

```bash
.\KBInsydeColours.exe theme [themeName]
```

### 🎨 Supported Themes:
- **Breathing Effect:**  
  ```bash
  .\KBInsydeColours.exe theme breathe
  ```
  🌬️ Enables a breathing effect (smooth pulsing transitions between colors).

- **Colourshift:**  
  ```bash
  .\KBInsydeColours.exe theme colourshift
  ```
  🔄 Alternates colors for **RGB** keyboards (designed for 3-zone keyboards, but compatible with 1-zone as well).

- **New Colour Breathe:**  
  ```bash
  .\KBInsydeColours.exe theme newcolourbreathe
  ```
  🌀 A custom theme designed for **@mehrshad315**, featuring an additional blue tone.

- **Colour Transform (Rainbow Sweep):**  
  ```bash
  .\KBInsydeColours.exe theme colourtransform
  ```
  🌈 Creates a rainbow sweep effect with smooth transitions.

- **Blink (Pulsating Blink):**  
  ```bash
  .\KBInsydeColours.exe theme blink
  ```
  ✨ Makes the keyboard lights blink in a pulsating pattern.

---

## 🛠️ How to Use

1. Navigate to the folder containing the executable files:
   ```
   CppKeyboardColour/Test/Build/
   ```

2. Open a **Command Prompt** in Administrator mode:
   - Search for "Command Prompt" in the Windows search bar.
   - Right-click and select **Run as Administrator**.

3. **Ensure that the **InsydeDHCU.dll** file is in the same directory as `KBInsydeColours.exe` if you're using a **Single-Zone** keyboard**.

4. Run the desired command using the syntax:
   ```
   .\KBInsydeColours.exe theme [themeName]
   ```

Example:  
To activate the breathing effect, run:
```bash
.\KBInsydeColours.exe theme breathe
```

---

## 📋 Requirements

- **Compatible CLEVO keyboards:**
  - **RGB 1-zone** or **3-zone** lighting.
  - For **1-zone keyboards**, the **InsydeDHCU.dll** file must be in the same directory as `KBInsydeColours.exe`.
- **Administrator Permissions:** Ensure the program is run as administrator to avoid WMI failures.

---

## 📌 Final Notes

- This is an initial version of the program, and more features (including better optimization for 1-zone keyboards) will be added in future updates.
- Feedback, suggestions, and contributions are highly appreciated to help improve the project.

---
