##Make mp4 video with FFmpeg and trace functions


### Part 1 - compile ffmpeg with 

```
git clone https://github.com/FFmpeg/FFmpeg
cd FFmpeg/
sudo apt install -y libx264-dev
sudo apt install -y libx265-dev
./configure --enable-static  --enable-libx264 --enable-gpl
make
```

Enagle gpl or you become "libx264 is gpl and --enable-gpl is not specified."
Install libx264 dev or you become "ERROR: x264 not found using pkg-config"


Convert images to mp4

```
./ffmpeg -r 1/2 -start_number 0 -i ./images/%02d.jpg -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4
```

