# LightFetch ⚙️  🇨

**LightFetch** is a fetch program written in pure C programming language. :)

## Important Information

**The program was created for fun :)**. But **I will still update it** and give new features (if needed to), as much as I can. 

**Preview:**

<img src="https://github.com/user-attachments/assets/1c41fa00-3a80-4e54-9faa-cd1bd516a350">

### So, what it does? 
You may already know what fetch programs are, but if not,I will tell here. 
Fetch programs and this aswell can show your  basic hardware information. Such as,
Your OS/Distribution, Kernel (Version of OS), Architecture(64, 32 bit...), Hostname;
GPU and CPU (Name and Vendor), etc...

### Why have I created it?  💭
The question why I wanted to create fetch program, is because 
I use fetch programs very often, as for example when I am trying new/old hardware, (playing with it), trying new Distributions / OSes, and just to see if everything on system works fine, if ram has been found and even more...

As why I created it, is because I wanted to dive in in C programming language (to expand my knowledge in it). And I wanted to see how fetch programs work, and where might be some difficulties. And I am being honest, I have learned a lot here. As I am only a beginner in C programming language (though I know Python pretty well :) ). 

### Why should I use THIS Fetch program?  👇
As why you may want to use this fetch program, is because it was being made to be very lightweight and have great performance (It means there will be no fancy stuff: images, fancy looking text, etc.). 
It is **Very Simple** designed. And also, because it was written by a person that only started to learn C :). 
Also it has *lightfetch.conf* file, where you can easily customize the output of the fetch program to your liking.
*Of course this project is just for fun and you can use any other Fetch program.* 

**( There are a lot of awesome Programs that are made by other people :D ) **



# Getting Started 

### Basic Installation

To install the program clone this repository in a folder of your choise on your pc. 
**Choose one of this options:**
### Cloning the repository [2 ways]

1. Installing using git clone in the directory of your liking                                       <-- [*] preferred way

   To clone in the repository open up a terminal. Change directory to your liking with ( cd ) command.
   And write following:
   ```sh
   git clone https://github.com/ValentinMENDIss/LightFetch
   ```
  
2. Installing zip file using a green button ( CODE ) and extracting to directory of your liking

   
### Post Installation

1. First to be able to run the code (for the GPU) **_you will need to download 'lshw'_** with your package manager. (Also, you need to be sure, that gcc compiler is installed, on Linux it is installed By DEFAULT. So you don't need to do anything...).

### Example:
```sh
# if your OS is Debian/Ubuntu-based
sudo apt install lshw

# if your OS is Arch-based
sudo pacman -S lshw
... # and so on
```
Nothing to be installed more :).

### Running the Code / Compile
Now you can just go to directory(folder) where it is installed and write following in the terminal to compile the program:
```sh
gcc main.c -o main 
```
3. **Run It**
To Run the code just type following in the same directory with the main file:
```sh
./main
```
Voila, everything works :)

...If you do have some troubles please read section below.


## Something does not work / I have a Problem (HELP)  🛟
If you have a problem, for example something does not work correctly, try to compile the main.c file with gcc, like following:
*gcc main.c -o main*

After this everything should be working fine. If not please submit the problem on the Github page, so I could help you :).


### What feature/s am I working on right now?
Right now I don't know what I could add to this fetch program, as I want this fetch program to **stay lightweight** and **contain only useful output**.

Of course **this fetch program will stay lightweight**, by configuring you can turn off or on the features that can impact the performance of code. The code that is turned off, will be not compiled, which means that it will not come in to the finishing application (*--> better response time of the code*). 

*This sounds Great :)*


### I hope you liked it as much as I did :)
And I hope that this fetch program will be useful for someone...


Best wishes,
Valentin :)
