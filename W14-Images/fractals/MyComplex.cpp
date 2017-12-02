/*    @file MyComplex.cpp   
      @author Paul Talaga
      @date April 5, 2017

			@description Implements a class for manipulating complex numbers.
*/

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include "MyComplex.h"

const double DELTA = 0.0001;


MyComplex::MyComplex(double real, double imaginary){
  this->real = real;
  this->imaginary = imaginary;
}
  
MyComplex MyComplex::operator+(const MyComplex &other) const{
  return MyComplex(real + other.real, imaginary + other.imaginary);
}

MyComplex MyComplex::operator-(const MyComplex &other) const{
  return MyComplex(real - other.real, imaginary - other.imaginary);
}
    
MyComplex MyComplex::operator*(const MyComplex &other) const{
  return MyComplex(real * other.real - imaginary * other.imaginary, 
    real * other.imaginary + other.real * imaginary);
} 
 
MyComplex MyComplex::operator/(const MyComplex &other) const{
  return MyComplex((real * other.real + imaginary * other.imaginary) /
                    (other.real * other.real + other.imaginary *other.imaginary), 
    (other.real * imaginary - real * other.imaginary) /
                    (other.real * other.real + other.imaginary * other.imaginary));
}

bool MyComplex::operator==(const MyComplex &other) const{
  return fabs(real - other.real) < DELTA && 
         fabs(imaginary - other.imaginary) < DELTA;
}
  
string MyComplex::getAsString() const{
  stringstream s;
  s << "(" << real << " + " << imaginary << "i)";
  return s.str();
}

double MyComplex::mag2() const{
  return real * real + imaginary * imaginary;
}

double MyComplex::dist2(const MyComplex &other) const{
  return (real - other.real) * (real - other.real) + 
     (imaginary - other.imaginary) * (imaginary - other.imaginary);
}
  
double MyComplex::getReal() const{
  return real;
}

double MyComplex::getImaginary() const{
  return imaginary;
}
  
void MyComplex::setReal(double real){
  this->real = real;  
}
void MyComplex::setImaginary(double imaginary){
  this->imaginary = imaginary;
}

