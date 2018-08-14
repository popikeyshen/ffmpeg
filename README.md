# Streaming opencv image with ffmpeg

In this repository i will show and code example of ffmpeg streaming an OpneCV image and difference between ffmpeg pipeline with banchmarks.

## How to use ffmpeg

[ffmpeg](https://www.ffmpeg.org/) - is an complete, cross-platform solution to record, convert and stream audio and video. He exist a very long time and includes many algorithms, so I will be not surprised if you use it in your pipelines.

### 1. ffmpeg direct streaming
First example is an streaming example directly from video device **/dev/video0** (in this example it is my notebook webcam but it can be your videofile)

```
ffmpeg -f video4linux2 -i /dev/video0 -f rtp_mpegts  rtp://127.0.0.1:1234
```
You can test the stream with ffplay or VLC
1. ffplay rtp://127.0.0.1:1234
2. VLC (media->network stream)

![This stream will use 36.4% CPU](image1.jpg) 
And this is how the streaming process look like

          _____________              ______________
         |             |            |              |
         |Video device |  demuxer   | encoded data |   decoder
         | /dev/video0 | ---------> | packets      | -----+
         |_____________|            |______________|      |
                                                          v
                                                      _________
                                                     |         |
                                                     | decoded |
                                                     | frames  |
                                                     |_________|
                ________             ______________       |
               |        |           |              |      |
               | output | <-------- | encoded data | <----+
               | file   |   muxer   | packets      |   encoder
               |________|           |______________|

This is tested on my notebook with **7th Gen CORE i5** but wee need use this with an OpenCV

### 2. ffmpeg OpenCV streaming pipeline

We can use an ffmpeg pipeline to stream an opencv image. This is a easiest pipeline - send an OpenCV Mat image data to stdout.

```
./cv | ffmpeg -f rawvideo -pixel_format rgb24 -video_size 640x480  -i - -f rtp_mpegts  rtp://127.0.0.1:1234
```
This stream will use 57.4% CPU and will stream not as expected 30fps but 16fps 
Yes! Stdout is very slow! Of course we can use faster write method - named pipe, unnamed pipe or socket pipeline, etc..  to ffmpeg. But it will alltime slower than direct streaming in p.1

### 3. Compiling ffmpeg with OpenCV

The efficientest way to stream with OpenCV code with ffmpeg and without pipelines. If we use this way we can abbadon double conversion. We can skip the demuxer, decoder and put the frame directly to encoder.

                ________            ______________	      _________
               |        |          |              |          |         |
               | OpenCV | -------->| encoded data | -------> | output  |
               |  Mat   |  encoder | packets      |  muxer   |	file   |
               |________|          |______________|          |_________|



```
./cv2ff
```
This stream will use 37.1% CPU

### 4. End

If we need more than 20% optimization and stream that is 10x faster and use less than 5% CPU - it is real but we need to increase operations in code. As ideal - form the packets direct. If it's interresant or have questions - you can send message to my direct.

### How to compile and install ffmpeg

If you wannt compile this examples use
```
make
```

You need to have installed libavcodec, libavformat, libavutil, libswscale, libswresample.

### Author

Viacheslav Popika
