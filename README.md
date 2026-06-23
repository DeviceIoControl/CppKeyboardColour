# CLEVO Keyboard Colour Program (C++)

**A C++ version of the original "keyboard-colour-program" developed in C#.**

This is a cleaner, more organized, and efficient version of the initial program. It is designed to provide enhanced features for customizing CLEVO keyboards with **RGB** lighting, supporting both **1-zone** and **3-zone** keyboards. The program also includes a variety of animated effects to enhance your keyboard’s visual experience.

---

## 🎨 Current Features

- **Support for CLEVO keyboards:**
  - **RGB 3-zone keyboards**.
  - **RGB 1-zone keyboards**.
- **Predefined Animated Effects:**
  - 🌈 **Fading Colors:** Smooth color transitions (predefined themes).
  - 🎥 **Optimized Animations:** Enhanced visual effects using animation objects.
  - ⏱️ **Custom Speed:** Change the speed to make an animation faster or slower.
  
  - **Note:** If you wish to run this program on startup (in the background), please run the "Scripts\RegisterClevoKbOnBoot.cmd" script **AS ADMINISTRATOR** and follow it's instructions. (Please use Scripts\UnregisterClevoKbOnBoot.cmd to stop running at startup) -- Also ensure you have confirmed your theme of choice prior to running the script and adjust the command line in "Scripts\StartClevoKB.cmd" to the requested theme.

⚠️ **Important Note:** This application requests for **Administrator privileges**. Please ensure you accept the Windows UAC prompt, as Windows Management Instrumentation (WMI) requires this to function correctly.

⚠️ **Warning (1):** Certain themes may utilize **~15% of CPU** at certain times.

⚠️ **Warning (2):** Please ensure that the **InsydeDCHU.dll** file is in the same directory as `CLEVO_KeyboardColour.exe` if you're using a **Single-Zone** keyboard.

⚠️ **Warning (3):** Some anti-virus products may incorrectly flag this application as **malware** and quarantine the program. If this happens, **please add the application to the AV exclusion list**.

---

## 🔧 Functional Commands

The following commands are supported and can be executed via the **Command Prompt**.

### 🖥️ General Syntax:
Extract the program zip and run the commands **as an administrator**. To execute the `.exe` files, prepend the `.\` before the command.

```bash
.\CLEVO_KeyboardColour.exe theme [theme] --speed [speed]
.\CLEVO_KeyboardColour.exe inbuilt [theme] (3-Zone keyboards only)
.\CLEVO_KeyboardColour.exe backlight [on/off]
.\CLEVO_KeyboardColour.exe colour [hexColour]
.\CLEVO_KeyboardColour.exe colours [hexColour] [hexColour] [hexColour] (3-Zone keyboards only)
```
---

### ⌨️ Backlight Operations: 

- **Turn Backlight Off:**  
  ```bash
  .\CLEVO_KeyboardColour.exe backlight off
  ```
  🖤 Turns off the keyboard backlight.

- **Default Backlight:**
  ```bash
  .\CLEVO_KeyboardColour.exe backlight on
  ```
  💙 Enables the default keyboard backlight colour (Solid Blue).

---

### ⌨️ Custom Colour Operations:

- **Set backlight colour to Red:**  
  ```bash
  .\CLEVO_KeyboardColour.exe colour 0xff0000
  ```
  ❤️ Turns the keyboard backlight Red.

- **Set backlight colour to Green:**
  ```bash
  .\CLEVO_KeyboardColour.exe colour 0x00ff00
  ```
  💚 Turns the keyboard backlight Green.

- **Set backlight colour to Blue:**  
  ```bash
  .\CLEVO_KeyboardColour.exe colour 0x0000ff
  ```
  💙 Turns the keyboard backlight Blue.

- **Set backlight colour to custom "Sakura Pink":**  
  ```bash
  .\CLEVO_KeyboardColour.exe colour 0xff6ea8
  ```
  🩷 Turns the keyboard backlight "Sakura Pink".

- **Set RGB colour to individual zones (3-Zone keyboards ONLY):**
  ```bash
  .\CLEVO_KeyboardColour.exe colours 0xff0000 0x00ff00 0x0000ff
  ```
  🌈 Sets the Left zone to Red, the middle zone to Green and right zone to Blue on the keyboard (3-Zone keyboards ONLY)
---

### 🎨 Supported Animations:

- **Breathing Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme breathe
  ```
  🌬️ Enables a breathing effect (smooth inhale/exhale transition pattern between colors).

- **Colourshift:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme colourshift
  ```
  🔄 Alternates colors for **RGB** keyboards (designed for 3-zone keyboards only!).

- **Fresh Breathe:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme freshbreathe
  ```
  🌀 A custom theme designed by **@mehrshad315**, featuring an additional blue tone.

- **Colour Transform (Rainbow Sweep):**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme colourtransform
  ```
  🌈 Creates a rainbow sweep effect with smooth transitions.

- **Blink (Pulsating Blink):**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme blink
  ```
  ✨ Makes the keyboard lights blink in a pulsating pattern.

- **Heartbeat (Double Pulsating Blink):**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme heartbeat
  ```
  💖 Makes the keyboard lights pulse red in a heartbeat pattern.

- **Sakura Transform (Pink & Violet colour sweep):**
  ```bash
  .\CLEVO_KeyboardColour.exe theme sakuratranform
  ```
  🩷 💙 Makes the keyboard lights sweep through various shades of Pink & Violet.

- **Sakura Sunset (Pink colour sweep):**
  ```bash
  .\CLEVO_KeyboardColour.exe theme sakurasunset
  ```
  🩷 Makes the keyboard lights transition through Sakura Pink & Sunset Pink colours.

- **Sunset Breathe:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme sunsetbreathe
  ```
  🌅 Enables a Sunset Pink breathing effect (smooth inhale/exhale transition pattern).

- **Pink Breathe:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme pinkbreathe
  ```
  🫁 Enables a Pink breathing effect (smooth inhale/exhale transition pattern).
---

### ⚙️ Inbuilt Themes (3-Zone Keyboards ONLY):

- **Breathing Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe inbuilt KB_MODE_BREATHE
  ```
  🌬️ Enables a breathing effect (Smooth inhale/exhale pattern on a single colour).

- **Wave Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe inbuilt KB_MODE_WAVE
  ```
  🌊 Enables a colour wave effect (Various colours transition from Left -> Mid -> Right zone of the keyboard).

- **Cycle Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe inbuilt KB_MODE_CYCLE
  ```
  🔄 Enables a breathing effect with various colour (Smooth inhale/exhale pattern over various colours).

- **Dance Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe inbuilt KB_MODE_DANCE
  ```
  🕺 Enables a flashy side-to-side dancing effect with various colours.

- **Flash Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe inbuilt KB_MODE_FLASH
  ```
  🔦 Makes the entire keyboard blink in various colours.

- **Tempo Effect:**  
  ```bash
  .\CLEVO_KeyboardColour.exe inbuilt KB_MODE_TEMPO
  ```
  🎶 Makes the keyboard lights 'dance' to the tempo of the music being played on the system (Keyboard tempo accuracy may vary on your system).

---

### ⏱️ Custom Speed:

- **Slower**
  ```bash
  .\CLEVO_KeyboardColour.exe theme colourtransform --speed 50
  ```
  🌈 Creates a slow rainbow sweep effect with smooth transitions at 50% speed.

- **Faster**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme colourtransform --speed 200
  ```
  🌈 Creates a fast rainbow sweep effect with smooth transitions at 200% speed.


**Setting speed is not required. You can leave it out, and it will default to the standard speed.**

---

## 🛠️ How to Use

1. Download the release which contains the version of the program that supports your system.

2. Open a **Command Prompt** in Administrator mode:
   - Search for "Command Prompt" in the Windows search bar.
   - Right-click and select **Run as Administrator**.

3. **Again, be sure that the **InsydeDHCU.dll** file is in the same directory as `CLEVO_KeyboardColour.exe` if you're using a **Single-Zone** keyboard**.

4. Run the desired command using the syntax:
   ```
   .\CLEVO_KeyboardColour.exe theme/inbuilt/backlight/colour/colours [argument] [--speed <speed>]
   ```

---

### Examples:
To activate the 'breathing' effect, run:
```bash
.\CLEVO_KeyboardColour.exe theme breathe
```

To activate an effect for a single iteration, add the `--once` argument:
```bash
.\CLEVO_KeyboardColour.exe theme breathe --once
```
NOTE: This will run the theme once, and stop. Use this command line if you want to experiment with the available themes.


To activate the inbuilt 'Wave' effect, run:
```bash
.\CLEVO_KeyboardColour.exe inbuilt KB_MODE_WAVE
```
NOTE: This command does not support the `--once` argument.

⚠️ **Warning (1):** This will use the themes that are programmed directly into your system, thus this application has no control over the colours these inbuilt themes use.

⚠️ **Warning (2):** This is supported on 3-Zone keyboard ONLY.


To turn off the keyboard backlight, run:
```bash
.\CLEVO_KeyboardColour.exe backlight off
```
NOTE: This command does not support the `--once` argument.

---

## 📋 Requirements

- **Compatible CLEVO keyboards:**
  - **RGB 1-zone** or **3-zone** lighting.
  - For **1-zone keyboards**, the **InsydeDHCU.dll** file must be in the same directory as `CLEVO_KeyboardColour.exe`.
- **Administrator Permissions:** This program requests for administrator privileges. Please ensure you accept the Windows UAC prompt to avoid WMI failures.

---

## 📌 Final Notes

- This is an initial version of the program, and more features (including better optimization for 1-zone keyboards) will be added in future updates.
- Feedback, suggestions, and contributions are highly appreciated to help improve the project.

---