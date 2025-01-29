<h1> Getting Started</h1>

<h2> STM32Cube IDE</h2>
We are working with the STM32F303K8 microcontroller for this project. STM32CubeIDE is what we will use to compile and flash our microcontroller with the latest firmware. It can also be used for developing code, but personally I prefer to use Visual Studio as my code editor and just use the IDE for compiling and flashing. It has a built-in debugger as well, which will allow us to get valuable information on memory and how our program is running.





To download STM32CubeIDE, go to the following link and install version **1.16.1** for your operating system: https://www.st.com/en/development-tools/stm32cubeide.html

<br>
<h2> Cloning the Repository </h2>

<h3> Setting up SSH </h3>

Before you can clone the repository, I will need your GitHub username to give you authorization to make changes. Regardless, you will need to set up SSH on your Github account. This takes at most two steps:

1. If you don't have any existing keys, you will need to generate a pair (https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

2. Add the SSH public key to your GitHub account (https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)


<h3> Cloning </h3>

**NOTE:** When you launch STM32CubeIDE, it will ask what directory to open from. Make sure you clone the repository into the workspace directory!
<br><br>
<img width="616" alt="image" src="https://github.com/user-attachments/assets/3004ec23-a040-4769-adc2-2cb2059d690b" />

<br><br>



To clone the repo, you need its URL. Navigate to the "Code" block and select the SSH URL and copy it to your clipboard.
<img width="1274" alt="image" src="https://github.com/user-attachments/assets/850d5104-f5fd-4840-b146-241222f45289" />
<br><br>

If on Windows, I recommend using the Git CLI. You can download it here: https://git-scm.com/downloads
<br>
Open the Git CLI, and use the `cd` command to set your PWD to the workspace directory that the STM32CubeIDE on your machine uses (see image above).
For example, I would type into the terminal `cd /Users/admin/STM32CubeIDE/workspace_1.16.1` <br><br>
<img width="566" alt="image" src="https://github.com/user-attachments/assets/958766b6-7663-4342-b33a-3f52c305fe20" />
<br><br>

Once in the directory, you can now clone the repository with the clone command! Type into your Git CLI: `git clone git@github.com:fleuryfrye/pushingPower.git` <br>
To confirm it worked properly, type in `ls` into your Git CLI and confirm "pushingPower" shows up. If it does, you can open the STM32CubeIDE and you will now be able to open the codebase.


<h1> Navigating the Codebase</h1>
While it may seem a bit overwhelming at first, it is quite simple. All the code we develop lives in the `Core` directory. `Core/Inc` is where all of the header files will be, and `Core/Src` is where all the source files are. I have written the drivers for everything relevant to our project such as GPIO, ADCs, SPI, etc. and they all live in the Core directory.
<br><br>
For simplicity, I've provided a HAL in `piezo.h/c`. If you're interested in how it works, you can dive into the abstraction layers, but you can just call the functions I've provided and trust that it works. For the signal modulation logic, ALL of the functions needed will be provided in piezo.h/c! Think of it as a libary.
<br><br>
I recommend putting all the logic for the signal modulation into `signal.h/c` to follow the existing structure of files, and including `piezo.h`.


<h1> Submitting Changes </h1>
todo

