
#ifndef Squares_hpp
#define Squares_hpp


#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include "CinderOpenCV.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <algorithm>
#include <vector>
#include <time.h>

using namespace cv;
class Squares
{
    
public:
    int N;
    int x1;
    int y1;
    int x2;
    int y2;
    int slowestChange;
    float ftrs;
    float r;
    float g;
    float b;
    clock_t start;
    clock_t end;
    double elapsed;
    std::vector <float> timeChange;
    virtual float count(ci::Rectf)=0;
    virtual float getDivisorOfSum()=0;
    virtual float max()=0;
    virtual void setN(int n)
    {
        N=n;
        
    }
    virtual float getMaxTime(){
        //gets the slowest time change value
        return slowestChange;
    }

    
    
    virtual void drawRect()
    {//for i,j etc.
        g=0;
        b=0;
        slowestChange=0;    //set up rate as 0
        start=clock();  //begin clock
        timeChange.clear(); //clear the vector
        
        int width=cinder::app::getWindowWidth()/N;   //set up width for each square
        int height=cinder::app::getWindowHeight()/N; //set up height for each square
       
 
        for(int i=0;i<=N;i++)
        {
            for(int j=0;j<=N;j++)
            {
                
                x1=i*width;
                y1=j*height;
                x2=width*(i+1);
                y2=height*(j+1);
                
                ci::Rectf curSquare = ci::Rectf(x1,y1,x2,y2);
               
              
                
                float sum = count(curSquare);   //count up instances in a square
                float getDivisorOfSum=sum/100;  //divide sum to be able to change color
                r=getDivisorOfSum*N*N*255;
         
                cinder::gl::color(r,g,b,.5); //set color to red
                cinder::gl::drawSolidRect(curSquare);   //draw square

                if(r!=0){   //if the square is red
                     end=clock();   //stop the clock
  
                    elapsed=(((double)(end-start))/ CLOCKS_PER_SEC) *100;   //calculate the time change
                    timeChange.push_back(elapsed);  //save the timechange to a vector

                }
               
                
            }
            
        }
        if(timeChange.data()){
            //if there is time changes, calculate the slowest time change
slowestChange= *std::max_element(timeChange.begin(),timeChange.end());

        }
        
    }

};


class SquaresFrameDiff : public Squares{    //frame diff class inherits functionality from squares
private:
    cv::Mat frameDiff;
    float s;
    int num;
    std::vector <float> allFeatures;
public:
    virtual void setN(int n)    //change n
    {
        num=n;
    }
    virtual void drawRect(cv::Mat b)
    {
        Squares::setN(num); //allows for n to change
        frameDiff = b;
        Squares::drawRect();    //creates and draws squares
        max();
    }
    
    virtual float count(ci::Rectf curSquare)    //passes in one rectangle at a time
    {
        s=0;
        allFeatures.clear(); //empty vector

        for(int o=x1; o<x2; o++){       //gets square boundaries
            for(int q=y1; q<y2;q++){
                
                s=s+frameDiff.at<u_int8_t>(q,o);    //adds up pixels
               
                allFeatures.push_back(s);   //saves pixels in vector
 
            }
        }
            
        return s;
    }
    
    float getDivisorOfSum()
    {
        
        float setColor=s/1000;  //divides pixels  for color
        cinder::gl::color(setColor*N*N*255,0,0,.5); //sets the color
     
        return 1;   //faux return. not used
    }
    

    
    virtual float max(){
        float maxm=0;
       
        if(allFeatures.data()){ //if the vector isnt empty

      maxm= *std::max_element(allFeatures.begin(),allFeatures.end());   //finds maximum pixel value for each square
           // std::cout<<"max"<<maxm<<std::endl;

         }
        
        return maxm;
        }
};






#endif /* Squares_hpp */

