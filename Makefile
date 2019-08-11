seg:
	g++ Segmentacion.cpp  -I/usr/local/include/opencv4/ -L/root/opencv/build/lib/ -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio -lopencv_imgcodecs -lopencv_core -lserial -o seg.bin
	
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/vlarobbyk/aplicaciones/Librerias/opencv-4.0.0/opencv4-installation/lib/
#export LD_LIBRARY_PATH
