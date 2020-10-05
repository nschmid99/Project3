
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

using namespace cv;
class Squares
{
    
public:
    int N;
    int x1;
    int y1;
    int x2;
    int y2;
    float ftrs;
    virtual float count(ci::Rectf)=0;
    virtual float getDivisorOfSum()=0;

    virtual void setN(int n)
    {
        N=n;
        
    }
    virtual float tally()=0;
    virtual float max()=0;
    
    
    virtual void drawRect()
    {//for i,j etc.
        
        int width=cinder::app::getWindowWidth()/N;   //set up width for each square
        int height=cinder::app::getWindowHeight()/N; //set up height for each square
        
        //do all the things to find the squares -
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
            //max();
                cinder::gl::color(getDivisorOfSum*N*N*255,0,0,.5); //set color to red
                cinder::gl::drawSolidRect(curSquare);   //draw square
                
            }
            
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
       //max();
    }
    
    virtual float count(ci::Rectf curSquare)    //passes in one rectangle at a time
    {
        s=0;
      

        for(int o=x1; o<x2; o++){       //gets square boundaries
            for(int q=y1; q<y2;q++){
                
                s=s+frameDiff.at<u_int8_t>(q,o);    //adds up pixels
                int sum=s;
                  for(int i=0; i<allFeatures.size();i++){
                allFeatures.push_back(sum);
                      std::cout<<allFeatures[i]<<std::endl;
                  }
            }
        }
            
       // }
 
        return s;
    }
    
    float getDivisorOfSum()
    {
        float setColor=s/1000;  //divides pixels  for color
        cinder::gl::color(setColor*N*N*255,0,0,.5); //sets the color
        return 1;   //faux return. not used
    }
    
    virtual float tally(){
        float tally=0;
//        for(int o=x1; o<x2; o++){
//        for(int q=y1; q<y2;q++){
//            tally=tally+s; //add up all the pixels in each square to get the total number of pixels
//          }}
//        for(int i=0; i<allFeatures.size(); i++){
//        tally=tally+allFeatures[i].totalFeatures(s);
//               }
      //  std::cout<<tally<<std::endl;
          return tally;
    }
    
    virtual float max(){
        float maxm=0;
        std::cout<<"size"<<allFeatures.size()<<std::endl;
         for(int i=0; i<allFeatures.size(); i++)
         {
              //std::cout<<"ftrs"<<allFeatures[i]<<std::endl;
      maxm= *std::max_element(allFeatures.begin(),allFeatures.end());
           //  std::cout<<"max"<<maxm<<std::endl;
         }
        return 0;
       // return maxm;
         }
};






#endif /* Squares_hpp */

