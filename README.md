# Active-Display-Selection-for-Unreal-4
Contants C++ blueprint library for fast and easy Run time setting For multi-screen player to select Which Monitor for the game to run on

# Unreal Version
4.22

# Library Version
1.0.1

# Support OS
Linux & Windows

# IMPORTANT
Don't forget to include Modules in your Build.cs file.

# How to
1. Right Click on your Unreal Content Browser and select "Create C++ Classes".
2. Select "Blueprint Function Library" and rename it to "ActiveDisplayBPLibrary" or anything as you wish.
3. Copy code from BPLibrary.h and .cpp file into your header and cpp file.
4. Change the UActiveDisplayBPLibrary Class name to the one you created (Dont forget the capital U)
5. Complie and run.
6. In any blueprint, call out these functions as your desire (You should see them under Active Display Category):


    -- <b>Set To Active Display</b> --
    
    Takes one integer as index number of the monitor, e.g. (0 for first and 1 for secound monitor, depend on how you set up)
    
    -- <b>Get Active Display Number(s)</b> --
    
    Returns maximum number of monitor you have currently on
    
    -- <b>Cycle To Next Display</b> --
    
    Cycle through your displays, return to first display if it reach the end of the list.
    causion: This requires a Monitor Index as input and returns next Monitor index as out put, You have to save those variables into 
    UGameUserSettings to make it work properly, otherwise index resets after relaunch.
    
    # In Addition
    I'm working on more options and features. if you have any problem or if you need specific request, contant me
    
    # Log
    05/Jun/2019 Active Display Blueprint Library Repo Created. v1.0.0 added.
    
    08/Jun/2019 Removed some unnessesary codes to prevent compile errors
    
    04/Apr/2020 Commented some changes on code for Newer version of unreal
