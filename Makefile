all:
	gcc -Wall cv2ff.cpp -c -o cv2ff.o
	gcc -std=c++11 -Wall -ggdb cv2ff.o -lavformat -lavcodec -lswresample -lswscale -lavutil -lSDL -lm -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio -lopencv_imgcodecs -lpthread -lstdc++ -lopencv_dnn -o cv2ff
