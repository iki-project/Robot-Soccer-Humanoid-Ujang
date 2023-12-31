/*
 *
 *   Author: Bismillah AL-'AADIYAAT Juara LKR (Amin.... :) )
 *	 Jangan Lupa Berdoa Guys
 *
 */

#include <stdio.h>
#include <cmath>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <darwin/framework/StatusCheck.h>

#include <darwin/framework/MX28.h>
#include <darwin/framework/Head.h>
#include <darwin/framework/Action.h>
#include <darwin/framework/Walking.h>
#include <darwin/framework/BallFollower.h>
#include <darwin/framework/MotionStatus.h>
#include <darwin/framework/ImgProcess.h>
#include <darwin/framework/Magneto.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"

#include <darwin/linux/LinuxDARwIn.h>

double nilai_x;
bool awal=true;
bool pas = true;
int nilai_tendang;
double 	posX;
double 	posY;
double 	centerX;
double 	centerY;
double 	offsetX;
double	offsetY;
bool 	deteksi	= false;
bool	delta 	=false;
bool	alpha	= false;
bool 	beta = true;
bool	akhir	= false;
struct 	termios SerialPortSettings;
char 	buf[32]; 
int 	yawkotor;
int areabola;
int jumlah_nendang = 0;
double nilai_pan;

using namespace cv;
using namespace std;
using namespace Robot;

Point2D last_pos;
BallTracker::BallTracker() :
	ball_position(Point2D(-1.0, -1.0))
{
NoBallCount = 0;
}
 

BallTracker::~BallTracker()
{
}

BallFollower::BallFollower()
{
	m_NoBallMaxCount 	= 10;
	m_NoBallCount 		= m_NoBallMaxCount;
	m_KickBallMaxCount 	= 5;
	m_KickBallCount 	= 0;

	m_KickTopAngle 		= -5.0;
	m_KickRightAngle 	= -20.0; 
	m_KickLeftAngle 	= 20.0;  

	m_FollowMaxFBStep 	= 32.0; //awal 20
    m_FollowMinFBStep 	= 20.0; //awal 10
	m_FollowMaxRLTurn 	= 30.0; //awal 30
	m_FitFBStep 		= 8.0; //awal 7
	m_FitMaxRLTurn 		= 13.0;
	m_UnitFBStep 		= 0.5; 
	m_UnitRLTurn 		= 0.3;

	m_GoalFBStep 		= 0;
	m_GoalRLTurn		= 0;
	m_FBStep 			= 0;
	m_RLTurn 			= 0;
	DEBUG_PRINT 		= false;
	KickBall 			= 0;
	
	yaw_tolerance		= 10;
}

BallFollower::~BallFollower()
{
}

//double hasil;
//hasil = ball_position;
Point2D Last_Pos;
Point2D ball_pos;
//Point2D ball_pos;

int 	Start_Search	= 1;
int     start_search    = 1;
int 	mag				= 119;
double 	FB_move			= 0; 
bool 	geser;
int 	arah_serang, gawang_kawan, selisih_serang;
int 	a,b,c;

int detekbal = 0;
int angkat = 0;
double nilai_tilt;
double tilt_max;

#ifdef MX28_1024
#define MOTION_FILE_PATH    "../../Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../../Data/motion_4096.bin"
#endif

#define INI_FILE_PATH       "../../Data/config.ini"
#define SCRIPT_FILE_PATH    "script.asc"
#define U2D_DEV_NAME0       "/dev/ttyUSB0"
#define U2D_DEV_NAME1       "/dev/ttyUSB1"

LinuxCM730 linux_cm730(U2D_DEV_NAME1);
CM730 cm730(&linux_cm730);

void InisialisasiSerial()
{
	int serial = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_SYNC);
	tcgetattr(serial, &SerialPortSettings);
	cfsetispeed(&SerialPortSettings, B9600);
	cfsetospeed(&SerialPortSettings, B9600);
	SerialPortSettings.c_cflag &= ~PARENB;
	SerialPortSettings.c_cflag &= ~CSTOPB;
	SerialPortSettings.c_cflag &= ~CSIZE;
	SerialPortSettings.c_cflag |= 8;
}
void mundur()
{
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
	Walking::GetInstance()->Start();
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 34.0;
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 45.5;
	Walking::GetInstance()->BALANCE_ENABLE=true;
	Walking::GetInstance()->HIP_PITCH_OFFSET = 39.2;
    Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35;//foot heigh
	Walking::GetInstance()->X_MOVE_AMPLITUDE = -20;//maju mundur}
	//Walking::GetInstance()->A_MOVE_AMPLITUDE = 2;
	fprintf(stderr, "maju1\n");
}
void mundur1()
{
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
	Walking::GetInstance()->Start();
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 34.0;
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 45.5;
	Walking::GetInstance()->BALANCE_ENABLE=true;
	Walking::GetInstance()->HIP_PITCH_OFFSET = 39.2;
    Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35;//foot heigh
	Walking::GetInstance()->X_MOVE_AMPLITUDE = -20;//maju mundur}
	//Walking::GetInstance()->A_MOVE_AMPLITUDE = 2;
	fprintf(stderr, "maju1\n");
}
void mundur2()
{
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
	Walking::GetInstance()->Start();
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 34.0;
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 45.5;
	Walking::GetInstance()->BALANCE_ENABLE=true;
	Walking::GetInstance()->HIP_PITCH_OFFSET = 39.2;
    Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35;//foot heigh
	Walking::GetInstance()->X_MOVE_AMPLITUDE = -20;//maju mundur}
	//Walking::GetInstance()->A_MOVE_AMPLITUDE = 2;
	fprintf(stderr, "maju1\n");
}
void berhenti()
{
	Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
	Walking::GetInstance()->Start();
	//Walking::GetInstance()->HIP_PITCH_OFFSET = 33.0;
	//Walking::GetInstance()->P_OFFSET=-8.4;
	Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
	Walking::GetInstance()->BALANCE_ENABLE=true;	
	//Walking::GetInstance()->A_MOVE_AMPLITUDE = 8.0;
	Walking::GetInstance()->Z_MOVE_AMPLITUDE = 20.0;
	Walking::GetInstance()->X_MOVE_AMPLITUDE = 0;
	fprintf(stderr, "berhenti \n");
}

void Tendang()
{
//	MotionManager::GetInstance()->SetEnable(true);
    Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
    Action::GetInstance()->LoadFile((char*)MOTION_FILE_PATH);
    Action::GetInstance()->m_Joint.SetEnableBody(true, true);
//	Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
	//Head::GetInstance()->m_Joint.SetPGain(JointData::ID_HEAD_PAN, 8);
	//Head::GetInstance()->m_Joint.SetPGain(JointData::ID_HEAD_TILT, 8);
	//Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);	
}



 
 cv::Mat imgOriginal; 
 cv::Mat hsvImg;
 cv::Mat hslImg;
 cv::Mat bola;
 cv::Mat tiang;
 cv::Mat lapangan;
  


void BallFollower::Process()
{	
    Head::GetInstance()->MoveToHome();
	//Head::GetInstance()->MoveTracking();
    
	//Mat imgOriginal, hsvImg, threshImg, ciko, dilatet, sayang, kucing, crop1;


 const int FRAME_WIDTH = 320;
 const int FRAME_HEIGHT = 240;
   
   
 int lowH = 41;       // Set Hue
 int highH = 96;

 int lowS = 42;       // Set Saturation
 int highS = 255;

 int lowV = 0;       // Set Value
 int highV = 255;
	 
 int erotion_size = 3;
 int dilation_size = 0; 
 int dilasi = 0;
//-----------------------------------------------------

 int lowH1 = 0;       // Set Hue
 int highH1 = 32;

 int lowS1 = 11;       // Set Saturation
 int highS1 = 255;

 int lowV1 = 0;       // Set Value
 int highV1 = 255;	

 int erotion_size1 = 0;
 int dilation_size1 = 0; 		
//-----------------------------------------------------

    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
    

    // cv::namedWindow("Setting Bola", CV_WINDOW_AUTOSIZE);
	// cv::namedWindow("Setting Lapangan", CV_WINDOW_AUTOSIZE);
	// cv::namedWindow("Lapangan", CV_WINDOW_AUTOSIZE);
	// cv::moveWindow("Lapangan",0,0);


    	 /* Create trackbars in "threshImg" window to adjust according to object and environment.*/
	
			  cv::createTrackbar("LowH", "Setting Lapangan", &lowH, 179); //Hue (0 - 179)
			  cv::createTrackbar("HighH", "Setting Lapangan", &highH, 179);

			  cv::createTrackbar("LowS", "Setting Lapangan", &lowS, 255); //Saturation (0 - 255)
			  cv::createTrackbar("HighS", "Setting Lapangan", &highS, 255);
  
			  cv::createTrackbar("LowV", "Setting Lapangan", &lowV, 255); //Value (0 - 255)
			  cv::createTrackbar("HighV", "Setting Lapangan", &highV, 255);
			  
			  cv::createTrackbar("opening", "Setting Lapangan", &erotion_size, 255);
			  cv::createTrackbar("closing", "Setting Lapangan", &dilation_size, 255);
			  cv::createTrackbar("dilasi", "Setting Lapangan", &dilasi, 255);
			  //-------------------------------------------------------------------
			  
			  cv::createTrackbar("LowH", "Setting Bola", &lowH1, 179); //Hue (0 - 179)
			  cv::createTrackbar("HighH", "Setting Bola", &highH1, 179);

			  cv::createTrackbar("LowS", "Setting Bola", &lowS1, 255); //Saturation (0 - 255)
			  cv::createTrackbar("HighS", "Setting Bola", &highS1, 255);
  
			  cv::createTrackbar("LowL", "Setting Bola", &lowV1, 255); //Value (0 - 255)
			  cv::createTrackbar("HighL", "Setting Bola", &highV1, 255);
			
			  cv::createTrackbar("opening", "Setting Bola", &erotion_size1, 255);
			  cv::createTrackbar("closing", "Setting Bola", &dilation_size1, 255);
				
    while(true)
    {
		
		deteksi = false;
		cap >>imgOriginal;
		
		

		Action::GetInstance()->LoadFile(MOTION_FILE_PATH);		

		       
		cv::Mat gambarkopi = imgOriginal.clone();  
			  cv::cvtColor(imgOriginal, hsvImg, CV_BGR2HSV);      // Convert Original Image to HSV Thresh Image
			  

			  cv::inRange(hsvImg, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), lapangan);
			  

			// cv::GaussianBlur(lapangan, lapangan, cv::Size(3, 3), 0);   //Blur Effect
			 //------------------------------------------------------------------morphologi lapangan
			 //morphologi opening
			  Mat element = getStructuringElement(cv::MORPH_RECT,
              cv::Size(2 * erotion_size + 1, 2 * erotion_size + 1),
              cv::Point(erotion_size, erotion_size) );
				//erode(bola,bola,element1);
				morphologyEx(lapangan,lapangan,2,element);
			
			//morphologi closing
			Mat element1 = getStructuringElement(cv::MORPH_RECT,
              cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
              cv::Point(dilation_size, dilation_size) );
			  //dilate(bola,bola,element);
			  morphologyEx(lapangan,lapangan,3,element1);
			 
						 
					  
			//-----------------------------------------------------------------------------------------------find contour dan masking lapangan	
			
			//invert lapangan
			//cv::bitwise_not(lapangan,lapangan);
			
			
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			int largest_area = 0;
			int largest_contour_index = 0;
							
			findContours(lapangan, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

			//this will find largest contour
			for (int i = 0; i< contours.size(); i++) // iterate through each contour.
			{
				double a = contourArea(contours[i], false);  //  Find the area of contour
				if (a>largest_area)
				{
					largest_area = a;
					largest_contour_index = i;                //Store the index of largest contour
									
				}
			
			}
			//search for largest contour has end
							
			
			//------------------------------------------------------------------------------------------------masking lapangan 1
			Mat finale;
			Mat lapangan2 = lapangan.clone();
			Mat masking = Mat::zeros(lapangan2.rows, lapangan2.cols, CV_8UC1);
			//masking.setTo(Scalar(0,0,0));
			imgOriginal.copyTo(masking,lapangan2);
					
			
			
			//------------------------------------------------------------------------------------------------fill hole
			
			
			Mat im_floodfill = lapangan2.clone();
			floodFill(im_floodfill, cv::Point(0,0), Scalar(255));
			Mat im_floodfill_inv;
			bitwise_not(im_floodfill, im_floodfill_inv);
			Mat im_out = (lapangan2 | im_floodfill_inv);
		    //bitwise_not(im_out,im_out);
		    
		    //------------------------------------------------------------------------------------------------------masking lapangan 2
			Mat im_out2 = im_out.clone();
			 
			   //morphologi dilasi
			Mat element69 = getStructuringElement(cv::MORPH_RECT,
              cv::Size(2 * dilasi + 1, 2 * dilasi + 1),
              cv::Point(dilasi, dilasi) );
			 dilate(im_out2,im_out2,element69);
			 
			Mat masking3 = Mat::zeros(im_out2.rows, im_out2.cols, CV_8UC1);
			//masking.setTo(Scalar(0,0,0));
			imgOriginal.copyTo(masking3,im_out2);
		
			//--------------------------------------------------------------------------------------------------xxxx
		
			//--------------------------------------------------------------------------------------------------convert warna
			cv::cvtColor(masking3, hslImg, CV_BGR2HSV);      // Convert Original Image to HLS Thresh Image	
			cv::inRange(hslImg, cv::Scalar(lowH1, lowS1, lowV1), cv::Scalar(highH1, highS1, highV1), bola);
		   
		   //------------------------------------------------------------------------------------------------morphologi bola
			 //morphologi opening
			  Mat element_bola = getStructuringElement(cv::MORPH_ELLIPSE,
              cv::Size(2 * erotion_size1 + 1, 2 * erotion_size1 + 1),
              cv::Point(erotion_size1, erotion_size1) );
				//erode(bola,bola,element1);
				morphologyEx(bola,bola,2,element_bola);
			
			//morphologi closing
			Mat element_bola1 = getStructuringElement(cv::MORPH_ELLIPSE,
              cv::Size(2 * dilation_size1 + 1, 2 * dilation_size1 + 1),
              cv::Point(dilation_size1, dilation_size1) );
			  //dilate(bola,bola,element);
			  morphologyEx(bola,bola,3,element_bola1);
			 
			  
			  
		  
		    //-----------------------------------------------------------------------------------------------find contour bola
			    //invert bola
			//cv::bitwise_not(bola,bola);
			
			Rect bounding_rect;
			vector<vector<Point> > contours1;
			vector<Vec4i> hierarchy1;
			
			int largest_area1 = 0;
			int largest_contour_index1 = 0;

			findContours(bola, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
			
			vector<Moments> mu1(contours1.size()); //get moments
				
				
				for (int i = 0; i < contours1.size(); i++)
				{
					mu1[i] = moments(contours1[i], false);
				}
			
			//this will find largest contour
			for (int i = 0; i< contours1.size(); i++) // iterate through each contour.
			{
				double a = contourArea(contours1[i], false);  //  Find the area of contour
				if (a>largest_area1)
				{
					largest_area1 = a;
					largest_contour_index1 = i;                //Store the index of largest contour
					bounding_rect=boundingRect(contours1[i]); // Find the bounding rectangle for biggest contour
				deteksi = true;
				posX = mu1[i].m10 / mu1[i].m00;
				posY = mu1[i].m01 / mu1[i].m00;
				}

				//areabola = contourArea(contours1[0]);
				//cout <<"Area : "<<a<<endl;
			}
			//search for largest contour has end
			
			Mat gabung;
				cv::hconcat(imgOriginal,masking3,gabung);	
			
			if (contours1.size() > 0)
			{
				rectangle(gabung, bounding_rect,  Scalar(0,255,0),2, 8,0);

			}			
			//  cv::imshow("Setting Lapangan", lapangan);
			//  cv::imshow("Setting Bola", bola);
		    //  cv::imshow("Lapangan", gabung);
		     
		     StatusCheck::Check(cm730);
		     if(StatusCheck::cek_kondisi==2)
		     {
					m_NoBallMaxCount 	= 10;
					m_NoBallCount 		= m_NoBallMaxCount;
					m_KickBallMaxCount 	= 5;
					m_KickBallCount 	= 0;
		
					m_KickTopAngle 		= -5.0;
					m_KickRightAngle 	= -20.0; //awal -30
					m_KickLeftAngle 	= 20.0;  //awal 30

					m_FollowMaxFBStep 	= 25.0; 
					m_FollowMinFBStep 	= 20.0;
					m_FollowMaxRLTurn 	= 30.0; // awal 20
					m_FitFBStep 		= 7.0;
					m_FitMaxRLTurn 		= 13.0;
					m_UnitFBStep 		= 0.5; //1
					m_UnitRLTurn 		= 0.3;

					m_GoalFBStep 		= 0;
					m_GoalRLTurn		= 0;
					m_FBStep 			= 0;
					m_RLTurn 			= 0;
					DEBUG_PRINT 		= false;
					KickBall 			= 0;
	
					yaw_tolerance		= 10;
				

				Point2D Last_Pos;
				Point2D ball_pos;
//Point2D ball_pos;

				Start_Search	= 1;
				start_search    = 1;


				detekbal = 0;
				angkat = 0;
				nilai_pan=0;
				
				awal=true;
				MotionManager::GetInstance()->SetEnable(true);
				Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
				Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
				
			    StatusCheck::cek_kondisi=1;
			    return;
			 }
		   

	if(deteksi==false)
		{
			posX = -1;
			posY = -1;	
			//Walking::GetInstance()->Stop();
			if(NoBallCount > NoBallMaxCount)
			{	
				if(offsetX>0 && offsetY>0)
				{
					 start_search=1;//kiri atas
					 Walking::GetInstance()->X_MOVE_AMPLITUDE=0;
				 }
				else if(offsetX<0 && offsetY>0)
				{
					 start_search=2;//kanan atas
					 Walking::GetInstance()->X_MOVE_AMPLITUDE=0;
				 }
				else if(offsetX<0 && offsetY<0)
				{
					 start_search=6;//kanan bawah
					 Walking::GetInstance()->X_MOVE_AMPLITUDE=0;
				 }
				else if(offsetX>0 && offsetY<0) 
				{
					start_search=5;//kiri bawah
					Walking::GetInstance()->X_MOVE_AMPLITUDE=0;
				}
				else 
				{
					start_search=1;
					//Walking::GetInstance()->X_MOVE_AMPLITUDE=15;
				}
				//Walking::GetInstance()->X_MOVE_AMPLITUDE=15;				
				//Head::GetInstance()->SetStartSearch(start_search);
				Head::GetInstance()->Start=true;
				//fprintf(stderr,"Starsearch = %d \n",start_search);
				Head::GetInstance()->MoveTracking();
				NoBallCount++;
			}
			else
			{
				Head::GetInstance()->InitTracking(start_search);
			}	
		}		
	else
		{
			NoBallCount = 0;
				
			centerX = 190; //160
			centerY = 120; //120
			
			offsetX = (posX - centerX);
			offsetY = (posY - centerY);

			offsetX *= -1; // Invers0e X-axis, Y-axis
			offsetY *= -1;
			
			offsetX *= 0.14375; // pixel per angle
			offsetY *= 0.24167; // pixel per angle
			Head::GetInstance()->MoveTracking(offsetX, offsetY);

		}
		//cout << "ballx : " << offsetX << endl;
		//cout << "bally : " << offsetY << endl;
		fprintf(stdout, "posX  : %.3f, posY   : %.3f\n",  posX, posY);
		fprintf(stderr, "ballx : %.3f, bally : %.3f\n",  offsetX, offsetY);
			
if(DEBUG_PRINT == true)
		fprintf(stderr, "\r\r");

	if(posX == -1.0 || posY == -1.0)
		{
			KickBall = 0;
			move = 0;

			if(m_NoBallCount > m_NoBallMaxCount)
			{
				// can not find a ball
				m_GoalFBStep = 0;
				m_GoalRLTurn = 0;
			
				Head::GetInstance()->InitTracking(Start_Search);
				int Putar = Head::GetInstance()->GetPutar();
			
				if(Putar==0)
				{
					if(Walking::GetInstance()->IsRunning() == false)
					{
						//Walking::GetInstance()->Start();
					//	Walking::GetInstance()->P_OFFSET=-8.4;
						Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
					}
					else
					//Walking::GetInstance()->X_MOVE_AMPLITUDE=15;
				//	Walking::GetInstance()->P_OFFSET=-8.4;
					Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
				}
				else if(Putar==1)//kiri
				{
					//Walking::GetInstance()->X_MOVE_AMPLITUDE = 5; //15
				//	Walking::GetInstance()->P_OFFSET=-8.4;
					Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
					//Walking::GetInstance()->A_MOVE_AMPLITUDE = 10;
					//if(Walking::GetInstance()->IsRunning() == false) Walking::GetInstance()->Start();
				}
				else if(Putar==2)//kanan
				{
					//Walking::GetInstance()->X_MOVE_AMPLITUDE = 5; //15
				//	Walking::GetInstance()->P_OFFSET=-8.4;
					Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
					//Walking::GetInstance()->A_MOVE_AMPLITUDE = -10;
					//if(Walking::GetInstance()->IsRunning() == false) Walking::GetInstance()->Start();
				}
			
				if(DEBUG_PRINT == true)
					fprintf(stderr, "[NO BALL]");
			
			}
			else
			{
				if(offsetX>0 && offsetY>0) start_search=1;//kiri atas
				else if(offsetX<0 && offsetY>0) start_search=2;//kanan atas
				else if(offsetX<0 && offsetY<0) start_search=6;//kanan bawah
				else if(offsetX>0 && offsetY<0) start_search=5;//kiri bawah
				else start_search=1;
				
				//Head::GetInstance()->SetStartSearch(Start_Search);
				Head::GetInstance()->Start=true;
				//fprintf(stderr,"Starsearch = %d \n",Start_Search);
			
				m_NoBallCount++;
				if(DEBUG_PRINT == true)
					fprintf(stderr, "[NO BALL COUNTING(%d/%d)]", m_NoBallCount, m_NoBallMaxCount);
			} 
			 
		}

	else
		{
			Last_Pos=ball_pos;
			//posX=offsetX;
			//posY=offsetY;
			
			Head::GetInstance()->putar=0;
			m_NoBallCount = 0;	

			double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
			double pan_range = Head::GetInstance()->GetLeftLimitAngle();
			double pan_percent = pan / pan_range;
			cout<<"pan  : "<<pan<<endl;
			

			double tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
			double tilt_min = Head::GetInstance()->GetBottomLimitAngle();		
			double tilt_range = Head::GetInstance()->GetTopLimitAngle() - tilt_min;
			double tilt_percent = (tilt - tilt_min) / tilt_range;
			if(tilt_percent < 0)
			tilt_percent = -tilt_percent;
			cout<<"tilt : "<<tilt<<endl;	
		
	
	if(pan > m_KickRightAngle && pan < m_KickLeftAngle)
		{
			geser = false;
	
			if(tilt<=-11.0)//(tilt<= 10  && tilt >= 5)
			{
				
					cout<<"return"<<endl;
					m_FBStep = 0;
					m_RLTurn = 0;
					Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
					if(DEBUG_PRINT == true)
						fprintf(stderr, "[KICK]");
						berhenti();
						usleep(2000000);
						Tendang();
						usleep(1000000);
						Action::GetInstance()->Start(218); //aman 216
						usleep(8000000);
						return;
					/*	berhenti();
						usleep(2000000);
						mundur();
						usleep(15000000);
						berhenti();
						usleep(2000000); */
						
  				
			}
			else
			{
				geser = false;
				m_KickBallCount = 0;
				KickBall = 0;
				m_GoalFBStep = m_FollowMaxFBStep * tilt_percent;
				if(m_GoalFBStep < m_FollowMinFBStep)
					m_GoalFBStep = m_FollowMinFBStep;
				m_GoalRLTurn = m_FollowMaxRLTurn * pan_percent * 1.2;//1.8
				if(DEBUG_PRINT == true)
					fprintf(stderr, "[FOLLOW(P:%.2f T:%.2f>%.2f]", pan, tilt, tilt_min);
					detekbal=0;
					angkat =0;
			}
			
		}
	else
		{
			geser = false;
			m_KickBallCount = 0;
			KickBall = 0;
			m_GoalFBStep = 0;
			m_GoalRLTurn = m_FollowMaxRLTurn * pan_percent * 1.2;//1.8
			if(DEBUG_PRINT == true)
				fprintf(stderr, "[FOLLOW(P:%.2f T:%.2f>%.2f]", pan, tilt, tilt_min);
				detekbal=0;

		 }	

	//if(m_GoalFBStep == 0 && m_GoalRLTurn == 0 && m_FBStep == 0 && m_RLTurn == 0 && geser == false)
	if(m_GoalFBStep == 0 && m_GoalRLTurn == 0 && m_FBStep == 0 && m_RLTurn == 0)
		{
		if(Head::GetInstance()->GetPutar()<1)
		{
			if(Walking::GetInstance()->IsRunning() == true)
				Walking::GetInstance()->Stop();
			else
			{
				if(m_KickBallCount < m_KickBallMaxCount)
					m_KickBallCount++;
			}
		
			//if(DEBUG_PRINT == true)
				fprintf(stderr, " STOP");
		}
	}
	else
	{
		if(DEBUG_PRINT == true)
			fprintf(stderr, " START");

		if(Walking::GetInstance()->IsRunning() == false)
		{
			m_FBStep = 0;
			m_RLTurn = 0;
			m_KickBallCount = 0;
			KickBall = 0;
			Walking::GetInstance()->X_MOVE_AMPLITUDE = m_FBStep;
			Walking::GetInstance()->A_MOVE_AMPLITUDE = m_RLTurn;
			Walking::GetInstance()->Start();			
		}
		else
		{
			if(detekbal == 0)
			{
				
				//aaaaaaaaaaaaaaaaaaaaa
				cout << "Bola terdeteksi ()"<<endl;
			//	Walking::GetInstance()->X_MOVE_AMPLITUDE=35;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 18.0;
				Walking::GetInstance()->HIP_PITCH_OFFSET = 38.8;
				Walking::GetInstance()->BALANCE_ENABLE=true;
			//	Walking::GetInstance()->A_MOVE_AMPLITUDE = 8.0;
			//	Walking::GetInstance()->P_OFFSET=-8.5;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 30;
				//Walking::GetInstance()->Y_OFFSET =59;
				
				
			if(m_FBStep < m_GoalFBStep)
				m_FBStep += m_UnitFBStep;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 18.0;
			else if(m_FBStep > m_GoalFBStep)
				m_FBStep = m_GoalFBStep;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 18.0;
				
			if( (m_RLTurn >= (m_FollowMaxRLTurn) && m_RLTurn > 0) || (m_RLTurn <= (-m_FollowMaxRLTurn) && m_RLTurn < 0))
			{
				//fprintf(stderr,"Rl Turn : %f \n",m_RLTurn);
				FB_move= m_FBStep - 1;
				fprintf(stderr,"Maju lurus : %f\n",m_RLTurn);
				Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;
			}
			else FB_move= m_FBStep;
			FB_move+=1;//kalibrasi dari setting walk tunner
			//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;
			fprintf(stderr,"Zmove 35\n",m_RLTurn);
			/*if (FB_move >=0)
			{
				if (FB_move<=3)
				{
					Walking::GetInstance()->P_OFFSET=-8.0;
					Walking::GetInstance()->Z_MOVE_AMPLITUDE = 42;
					Walking::GetInstance()->HIP_PITCH_OFFSET = 29.3;
				}
				else
				{
					Walking::GetInstance()->Z_OFFSET = 42.5;
					Walking::GetInstance()->HIP_PITCH_OFFSET = 29.6;
					Walking::GetInstance()->P_OFFSET=-8.5;
				}
					
					
			}*/
			
			
	//		else if (FB_move <=15)
		//	{
			//	Walking::GetInstance()->P_OFFSET=-6.3;
			//	Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;
				//Walking::GetInstance()->HIP_PITCH_OFFSET = 26.5;
		//	}
			Walking::GetInstance()->X_MOVE_AMPLITUDE = FB_move;
			
			//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;
	
	/*
		if(FB_move>=5)
		{
			Walking::GetInstance()->A_MOVE_AMPLITUDE =-15;
			}
			else
			{Walking::GetInstance()->A_MOVE_AMPLITUDE = m_RLTurn;
				}
	
	*/
		if (m_FBStep >=1 && angkat ==0)
				{
				Walking::GetInstance()->A_MOVE_AMPLITUDE = m_RLTurn;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;
				//Walking::GetInstance()->P_OFFSET=-7.9;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.5;
				//Walking::GetInstance()->HIP_PITCH_OFFSET = 29.0;
				}
				else
				{
				Walking::GetInstance()->A_MOVE_AMPLITUDE = m_RLTurn;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;
				//Walking::GetInstance()->P_OFFSET=-7.6;
				//Walking::GetInstance()->P_OFFSET=-7.9;
				//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.5;
				//Walking::GetInstance()->HIP_PITCH_OFFSET = 29.0;
			   // 				

			    //Walking::GetInstance()->Z_OFFSET=68;
			    }
	
			if(m_RLTurn < m_GoalRLTurn)
				m_RLTurn += m_UnitRLTurn;
			else if(m_RLTurn > m_GoalRLTurn)
				m_RLTurn -= m_UnitRLTurn;
			
			Walking::GetInstance()->A_MOVE_AMPLITUDE = m_RLTurn;
			//Walking::GetInstance()->Z_MOVE_AMPLITUDE = 35.0;

			if(DEBUG_PRINT == true)
				fprintf(stderr, " (FB:%.1f RL:%.1f)", m_FBStep, m_RLTurn);
			}
		}
	}

	if (waitKey(30) == 27)
		{
				cout<<"keluar"<<endl;
				break;
		}
	}
}
}
