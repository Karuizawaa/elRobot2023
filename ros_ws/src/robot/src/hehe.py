#!/usr/bin/env python
import cv2 as cv
import numpy as np
import random

# Lengkapi fungsi berikut ini agar dapat mengkonversi color space BGR ke grayscale
# kemudian kembalikan nilai intensitas warna grey pada koordinat pixel x, y
# gambar `img` merupakan sebuah sebuah gambar berwarna dengan color space BGR
def gray_at_pixel(img, x, y):
    image = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    grey = image[y, x]
    # tuliskan script anda disini

    # akhir script
    return grey

# Lengkapi fungsi berikut ini agar dapat mengkonversi color space BGR ke HSV
# kemudian kembalikan nilai hue pada koordinat pixel x, y
# gambar `img` merupakan sebuah sebuah gambar berwarna dengan color space BGR
def hue_at_pixel(img, x, y):
    image = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    hue = image[y,x,0]
    # tuliskan script anda disini

    # akhir script
    return hue

# Lengkapi fungsi berikut ini agar dapat mengkonversi color space BGR ke HSV
# kemudian kembalikan nilai saturation pada koordinat pixel x, y
# gambar `img` merupakan sebuah sebuah gambar berwarna dengan color space BGR
def saturation_at_pixel(img, x, y):
    image = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    saturation = image[y, x, 1]
    # tuliskan script anda disini

    # akhir script
    return saturation

# Lengkapi fungsi berikut ini agar dapat mengkonversi color space BGR ke HSV
# kemudian kembalikan nilai value/brightness pada koordinat pixel x, y
# gambar `img` merupakan sebuah sebuah gambar berwarna dengan color space BGR
def brightness_at_pixel(img, x, y):
    image = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    brightness = image[y, x, 2]
    # tuliskan script anda disini

    # akhir script
    return brightness

# Lengkapi fungsi berikut ini agar dapat mengkonversi color space BGR ke HSL
# kemudian kembalikan nilai lightness pada koordinat pixel x, y
# gambar `img` merupakan sebuah sebuah gambar berwarna dengan color space BGR
def lightness_at_pixel(img, x, y):
    image = cv.cvtColor(img, cv.COLOR_BGR2HLS)
    lightness = img[y, x, 1]
    # tuliskan script anda disini

    # akhir script
    return lightness

# Gunakan fungsi `main` untuk menguji-coba fungsi diatas
def main():
    print("=======================================")
    print("Exercise 2 - Color Space & Conversion")
    print("=======================================")
    
    bgr_img = cv.imread("./images/cat-image.jpg")
    # x = random.randint(0, bgr_img.shape[1])
    # y = random.randint(0, bgr_img.shape[0])
    x = 2
    y = 1
    gray = gray_at_pixel(bgr_img, x, y)
    hue = hue_at_pixel(bgr_img, x, y)
    sat = saturation_at_pixel(bgr_img, x, y)
    val = brightness_at_pixel(bgr_img, x, y)
    lig = lightness_at_pixel(bgr_img, x, y)

    print("Gray value at {", x, y, "} = ", gray)
    print("Hue value at {", x, y, "} = ", hue)
    print("Saturation value at {", x, y, "} = ", sat)
    print("Brightness value at {", x, y, "} = ", val)
    print("Lightness value at {", x, y, "} = ", lig)

if __name__ == "__main__":
    main()