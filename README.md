### 1000 Words
It's often said that a picture is worth a thousand words. In this case, it's worth a thousand 16-bit words.

This program takes 2000-byte text files and deterministically generates 50×40 PPM images.

Check out the ```examples``` folder for sample outputs. (Please note that these were generated during development from the same input with transformations hard-coded.)

### Usage
```
git clone https://github.com/hhaiyun/1000-words.git
cd 1000-words
c++ -o 1000words 1000words.cc
1000words.exe <INPUT>.txt
```

### Process
The file is hashed, and every character is mapped to an RGB triplet.

Modulo arithmetic is then used to extract parameters from the hash. Depending on these parameters, a combination of the following will be applied:

- harmonize_RGBs(): converts RGB to HSV, constrains hue/saturation/lightness, then converts back to RGB

- Pixel sort along each row

- Pixel sort along each column
