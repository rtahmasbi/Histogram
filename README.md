
# Histogram
A C++ program to report basic statistics and to draw histogram with a simple reprisentation.


# Download
    git clone https://github.com/rtahmasbi/Histogram


# Compile
To compile Histogram, go to the directory and run the following commands:

    make


# Examples
## Example 1
```
histogram -f data.txt -c 1 --header
```

```
# NumSamples = 120000
# Min        = -3.0247
# Max        = 2.84795
# Mean       = -3.6781e-17
# Sum        = -4.41372e-12
# Variance   = 0.373387
# SD         = 0.611054
# Median     = 0.000635193
# each ∎ represents a count of 661
# --------------------------------------
[   -3.024704,    -2.679254) |        1| 
[   -2.679254,    -2.333804) |        8| 
[   -2.333804,    -1.988354) |       59| 
[   -1.988354,    -1.642904) |      371| 
[   -1.642904,    -1.297454) |     1537| ∎∎
[   -1.297454,    -0.952004) |     5220| ∎∎∎∎∎∎∎
[   -0.952004,    -0.606554) |    12055| ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎
[   -0.606554,    -0.261104) |    20802| ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎
[   -0.261104,     0.084346) |    26478| ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎
[    0.084346,     0.429796) |    24609| ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎
[    0.429796,     0.775246) |    16625| ∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎∎
[    0.775246,     1.120696) |     8257| ∎∎∎∎∎∎∎∎∎∎∎∎
[    1.120696,     1.466146) |     2972| ∎∎∎∎
[    1.466146,     1.811596) |      791| ∎
[    1.811596,     2.157046) |      184| 
[    2.157046,     2.502496) |       26| 
[    2.502496,     2.847947) |        5| 
# --------------------------------------
```

## Example 2
    cat file.txt | histogram

## Example 3
    histogram -f file.txt --summary var
    0.373387

## Example 4
```
histogram -f data.txt -c 1 --header  --dotsymbol "*"

# NumSamples = 120000
# Min        = -3.0247
# Max        = 2.84795
# Mean       = -3.6781e-17
# Sum        = -4.41372e-12
# Variance   = 0.373387
# SD         = 0.611054
# Median     = 0.000635193
# each * represents a count of 661
# --------------------------------------
[   -3.024704,    -2.679254) |        1| 
[   -2.679254,    -2.333804) |        8| 
[   -2.333804,    -1.988354) |       59| 
[   -1.988354,    -1.642904) |      371| 
[   -1.642904,    -1.297454) |     1537| **
[   -1.297454,    -0.952004) |     5220| *******
[   -0.952004,    -0.606554) |    12055| ******************
[   -0.606554,    -0.261104) |    20802| *******************************
[   -0.261104,     0.084346) |    26478| ****************************************
[    0.084346,     0.429796) |    24609| *************************************
[    0.429796,     0.775246) |    16625| *************************
[    0.775246,     1.120696) |     8257| ************
[    1.120696,     1.466146) |     2972| ****
[    1.466146,     1.811596) |      791| *
[    1.811596,     2.157046) |      184| 
[    2.157046,     2.502496) |       26| 
[    2.502496,     2.847947) |        5| 
# --------------------------------------
```
