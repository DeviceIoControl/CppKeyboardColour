# CLEVO Keyboard Colour Program

**A command-line RGB Keyboard backlight control program for CLEVO & Tongfang based laptops.**

This is a cleaner, more organized, and efficient version of the initial program. It is designed to provide enhanced features for customizing CLEVO & Tongfang based laptop keyboards with **RGB** lighting, supporting devices with **1-zone**, **3-zone** keyboards and devices with **RGB Lightbars**. The program also includes a variety of animated effects to enhance your keyboard’s visual experience.

---

## 🎨 Current Features

- **Support for CLEVO & Tongfang based systems with the following RGB components:**
  - **RGB 3-zone keyboards**.
  - **RGB 1-zone keyboards**.
  - **RGB Lightbars**.
- **Predefined Animated Effects:**
  - 🌈 **Fading Colors:** Smooth color transitions (predefined themes).
  - 🎥 **Optimized Animations:** Enhanced visual effects using animation objects.
  - ⏱️ **Custom Speed:** Change the speed to make an animation faster or slower.
  
⚠️ **Important Note:** This application requests for **Administrator privileges**. Please ensure you accept the Windows UAC prompt, as Windows Management Instrumentation (WMI) requires this to function correctly.

⚠️ **Warning (1):** Certain themes may utilize **~15% of CPU** at certain times.

⚠️ **Warning (2):** Please ensure that the **InsydeDCHU.dll** file is in the same directory as `CLEVO_KeyboardColour.exe` if you're using a **Single-Zone** keyboard.

⚠️ **Warning (3):** Some anti-virus products may incorrectly flag this application as **malware** and quarantine the program. If this happens, **please add the application to the AV exclusion list**.

---

## ❓FAQ - Frequently asked questions:

**How do I request for support?** - *Please report it [here](https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose).*

**What systems are supported?** - *This program is built for laptops based off of the CLEVO / Tongfang ODM design - For a list of supported CLEVO Models, please take a look at the [releases](https://github.com/DeviceIoControl/CppKeyboardColour/releases/latest)*

**How do I get more themes?** - *Please create an issue and request for it [here](https://github.com/DeviceIoControl/CppKeyboardColour/issues)*

**Does this program have a GUI?** - *No. The intention of this program is to be a lightweight app to enable keyboard themes on your system without the need for the bloatware included with the Control Center. This program does not intend to be a complete replacement of the software shipped with your system.*

**How long does it take to add support for my system?** - *Depends on your device. In most cases (If GitHub notifications worked properly), I can add support for certain models of laptop and create a new release within an hour. On certain occassions (depending of the device) it can take 24-hours or more, but I will ensure communication with you to let you know when that is the case.*

**NOTE:** Please bear in mind, I am the sole developer for this project, and although on occassion there maybe a single code contribution, the majority of the time, it is *only me* adding support and servicing requests for this project. **Therefore some requests may take longer than expected, if I am not available. Thank you for your understanding!**

---

## 🔧 Functional Commands

The following commands are supported and can be executed via the **Command Prompt**.

### 🖥️ General Syntax:
Extract the program zip and run the commands **as an administrator**. To execute the `.exe` files, prepend the `.\` before the command.

```bash
.\CLEVO_KeyboardColour.exe theme [theme] --speed [speed] [--dmm] [--hide]
.\CLEVO_KeyboardColour.exe inbuilt [theme] [--dmm] [--hide] (3-Zone keyboards only)
.\CLEVO_KeyboardColour.exe backlight [on/off] [--dmm] [--hide]
.\CLEVO_KeyboardColour.exe colour [hexColour] [--dmm] [--hide]
.\CLEVO_KeyboardColour.exe colours [hexColour] [hexColour] [hexColour] [--dmm] [--hide] (3-Zone keyboards only)
.\CLEVO_KeyboardColour.exe lightbar [hexColour] [--dmm] [--hide]
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

### 🚥 Custom Lightbar Colour Operations:

- **Set lightbar colour to Red:**  
  ```bash
  .\CLEVO_KeyboardColour.exe lightbar 0xff0000
  ```
  ❤️ Turns the lightbar Red.

- **Set lightbar colour to Green:**
  ```bash
  .\CLEVO_KeyboardColour.exe lightbar 0x00ff00
  ```
  💚 Turns the lightbar Green.

- **Set lightbar colour to Blue:**  
  ```bash
  .\CLEVO_KeyboardColour.exe lightbar 0x0000ff
  ```
  💙 Turns the lightbar Blue.

This command works in the same way as the `colour` command - For more info, please read the 'Custom Colour Operations' section.

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
  .\CLEVO_KeyboardColour.exe theme sakuratransform
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

- **Colour Wave:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme colourwave
  ```
  🏄 Enables an RGB colour wave effect over the 3 keyboard zones (designed for 3-zone keyboards only!).

- **Awesome:**  
  ```bash
  .\CLEVO_KeyboardColour.exe theme awesome
  ```
  😎 Cycles through all of the supported animations for the device.

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

  **This is an optional argument, and it will default to the standard speed if not provided.**

---

### 💻 Device Monitor Mode:

  Device Monitor mode is a feature for power users and developers to display extended console output of the in-flight data that is sent to the device when performing keyboard operations.

  ```bash
  .\CLEVO_KeyboardColour.exe theme colourtransform --dmm
  ```
  Plays the requested 'colourtransform' theme, while the console outputs the in-flight data being processed by the device.

  ```bash
  .\CLEVO_KeyboardColour.exe theme colourtransform --speed 150 --dmm
  ```
  Plays the requested 'colourtransform' theme at 150% speed, while the console outputs the in-flight data being processed by the device.

  ```bash
  .\CLEVO_KeyboardColour.exe backlight on --dmm
  ```
  Turns off the backlight for all detected devices on the system, and outputs the in-flight data being processed by the device.

  **This is an optional argument, and will not display the extended console output if the argument is not provided.**

  ⚠️ **Warning:** This argument will have a performance impact when provided and is therefore only recommended for debugging purposes. 

---

### 🪄 Background Modes:

If you wish to run this program on (in the background), there are multiple approaches that can be used to hide the CLI Window. 

**On Startup (as a background application)**

 1. Adjust the command line in "Scripts\StartClevoKB.cmd" to play your favourite theme.
 
 2. Please run the "Scripts\RegisterClevoKbOnBoot.cmd" script **AS ADMINISTRATOR** and follow it's instructions. (Please use Scripts\UnregisterClevoKbOnBoot.cmd to deregister it from startup.)
 
 ⚠️ **WARNING:** This argument should not be used in conjunction with the "--dmm" (Device monitor mode) argument.
 
 **For hidden mode**

 1. Append the "--hide" argument to your requested theme command-line before launching.

**NOTE:** Please use Task Manager to locate close the application to play other themes.

⚠️ **WARNING:** This argument cannot be used in conjunction with the "--dmm" (Device monitor mode) argument.

---

## 🛠️ How to Use

1. Download the release which contains the version of the program that supports your system.

2. Open a **Command Prompt** in Administrator mode:
   - Search for "Command Prompt" in the Windows search bar.
   - Right-click and select **Run as Administrator**.

3. **Again, be sure that the **InsydeDCHU.dll** file is in the same directory as `CLEVO_KeyboardColour.exe` if you're using a **Single-Zone** keyboard**.

4. Run the desired command using the syntax:
   ```
   .\CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [argument] [--speed <speed>] [--dmm] [--hide]
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

To enable 'Device Monitor Mode' for the 'breathing' effect, run:
```bash
.\CLEVO_KeyboardColour.exe theme breathe --dmm
```
NOTE: This argument will have a performance impact when provided and is therefore only recommended for debugging purposes.

To activate the inbuilt 'Wave' effect, run:
```bash
.\CLEVO_KeyboardColour.exe inbuilt KB_MODE_WAVE
```
NOTE: This command does not support the `--once` argument.

⚠️ **Warning (1):** This will use the system's inbuilt themes, thus this application has no control over these types of themes.

⚠️ **Warning (2):** This is supported on 3-Zone keyboard ONLY.

To activate an effect to run in the background, add the `--hide` argument:
```bash
.\CLEVO_KeyboardColour.exe theme breathe --hide
```
NOTE: This will run the 'breathe' theme, and hide the command-line window. Please use Task Manager to locate close the application to play other themes.

To turn off the keyboard backlight, run:
```bash
.\CLEVO_KeyboardColour.exe backlight off
```
NOTE: This command does not support the `--once` argument.

---

## 📋 Requirements

- **Compatible CLEVO & Tongfang based devices:**
  - **RGB 1-zone** or **3-zone** lighting.
  - **RGB Lightbar** lighting.
  - For **1-zone keyboards**, the **InsydeDCHU.dll** file must be in the same directory as `CLEVO_KeyboardColour.exe`.
- **Administrator Permissions:** This program requests for administrator privileges. Please ensure you accept the Windows UAC prompt to avoid WMI failures.

---

## Legal / Disclaimer

**This is an unofficial, non-commercial project. CLEVO, Tongfang, Insyde and related names or binaries (except CLEVO_KeyboardColour.exe), are property of CLEVO. This project is not affiliated with, endorsed by, or sponsored by CLEVO, Tongfang or Insyde.**

---

## 📌 Final Notes

- Feedback, suggestions, and contributions are highly appreciated to help improve the project.
- Found an issue or a bug? Please report it [here](https://github.com/DeviceIoControl/CppKeyboardColour/issues).

---